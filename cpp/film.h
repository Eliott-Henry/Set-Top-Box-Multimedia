#ifndef FILM_H
#define FILM_H

#include "multimedia.h"
#include "video.h"

class Film : public Video
{
    friend class Tables;
private:
    int * chapters{};
    int nb_chapters{};

protected:
    Film(){};
    // Constructor
    Film(std::string _name, std::string _pathname, int _duration, int * _chapters, int _nb_chapters)
    {
        set_name(_name);
        set_pathname(_pathname);
        set_duration(_duration);
        chapters = copy(_chapters, _nb_chapters); // On créé un tableau dont on connait l'adresse seulement dans l'objet et qui est le même en contenu que le paramètre
        nb_chapters = _nb_chapters;
    }

    // Define deep copy constructor
    Film(const Film& from) : Video(from){
        nb_chapters = from.nb_chapters;
        chapters =  from.chapters ? copy(from.chapters, from.nb_chapters) : nullptr;
    }
public:


    // Destructor which takes care to delete stuff on the heap
    ~Film(){
        delete[] chapters;
    };


    // Define deep copy operator
    Film& operator=(const Film& from){
        Video::operator=(from);
        nb_chapters = from.nb_chapters;
        if(chapters && from.chapters) *chapters = *from.chapters;
        else{
            delete chapters;
            chapters = from.chapters ? copy(from.chapters, from.nb_chapters) : nullptr;
        }
        return *this;
    }


    // On fait ça pour que l'objet reste le seul à pouvoir modifier son attribut chapters (qui est un pointeur donc on pourrait y accéder à l'éxterieur si on avait l'adresse du pointeur)
    // Define a function which creates a new objects chapters, that is equal for each attribute to _chapters, and returns a pointer on it
    int * copy(int * _chapters, int _nb_chapters) const{
        if(_nb_chapters == 0) return nullptr;
        int * new_chapters = new int[_nb_chapters];
        for(int i = 0; i < _nb_chapters; i++){
            new_chapters[i] = _chapters[i];
        }
        return new_chapters;
    }

    // retourne un pointeur sur un tableau qui contient la même donnée
    int * get_chapters() const{return copy(chapters, nb_chapters);}

    // Retourne le nombre de chapitres
    int get_nb_chapters() const{return nb_chapters;}

    // Modifie la valeur de chapters, en prenant en compte la question de la propriété de l'objet
    void set_chapters(int * _chapters, int _nb_chapters){
        if(_nb_chapters == 0){chapters = nullptr;}
        else{
            delete[] chapters; // Différencier les cas où on a la même taille pour les deux tableaux ou pas
            chapters = copy(_chapters, _nb_chapters); // On utilise une fois de plus une copie
        }
        nb_chapters = _nb_chapters;
    }

    void print_values(std::ostream & out) const override{
        std::stringstream ss;
        ss << get_name() << " " << get_pathname() << " " << get_duration() << std::endl;
        out << ss.str();
    }

    void print_chapters_duration(std::ostream & out) const{
        for(int i = 0; i < nb_chapters; i++){
            std::stringstream ss;
            ss << "Chapter " << i << " : " << get_chapters()[i] << std::endl;
            out << ss.str();
        }
    }

    void play() const override{
        std::string arg1 = "mpv ";
        std::string arg2 = " &";
        std::string arg = arg1 + get_pathname() + arg2;
        system(arg.data());
    }
};

#endif // FILM_H
