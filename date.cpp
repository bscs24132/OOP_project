#include "Date.h"
#include <iostream>
using namespace std;
Date::Date() : day(0), month(0), year(0) {}
Date::Date(int y, int m, int d) : day(d), month(m), year(y) {}
void Date::print() const { cout << day << "/" << month << "/" << year; }