#ifndef DLIST
#define DLIST
#include "../DType/DtypeSchema.h"
#include "../DType/DSchema.h"
#include "../utils/Wei.h"
class DList {
	friend class valuelistsTree;
protected:
	DSchema* fa = NULL;
	int RID;
	int isNull;
	int num;
	bool Nullchange=true;
	DtypeData* a[20];
public:
	DList() {
		RID = 0;
		isNull = 0;
	}
	DList(DSchema* i) {
		RID = 0;
		isNull = 0;
		setfa(i);		
	}
	DSchema* getfa() {
		return fa;
	}	
	void setfa(DSchema* i) {
		fa = i;
		num = fa->getnum();
		for (int j = 0; j < num; j++)
			switch (fa->getPart(j)->getType()) {
			case TypeName::Int:
				a[j] = new DtypeDataInt();
				break;
			case TypeName::SmallInt:
				a[j] = new DtypeDataSmallInt();
				break;
			case TypeName::Char:
				a[j] = new DtypeDataChar(((DtypeSchemaChar*)fa->getPart(j))->getlen());
				break;
			case TypeName::Double:
				a[j] = new DtypeDataDouble();
				break;
			case TypeName::Float:
				a[j] = new DtypeDataFloat();
				break;
			case TypeName::Date:
				a[j] = new DtypeDataDate();
				break;
			case TypeName::Numeric:
				a[j] = new DtypeDataNumeric(((DtypeSchemaNumeric*)fa->getPart(j))->getsumdotd());
				break;
			default:
				printf("ERROR setfa type %d\n",j);
			}
	}
	void setRID(int i) {
		RID = i;
	}
	int getRID() {
		return RID;
	}
	DtypeData* getPart(int i) {
		return a[i];
	}	
	void makeNull() {
		isNull = 0;
		int i;
		for (i = 0; i < num; i++)
			if (a[i]->getData() == NULL)
				isNull |= Wei::wei[i];
	}
	int getNull() {
		if (Nullchange) {
			makeNull();
			Nullchange = false;			
		}
		return isNull;
	}
	void setNull(int i) {
		Nullchange = false;
		isNull = i;
	}
	void writeDataBuf(BufType& buf) {		
		int k = 0;
		buf[0] = RID;
		buf[1] = getNull();
		k += 2;
		int i;
		for (i = 0; i < num; i++) {
			k += a[i]->writeDataBuf(buf+k);
		}
	}
	void readDataBuf(BufType buf) {
		int k = 0;
		setRID(buf[0]);
		setNull(buf[1]);
		k += 2;
		int i;
		for (i = 0; i < num; i++) {
			k += a[i]->readDataBuf(buf+k);
		}
	}
	~DList() {				
		for (int j = 0; j < num; j++)
			delete a[j];		
	}
	void writeDList() {
		//输出记录结果
		//printf("DList in (%d,%d)'s father is %s\n", pl.PageID, pl.LocID, li.getfa()->getName());
		printf("DList 's RID is %d\n", RID);
		int nk = getNull();
		printf("DList 's isNull is %d\n", nk);
		int k = getfa()->getnum();
		int i;
		char* s[] = { "Int", "SmallInt", "Char", "Double", "Float", "Date", "Numeric" };
		TypeName tn;
		for (i = 0; i < k; i++) {
			tn = getfa()->getPart(i)->getType();
			//printf("DList in (%d,%d)'s part %d 's Type is %s\n", pl.PageID, pl.LocID, i, s[int(tn)]);
			//if (tn == TypeName::Char)printf("DList in (%d,%d)'s part %d 's Len is %d\n", pl.PageID, pl.LocID, i, ((DtypeSchemaChar*)li.getfa()->getPart(i))->getlen());				
			if ((nk & Wei::wei[i]) > 0)
				printf("DList 's part %d is NULL\n", i);
			else {
				printf("DList 's part %d is ", i);
				DateType* tmp;
				NumericType* tmp2;
				int sumd, dotd, len;
				switch (tn) {
				case TypeName::Int:
					len = ((DtypeSchemaInt*)fa->getPart(i))->getlen();
					sumd = *((int*)a[i]->getData());
					if (sumd < 0) {
						printf("-");
						sumd = -sumd;
					}
					for (int j = len - 1; j >= 0; j--)printf("%d", sumd / Wei::shiwei[j] % 10);
					printf("\n");
					break;
				case TypeName::SmallInt:
					printf("%d\n", *((short*)a[i]->getData()));
					break;
				case TypeName::Char:
					printf("%s\n", ((char*)a[i]->getData()));
					break;
				case TypeName::Double:
					printf("%f\n", *((double*)a[i]->getData()));
					break;
				case TypeName::Float:
					printf("%f\n", *((float*)a[i]->getData()));
					break;
				case TypeName::Date:
					tmp = ((DateType*)a[i]->getData());
					printf("Date:%d\\%d\\%d\n", tmp->getyear(), tmp->getmonth(), tmp->getday());
					break;
				case TypeName::Numeric:
					tmp2 = ((NumericType*)a[i]->getData());
					sumd = ((DtypeSchemaNumeric*)fa->getPart(i))->getsumd();
					dotd = ((DtypeSchemaNumeric*)fa->getPart(i))->getdotd();
					printf("Numeric:%s\n", tmp2->getd(sumd, dotd));
					break;
				default:
					printf("Type ERROR\n");
				}
			}
		}
		printf("DList END!\n");
	}
};
#endif