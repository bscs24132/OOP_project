#ifndef PUBLIC_H
#define PUBLIC_H
#include "User.h"
class Public : public User {
public:
    Public(const String& id, const String& fname, const String& lname, const Date& dob, const String& pass, const String& bio);
    void follow(User* other);
};
#endif
