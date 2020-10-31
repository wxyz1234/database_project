#ifndef DKEY
#define DKEY
#include <string.h>
using namespace std;
enum class KeyName { Primary, Foreign, Null };
class DKey {
public:
	virtual KeyName getKey() {
		return KeyName::Null;
	}
	virtual char* getFile();
	virtual char* getName();
	virtual void setFile(char* buf);
	virtual void setName(char* buf);
};

class DPrimary :public DKey {
public:
	KeyName getKey() {
		return KeyName::Primary;
	}
};

class DForeign :public DKey {
private:
	char* refFile;
	char* refName;
public:
	DForeign() {
		refFile = new char[20];
		refName = new char[20];
	}
	KeyName getKey() {
		return KeyName::Foreign;
	}
	void setFile(char* buf) {
		memcpy(refFile, buf, 20);
	}
	void setName(char* buf) {
		memcpy(refName, buf, 20);
	}
	char* getFile() {
		return refFile;
	}
	char* getName() {
		return refName;
	}
	~DForeign() {
		delete refFile;
		delete refName;
	}
};
#endif