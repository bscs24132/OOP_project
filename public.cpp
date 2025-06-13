#include "Public.h"
#include "Follow.h"
#include "Notification.h"
using namespace std;
Public::Public(const String& id, const String& fname, const String& lname, const Date& dob, const String& pass, const String& bio)
    : User(id, fname, lname, dob, pass, bio, true) {}
void Public::follow(User* other) {
    if (other == this) return;
    Follow* f = new Follow(other, this);
    other->a_followed(f);
    this->a_follower(f);
    Notification* n = new Notification(other->getid() + String(" has followed you."));
    this->a_noti(n);
}
