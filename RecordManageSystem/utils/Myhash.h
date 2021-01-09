#ifndef MY_HASH
#define MY_HASH
#include <vector>
enum flag { null = 0, data, deleted };
class Myhash {
private:
	static const int mo = 199997;
	int unnum;
	void* a[mo][3];
	flag b[mo];
	TypeName type[3];
	int len[3],sumd[3],dotd[3];
public:
	Myhash() {
		memset(b, 0, sizeof(b));
	}
	bool sameType(DtypeSchema* ds,int k) {
		if (type[k] != ds->getType())return false;
		if (ds->getType() == TypeName::Int) {
			if (len[k] != ((DtypeSchemaInt*)ds)->getlen())
				return false;
		}
		if (ds->getType() == TypeName::Char) {
			if (len[k] != ((DtypeSchemaChar*)ds)->getlen())
				return false;
		}
		if (ds->getType() == TypeName::Numeric) {
			if (sumd[k] != ((DtypeSchemaNumeric*)ds)->getsumd())
				return false;
			if (dotd[k] != ((DtypeSchemaNumeric*)ds)->getdotd())
				return false;
		}
		return true;
	}
	void setunnum(int i) {
		unnum = i;		
	}
	void setType(TypeName i, int k) {
		type[k] = i;
	}
	void setlen(int i,int k) {
		len[k] = i;		
	}
	void setsumdotd(int i,int j,int k) {
		sumd[k] = i;
		dotd[k] = j;
	}
	void setsumd(int i,int k) {
		sumd[k] = i;
	}
	void setdotd(int i,int k) {
		dotd[k] = i;
	}
	int score(void* i, int num) {
		int k=0;			
		void* i2;
		switch (type[num]) {
		case(TypeName::Int):
			i2 = (((DtypeDataInt*)i)->getData());
			return (*((int*)i2)) % mo;
			break;
		case(TypeName::SmallInt):
			i2 = (((DtypeDataSmallInt*)i)->getData());
			return (*((short*)i2)) % mo;
			break;
		case(TypeName::Char):
			i2 = (((DtypeDataChar*)i)->getData());
			for (int j = 0; j < len[num]; j++) {
				k = k * 128 + (int)(((char*)i2)[j]);
				if (k > mo)k %= mo;
			}
			return k;
			break;
		case(TypeName::Double):
			i2 = (((DtypeDataDouble*)i)->getData());
			return (*((long*)i2)) % mo;
			break;
		case(TypeName::Float):
			i2 = (((DtypeDataFloat*)i)->getData());
			return (*((int*)i2)) % mo;
			break;
		case(TypeName::Date):
			i2 = (((DtypeDataDate*)i)->getData());
			return (((DateType*)i2)->getday() * 35 + ((DateType*)i2)->getmonth() * 12 + ((DateType*)i2)->getyear()) % mo;
			break;
		case (TypeName::Numeric):
			i2 = (((DtypeDataNumeric*)i)->getData());
			return (((NumericType*)i2)->getd(0) % mo * (1000000000 % mo) % mo * ((NumericType*)i2)->getd(1) % mo * (1000000000 % mo) % mo * ((NumericType*)i2)->getd(2) % mo);
			break;
		default:
			printf("Hash Score Type ERROR!\n");
		}			
		return 0;
	}
	bool equal(void* k, void* i,int num) {
		void* i2;
		switch (type[num]) {
		case(TypeName::Int):
			i2 = (((DtypeDataInt*)i)->getData());
			return ((*(int*)k) == (*(int*)i2));
			break;
		case(TypeName::SmallInt):
			i2 = (((DtypeDataSmallInt*)i)->getData());
			return ((*(short*)k) == (*(short*)i2));
			break;
		case(TypeName::Char):
			i2 = (((DtypeDataChar*)i)->getData());
			for (int j = 0; j < len[num]; j++)
				if (((char*)k)[j] != ((char*)i2)[j])return false;
			return true;
			break;
		case(TypeName::Double):
			i2 = (((DtypeDataDouble*)i)->getData());
			return ((*(double*)k) == (*(double*)i));
			break;
		case(TypeName::Float):
			i2 = (((DtypeDataFloat*)i)->getData());
			return ((*(float*)k) == (*(float*)i));
			break;
		case(TypeName::Date):
			i2 = (((DtypeDataDate*)i)->getData());
			return (((DateType*)k)->equal((DateType*)i));
			break;
		case (TypeName::Numeric):
			i2 = (((DtypeDataNumeric*)i)->getData());
			return (((NumericType*)k)->equal((NumericType*)i));
			break;
		default:
			printf("Hash Equal Type ERROR!\n");
		}
		return false;
	}
	bool equalall(int num,void* i0, void* i1 = NULL, void* i2 = NULL) {
		if (!equal(a[num][0], i0, 0)) return false;
		if (unnum>1)
			if (!equal(a[num][1], i1, 1))return false;
		if (unnum > 2)
			if (!equal(a[num][2], i2, 2))return false;
		return true;
	}
	void Insert(void* i0, void* i1 = NULL, void* i2 = NULL) {				
		int k = 0;
		k = score(i0, 0);
		if (unnum > 1)
			k = (k * 197 + score(i1, 1)) % mo;
		if (unnum > 2)
			k = (k * 197 + score(i2, 2)) % mo;
		while (b[k] == flag::data) {
			k++;
			if (k == mo)k = 0;
		}		
		void* tmpi;
		switch (type[0]) {
		case (TypeName::Int):
			tmpi = (((DtypeDataInt*)i0)->getData());
			a[k][0] = new int((*(int*)tmpi));
			break;
		case (TypeName::SmallInt):
			tmpi = (((DtypeDataSmallInt*)i0)->getData());
			a[k][0] = new short((*(short*)tmpi));
			break;
		case (TypeName::Char):
			tmpi = (((DtypeDataChar*)i0)->getData());
			a[k][0] = new char[len[0]];
			for (int j = 0; j < len[0]; j++)((char*)a[k])[j] = ((char*)tmpi)[j];
			break;
		case (TypeName::Double):
			tmpi = (((DtypeDataDouble*)i0)->getData());
			a[k][0] = new double((*(double*)tmpi));
			break;
		case (TypeName::Float):
			tmpi = (((DtypeDataFloat*)i0)->getData());
			a[k][0] = new float((*(float*)tmpi));
			break;
		case (TypeName::Date):
			tmpi = (((DtypeDataDate*)i0)->getData());
			a[k][0] = new DateType((*(DateType*)tmpi));
			break;
		case (TypeName::Numeric):
			tmpi = (((DtypeDataNumeric*)i0)->getData());
			a[k][0] = new NumericType((*(NumericType*)tmpi));
			break;
		default:
			printf("Hash Insert Type ERROR!\n");
		}
		if (unnum>1)
			switch (type[1]) {
			case (TypeName::Int):
				tmpi = (((DtypeDataInt*)i1)->getData());
				a[k][1] = new int((*(int*)tmpi));
				break;
			case (TypeName::SmallInt):
				tmpi = (((DtypeDataSmallInt*)i1)->getData());
				a[k][1] = new short((*(short*)tmpi));
				break;
			case (TypeName::Char):
				tmpi = (((DtypeDataChar*)i1)->getData());
				a[k][1] = new char[len[0]];
				for (int j = 0; j < len[0]; j++)((char*)a[k])[j] = ((char*)tmpi)[j];
				break;
			case (TypeName::Double):
				tmpi = (((DtypeDataDouble*)i1)->getData());
				a[k][1] = new double((*(double*)tmpi));
				break;
			case (TypeName::Float):
				tmpi = (((DtypeDataFloat*)i1)->getData());
				a[k][1] = new float((*(float*)tmpi));
				break;
			case (TypeName::Date):
				tmpi = (((DtypeDataDate*)i1)->getData());
				a[k][1] = new DateType((*(DateType*)tmpi));
				break;
			case (TypeName::Numeric):
				tmpi = (((DtypeDataNumeric*)i1)->getData());
				a[k][1] = new NumericType((*(NumericType*)tmpi));
				break;
			default:
				printf("Hash Insert Type ERROR!\n");
			}
		if (unnum>2)
			switch (type[2]) {
			case (TypeName::Int):
				tmpi = (((DtypeDataInt*)i2)->getData());
				a[k][2] = new int((*(int*)tmpi));
				break;
			case (TypeName::SmallInt):
				tmpi = (((DtypeDataSmallInt*)i2)->getData());
				a[k][2] = new short((*(short*)tmpi));
				break;
			case (TypeName::Char):
				tmpi = (((DtypeDataChar*)i2)->getData());
				a[k][2] = new char[len[0]];
				for (int j = 0; j < len[0]; j++)((char*)a[k])[j] = ((char*)tmpi)[j];
				break;
			case (TypeName::Double):
				tmpi = (((DtypeDataDouble*)i2)->getData());
				a[k][2] = new double((*(double*)tmpi));
				break;
			case (TypeName::Float):
				tmpi = (((DtypeDataFloat*)i2)->getData());
				a[k][2] = new float((*(float*)tmpi));
				break;
			case (TypeName::Date):
				tmpi = (((DtypeDataDate*)i2)->getData());
				a[k][2] = new DateType((*(DateType*)tmpi));
				break;
			case (TypeName::Numeric):
				tmpi = (((DtypeDataNumeric*)i2)->getData());
				a[k][2] = new NumericType((*(NumericType*)tmpi));
				break;
			default:
				printf("Hash Insert Type ERROR!\n");
			}
		b[k] = flag::data;
	}
	bool Delete(void* i0, void* i1 = NULL, void* i2 = NULL) {
		int k = 0;
		k = score(i0, 0);
		if (unnum > 1)
			k = (k * 197 + score(i1, 1)) % mo;
		if (unnum > 2)
			k = (k * 197 + score(i2, 2)) % mo;
		while (b[k] != flag::null) {
			if ((b[k] == flag::data) && (equalall(k,i0,i1,i2))) {
				for (int i=0;i<unnum;i++)
					delete a[k][i];
				b[k] = flag::deleted;
				return true;
			}
			k++;
			if (k == mo)k = 0;
		}
		return false;
	}
	bool Find(int num,void* i0, void* i1 = NULL, void* i2 = NULL) {
		int k = 0;
		k = score(i0, 0);
		if (unnum > 1)
			k = (k * 197 + score(i1, 1)) % mo;
		if (unnum > 2)
			k = (k * 197 + score(i2, 2)) % mo;
		while (b[k] != flag::null) {
			if ((b[k]==flag::data)&&(equalall(k, i0,i1,i2))) {
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
			if (b[i] == flag::data) {
				delete a[i][0];
				if (unnum > 1)
					delete a[i][1];
				if (unnum > 2)
					delete a[i][2];
			}
				
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
	friend class AddPrimaryTree;
	friend class AddForeignTree;
protected:
	int num=0;
	std::vector<Myhash*>a;
	int unnum[30];
	std::string filename[30];
	std::string attrname[30][3];
	std::string pdname[30];
public:
	void clean() {
		for (int i = 0; i < num; i++)delete a[i];
		a.clear();
		num = 0;
	}
	void add(const char* fn, int k) {
		filename[num] = fn;
		unnum[num] = k;		
		num++;
	}
	void add(char* an, DtypeSchema* ty, int k) {
		attrname[num][k] = an;
		Myhash* b = new Myhash();
		b->setType(ty->getType(),k);
		if (ty->getType() == TypeName::Int) {
			b->setlen(((DtypeSchemaInt*)ty)->getlen(),k);
		}
		if (ty->getType() == TypeName::Char) {
			b->setlen(((DtypeSchemaChar*)ty)->getlen(),k);
		}
		if (ty->getType() == TypeName::Numeric) {
			b->setsumd(((DtypeSchemaNumeric*)ty)->getsumd(),k);
			b->setdotd(((DtypeSchemaNumeric*)ty)->getdotd(),k);
		}
		a.push_back(b);
	}
};
class ForeignData {
	friend class DropTableTree;	
	friend class DeleteTree;
	friend class UpdateTree;
	friend class DeleteTree;
	friend class valuelistsTree;
	friend class DropPrimaryTree;
	friend class DropForeignTree;
	friend class AddAttributeTree;
	friend class AddForeignTree;		
protected:
	int num=0;
	std::string filename[30];
	std::string fdname[30];
	int unnum[30];
	std::string attrname[30][3];
	std::string reffilename[30];
	std::string refattrname[30][3];	
public:
	void clean() {
		num = 0;
	}
	void add(const char* fn, char* fname, int k) {
		filename[num] = fn;	
		unnum[num] = k;
		reffilename[num] = fname;
		num++;
	}
	void add(char* an, char* nname,int k) {
		attrname[num][k] = an;	
		refattrname[num][k] = nname;
	}
};

#endif