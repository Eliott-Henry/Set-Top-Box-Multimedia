#ifndef PHOTO_H
#define PHOTO_H

#include <string>
#include <iostream>
#include <sstream>
#include "multimedia.h"

class Photo : public Multimedia
{

    friend class Tables;
private:
    int lattitude{}, longitude{};

protected :
    Photo(){};
    Photo(std::string _name, std::string _pathname, int _lattitude, int _longitude)
    {
        set_name(_name);
        set_pathname(_pathname);
        lattitude = _lattitude;
        longitude = _longitude;
    }
public:

    ~Photo(){};
    int get_longitude() const{return longitude;}
    int get_lattitude() const{return lattitude;}
    void set_lattitude(int _lattitude){lattitude = _lattitude;}
    void set_longitude(int _longitude){longitude = _longitude;}

    void print_values(std::ostream & out) const override{
        std::stringstream ss;
        ss << get_name() << " " << get_pathname() << " " << get_longitude() << " " << get_lattitude() << std::endl;
        out << ss.str();
    }

    void play() const override{
        std::string arg1 = "imagej ";
        std::string arg2 = " &";
        std::string arg = arg1 + get_pathname() + arg2;
        system(arg.data());
    }
};

#endif // PHOTO_H
