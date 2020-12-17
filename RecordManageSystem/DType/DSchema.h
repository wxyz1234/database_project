#ifndef DSCHEMA
#define DSCHEMA
#include "../DType/DTypeSchema.h"
#include <string.h>
//#include "../../parser/tree.h"

using namespace std;
class DSchema {
	friend void makeDSchema(DSchema& sh);
	friend class attributeTree;
	friend class attributelistTree;	
	friend class AddAttributeTree;
protected:
	char* name;
	int num;
	DtypeSchema* a[20];
	char* typeName[20];
public:
	DSchema() {
		name = new char[20];
		num = 0;
	}
	void setName(const char* buf) {
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
	void DropAttr(int k) {
		int i;
		delete[] typeName[k];
		delete a[k];
		num--;
		for (i = k; i < num; i++) {
			a[i] = a[i + 1];
			typeName[i] = typeName[i + 1];
		}		
	}
	void addnum() {
		num++;
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
	void writeDSchema() {
		//输出模式结果
		printf("DSchema Name is %s\n", name);
		int k = num;
		printf("DSchema Num is %d\n", k);
		char* s[] = { "Int", "SmallInt", "Char", "Double", "Float", "Date", "Numeric" };
		char* s2[] = { "Primary", "Foreign", "Null" };
		bool hd;
		TypeName tn;
		int i,sumd,dotd;
		for (i = 0; i < k; i++) {
			printf("DSchema Part %d 's Name is %s\n", i, typeName[i]);
			tn = a[i]->getType();
			printf("DSchema Part %d 's Type is %s\n", i, s[int(tn)]);
			if (tn == TypeName::Int) {
				printf("DSchema Part %d 's Len is %d\n", i, ((DtypeSchemaInt*)a[i])->getlen());
			}
			if (tn == TypeName::Char) {
				printf("DSchema Part %d 's Len is %d\n", i, ((DtypeSchemaChar*)a[i])->getold_len());
			}
			if (tn == TypeName::Numeric) {
				sumd = ((DtypeSchemaNumeric*)a[i])->getsumd();
				dotd = ((DtypeSchemaNumeric*)a[i])->getdotd();
				printf("DSchema Part %d 's sumd is %d\n", i, sumd);
				printf("DSchema Part %d 's dotd is %d\n", i, dotd);
			}
			printf("DSchema Part %d 's Key is %s\n", i, s2[int(a[i]->getKey()->getKey())]);
			if (a[i]->getKey()->getKey() == KeyName::Foreign) {
				printf("DSchema Part %d 's Key 's Filename is %s\n", i, ((DForeign*)a[i]->getKey())->getFile());
				printf("DSchema Part %d 's Key 's Dataname is %s\n", i, ((DForeign*)a[i]->getKey())->getName());
			}
			printf("DSchema Part %d 's AllowNull is %d\n", i, a[i]->getAllowNull());
			hd = a[i]->getHaveDefault();
			printf("DSchema Part %d 's HaveDef is %d\n", i, hd);
			if (hd) {
				printf("DSchema Part %d 's DefData is ", i);
				DateType* tmp;
				NumericType* tmp2;
				switch (tn) {
				case TypeName::Int:
					printf("%d\n", *((int*)a[i]->getDef()->getData()));
					break;
				case TypeName::SmallInt:
					printf("%d\n", *((short*)a[i]->getDef()->getData()));
					break;
				case TypeName::Char:
					printf("%s\n", ((char*)a[i]->getDef()->getData()));
					break;
				case TypeName::Double:
					printf("%f\n", *((double*)a[i]->getDef()->getData()));
					break;
				case TypeName::Float:
					printf("%f\n", *((float*)a[i]->getDef()->getData()));
					break;
				case TypeName::Date:
					tmp = ((DateType*)a[i]->getDef()->getData());
					printf("Date:%d\\%d\\%d\n", tmp->getyear(), tmp->getmonth(), tmp->getday());
					break;
				case TypeName::Numeric:
					tmp2 = ((NumericType*)a[i]->getDef()->getData());					
					printf("Numeric:%s\n", tmp2->getd(sumd,dotd));
					break;
				default:
					printf("Type ERROR\n");
				}
			}
		}
		printf("DSchema %s END!\n", name);
	}
};
#endif