#ifndef DTYPEDATA
#define DTYPEDATA
#include "../DType/DKey.h"
#include "../DType/TypeName.h"
#include "../DType/Date.h"
#include "../DType/Numeric.h"
#include "../../filesystem/utils/pagedef.h"
#include <string.h>
using namespace std;

class DtypeData {
public:	
	virtual TypeName getType() = 0;
	virtual int getsize() = 0;
	virtual void* getData() { return NULL; };
	virtual void setData(int* i) {};
	virtual void setData(short* i) {};
	virtual void setData(const char* i) {};
	virtual void setData(double* i) {};
	virtual void setData(float* i) {};
	virtual void setData(DateType* i) {};
	virtual void setData(NumericType* i) {};
	virtual void setData(int* i, bool& Nullchange) {};
	virtual void setData(short* i, bool& Nullchange) {};
	virtual void setData(char* i, bool& Nullchange) {};
	virtual void setData(double* i, bool& Nullchange) {};
	virtual void setData(float* i, bool& Nullchange) {};
	virtual void setData(DateType* i, bool& Nullchange) {};
	virtual int writeDataBuf(BufType buf) = 0;
	virtual int readDataBuf(BufType buf) = 0;
};

class DtypeDataInt :public DtypeData {
private:
	int* data = NULL;
public:
	void setData(int* i) {		
		if (i != NULL) {
			if (data == NULL)data = new int;
			*data = *i;
		}
		else {
			if (data != NULL)delete data;
			data = i;
		}
	}
	void setData(int* i, bool& Nullchange) {
		if ((i == NULL && data != NULL) || (i != NULL && data == NULL))Nullchange = true;
		setData(i);
	}
	void* getData() {		
		return data;
	}		
	TypeName getType() {
		return TypeName::Int;
	}
	int getsize() {
		return 1;
	}
	int writeDataBuf(BufType buf) {
		int k = 0;
		if (data!=NULL)memcpy(buf, data, 4);
		k += 1;
		return k;
	}		
	int readDataBuf(BufType buf) {
		int k = 0;
		setData((int*)buf);
		k += getsize();
		return k;
	}
};

class DtypeDataSmallInt :public DtypeData {
private:
	short* data = NULL;
public:
	void setData(short* i) {		
		if (i != NULL) {
			if (data == NULL)data = new short;
			*data = *i;
		}
		else {
			if (data != NULL)delete data;
			data = i;
		}
	}
	void setData(short* i, bool& Nullchange) {
		if ((i == NULL && data != NULL) || (i != NULL && data == NULL))Nullchange = true;
		setData(i);
	}
	void* getData() {
		return data;
	}	
	TypeName getType() {
		return TypeName::SmallInt;
	}
	int getsize() {
		return 1;
	}
	int writeDataBuf(BufType buf) {
		int k = 0;
		if (data != NULL)memcpy(buf, data, 2);
		k += 1;
		return k;
	}
	int readDataBuf(BufType buf) {
		int k = 0;
		setData((short*)buf);
		k += getsize();
		return k;
	}
};

class DtypeDataChar :public DtypeData {
private:
	int len;
	char* data = NULL;
public:
	DtypeDataChar(int i) {
		len = i;		
		data = NULL;
	}
	void setData(const char* i) {		
		if (i != NULL) {
			if (data == NULL)data = new char[len];
			memcpy(data, i, len);
		}
		else {
			if (data != NULL)delete data;
			data = (char*)i;
		}
	}
	void setData(char* i, bool& Nullchange) {
		if ((i == NULL && data != NULL) || (i != NULL && data == NULL))Nullchange = true;
		setData(i);
	}
	void* getData() {
		return data;
	}
	int get_len() {
		return len;
	}
	TypeName getType() {
		return TypeName::Char;
	}
	int getsize() {
		return len / 4;
	}
	~DtypeDataChar() {
		delete data;
	}
	int writeDataBuf(BufType buf) {
		int k = 0;
		if (data != NULL)memcpy(buf, data, len);
		k += getsize();
		return k;
	}
	int readDataBuf(BufType buf) {
		int k = 0;
		setData((char*)buf);		
		k += getsize();
		return k;
	}
};

class DtypeDataDouble :public DtypeData {
private:
	double* data = NULL;
public:
	void setData(double* i) {		
		if (i != NULL) {
			if (data == NULL)data = new double;
			*data = *i;
		}
		else {
			if (data != NULL)delete data;
			data = i;
		}
	}
	void setData(double* i, bool& Nullchange) {
		if ((i == NULL && data != NULL) || (i != NULL && data == NULL))Nullchange = true;
		setData(i);
	}
	void* getData() {
		return data;
	}	
	TypeName getType() {
		return TypeName::Double;
	}
	int getsize() {
		return 2;
	}
	int writeDataBuf(BufType buf) {
		int k = 0;
		if (data != NULL)memcpy(buf, data, 8);
		k += getsize();
		return k;
	}		
	int readDataBuf(BufType buf) {
		int k = 0;
		setData((double*)buf);
		k += getsize();
		return k;
	}
};

class DtypeDataFloat :public DtypeData {
private:
	float* data = NULL;
public:
	void setData(float* i) {
		if (i != NULL) {
			if (data == NULL)data = new float;
			*data = *i;
		}
		else {
			if (data != NULL)delete data;
			data = i;
		}
	}
	void setData(float* i, bool& Nullchange) {
		if ((i == NULL && data != NULL) || (i != NULL && data == NULL))Nullchange = true;
		setData(i);
	}
	void* getData() {
		return data;
	}	
	TypeName getType() {
		return TypeName::Float;
	}
	int getsize() {
		return 1;
	}
	int writeDataBuf(BufType buf) {
		int k = 0;
		if (data != NULL)memcpy(buf, data, 4);
		k += getsize();
		return k;
	}		
	int readDataBuf(BufType buf) {
		int k = 0;
		setData((float*)buf);
		k += getsize();
		return k;
	}
};

class DtypeDataDate :public DtypeData {
private:
	DateType* data = NULL;
public:
	void setData(DateType* i) {
		if (i != NULL) {
			if (data == NULL)data = new DateType;
			data->setyear(i->getyear());
			data->setmonth(i->getmonth());
			data->setday(i->getday());
		}
		else {
			if (data != NULL)delete data;
			data = NULL;
		}
	}
	void setData(DateType* i, bool& Nullchange) {
		if ((i == NULL && data != NULL) || (i != NULL && data == NULL))Nullchange = true;
		setData(i);
	}
	void* getData() {
		return data;
	}	
	TypeName getType() {
		return TypeName::Date;
	}
	int getsize() {
		return 1;
	}
	int writeDataBuf(BufType buf) {
		int k = 0;
		if (data != NULL) {
			buf[k] = data->getdata();			
		}
		k += getsize();
		return k;
	}		
	int readDataBuf(BufType buf) {
		int k = 0;
		setData(new DateType(buf[0]));
		k += getsize();
		return k;
	}
};

class DtypeDataNumeric :public DtypeData {
private:
	int sumd, dotd;
	NumericType* data = NULL;
public:
	DtypeDataNumeric(int i) {
		sumd = i / 100;
		dotd = i % 100;
		data = NULL;
	}
	DtypeDataNumeric(int i,int j) {
		sumd = i;
		dotd = j;
		data = NULL;
	}
	TypeName getType() {
		return TypeName::Numeric;
	}
	int getsize() {
		return 3;
	}
	void* getData() {
		return data;
	}
	void setData(NumericType* i) {
		if (i != NULL) {
			if (data == NULL)data = new NumericType;					
			data->setd(i->getd(0), i->getd(1), i->getd(2));
		}
		else {
			if (data != NULL)delete data;
			data = NULL;
		}
	}
	void setData(NumericType* i, bool& Nullchange) {
		if ((i == NULL && data != NULL) || (i != NULL && data == NULL))Nullchange = true;
		setData(i);
	}
	int writeDataBuf(BufType buf) {
		int k = 0;
		if (data != NULL) {			
			buf[k] = data->getd(0);
			buf[k + 1] = data->getd(1);
			buf[k + 2] = data->getd(2);			
		}
		k += getsize();
		return k;
	}
	int readDataBuf(BufType buf) {		
		int k = 0;
		NumericType* data2 = new NumericType();		
		data2->setd(buf[0], buf[1], buf[2]);
		setData(data2);
		k += getsize();
		return k;
	}	
};
#endif