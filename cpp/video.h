#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <iostream>
#include <sstream>
#include "multimedia.h"

class Video : public Multimedia
{
    friend class Tables;
private:
    int duration{};

protected:
    Video(){};

    Video(std::string _name, std::string _pathname, int _duration)
    {
        set_name(_name);
        set_pathname(_pathname);
        duration = _duration;
    }

public:
    ~Video(){};

    int get_duration() const{return duration;}
    void set_duration(int _duration){duration = _duration;}

    void print_values(std::ostream & out) const override{
        std::stringstream ss;
        ss << get_name() << " " << get_pathname() << " " << get_duration() << std::endl;
        out << ss.str();
    }

    void play() const override{
        std::string arg1 = "mpv ";
        std::string arg2 = " &";
        std::string arg = arg1 + get_pathname() + arg2;
        system(arg.data());
    }
};

#endif // VIDEO_H
