#ifndef DATE_H
#define DATE_H
#include "String.h"
class Date {
	public:
		class invalidDate{
		};
    int day, month, year;
    Date();
    Date(int y, int m, int d);
    void print() const;
};
#endif
