#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include "String.h"
#include"iostream"
#include"fstream"
class Notification {
    String msg;
public:
    Notification(const String& m);
    void print() const;
    void wif(ofstream& fout) const;
    static Notification* rif(ifstream& fin);
};
#endif
