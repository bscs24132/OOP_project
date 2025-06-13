#include "Reply.h"
#include "User.h"
#include <iostream>
#include <fstream>
using namespace std;
Reply::Reply(User* user, const String& msg) : user(user), msg(msg) {}
Reply::~Reply() {}
void Reply::print() const {
    user->getid().print();
    cout << ": ";
    msg.print();
    cout << endl;
}
User* Reply::get_user() const {
return user;
}
void Reply::wif(ofstream& fout) const {
    user->getid().wif(fout);
    msg.wif(fout);
}
Reply* Reply::rif(ifstream& fin, User** users, int usern) {
    String uid, m;
    uid.rif(fin);
m.rif(fin);
    User* u = NULL;
    for (int i = 0; i < usern; ++i)
if (users[i]->getid() == uid) u = users[i];
    if (!u) return NULL;
    return new Reply(u, m);
}
