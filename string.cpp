#include "String.h"
#include <iostream>
#include <fstream>
using namespace std;
int my_strlen(const char* p) {
    int i = 0;
    while (p[i] != '\0') i++;
    return i;
}
String::String() : s(0), c(0), ch(NULL) {}
String::String(const char* p) {
    s = my_strlen(p);
    c = s;
    ch = new char[s];
    for (int i = 0; i < s; ++i) ch[i] = p[i];
}
String::String(const String& p) {
    s = p.s;
    c = p.c;
    ch = new char[c];
    for (int i = 0; i < s; ++i) ch[i] = p.ch[i];
}
String::~String() {
delete[] ch;
}
String& String::operator=(const String& p) {
    if (this != &p) {
        delete[] ch;
        s = p.s;
        c = p.c;
        ch = new char[c];
        for (int i = 0; i < s; ++i)
		ch[i]=p.ch[i];
    }
    return *this;
}
int String::length() const {
return s;
}
void String::print() const {
for (int i = 0; i < s; ++i)
cout << ch[i];
}
bool String::operator==(const String& str) const {
    if (s != str.s) return false;
    for (int i = 0; i < s; ++i) if (ch[i] != str.ch[i]) return false;
    return true;
}
String String::operator+(const String& p) const {
    String temp;
    temp.s = s + p.s;
    temp.c = temp.s;
    temp.ch = new char[temp.s];
    for (int i = 0; i < s; ++i) temp.ch[i] = ch[i];
    for (int i = s; i < temp.s; ++i) temp.ch[i] = p.ch[i - s];
    return temp;
}
const char String::operator[](int i) const {
return ch[i];
}
char& String::operator[](int i) {
return ch[i];
}
String String::substring(int start, int len) const {
    if (start < 0) start = 0;
    if (start >= s) return String("");
    if (len < 0) len = 0;
    if (start + len > s) len = s - start;
    char* temp = new char[len + 1];
    for (int i = 0; i < len; ++i) temp[i] = ch[start + i];
    temp[len] = '\0';
    String result(temp);
    delete[] temp;
    return result;
}
void String::input() {
    char b[300];
    std::cin.getline(b,300);
    s = my_strlen(b);
    c = s;
    delete[] ch;
    ch = new char[s];
    for (int i = 0; i < s; ++i) ch[i] = b[i];
}
void String::wif(ofstream& fout) const {
    fout.write((char*)&s, sizeof(s));
    fout.write(ch, s);
}
void String::rif(ifstream& fin) {
    fin.read((char*)&s, sizeof(s));
    delete[] ch;
    ch = new char[s];
    fin.read(ch, s);
}
