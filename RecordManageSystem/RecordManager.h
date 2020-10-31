#ifndef RECORD_MANAGER
#define RECORD_MANAGER
#include "../filesystem/bufmanager/BufPageManager.h"
#include "../filesystem/fileio/FileManager.h"
#include "../filesystem/utils/pagedef.h"
#include "../filesystem/filesystem.h"
#include "utils/PageLoc.h"
#include "utils/Wei.h"
#include "DType/DTypeSchema.h"
#include "DType/DSchema.h"
#include "DType/DList.h"
#include "DType/TypeName.h"
#include <iostream>
#include <stdio.h>
using namespace std;
const unsigned int maxunsignint = 4294967295;
class RecordManager {
public:
	BufFileManager* fm;
	RecordManager() {
		//�����ʼ��
		MyBitMap::initConst();   //�¼ӵĳ�ʼ��
		fm = new BufFileManager();
		Wei::init();
	}
	/*
	�ļ�������Ϣ��
		��һҳ��
			buf[0]��ҳ��(������0)
			buf[1]�ܼ�¼����
			buf[2+]��ǰ����¼��ʽ��
				1��char[20]����
				2��һ��int��Ӧ��������
				3��ÿ�����ԣ�һ��char[20]���ֿ�ͷ��Ȼ��1��int��ʾ���ͣ�Ȼ����������
				4��֮��һ��int��ʾ������������������һ��int��ʾAllowNull��һ��int��ʾHaveDefault�����������
				5�����������䴦����֮���ģ��ʵ��
		ÿһҳ��
			������¼����64*4�ֽ�
			ÿһҳ����31��32-1������¼
			buf[0]��ǰҳ���˼�����¼
			buf[1]��¼�ռ�ռ�õ�λ���飬1�пռ䣬0û�ռ�
			buf[2+]���������¼��ÿ����¼����RID+null��¼+���յ�һҳ��¼˳�򱣴������
	��¼������Ϣ��
		��ʼ1��int��ʾRID��֮���չ̶�˳�򴢴����ԣ���λ4�ֽڡ�
	*/
	bool CreatFile(const char* name, DSchema Schema) {
		//�����ļ�
		fm->createFile(name);
		//��ʼ����һҳ��¼�ļ������Ϣ
		int fileID;
		if (fm->openFile(name, fileID)) {
			BufType buf = new unsigned int[2048];			
			buf[0] = 0;
			buf[1] = 0;
			//DSchema��Ϣתbuf
			Schema.writeSchemaBuf(buf);
			if (fm->writePage(fileID, 0, buf, 0) == -1) {
				printf("ERROR");
				return false;
			}
			delete[] buf;
		}
		else {
			this->DeleteFile(name);
			return false;
		}
		CloseFile(fileID);
		return true;
	}
	int DeleteFile(const char* name) {
		//ɾ���ļ�	
		return remove(name);
	}
	bool OpenFile(const char* name, int& fileID) {
		//���ļ�
		return fm->openFile(name, fileID);
	}
	int CloseFile(int fileID) {
		//�ر��ļ�
		return fm->closeFile(fileID);
	}
	PageLoc InsertRecord(int fileID, DList data) {
		//data��Ϣд��buf
		BufType buf = new unsigned int[64];
		data.writeDataBuf(buf);
		//�����¼
		BufType filebuf = new unsigned int[2048];
		BufType pagebuf = new unsigned int[2048];
		if (fm->readPage(fileID, 0, filebuf, 0) == -1) {
			printf("ERROR\n");
			delete[] filebuf, pagebuf, buf;
			return PageLoc(-1, -1);
		}
		int PageNum = filebuf[0];
		int i;
		for (i = 1; i <= PageNum; i++) {
			//ÿһҳ���
			if (fm->readPage(fileID, i, pagebuf, 0) == -1) {
				printf("ERROR\n");
				delete[] filebuf, pagebuf, buf;
				return PageLoc(-1, -1);
			}
			//���뱾ҳ
			if (pagebuf[0] < 31) {
				//�ҵ���λ
				int k;
				unsigned int tmp;
				tmp = pagebuf[1];
				pagebuf[1] = pagebuf[1] & (pagebuf[1] - 1);
				tmp -= pagebuf[1];
				k = Wei::BitConvInt(tmp);
				//��Ӧҳ�����
				memcpy(pagebuf + 2 + k * 64, buf, 64);
				pagebuf[0] += 1;
				fm->writePage(fileID, i, pagebuf, 0);
				//��һҳ����
				filebuf[0] += 1;
				fm->writePage(fileID, 0, filebuf, 0);
				delete[] filebuf, pagebuf, buf;
				return PageLoc(i, k);
			}
		}
		//��չ��ҳ
		filebuf[0] += 1;
		i = PageNum + 1;
		if (fm->readPage(fileID, 1 + i, pagebuf, 0) == -1) {
			printf("ERROR\n");
			delete[] filebuf, pagebuf, buf;
			return PageLoc(-1, -1);
		}
		pagebuf[0] = 0;
		pagebuf[1] = Wei::getWei(31) - 1;
		//�ҵ���λ
		int k;
		unsigned int tmp;
		tmp = pagebuf[1];
		pagebuf[1] = pagebuf[1] & (-pagebuf[1]);
		tmp -= pagebuf[1];
		k = Wei::BitConvInt(tmp);
		//��Ӧҳ�����
		memcpy(pagebuf + 2 + k * 64, buf, 64);
		pagebuf[0] += 1;
		fm->writePage(fileID, 1 + i, pagebuf, 0);
		//��һҳ����
		filebuf[0] += 1;
		fm->writePage(fileID, 0, filebuf, 0);
		delete[] filebuf, pagebuf, buf;
		return PageLoc(i, k);
	}
	bool DeleteRecord(int fileID, PageLoc page) {
		//ɾ����¼	
		//��ҳ��
		BufType pagebuf = new unsigned int[2048];
		if (fm->readPage(fileID, page.PageID, pagebuf, 0) == -1) {
			printf("ERROR\n");
			delete[] pagebuf;
			return false;
		}
		//����
		pagebuf[0] -= 1;
		pagebuf[1] |= Wei::getWei(page.LocID);
		fm->writePage(fileID, page.PageID, pagebuf, 0);
		return true;
	}
	bool UpdataRecord(int fileID, PageLoc page, DList data) {
		//���¼�¼
		//��Ϣתbuf
		BufType buf = new unsigned int[64];
		data.writeDataBuf(buf);
		//��ҳ��
		BufType pagebuf = new unsigned int[2048];
		if (fm->readPage(fileID, page.PageID, pagebuf, 0) == -1) {
			printf("ERROR\n");
			delete[] buf, pagebuf;
			return false;
		}
		//�жϼ�¼�Ƿ����
		if ((pagebuf[1] & Wei::getWei(page.LocID)) > 0) {
			printf("ERROR\n");
			delete[] buf, pagebuf;
			return false;
		}
		//����
		memcpy(pagebuf + 2 + 64 * page.LocID, buf, 64);
		fm->writePage(fileID, page.PageID, pagebuf, 0);
		return true;
	}
	bool FindRecord(int fileID, PageLoc page, DList& data) {
		//��ȡ��¼
		//��ҳ��
		BufType pagebuf = new unsigned int[2048];
		if (fm->readPage(fileID, page.PageID, pagebuf, 0) == -1) {
			printf("ERROR\n");
			delete[] pagebuf;
			return false;
		}
		//�жϼ�¼�Ƿ����
		if ((pagebuf[1] & Wei::getWei(page.LocID)) > 0) {
			printf("ERROR\n");
			delete[] pagebuf;
			return false;
		}
		//buf��ϢתDList
		data.readDataBuf(pagebuf + 2 + 64 * page.LocID);
		return true;
	}
	bool GetSchema(int fileID, DSchema& schema) {
		//��ȡģʽ
		BufType filebuf = new unsigned int[2048];		
		if (fm->readPage(fileID, 0, filebuf, 0) == -1) {
			printf("ERROR\n");
			delete[] filebuf;
			return false;
		}
		//buf��ϢתDSchema
		schema.readSchemaBuf(filebuf+2);
		return true;
	}
	~RecordManager() {
		//��������
		delete fm;
	}
};
#endif