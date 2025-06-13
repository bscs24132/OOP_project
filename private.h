#ifndef PRIVATE_H
#define PRIVATE_H
#include "User.h"
class Private : public User {
public:
    Private(const String& id, const String& fname, const String& lname, const Date& dob, const String& pass, const String& bio);
    void follow(User* other);
};
#endif
