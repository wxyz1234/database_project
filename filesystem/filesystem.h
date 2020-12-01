#ifndef BUF_FILE_MANAGER
#define BUF_FILE_MANAGER
/*
目标：构建一个class直接用FileManager的接口封装BufPageManager的功能
 */
#include "bufmanager/BufPageManager.h"
#include "fileio/FileManager.h"
#include "utils/pagedef.h"
#include <iostream>
#include <cstring>

using namespace std;
class BufFileManager {
private:
	FileManager* fm;
	BufPageManager* bpm;
public:
	/*
	 * FilManager构造函数
	 */
	BufFileManager() {
		MyBitMap::initConst();   //新加的初始化
		fm = new FileManager();
		bpm = new BufPageManager(fm);
	}
	/*
	 * @函数名writePage
	 * @参数fileID:文件id，用于区别已经打开的文件
	 * @参数pageID:文件的页号
	 * @参数buf:存储信息的缓存(4字节无符号整数数组)
	 * @参数off:偏移量
	 * 功能:将buf+off开始的2048个四字节整数(8kb信息)写入fileID和pageID指定的文件页中
	 * 返回:成功操作返回0
	 */
	int writePage(int fileID, int pageID, BufType buf, int off) {		
		int index;
		BufType b = bpm->getPage(fileID, pageID, index);
		memcpy(b, buf + off, 8192);
		bpm->markDirty(index); //标记脏页		
		return 0;
	}
	/*
	 * @函数名readPage
	 * @参数fileID:文件id，用于区别已经打开的文件
	 * @参数pageID:文件页号
	 * @参数buf:存储信息的缓存(4字节无符号整数数组)
	 * @参数off:偏移量
	 * 功能:将fileID和pageID指定的文件页中2048个四字节整数(8kb)读入到buf+off开始的内存中
	 * 返回:成功操作返回0
	 */
	int readPage(int fileID, int pageID, BufType buf, int off) {
		int index;
		BufType b = bpm->getPage(fileID, pageID, index);
		memcpy(buf + off, b , 8192);
		bpm->access(index);
		return 0;
	}
	/*
	 * @函数名closeFile
	 * @参数fileID:用于区别已经打开的文件
	 * 功能:关闭文件
	 * 返回:操作成功，返回0
	 */
	int closeFile(int fileID) {
		//fileID不能为0，不然会出错（空白区fileID都是0）
		int fileid, pageid;
		for (int i = 0; i < CAP; ++i) {
			bpm->getKey(i, fileid, pageid);
			if (fileid==fileID)
				bpm->writeBack(i);
		}
		fm->closeFile(fileID);
		return 0;
	}
	/*
	 * @函数名createFile
	 * @参数name:文件名
	 * 功能:新建name指定的文件名
	 * 返回:操作成功，返回true
	 */
	bool createFile(const char* name) {
		return fm->createFile(name);		
	}
	/*
	 * @函数名openFile
	 * @参数name:文件名
	 * @参数fileID:函数返回时，如果成功打开文件，那么为该文件分配一个id，记录在fileID中
	 * 功能:打开文件
	 * 返回:如果成功打开，在fileID中存储为该文件分配的id，返回true，否则返回false
	 */
	bool openFile(const char* name, int& fileID) {
		return fm->openFile(name, fileID);
	}

	~BufFileManager() {		
		bpm->close();
		delete bpm;
		delete fm;
	}
};
#endif