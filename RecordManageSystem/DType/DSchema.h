#ifndef DSCHEMA
#define DSCHEMA
#include "../DType/DtypeSchema.h"
#include <string.h>
using namespace std;
class DSchema {
	friend void makeDSchema(DSchema& sh);
private:
	char* name;
	int num;
	DtypeSchema* a[20];
	char* typeName[20];
public:
	DSchema() {
		name = new char[20];
	}
	void setName(char* buf) {
		memcpy(name, buf, 20);
	}
	char* getName() {
		return name;
	}
	void setTypeName(int i,char* buf) {
		memcpy(typeName[i], buf, 20);
	}
	char* getTypeName(int i) {
		return typeName[i];
	}
	void setPart(int i,DtypeSchema* tmp) {
		a[i] = tmp;
	}
	DtypeSchema* getPart(int i) {
		return a[i];
	}
	void setnum(int i) {
		num = i;
	}
	int getnum() {
		return num;
	}
	void readSchemaBuf(BufType buf) {
		int k = 0;
		memcpy(name, buf, 20);
		k += 5;
		setnum(buf[k]);
		k += 1;
		int i;
		for (i = 0; i < num; i++) {
			typeName[i] = new char[20];
			memcpy(typeName[i], buf + k, 20);
			k += 5;
			switch (TypeName(buf[k])) {
			case TypeName::Int:
				a[i] = new DtypeSchemaInt();				
				break;
			case TypeName::SmallInt:
				a[i] = new DtypeSchemaSmallInt();				
				break;
			case TypeName::Char:
				a[i] = new DtypeSchemaChar();				
				break;
			case TypeName::Double:
				a[i] = new DtypeSchemaDouble();				
				break;
			case TypeName::Float:
				a[i] = new DtypeSchemaFloat();
				break;
			case TypeName::Date:
				a[i] = new DtypeSchemaDate();
				break;
			case TypeName::Numeric:
				a[i] = new DtypeSchemaNumeric();
				break;
			default:
				printf("TypeName ERROR %d\n", buf[k]);
			}
			k += 1;
			k += a[i]->readBuf(buf + k);
			k += a[i]->readTypebuf(buf + k);
		}		
	}
	void writeSchemaBuf(BufType buf) {
		memcpy(buf, getName(), 20);
		buf[5] = getnum();
		int i, p;
		p = 6;
		for (i = 0; i < buf[5]; i++) {
			memcpy(buf + p, getTypeName(i), 20);
			p += 5;
			p += getPart(i)->writeTypeBuf(buf + p);
		}
	}
	int getsize() {
		int i,ans;
		ans = 2;
		for (i = 0; i < num; i++) {
			ans += a[i]->getsize();
		}
		return ans;
	}
	~DSchema() {
		delete name;
		int i;
		for (i = 0; i < num; i++)
			delete a[i],typeName[i];
	}
};
#endif