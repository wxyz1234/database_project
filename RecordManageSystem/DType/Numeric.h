#ifndef NUMERICCLASS
#define NUMERICCLASS
#include <string.h>
#include "../utils/Wei.h"
class NumericType {
private:		
	int d[3];
	char* c= NULL;
	void makechar(int sumd, int dotd) {
		int k, help,o;
		help = sumd - dotd;
		o = 0;
		for (k = 0; k < help; k++) {
			c[k] = '0' + d[o / 9] / Wei::shiwei[8 - o % 9] % 10;
			o++;
		}
		c[help] = '.';
		for (k = help; k < sumd; k++) {
			c[k + 1] = '0' + d[o / 9] / Wei::shiwei[8 - o % 9] % 10;
			o++;
		}				
		c[sumd + 1] = '\0';
	}
	void makeint(int sumd, int dotd) {
		d[0] = 0;
		d[1] = 0;
		d[2] = 0;
		int k, help;
		help = sumd - dotd;
		for (k = 0; k < help; k++)
			d[k / 9] += Wei::shiwei[8 - k % 9] * (c[k] - '0');
		for (k = help; k < sumd; k++) 
			d[k / 9] += Wei::shiwei[8 - k % 9] * (c[k+1] - '0');	
	}
public:
	NumericType() {		
		d[0] = 0;
		d[1] = 0;
		d[2] = 0;		
		c = new char[30];
	}	
	NumericType(int y1, int y2, int y3) {		
		d[0] = y1;
		d[1] = y2;
		d[2] = y3;
		c = new char[30];
	}
	NumericType(NumericType* i) {		
		d[0] = i->getd(0);
		d[1] = i->getd(1);
		d[2] = i->getd(2);
		c = new char[30];
	}
	void setd(int i, int j, int k) {
		d[0] = i;
		d[1] = j;
		d[2] = k;		
	}
	int getd(int i) {
		return d[i];
	}
	void setd(const char* c2,int sumd,int dotd) {
		int i,j;
		int k, help;
		help = sumd - dotd;
		for (k = 0; k < help; k++)c[k] = '0';
		c[help] = '.';
		for (k = 1; k <= dotd; k++)c[help + k] = '0';

		for (i = 0; i <= sumd; i++)
			if (c2[i] == '.')break;
		for (k = 0; k < i; k++)c[help + k - i] = c2[k];
		for (k = 1; k <= dotd; k++) {
			if (c2[i + k] == '\0')break;
			c[help + k] = c2[i + k];
		}
		makeint(sumd,dotd);
	}
	char* getd(int sumd, int dotd) {
		makechar(sumd, dotd);
		return c;
	}
	
	bool equal(NumericType* i) {
		return ((d[0] == i->getd(0)) && (d[1] == i->getd(1)) && (d[2] == i->getd(2)));
	}
	~NumericType() {
		if (c!=NULL)
			delete c;
	}
};
#endif