#ifndef DTYPESCHEMA
#define DTYPESCHEMA
#include "../DType/DKey.h"
#include "../DType/TypeName.h"
#include "../DType/Date.h"
#include "../DType/DTypeData.h"
#include "../../filesystem/utils/pagedef.h"
#include <string.h>
using namespace std;

class DtypeSchema {
	friend class DSchema;
	friend class attributeTree;
protected:
	bool AllowNull,HaveDefault;
	DKey* key;	
	DtypeData* def = NULL;
public:
	DtypeSchema() {
		key = new DKey();
	}
	virtual TypeName getType()=0;
	virtual int getsize()=0;	
	virtual int writeBuf(BufType buf) {
		return 0;
	}
	virtual int readBuf(BufType buf) { return 0; };
	virtual void setDefault(const char* v) = 0;
	void setAllowNull(bool i) {
		AllowNull = i;		
	}
	bool getAllowNull() {
		return AllowNull;
	}
	void setHaveDefault(bool i) {
		HaveDefault = i;
	}
	bool getHaveDefault() {
		return HaveDefault;
	}
	DtypeData* getDef() {
		return def;
	}
	void setKey(KeyName i) {
		if (key != NULL)delete key;
		if (i== KeyName::Null)key=new DKey();
		if (i == KeyName::Primary)key = new DPrimary();
		if (i == KeyName::Foreign)key = new DForeign();
	}
	DKey* getKey() {
		return key;
	}
	int writeTypeBuf(BufType buf) {
		int k = 0;
		buf[k] = int(getType());
		k += 1;	
		k += writeBuf(buf + k);

		buf[k] = int(key->getKey());
		k += 1;
		if (key->getKey() == KeyName::Foreign) {
			char* tmp = key->getFile();
			memcpy(buf + k, tmp, 20);
			k += 5;
			tmp = key->getName();
			memcpy(buf + k, tmp, 20);
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
			key->setFile((char*)(buf+k));
			k += 5;
			key->setName((char*)(buf+k));
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
	DtypeSchemaInt() {
		def = new DtypeDataInt();
	}
	int readBuf(BufType buf) {		
		return 0;
	}
	enum TypeName getType() {
		return TypeName::Int;
	}
	int getsize() {
		return 1;
	}	
	void setDefault(const char* v) {
		int i = atoi(v);
		def->setData(&i);
	}
};

class DtypeSchemaSmallInt :public DtypeSchema {
public:
	DtypeSchemaSmallInt() {
		def = new DtypeDataSmallInt();
	}
	int readBuf(BufType buf) {		
		return 0;
	}
	enum TypeName getType() {
		return TypeName::SmallInt;
	}
	int getsize() {
		return 1;
	}
	void setDefault(const char* v) {
		short i = atoi(v);
		def->setData(&i);
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
	void setlen(int i) {
		len = i;
		len = (len / 4 + 1) * 4;
		if (def != NULL)delete def;
		def = new DtypeDataChar(len);
	}
	int getlen() {
		return len;
	}
	int getsize() {
		return len/4;
	}
	void setDefault(const char* v) {
		def->setData(v);
	}
};

class DtypeSchemaDouble :public DtypeSchema {
public:
	DtypeSchemaDouble() {
		def = new DtypeDataDouble();
	}
	int readBuf(BufType buf) {			
		return 0;
	}		
	enum TypeName getType() {
		return TypeName::Double;
	}
	int getsize() {
		return 2;
	}
	void setDefault(const char* v) {
		double i= atof(v);
		def->setData(&i);
	}
};

class DtypeSchemaFloat :public DtypeSchema {
public:
	DtypeSchemaFloat() {
		def = new DtypeDataFloat();
	}
	int readBuf(BufType buf) {			
		return 0;
	}	
	enum TypeName getType() {
		return TypeName::Float;
	}
	int getsize() {
		return 1;
	}
	void setDefault(const char* v) {
		float i = atof(v);
		def->setData(&i);
	}
};

class DtypeSchemaDate :public DtypeSchema {
public:		
	DtypeSchemaDate() {
		def = new DtypeDataDate();
	}
	int readBuf(BufType buf) {		
		return 0;
	}	
	enum TypeName getType() {
		return TypeName::Date;
	}
	int getsize() {
		return 1;
	}
	void setDefault(const char* v) {
		DateType i = DateType(atoi(v));
		def->setData(&i);
	}
};

class DtypeSchemaNumeric :public DtypeSchema {
public:	
	DtypeSchemaNumeric() {
		def = new DtypeDataNumeric();
	}
	int readBuf(BufType buf) {
		return 0;
	}
	TypeName getType() {
		return TypeName::Numeric;
	}
	int getsize() {
		return 4;
	}	
	void setDefault(const char* v) {
		//NumericType i = DateType(atoi(v->data));
		//def->setData(&i);
	}	
};
#endif