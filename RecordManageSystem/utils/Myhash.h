#ifndef MY_HASH
#define MY_HASH
#include <vector>
enum flag { null = 0, data, deleted };
class Myhash {
private:
	static const int mo = 19997;
	void* a[mo];
	flag b[mo];
	TypeName type;
	int len,sumd,dotd;
public:
	Myhash() {
		memset(b, 0, sizeof(b));
	}
	bool sameType(DtypeSchema* ds) {
		if (type != ds->getType())return false;
		if (ds->getType() == TypeName::Int) {
			if (len != ((DtypeSchemaInt*)ds)->getlen())
				return false;
		}
		if (ds->getType() == TypeName::Char) {
			if (len != ((DtypeSchemaChar*)ds)->getlen())
				return false;
		}
		if (ds->getType() == TypeName::Numeric) {
			if (sumd != ((DtypeSchemaNumeric*)ds)->getsumd())
				return false;
			if (dotd != ((DtypeSchemaNumeric*)ds)->getdotd())
				return false;
		}
		return true;
	}
	void setType(TypeName i) {
		type = i;
	}
	void setlen(int i) {
		len = i;		
	}
	void setsumdotd(int i,int j) {
		sumd = i;
		dotd = j;
	}
	void setsumd(int i) {
		sumd = i;
	}
	void setdotd(int i) {
		dotd = i;
	}
	int score(void* i) {
		int k=0;
		switch (type) {
		case(TypeName::Int):
			return (*((int*)i)) % mo;
			break;
		case(TypeName::SmallInt):
			return (*((short*)i)) % mo;
			break;
		case(TypeName::Char):			
			for (int j = 0; j < len; j++) {
				k = k * 128 + (int)(((char*)i)[j]);
				if (k > mo)k %= mo;
			}
			return k;
			break;
		case(TypeName::Double):
			return (*((long*)i)) % mo;
			break;
		case(TypeName::Float):
			return (*((int*)i)) % mo;			
			break;
		case(TypeName::Date):
			return (((DateType*)i)->getday() * 35 + ((DateType*)i)->getmonth() * 12 + ((DateType*)i)->getyear()) % mo;
			break;
		case (TypeName::Numeric):
			return (((NumericType*)i)->getd(0) % mo * (1000000000 % mo) % mo * ((NumericType*)i)->getd(1) % mo * (1000000000 % mo) % mo * ((NumericType*)i)->getd(2) % mo);
			break;
		default:
			printf("Hash Score Type ERROR!\n");
		}
		return 0;
	}
	bool equal(void* k, void* i) {
		switch (type) {
		case(TypeName::Int):
			return ((*(int*)k) == (*(int*)i));
			break;
		case(TypeName::SmallInt):
			return ((*(short*)k) == (*(short*)i));
			break;
		case(TypeName::Char):
			for (int j = 0; j < len; j++)
				if (((char*)k)[j] != ((char*)i)[j])return false;
			return true;
			break;
		case(TypeName::Double):
			return ((*(double*)k) == (*(double*)i));
			break;
		case(TypeName::Float):
			return ((*(float*)k) == (*(float*)i));
			break;
		case(TypeName::Date):
			return (((DateType*)k)->equal((DateType*)i));
			break;
		case (TypeName::Numeric):
			return (((NumericType*)k)->equal((NumericType*)i));
			break;
		default:
			printf("Hash Equal Type ERROR!\n");
		}
		return false;
	}
	void Insert(void* i) {	
		int k = score(i);
		while (b[k] == flag::data) {
			k++;
			if (k == mo)k = 0;
		}
		switch (type) {
		case (TypeName::Int):
			a[k] = new int((*(int*)i));
			break;
		case (TypeName::SmallInt):
			a[k] = new short((*(short*)i));
			break;
		case (TypeName::Char):
			a[k] = new char[len];
			for (int j = 0; j < len; j++)((char*)a[k])[j] = ((char*)i)[j];
			break;
		case (TypeName::Double):
			a[k] = new double((*(double*)i));
			break;
		case (TypeName::Float):
			a[k] = new float((*(float*)i));
			break;
		case (TypeName::Date):
			a[k] = new DateType((*(DateType*)i));
			break;
		case (TypeName::Numeric):
			a[k] = new NumericType((*(NumericType*)i));
			break;
		default:
			printf("Hash Insert Type ERROR!\n");
		}
		b[k] = flag::data;
	}
	bool Delete(void* i) {
		int k = score(i);
		while (b[k] != flag::null) {
			if ((b[k] == flag::data) && (equal(a[k], i))) {
				delete  a[k];
				b[k] = flag::deleted;
				return true;
			}
			k++;
			if (k == mo)k = 0;
		}
		return false;
	}
	bool Find(void* i) {
		int k = score(i);
		while (b[k] != flag::null) {
			if ((b[k]==flag::data)&&(equal(a[k], i))) {
				return true;
			}
			k++;
			if (k == mo)k = 0;
		}
		return false;
	}
	~Myhash() {
		int i;
		for (i=0;i<mo;i++)
			if (b[i]==flag::data)
				delete a[i];		
	}
};
class PrimaryData {
	friend class CreateTableTree;
	friend class DropTableTree;
	friend class valuelistsTree;
	friend class UseDatabaseTree;
	friend class RecordManager;
	friend class DeleteTree;
	friend class DropPrimaryTree;
	friend class AddAttributeTree;
protected:
	int num=0;
	std::vector<Myhash*>a;
	std::string filename[30];
	std::string attrname[30];
public:
	void clean() {
		for (int i = 0; i < num; i++)delete a[i];
		a.clear();
		num = 0;
	}
	void add(const char* fn, char* an, DtypeSchema* ty) {
		filename[num] = fn;
		attrname[num] = an;
		Myhash* b = new Myhash();
		b->setType(ty->getType());
		if (ty->getType() == TypeName::Int) {
			b->setlen(((DtypeSchemaInt*)ty)->getlen());
		}
		if (ty->getType() == TypeName::Char) {
			b->setlen(((DtypeSchemaChar*)ty)->getlen());
		}
		if (ty->getType() == TypeName::Numeric) {
			b->setsumd(((DtypeSchemaNumeric*)ty)->getsumd());
			b->setdotd(((DtypeSchemaNumeric*)ty)->getdotd());
		}
		a.push_back(b);
		num++;
	}
};
class ForeignData {
	friend class DropTableTree;	
	friend class DeleteTree;
	friend class UpdateTree;
	friend class DeleteTree;
	friend class DropPrimaryTree;
	friend class DropForeignTree;
	friend class AddAttributeTree;
protected:
	int num=0;
	std::string filename[30];
	std::string attrname[30];
	std::string reffilename[30];
	std::string refattrname[30];
public:
	void clean() {
		num = 0;
	}
	void add(const char* fn, char* an, DKey* a) {
		filename[num] = fn;
		attrname[num] = an;
		reffilename[num] = ((DForeign*)a)->getFile();
		refattrname[num] = ((DForeign*)a)->getName();
		num++;
	}
};

#endif