#ifndef NAME_H
#define NAME_H
#include "String.h"
class Name {
    String firstName, lastName;
public:
    Name();
    Name(const String& f, const String& l);
    String get_f() const;
    String get_l() const;
    void print() const;
};
#endif
