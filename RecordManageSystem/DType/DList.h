#ifndef DLIST
#define DLIST
#include "../DType/DtypeSchema.h"
#include "../DType/DSchema.h"
#include "../Wei.h"
class DList {
private:
	DSchema* fa;
	int RID;
	int isNull;
	bool Nullchange=true;
	DtypeData* a[20];	
public:
	DList(DSchema* i) {
		fa = i;
		RID = 0;
		isNull = 0;
		for (int j = 0; j < fa->getnum(); j++)
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
			}			
	}
	DSchema* getfa() {
		return fa;
	}
	void setRID(int i) {
		RID = i;
	}
	int getRID() {
		return RID;
	}
	void makeNull() {
		isNull = 0;
		int i;
		for (i = 0; i < fa->getnum(); i++)
			if (a[i]->getData() == NULL)
				isNull |= Wei::getWei(i);
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
	bool &getNullchange() {
		return Nullchange;
	}
	DtypeData* getPart(int i) {
		return a[i];
	}	
	void writeDataBuf(BufType& buf) {		
		int k = 0;
		buf[0] = getRID();
		buf[1] = getNull();
		k += 2;
		int i;
		for (i = 0; i < getfa()->getnum(); i++) {
			k += getPart(i)->writeDataBuf(&buf[k]);
		}
	}
	void readDataBuf(BufType buf) {
		int k = 0;
		setRID(buf[0]);
		setNull(buf[1]);
		k += 2;
		int i;
		for (i = 0; i < getfa()->getnum(); i++) {
			k += getPart(i)->readDataBuf(&buf[k]);
		}
	}
	~DList() {
		for (int j = 0; j < fa->getnum(); j++)
			delete a[j];
	}
};
#endif