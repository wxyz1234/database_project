#ifndef DLIST
#define DLIST
#include "../DType/DtypeSchema.h"
#include "../DType/DSchema.h"
#include "../utils/Wei.h"
class DList {
private:
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
				a[j] = new DtypeDataNumeric();
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
};
#endif