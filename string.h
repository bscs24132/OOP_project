#ifndef STRING_H
#define STRING_H
#include <iostream>
#include <fstream>
using namespace std;
class String {
    int s;
    int c;
    char* ch;
public:
    String();
    String(const char* p);
    String(const String& p);
    ~String();
    String& operator=(const String& p);
    int length() const;
    void print() const;
    bool operator==(const String& str) const;
    String operator+(const String& p) const;
    const char operator[](int i) const;
    char& operator[](int i);
    String substring(int start, int len) const;
    void input();
    void wif(ofstream& fout) const;
    void rif(ifstream& fin);
};
#endif
