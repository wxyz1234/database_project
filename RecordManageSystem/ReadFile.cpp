#include "RecordManager.h"
#include "utils/Myhash.h"
#include <stdio.h>
#include <map>
using namespace std;
DSchema *sh,*sh2;
DList *li,*li2;
PageLoc pl[100];
int R = 0;
map<int, PageLoc> RP;
RecordManager* rm = new RecordManager();
void makeDSchema(DSchema& sh) {
	//构造测试模式：ID int,Name char,Date date,Score double
	sh.setName("BigdataCeshi");
	sh.setnum(4);
	sh.typeName[0] = new char[20];
	sh.setTypeName(0, "ID");
	sh.a[0] = new DtypeSchemaNumeric();
	((DtypeSchemaNumeric*)sh.a[0])->setsumdotd(18,0);	
	sh.a[0]->setAllowNull(false);
	sh.a[0]->setHaveDefault(false);
	//sh.a[0]->getDef()->setData(new NumericType(0,213,0));
	sh.a[0]->setKey(KeyName::Primary);

	sh.typeName[1] = new char[20];
	sh.setTypeName(1, "Name");
	sh.a[1] = new DtypeSchemaChar();
	((DtypeSchemaChar*)sh.a[1])->setlen(30);
	sh.a[1]->setAllowNull(false);
	sh.a[1]->setHaveDefault(false);
	sh.a[1]->setKey(KeyName::Foreign);
	sh.a[1]->getKey()->setFile("ceshi2");
	sh.a[1]->getKey()->setName("Char");

	sh.typeName[2] = new char[20];
	sh.setTypeName(2, "Date");
	sh.a[2] = new DtypeSchemaDate();
	sh.a[2]->setAllowNull(true);
	sh.a[2]->setHaveDefault(true);
	sh.a[2]->getDef()->setData(new DateType(2000, 1, 1));
	sh.a[2]->setKey(KeyName::Null);

	sh.typeName[3] = new char[20];
	sh.setTypeName(3, "Score");
	sh.a[3] = new DtypeSchemaInt(10);
	sh.a[3]->setAllowNull(true);
	sh.a[3]->setHaveDefault(true);
	sh.a[3]->getDef()->setData(new int(87));
	sh.a[3]->setKey(KeyName::Null);

	printf("makeDSchema Finish!\n");
}
void makeDList(DList& li,int id,int y,int m,int d,double s) {
	//构造测试数据
	R++;
	li.setRID(R);
	li.setfa(sh);
	li.setNull(0);
	li.getPart(0)->setData(new NumericType(0,id,0));	
	char c[30];
	c[0] = 'A';
	c[1] = 'A';
	c[2] = 'A';
	c[3] = char('0' + (id / 10 % 10));
	c[4] = char('0' + (id % 10));
	c[5] = '\0';	
	li.getPart(1)->setData(c);
	li.getPart(2)->setData(new DateType(y, m, d));
	li.getPart(3)->setData(new int(s));		
	printf("makeDList Finish!\n");
}
int main() {
	rm = new RecordManager();
	sh = new DSchema();
	sh2 = new DSchema();
	int fileID;
	makeDSchema(*sh);
	rm->CreateFileF("../data/test", sh);
	rm->OpenFile("../data/test", fileID);
	printf("Create and Open File Finish!\n");

	li = new DList[100]();
	li2 = new DList[100]();
	for (int i = 1; i <= 80; i++) {
		makeDList(li[i], i, 2020, 11, i, double(i) * i * 0.5);
		pl[i] = rm->InsertRecord(fileID, &li[i]);
	}
	printf("InsertRecord Finish!\n");
	rm->GetSchema(fileID, *sh2);
	sh2->writeDSchema();
	printf("writeDSchema Finish!\n");
	for (int i = 1; i <= 80; i++) {
		li2[i].setfa(sh2);
		rm->FindRecord(fileID, pl[i], li2[i]);
		li2[i].writeDList();		
	}
	printf("FindRecord Finish!\n");
	for (int i = 1; i <= 80; i++) {
		makeDList(li[i], i, 2020, 12, i, double(i) * i * i * 2);
		rm->UpdateRecord(fileID, pl[i], &li[i]);
	}
	printf("UpdateRecord Finish!\n");
	for (int i = 1; i <= 80; i++) {
		li2[i].setfa(sh2);
		rm->FindRecord(fileID, pl[i], li2[i]);
		li2[i].writeDList();
	}
	printf("FindRecord Finish!\n");
	for (int i = 1; i <= 80; i++)
		if (i % 2 == 0) {
			rm->DeleteRecord(fileID, pl[i]);
		}
	printf("DeleteRecord Finish!\n");
	for (int i = 1; i <= 80; i++)
		if (i % 2 == 0) {
			makeDList(li[i], 100+i, 2021, 1, i, double(i) * i * i);
			pl[i] = rm->InsertRecord(fileID, &li[i]);
		}
	printf("InsertRecord again Finish!\n");
	for (int i = 1; i <= 80; i++) {
		li2[i].setfa(sh2);
		rm->FindRecord(fileID, pl[i], li2[i]);
		li2[i].writeDList();
	}
	printf("FindRecord Finish!\n");
	//hash检查		
	int pk = 3;
	TypeName tn;
	Myhash ha;	
	for (int i = 0; i < sh->getnum(); i++)
		if (sh->getPart(i)->getKey()->getKey() == KeyName::Primary) {
			pk = i;
			tn = sh->getPart(i)->getType();
			if (tn == TypeName::Char) {
				int l = ((DtypeSchemaChar*)sh->getPart(i))->getlen();
				ha.setlen(l);
			}
			ha.setType(tn);
			break;
		}
	int i, j, k, p;
	for (i = 1; i <= 80; i++) {
		RP[li2[i].getRID()] = pl[i];
		ha.Insert(li2[i].getPart(pk)->getData());
	}
	for (i = 1; i <= 80; i++) {
		printf("PageLoc of RID %d is (%d,%d)\n", li2[i].getRID(), RP[li2[i].getRID()].PageID, RP[li2[i].getRID()].LocID);
		if (ha.Find(new NumericType(0, i, 0)))
			printf("Find ID %d success!\n", i);
		if (ha.Find(new NumericType(0, i+100, 0)))
			printf("Find ID %d success!\n", i+100);
	}
	printf("Hash Check Finish!\n");	
	rm->CloseFile(fileID);
	rm->DeleteFile("data/input.txt");
	printf("Close and Delete File Finish!\n");
	delete[] li;
	delete[] li2;
	delete sh;
	delete sh2;
	return 0;
}