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
		//整体初始化
		Wei::init();		
		fm = new BufFileManager();				
	}
	/*
	文件保存信息：
		第一页：
			buf[0]总页数(不包括0)
			buf[1]总记录个数
			buf[2+]当前表记录格式：
				1、char[20]名字
				2、一个int对应属性数量
				3、每个属性，一个char[20]名字开头，然后1个int表示类型，然后具体参数。
				4、之后一个int表示主键外键，后跟参数。一个int表示AllowNull，一个int表示HaveDefault，后跟参数。
				5、主键外键语句处理在之后的模块实现
		每一页：
			单个记录长度64*4字节
			每一页最多存31（32-1）个记录
			buf[0]当前页存了几个记录
			buf[1]记录空间占用的位数组，1有空间，0没空间
			buf[2+]具体各个记录，每个记录都是RID+null记录+按照第一页记录顺序保存的数据
	记录保存信息：
		开始1个int表示RID，之后按照固定顺序储存属性，单位4字节。
	*/
	bool CreateFileF(const char* name, DSchema* Schema) {
		//创建文件
		fm->createFile(name);
		//初始化第一页记录文件相关信息
		int fileID;
		if (fm->openFile(name, fileID)) {
			BufType buf = new unsigned int[2048];			
			buf[0] = 0;
			buf[1] = 0;
			//DSchema信息转buf
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
		//删除文件	
		return remove(name);
	}
	bool OpenFile(const char* name, int& fileID) {
		//打开文件
		return fm->openFile(name, fileID);
	}
	int CloseFile(int fileID) {
		//关闭文件
		return fm->closeFile(fileID);
	}
	PageLoc InsertRecord(int fileID, DList* data) {
		//data信息写入buf
		BufType buf = new unsigned int[64];
		data->writeDataBuf(buf);
		//插入记录
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
			//每一页检查
			if (fm->readPage(fileID, i, pagebuf, 0) == -1) {
				printf("ERROR\n");
				delete[] filebuf, pagebuf, buf;
				return PageLoc(-1, -1);
			}
			//插入本页
			if (pagebuf[0] < 31) {
				//找到空位
				int k;
				unsigned int tmp;
				tmp = pagebuf[1];
				pagebuf[1] = pagebuf[1] & (pagebuf[1] - 1);
				tmp -= pagebuf[1];
				k = Wei::BitConvInt(tmp);
				//对应页面更新
				memcpy(pagebuf + 2 + k * 64, buf, 256);
				pagebuf[0] += 1;
				fm->writePage(fileID, i, pagebuf, 0);
				//第一页更新
				filebuf[1] += 1;
				fm->writePage(fileID, 0, filebuf, 0);
				delete[] filebuf, pagebuf, buf;
				return PageLoc(i, k);
			}
		}
		//扩展新页
		filebuf[0] += 1;
		i = PageNum + 1;		
		if (fm->readPage(fileID, i, pagebuf, 0) == -1) {
			printf("ERROR\n");
			delete[] filebuf, pagebuf, buf;
			return PageLoc(-1, -1);
		}
		pagebuf[0] = 0;
		pagebuf[1] = Wei::wei[31] - 1;		
		//找到空位
		int k;
		unsigned int tmp;
		tmp = pagebuf[1];
		tmp = tmp & (-tmp);		
		pagebuf[1] -= tmp;
		k = Wei::BitConvInt(tmp);
		//对应页面更新
		memcpy(pagebuf + 2 + k * 64, buf, 256);
		pagebuf[0] += 1;
		fm->writePage(fileID, i, pagebuf, 0);
		//第一页更新
		filebuf[1] += 1;		
		fm->writePage(fileID, 0, filebuf, 0);
		delete[] filebuf, pagebuf, buf;
		return PageLoc(i, k);
	}
	bool DeleteRecord(int fileID, PageLoc page) {
		//删除记录	
		//打开页面
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
		//更新
		filebuf[1] -= 1;
		pagebuf[0] -= 1;
		pagebuf[1] |= Wei::wei[page.LocID];
		fm->writePage(fileID, 0, filebuf, 0);
		fm->writePage(fileID, page.PageID, pagebuf, 0);
		return true;
	}
	bool UpdateRecord(int fileID, PageLoc page, DList* data) {
		//更新记录
		//信息转buf
		BufType buf = new unsigned int[64];
		data->writeDataBuf(buf);
		//打开页面
		BufType pagebuf = new unsigned int[2048];
		if (fm->readPage(fileID, page.PageID, pagebuf, 0) == -1) {
			printf("ERROR\n");
			delete[] buf, pagebuf;
			return false;
		}
		//判断记录是否存在
		if ((pagebuf[1] & Wei::wei[page.LocID]) > 0) {
			printf("ERROR\n");
			delete[] buf, pagebuf;
			return false;
		}
		//更新
		memcpy(pagebuf + 2 + 64 * page.LocID, buf, 256);
		fm->writePage(fileID, page.PageID, pagebuf, 0);
		return true;
	}
	bool FindRecord(int fileID, PageLoc page, DList& data) {
		//读取记录
		//打开页面
		BufType pagebuf = new unsigned int[2048];
		if (fm->readPage(fileID, page.PageID, pagebuf, 0) == -1) {
			printf("ERROR\n");
			delete[] pagebuf;
			return false;
		}
		//判断记录是否存在
		if ((pagebuf[1] & Wei::wei[page.LocID]) > 0) {
			printf("No Record ERROR\n");
			delete[] pagebuf;
			return false;
		}
		//buf信息转DList
		data.readDataBuf(pagebuf + 2 + 64 * page.LocID);
		data.makeNull();
		return true;
	}
	bool PDUpdate(int fileID,int pdnum,int panum,DSchema* sh) {
		//制作文件所有记录位置的列表
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
		//输出当前文件模式和所有记录
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
		//读取模式
		BufType filebuf = new unsigned int[2048];		
		if (fm->readPage(fileID, 0, filebuf, 0) == -1) {
			printf("ERROR\n");
			delete[] filebuf;
			return false;
		}
		//buf信息转DSchema		
		schema.readSchemaBuf(filebuf+2);
		return true;
	}
	~RecordManager() {
		//析构函数
		delete fm;
	}
};
#endif