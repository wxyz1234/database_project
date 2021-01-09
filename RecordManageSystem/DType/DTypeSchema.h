#ifndef DTYPESCHEMA
#define DTYPESCHEMA
#include "../DType/TypeName.h"
#include "../DType/Date.h"
#include "../DType/DTypeData.h"
#include "../../filesystem/utils/pagedef.h"
#include <string.h>
using namespace std;

class DtypeSchema {
	friend class DSchema;
	friend class attributeTree;
	friend class attributelistTree;
	friend class AddAttributeTree;
	friend class AddPrimaryTree;
	friend class AddForeignTree;
protected:
	bool AllowNull,HaveDefault;
	//DKey* key;	
	bool isPrimary,isForeign;
	char* refFile;
	char* refName;
	DtypeData* def = NULL;
public:
	DtypeSchema() {
		isPrimary = false;
		isForeign = false;
	}
	virtual TypeName getType()=0;
	virtual int getsize()=0;	
	virtual int writeBuf(BufType buf) {
		return 0;
	}
	virtual int readBuf(BufType buf) { return 0; };
	virtual void setDefault(const char* v) = 0;
	void initfilename() {
		refFile = new char[20];
		refName = new char[20];
	}
	void clearfileattr() {
		if (isForeign) {
			delete refFile;
			delete refName;
		}
	}
	void setAllowNull(bool i) {
		AllowNull = i;		
	}
	bool getAllowNull() {
		return AllowNull;
	}
	void setHaveDefault(bool i) {
		HaveDefault = i;
	}
	bool getisPrimary() {
		return isPrimary;
	}
	bool getisForeign() {
		return isForeign;
	}
	void setisPrimary(bool i) {
		isPrimary = i;
	}
	void setisForeign(bool i) {
		isForeign = i;
	}
	void setFile(const char* buf) {
		memcpy(refFile, buf, 20);
	}
	void setName(const char* buf) {
		memcpy(refName, buf, 20);
	}
	char* getFile() {
		return refFile;
	}
	char* getName() {
		return refName;
	}
	bool getHaveDefault() {
		return HaveDefault;
	}
	DtypeData* getDef() {
		return def;
	}
	int writeTypeBuf(BufType buf) {
		int k = 0;
		buf[k] = int(getType());
		k += 1;	
		k += writeBuf(buf + k);

		buf[k] = int(isPrimary);
		k += 1;
		buf[k] = int(isForeign);
		k += 1;
		if (isForeign) {			
			memcpy(buf + k, refFile, 20);
			k += 5;			
			memcpy(buf + k, refName, 20);
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
		isPrimary = buf[k];
		k += 1;
		isForeign = buf[k];
		k += 1;
		if (isForeign) {
			refFile = new char[20];
			refName = new char[20];
			memcpy(refFile, buf+k, 20);			
			k += 5;
			memcpy(refName, buf+k, 20);			
			k += 5;
		}		
		AllowNull = (bool)buf[k];
		k += 1;
		HaveDefault = (bool)buf[k];
		k += 1;
		if (HaveDefault) k += def->readDataBuf(&buf[k]);
		return k;
	}
	virtual ~DtypeSchema() {
		if (isForeign) {
			delete refFile;
			delete refName;
		}
		if (def != NULL)delete def;
	}
};

class DtypeSchemaInt:public DtypeSchema {	
private:
	int len;
public:	
	DtypeSchemaInt() {
		def = new DtypeDataInt();
	}
	DtypeSchemaInt(int i) {		
		len = i;
		def = new DtypeDataInt();
	}
	int writeBuf(BufType buf) {
		buf[0] = len;
		return 1;
	}
	int readBuf(BufType buf) {
		len = buf[0];		
		return 1;
	}
	enum TypeName getType() {
		return TypeName::Int;
	}
	void setlen(int i) {
		len = i;
	}
	int getlen() {
		return len;
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
	int old_len,len;
public:	
	int writeBuf(BufType buf) {
		buf[0] = old_len;
		return 1;
	}
	int readBuf(BufType buf) {
		old_len = buf[0];
		len = (old_len / 4 + 1) * 4;
		def = new DtypeDataChar(len);
		return 1;
	}
	enum TypeName getType() {
		return TypeName::Char;
	}
	void setlen(int i) {
		old_len = i;
		len = (old_len / 4 + 1) * 4;
		if (def != NULL)delete def;
		def = new DtypeDataChar(len);
	}
	int getlen() {
		return len;
	}
	int getold_len() {
		return old_len;
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
private:
	int sumd, dotd;
public:	
	void setsumdotd(int i) {
		sumd = i / 100;
		dotd = i % 100;
		if (def != NULL)delete def;
		def = new DtypeDataNumeric(sumd * 100 + dotd);
	}
	void setsumdotd(int i,int j) {
		sumd = i;
		dotd = j;
		if (def != NULL)delete def;
		def = new DtypeDataNumeric(sumd,dotd);
	}
	int getsumdotd() {
		return sumd * 100 + dotd;
	}
	int getsumd() {
		return sumd;
	}
	int getdotd() {
		return dotd;
	}
	bool islegal() {
		if (sumd > 27)return false;
		if (dotd > sumd)return false;
		return true;
	}
	int writeBuf(BufType buf) {
		buf[0] = sumd * 100 + dotd;
		return 1;
	}
	int readBuf(BufType buf) {
		sumd = buf[0] / 100;
		dotd = buf[0] % 100;
		def = new DtypeDataNumeric(sumd,dotd);
		return 1;
	}
	TypeName getType() {
		return TypeName::Numeric;
	}
	int getsize() {
		return 3;
	}	
	void setDefault(const char* v) {
		NumericType i;
		i.setd(v,sumd,dotd);
		def->setData(&i);
	}	
};
#endif