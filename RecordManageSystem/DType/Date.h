#ifndef DATECLASS
#define DATECLASS
class DateType {
private:
	int year, month, day;
public:
	DateType() {
		year = 1970;
		month = 1;
		day = 1;
	}
	DateType(int i) {
		year = i/10000;
		month = i/100%100;
		day = i%100;
	}
	DateType(const char* i) {
		year = (i[0] - '0') * 1000 + (i[1] - '0') * 100 + (i[2] - '0') * 10 + (i[3] - '0');
		month = (i[5] - '0') * 10 + (i[6] - '0');
		day = (i[8] - '0') * 10 + (i[9] - '0');
	}
	DateType(int y, int m, int d)
	{
		year = y;
		month = m;
		day = d;
	}	
	bool equal(DateType* i) {
		return ((i->getyear() == year) && (i->getmonth() == month) && (i->getday() == day));
	}
	void setyear(int y) {
		year = y;
	}
	void setmonth(int m) {
		month = m;
	}
	void setday(int d) {
		day = d;
	}
	int getyear() {
		return year;
	}
	int getmonth() {
		return month;
	}
	int getday() {
		return day;
	}
	int getdata() {
		return year * 10000 + month * 100 + day;
	}
	bool IsLeapYear()
	{
		if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
			return true;
		return false;
	}
	bool islegal() {
		if (year < 0 || month <= 0 || month > 12)return false;
		if (1 == month || 3 == month || 5 == month || 7 == month || 8 == month || 10 == month || 12 == month) {
			if (day <= 0 || day > 31)return false;
			return true;
		}
		if (4 == month || 6 == month || 9 == month || 11 == month) {
			if (day <= 0 || day > 30)return false;
			return true;
		}
		if (IsLeapYear()) {
			if (2 == month && (day <= 0 || day > 29))return false;
			return true;
		}
		else {
			if (2 == month && (day <= 0 || day > 28))return false;
			return true;
		}
		return true;
	}
};
#endif