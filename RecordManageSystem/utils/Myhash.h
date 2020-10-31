#ifndef MY_HASH
#define MY_HASH
enum flag { null = 0, data, deleted };
class Myhash {
private:
	static const int mo = 999997;
	void* a[mo];
	flag b[mo];
	TypeName type;
	int len;
public:
	Myhash() {
		memset(b, sizeof(b), 0);
	}
	void setType(TypeName i) {
		type = i;
	}
	void setlen(int i) {
		len = i;		
	}
	int score(void* i) {
		switch (type) {
		case(TypeName::Int):
			return (*((int*)i)) % mo;
			break;
		case(TypeName::SmallInt):
			return (*((short*)i)) % mo;
			break;
		case(TypeName::Char):
			int k = 0;
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
			return (((DateType*)k)->equal(*((DateType*)i)));
			break;
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
		//
	}
};
#endif