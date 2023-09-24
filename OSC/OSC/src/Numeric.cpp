#include "Numeric.h"

ocas::Numeric::Numeric() : Element() , number() {}

ocas::Number ocas::Numeric::get_number() { return this->number; }

void ocas::Numeric::set_number(Number number) { this->number = number; }