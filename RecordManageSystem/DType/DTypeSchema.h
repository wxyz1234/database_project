#ifndef DTYPESCHEMA
#define DTYPESCHEMA
#include "../DType/Dkey.h"
#include "../DType/TypeName.h"
#include "../DType/Date.h"
#include "../DType/DTypeData.h"
#include "../../filesystem/utils/pagedef.h"
#include <string.h>
using namespace std;

class DtypeSchema {
public:
	bool AllowNull,HaveDefault;
	DKey* key;	
	DtypeSchema() {
		key = new DKey();
	}
	DtypeData* def;
	virtual TypeName getType()=0;
	virtual int getsize()=0;	
	virtual int writeBuf(BufType buf) {
		return 0;
	}
	virtual int readBuf(BufType buf);
	int writeTypeBuf(BufType buf) {
		int k = 0;
		buf[k] = int(getType());
		k += 1;	
		k += writeBuf(buf);

		buf[k] = int(key->getKey());
		k += 1;
		if (key->getKey() == KeyName::Foreign) {
			char* tmp = key->getFile();
			memcpy(buf, tmp, 20);
			k += 5;
			tmp = key->getName();
			memcpy(buf, tmp, 20);
			k += 5;
		}
		buf[k] = AllowNull;
		k += 1;
		buf[k] = HaveDefault;
		k += 1;
		if (HaveDefault) k += def->writeDataBuf(&buf[k]);
		return k;
	}
	int readTypebuf(BufType buf) {
		int k = 0;
		switch ((KeyName)buf[k]) {
		case KeyName::Primary:
			key = new DPrimary();
			k += 1;
			break;
		case KeyName::Foreign:
			key = new DForeign();
			k += 1;
			key->setFile((char*)buf[k]);
			k += 5;
			key->setName((char*)buf[k]);
			k += 5;
			break;
		case KeyName::Null:
			key = new DKey();
			k += 1;
			break;
		};		
		AllowNull = (bool)buf[k];
		k += 1;
		HaveDefault = (bool)buf[k];
		k += 1;
		if (HaveDefault) k += def->readDataBuf(&buf[k]);
		return k;
	}
	virtual ~DtypeSchema() {
		delete key;
		if (def != NULL)delete def;
	}
};

class DtypeSchemaInt:public DtypeSchema {	
public:	
	int readBuf(BufType buf) {
		def = new DtypeDataInt();	
		return 0;
	}
	enum TypeName getType() {
		return TypeName::Int;
	}
	int getsize() {
		return 1;
	}	
};

class DtypeSchemaSmallInt :public DtypeSchema {
public:
	int readBuf(BufType buf) {
		def = new DtypeDataSmallInt();
		return 0;
	}
	enum TypeName getType() {
		return TypeName::SmallInt;
	}
	int getsize() {
		return 1;
	}
};

class DtypeSchemaChar :public DtypeSchema {
private:
	int len;
public:	
	int writeBuf(BufType buf) {
		buf[0] = len;
		return 1;
	}
	int readBuf(BufType buf) {
		len = buf[0];
		def = new DtypeDataChar(len);
		return 1;
	}
	enum TypeName getType() {
		return TypeName::Char;
	}
	int getsize() {
		return len/4;
	}
	int getlen() {
		return len;
	}
};

class DtypeSchemaDouble :public DtypeSchema {
public:
	int readBuf(BufType buf) {
		def = new DtypeDataDouble();			
		return 0;
	}		
	enum TypeName getType() {
		return TypeName::Double;
	}
	int getsize() {
		return 2;
	}
};

class DtypeSchemaFloat :public DtypeSchema {
public:
	int readBuf(BufType buf) {
		def = new DtypeDataFloat();		
		return 0;
	}	
	enum TypeName getType() {
		return TypeName::Float;
	}
	int getsize() {
		return 1;
	}
};

class DtypeSchemaDate :public DtypeSchema {
public:		
	int readBuf(BufType buf) {
		def = new DtypeDataDate();	
		return 0;
	}	
	enum TypeName getType() {
		return TypeName::Date;
	}
	int getsize() {
		return 3;
	}
};

//Numeric 数字总数最多27个
/*
class Numeric {
private:
	int SumDigit, PointDigit,;
	int digit[3];
};
class DtypeSchemaNumeric :public DtypeSchema {
public:
	//
	TypeName getType() {
		return 'Numeric';
	}
	int getsize() {
		return 5;
	}
	bool islegal() {
		if (SumDigit > 27)return false;
		if (PointDigit >= SumDigit)return false;
	}	
};
*/
#endif