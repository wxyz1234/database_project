#ifndef DTYPEDATA
#define DTYPEDATA
#include "../DType/Dkey.h"
#include "../DType/TypeName.h"
#include "../DType/Date.h"
#include "../../filesystem/utils/pagedef.h"
#include <string.h>
using namespace std;

class DtypeData {
public:	
	virtual TypeName getType() = 0;
	virtual int getsize() = 0;
	virtual void* getData();
	virtual void setData(int* i);
	virtual void setData(short* i);
	virtual void setData(char* i);
	virtual void setData(double* i);
	virtual void setData(float* i);
	virtual void setData(DateType* i);
	virtual void setData(int* i, bool &Nullchange);
	virtual void setData(short* i, bool& Nullchange);
	virtual void setData(char* i, bool& Nullchange);
	virtual void setData(double* i, bool& Nullchange);
	virtual void setData(float* i, bool& Nullchange);
	virtual void setData(DateType* i, bool& Nullchange);
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
		len = ((len - 1) / 4 + 1) * 4;
		data = NULL;
	}
	void setData(char* i) {		
		if (i != NULL) {
			if (data == NULL)data = new char[len];
			memcpy(data, i, len);
		}
		else {
			if (data != NULL)delete data;
			data = i;
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
		k += len / 4;
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
		k += 2;
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
		if (data != NULL)memcpy(buf, &data, 4);
		k += 1;
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
			*data = *i;
		}
		else {
			if (data != NULL)delete data;
			data = i;
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
		return 3;
	}
	int writeDataBuf(BufType buf) {
		int k = 0;
		if (data != NULL)memcpy(buf, data, 12);//sizeof(Date)=12
		k += 3;
		return k;
	}		
	int readDataBuf(BufType buf) {
		int k = 0;
		setData((DateType*)buf);
		k += getsize();
		return k;
	}
};

//Numeric 数字总数最多27个
/*
class Numeric {
private:
	int SumDigit, PointDigit,;
	int digit[3];
};
class DtypeDataNumeric :public DtypeData {
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