#include "Notification.h"
#include <iostream>
#include <fstream>
using namespace std;
Notification::Notification(const String& m) : msg(m) {}
void Notification::print() const { msg.print(); cout << endl; }
void Notification::wif(ofstream& fout) const {
    msg.wif(fout);
}
Notification* Notification::rif(ifstream& fin) {
    String m;
    m.rif(fin);
    return new Notification(m);
}
