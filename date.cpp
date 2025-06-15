#include "Date.h"
#include <iostream>
using namespace std;
bool IsLeapYear(int year) {
if(year%4==0){
	if(year%100){
		if(year%400){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		return 1;
	}
}
return 0;
}
bool IsValidDate(int day, int month, int year) {
if(year>=1&&month>=1&&month<=12&&day>=1){
	if((month==1||month==3||month==5||month==7||month==8||month==10||month==12)&&day<=31){
		return 1;
	}
	else if((month==4||month==6||month==9||month==11)&&day<=30){
		return 1;
	}
	else if(month==2){
		bool l=IsLeapYear(year);
		if(l){
			if(day<=29){
				return 1;
			}
		}
		else{
			if(day<=28){
				return 1;
			}
		}
	}
}
return 0;
}
Date::Date() : day(0), month(0), year(0) {}
Date::Date(int y, int m, int d) : day(d), month(m), year(y) {
if(!IsValidDate(day,month,year)){
	throw invalidDate();
}
}
void Date::print() const { cout << day << "/" << month << "/" << year; }
