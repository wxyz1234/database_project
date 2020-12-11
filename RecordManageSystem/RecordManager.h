#ifndef RECORD_MANAGER
#define RECORD_MANAGER
#include "../filesystem/utils/pagedef.h"
#include "../filesystem/filesystem.h"
#include "utils/PageLoc.h"
#include "utils/Wei.h"
#include "DType/DTypeSchema.h"
#include "DType/DSchema.h"
#include "DType/DList.h"
#include "DType/TypeName.h"
#include "utils/Myhash.h"
#include <iostream>
#include <stdio.h>
using namespace std;
const unsigned int maxunsignint = 4294967295;
int Wei::wei[32];
int Wei::shiwei[10];
extern PrimaryData pd;
class RecordManager {
public:
	BufFileManager* fm;
	RecordManager() {
		//�����ʼ��
		Wei::init();		
		fm = new BufFileManager();				
	}
	/*
	�ļ�������Ϣ��
		��һҳ��
			buf[0]��ҳ��(������0)
			buf[1]�ܼ�¼����
			buf[2+]��ǰ���¼��ʽ��
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
	bool CreateFileF(const char* name, DSchema* Schema) {
		//�����ļ�
		fm->createFile(name);
		//��ʼ����һҳ��¼�ļ������Ϣ
		int fileID;
		if (fm->openFile(name, fileID)) {
			BufType buf = new unsigned int[2048];			
			buf[0] = 0;
			buf[1] = 0;
			//DSchema��Ϣתbuf
			Schema->writeSchemaBuf(buf+2);
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
	PageLoc InsertRecord(int fileID, DList* data) {
		//data��Ϣд��buf
		BufType buf = new unsigned int[64];
		data->writeDataBuf(buf);
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
				memcpy(pagebuf + 2 + k * 64, buf, 256);
				pagebuf[0] += 1;
				fm->writePage(fileID, i, pagebuf, 0);
				//��һҳ����
				filebuf[1] += 1;
				fm->writePage(fileID, 0, filebuf, 0);
				delete[] filebuf, pagebuf, buf;
				return PageLoc(i, k);
			}
		}
		//��չ��ҳ
		filebuf[0] += 1;
		i = PageNum + 1;		
		if (fm->readPage(fileID, i, pagebuf, 0) == -1) {
			printf("ERROR\n");
			delete[] filebuf, pagebuf, buf;
			return PageLoc(-1, -1);
		}
		pagebuf[0] = 0;
		pagebuf[1] = Wei::wei[31] - 1;		
		//�ҵ���λ
		int k;
		unsigned int tmp;
		tmp = pagebuf[1];
		tmp = tmp & (-tmp);		
		pagebuf[1] -= tmp;
		k = Wei::BitConvInt(tmp);
		//��Ӧҳ�����
		memcpy(pagebuf + 2 + k * 64, buf, 256);
		pagebuf[0] += 1;
		fm->writePage(fileID, i, pagebuf, 0);
		//��һҳ����
		filebuf[1] += 1;		
		fm->writePage(fileID, 0, filebuf, 0);
		delete[] filebuf, pagebuf, buf;
		return PageLoc(i, k);
	}
	bool DeleteRecord(int fileID, PageLoc page) {
		//ɾ����¼	
		//��ҳ��
		BufType filebuf = new unsigned int[2048];			
		BufType pagebuf = new unsigned int[2048];
		if (fm->readPage(fileID, page.PageID, pagebuf, 0) == -1) {
			printf("ERROR\n");
			delete[] pagebuf;
			return false;
		}
		if (fm->readPage(fileID, 0, filebuf, 0) == -1) {
			printf("ERROR\n");
			delete[] filebuf, pagebuf;
			return false;
		}
		//����
		filebuf[1] -= 1;
		pagebuf[0] -= 1;
		pagebuf[1] |= Wei::wei[page.LocID];
		fm->writePage(fileID, 0, filebuf, 0);
		fm->writePage(fileID, page.PageID, pagebuf, 0);
		return true;
	}
	bool UpdateRecord(int fileID, PageLoc page, DList* data) {
		//���¼�¼
		//��Ϣתbuf
		BufType buf = new unsigned int[64];
		data->writeDataBuf(buf);
		//��ҳ��
		BufType pagebuf = new unsigned int[2048];
		if (fm->readPage(fileID, page.PageID, pagebuf, 0) == -1) {
			printf("ERROR\n");
			delete[] buf, pagebuf;
			return false;
		}
		//�жϼ�¼�Ƿ����
		if ((pagebuf[1] & Wei::wei[page.LocID]) > 0) {
			printf("ERROR\n");
			delete[] buf, pagebuf;
			return false;
		}
		//����
		memcpy(pagebuf + 2 + 64 * page.LocID, buf, 256);
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
		if ((pagebuf[1] & Wei::wei[page.LocID]) > 0) {
			printf("No Record ERROR\n");
			delete[] pagebuf;
			return false;
		}
		//buf��ϢתDList
		data.readDataBuf(pagebuf + 2 + 64 * page.LocID);
		data.makeNull();
		return true;
	}
	bool PDUpdate(int fileID,int pdnum,int panum,DSchema* sh) {
		//�����ļ����м�¼λ�õ��б�
		BufType pagebuf = new unsigned int[2048];
		if (fm->readPage(fileID, 0, pagebuf, 0) == -1) {
			printf("ERROR\n");			
			delete[] pagebuf;
			return false;
		}
		int pagenum = pagebuf[0];
		int i, j, k, l;
		DList* b=new DList(sh);				
		for (i = 1; i <= pagenum; i++) {			
			if (fm->readPage(fileID, i, pagebuf, 0) == -1) {
				printf("ERROR\n");
				delete b;
				delete[] pagebuf;
				return false;
			}
			k = Wei::wei[31]-1-pagebuf[1];
			while (k > 0) {
				j = k & (-k);
				k -= j;
				j = Wei::BitConvInt(j);											
				b->readDataBuf(pagebuf + 2 + 64 * j);						
				pd.a[pdnum]->Insert(b->getPart(panum)->getData());
			}			
		}		
		delete b;
		delete[] pagebuf;
		return true;
	}
	bool ShowTable(const char* name, bool rev) {
		//�����ǰ�ļ�ģʽ�����м�¼
		int fileID;
		OpenFile(name, fileID);
		//CheckPage(fileID, 1);
		DSchema* sh = new DSchema();
		GetSchema(fileID, *sh);
		sh->writeDSchema();
		DList* b = new DList(sh);
		BufType pagebuf = new unsigned int[2048];
		if (fm->readPage(fileID, 0, pagebuf, 0) == -1) {
			printf("ERROR\n");
			delete[] pagebuf;
			delete sh;
			delete b;
			CloseFile(fileID);
			return false;
		}
		int pagenum = pagebuf[0];
		int i, j, k, l;
		int ll[40];		
		if (rev) {
			for (i = pagenum; i >= 1; i--) {
				if (fm->readPage(fileID, i, pagebuf, 0) == -1) {
					printf("ERROR\n");
					delete sh;
					delete b;
					CloseFile(fileID);
					delete[] pagebuf;
					return false;
				}
				k = Wei::wei[31] - 1 - pagebuf[1];
				ll[0] = 0;
				while (k > 0) {
					j = k & (-k);
					k -= j;
					j = Wei::BitConvInt(j);					
					ll[0] += 1;
					ll[ll[0]] = j;
				}
				for (j = ll[0]; j >= 1; j--) {
					b->readDataBuf(pagebuf + 2 + 64 * ll[j]);
					b->writeDList();
				}
			}
		}
		else {
			for (i = 1; i <= pagenum; i++) {
				if (fm->readPage(fileID, i, pagebuf, 0) == -1) {
					printf("ERROR\n");
					delete sh;
					delete b;
					CloseFile(fileID);
					delete[] pagebuf;
					return false;
				}
				k = Wei::wei[31] - 1 - pagebuf[1];
				ll[0] = 0;
				while (k > 0) {
					j = k & (-k);
					k -= j;
					j = Wei::BitConvInt(j);					
					ll[0] += 1;
					ll[ll[0]] = j;					
				}
				for (j = 1; j <= ll[0]; j++) {
					b->readDataBuf(pagebuf + 2 + 64 * ll[j]);
					b->writeDList();
				}				
			}
		}
		delete[] pagebuf;
		delete sh;
		delete b;
		CloseFile(fileID);
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