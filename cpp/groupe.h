#ifndef GROUPE_H
#define GROUPE_H

#include "multimedia.h"
#include <list>
#include <memory>

using MultimediaPtr = std::shared_ptr<Multimedia>;

class Groupe : public std::list<MultimediaPtr>
{
    friend class Tables;
private:
    std::string name{};

protected:
    Groupe(){};
    Groupe(std::string _name){
        name = _name;
    }

public:


    std::string get_name() const {return name;}

    // Subtilité ici : il faut avoir un const_iterator comme la fonction est const
    void display(std::ostream & out) const {
        for(std::list<MultimediaPtr>::const_iterator it = begin(); it != end(); ++it) {
            (*it)->print_values(out);
        }
    }
};

#endif // GROUPE_H
