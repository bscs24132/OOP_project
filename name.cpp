#include "Name.h"
#include <iostream>
using namespace std;
Name::Name() : firstName("First"), lastName("Last") {}
Name::Name(const String& f, const String& l) : firstName(f), lastName(l) {}
String Name::get_f() const { return firstName; }
String Name::get_l() const { return lastName; }
void Name::print() const { firstName.print(); cout << " "; lastName.print(); }
