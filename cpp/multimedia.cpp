#include "multimedia.h"
#include <string>
#include <iostream>
#include <sstream>

Multimedia::Multimedia(){}
Multimedia::~Multimedia(){
    std::cout << "Destruction" << std::endl;
}

Multimedia::Multimedia(std::string _name, std::string _pathname)
{
    name = _name;
    pathname = _pathname;
}

std::string Multimedia::get_name() const{
    return name;
}

std::string Multimedia::get_pathname() const{
    return pathname;
}

void Multimedia::set_name(std::string _name){
    name = _name;
}

void Multimedia::set_pathname(std::string _pathname){
    pathname = _pathname;
}

void Multimedia::print_values(std::ostream & out) const{
    std::stringstream ss;
    ss << get_name() << " " << get_pathname();
    out << ss.str();
}
