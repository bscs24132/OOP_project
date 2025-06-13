#include "Private.h"
#include "Follow.h"
#include "Notification.h"
#include <iostream>
using namespace std;
Private::Private(const String& id, const String& fname, const String& lname, const Date& dob, const String& pass, const String& bio): User(id, fname, lname, dob, pass, bio, false) {}
void Private::follow(User* other) {
    if (other == this) return;
    this->a_request(other);
    other->a_sentrequest(this);
    Notification* n = new Notification(other->getid() + String(" has sent you a follow request."));
    this->a_noti(n);
    cout << "Follow request is sent to ";
    this->getid().print();
    cout << endl;
}
