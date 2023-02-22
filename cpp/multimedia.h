#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <string>
#include <iostream>

class Multimedia
{
    friend class Tables;
private:
    std::string name{}, pathname{};
protected:
    Multimedia();
    Multimedia(std::string _name, std::string _pathname);
public:
    ~Multimedia();
    std::string get_name() const;
    std::string get_pathname() const;
    void set_name(std::string _name);
    void set_pathname(std::string _pathname);
    virtual void print_values(std::ostream & out) const;
    virtual void play() const = 0;
};

#endif // MULTIMEDIA_H
