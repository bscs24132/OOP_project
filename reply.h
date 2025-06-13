#ifndef REPLY_H
#define REPLY_H
#include "String.h"
#include <iostream>
#include <fstream>
using namespace std;
class User;
class Reply {
    User* user;
    String msg;
public:
    Reply(User* user, const String& msg);
    ~Reply();
    void print() const;
    User* get_user() const;
    void wif(ofstream& fout) const;
    static Reply* rif(ifstream& fin, User** users, int usern);
};
#endif
