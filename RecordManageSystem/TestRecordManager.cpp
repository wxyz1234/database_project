/*
#include "RecordManager.h"
#include "../RecordManageSystem/utils/Wei.h"
DSchema *sh,*sh2;
DList *li,*li2;
PageLoc pl;
int R = 0;
void makeDSchema(DSchema& sh) {	
	//构造测试模式：主键 外键 默认值 不为空 6种数据类型
	sh.setName("CeShiMoShiCeShiMoSh");
	sh.setnum(7);
	sh.typeName[0] = new char[20];
	sh.setTypeName(0, "Int");
	sh.a[0]=new DtypeSchemaInt();
	sh.a[0]->setAllowNull(true);
	sh.a[0]->setHaveDefault(true);
	sh.a[0]->getDef()->setData(new int(10));
	sh.a[0]->setKey(KeyName::Primary);
	
	sh.typeName[1] = new char[20];
	sh.setTypeName(1, "SmallInt");
	sh.a[1] = new DtypeSchemaSmallInt();
	sh.a[1]->setAllowNull(true);
	sh.a[1]->setHaveDefault(true);
	sh.a[1]->getDef()->setData(new short(255));
	sh.a[1]->setKey(KeyName::Null);

	sh.typeName[2] = new char[20];
	sh.setTypeName(2, "Char");
	sh.a[2] = new DtypeSchemaChar();
	((DtypeSchemaChar*)sh.a[2])->setlen(50);
	sh.a[2]->setAllowNull(true);
	sh.a[2]->setHaveDefault(true);
	char c[50] = "ceshiandcheck";	
	printf("makeDSchema Char* is %s\n",c);
	sh.a[2]->getDef()->setData(c);
	sh.a[2]->setKey(KeyName::Foreign);
	sh.a[2]->getKey()->setFile("ceshi2");
	sh.a[2]->getKey()->setName("Char");	

	sh.typeName[3] = new char[20];
	sh.setTypeName(3, "Double");
	sh.a[3] = new DtypeSchemaDouble();
	sh.a[3]->setAllowNull(true);
	sh.a[3]->setHaveDefault(true);
	sh.a[3]->getDef()->setData(new double(1.005));
	sh.a[3]->setKey(KeyName::Null);

	sh.typeName[4] = new char[20];
	sh.setTypeName(4, "Float");
	sh.a[4] = new DtypeSchemaFloat();
	sh.a[4]->setAllowNull(true);
	sh.a[4]->setHaveDefault(true);
	sh.a[4]->getDef()->setData(new float(2.1));
	sh.a[4]->setKey(KeyName::Null);

	sh.typeName[5] = new char[20];
	sh.setTypeName(5, "Date");
	sh.a[5] = new DtypeSchemaDate();
	sh.a[5]->setAllowNull(true);
	sh.a[5]->setHaveDefault(true);
	sh.a[5]->getDef()->setData(new DateType(2020,11,3));
	sh.a[5]->setKey(KeyName::Null);
	printf("makeDSchema Finish!\n");

	sh.typeName[6] = new char[20];
	sh.setTypeName(6, "Numeric");
	sh.a[6] = new DtypeSchemaNumeric();
	sh.a[6]->setAllowNull(false);
	sh.a[6]->setHaveDefault(true);
	sh.a[6]->getDef()->setData(new NumericType(10,2,405,0,0));
	sh.a[6]->setKey(KeyName::Null);
	printf("makeDSchema Finish!\n");
}
void writeDSchema(DSchema& sh) {
	//输出模式结果
	printf("DSchema Name is %s\n", sh.getName());
	int k = sh.getnum();
	printf("DSchema Num is %d\n", k);
	char *s[]= { "Int", "SmallInt", "Char", "Double", "Float", "Date", "Numeric" };
	char* s2[] = { "Primary", "Foreign", "Null" };
	bool hd;
	TypeName tn;
	int i;
	for (i = 0; i < k; i++) {
		printf("DSchema Part %d 's Name is %s\n", i, sh.getTypeName(i));
		tn = sh.getPart(i)->getType();
		printf("DSchema Part %d 's Type is %s\n", i, s[int(tn)]);
		if (tn == TypeName::Char) {
			printf("DSchema Part %d 's Len is %d\n", i, ((DtypeSchemaChar*)sh.getPart(i))->getlen());
		}		
		printf("DSchema Part %d 's Key is %s\n", i, s2[int(sh.getPart(i)->getKey()->getKey())]);
		if (sh.getPart(i)->getKey()->getKey() == KeyName::Foreign) {
			printf("DSchema Part %d 's Key 's Filename is %s\n", i, ((DForeign*)sh.getPart(i)->getKey())->getFile());
			printf("DSchema Part %d 's Key 's Dataname is %s\n", i, ((DForeign*)sh.getPart(i)->getKey())->getName());
		}		
		printf("DSchema Part %d 's AllowNull is %d\n", i, sh.getPart(i)->getAllowNull());
		hd = sh.getPart(i)->getHaveDefault();
		printf("DSchema Part %d 's HaveDef is %d\n", i, hd);		
		if (hd) {
			printf("DSchema Part %d 's DefData is ", i);
			DateType* tmp; 
			NumericType* tmp2;
			switch (tn) {
			case TypeName::Int:
				printf("%d\n", *((int*)sh.getPart(i)->getDef()->getData()));
				break;
			case TypeName::SmallInt:
				printf("%d\n", *((short*)sh.getPart(i)->getDef()->getData()));
				break;
			case TypeName::Char:
				printf("%s\n", ((char*)sh.getPart(i)->getDef()->getData()));
				break;
			case TypeName::Double:
				printf("%f\n", *((double*)sh.getPart(i)->getDef()->getData()));
				break;
			case TypeName::Float:
				printf("%f\n", *((float*)sh.getPart(i)->getDef()->getData()));
				break;
			case TypeName::Date:
				tmp = ((DateType*)sh.getPart(i)->getDef()->getData());
				printf("Date:%d\\%d\\%d\n", tmp->getyear(), tmp->getmonth(), tmp->getday());
				break;
			case TypeName::Numeric:
				tmp2 = ((NumericType*)sh.getPart(i)->getDef()->getData());
				printf("Numeric:%s\n", tmp2->getd());
				break;
			default:
				printf("Type ERROR\n");
			}			
		}		
	}
	printf("DSchema %s END!\n", sh.getName());
}
void makeDList(DList& li) {
	//构造测试数据
	R++;
	li.setRID(R);
	li.setfa(sh);	
	li.setNull(0);
	li.getPart(0)->setData(new int(1));
	li.getPart(1)->setData(new short(2));
	char c[50] = "3";	
	printf("makeDList char* is %s\n",c);
	li.getPart(2)->setData(c);
	li.getPart(3)->setData(new double(4.0));
	li.getPart(4)->setData(new float(5.0));
	li.getPart(5)->setData(new DateType(2020,11,6));
	li.getPart(6)->setData(new NumericType(10,2,1005,0,0));
	printf("makeDList Finish!\n");
}
void writeDList(PageLoc pl,DList& li) {
	//输出记录结果
	printf("DList in (%d,%d)'s father is %s\n",pl.PageID,pl.LocID,li.getfa()->getName());
	printf("DList in (%d,%d)'s RID is %d\n", pl.PageID, pl.LocID, li.getRID());
	int nk = li.getNull();
	printf("DList in (%d,%d)'s isNull is %d\n", pl.PageID, pl.LocID, nk);
	int k = li.getfa()->getnum();
	int i;
	char* s[] = { "Int", "SmallInt", "Char", "Double", "Float", "Date", "Numeric" };
	TypeName tn;
	for (i = 0; i < k; i++) {
		tn = li.getfa()->getPart(i)->getType();
		printf("DList in (%d,%d)'s part %d 's Type is %s\n", pl.PageID, pl.LocID, i, s[int(tn)]);
		if (tn == TypeName::Char) {
			printf("DList in (%d,%d)'s part %d 's Len is %d\n", pl.PageID, pl.LocID, i, ((DtypeSchemaChar*)li.getfa()->getPart(i))->getlen());
		}

		if ((nk & Wei::wei[i]) > 0)		
			printf("DList in (%d,%d)'s part %d is NULL\n", pl.PageID, pl.LocID, i);
		else {
			printf("DList in (%d,%d))'s part %d is ", pl.PageID, pl.LocID, i);
			DateType* tmp;
			NumericType* tmp2;
			switch (tn) {
			case TypeName::Int:
				printf("%d\n", *((int*)li.getPart(i)->getData()));
				break;
			case TypeName::SmallInt:
				printf("%d\n", *((short*)li.getPart(i)->getData()));
				break;
			case TypeName::Char:
				printf("%s\n", ((char*)li.getPart(i)->getData()));
				break;
			case TypeName::Double:
				printf("%f\n", *((double*)li.getPart(i)->getData()));
				break;
			case TypeName::Float:
				printf("%f\n", *((float*)li.getPart(i)->getData()));
				break;
			case TypeName::Date:
				tmp = ((DateType*)li.getPart(i)->getData());
				printf("Date:%d\\%d\\%d\n", tmp->getyear(), tmp->getmonth(), tmp->getday());
				break;
			case TypeName::Numeric:
				tmp2 = ((NumericType*)li.getPart(i)->getData());
				printf("Numeric:%s\n", tmp2->getd());
				break;
			default:
				printf("Type ERROR\n");
			}
		}			
	}
	printf("DList in (%d,%d) END!\n", pl.PageID,pl.LocID);
}
int main() {	
	//构造测试模式
	sh = new DSchema();
	sh2 = new DSchema();
	makeDSchema(*sh);
	//构造测试记录
	li = new DList();
	li2 = new DList();
	makeDList(*li);		
	RecordManager rm;	
	int fileID;
	//创造文件/写模式
	rm.CreateFile("data/input.txt",sh);	
	rm.OpenFile("data/input.txt",fileID);
	printf("Create and Open File Finish!\n");
	//写记录
	pl=rm.InsertRecord(fileID,li);
	printf("InsertRecord Finish!\n");				
	//读取模式检查
	rm.GetSchema(fileID,*sh2);
	writeDSchema(*sh2);	
	printf("writeDSchema Finish!\n");
	//读取记录检查		
	li2->setfa(sh2);	
	rm.FindRecord(fileID,pl,*li2);
	printf("FindRecord Finish!\n");
	writeDList(pl,*li2);			
	//删除文件
	rm.CloseFile(fileID);
	rm.DeleteFile("data/input.txt");		
	printf("Close and Delete File Finish!\n");
	return 0;
}
*/