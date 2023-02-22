#ifndef TABLES_H
#define TABLES_H

#include "multimedia.h"
#include "photo.h"
#include "photo.h"
#include "film.h"
#include "groupe.h"

#include <iostream>
#include <memory>
#include <map>

using PhotoPtr = std::shared_ptr<Photo>;
using VideoPtr = std::shared_ptr<Video>;
using FilmPtr = std::shared_ptr<Film>;
using GroupePtr = std::shared_ptr<Groupe>;
using MultimediaPtr = std::shared_ptr<Multimedia>;
using namespace std;

class Tables
{

private:

    map<std::string, MultimediaPtr> table_multimedia;
    map<std::string, GroupePtr> table_groupe;

public:
    Tables(){};
    ~Tables(){};

    // Méthode de création d'objets et insertion dans les tables

    VideoPtr create_video(std::string _name, std::string _pathname, int _duration){
        VideoPtr video(new Video(_name, _pathname,  _duration));
        table_multimedia[_name] = video;
        return video;
    }

    PhotoPtr create_photo(std::string _name, std::string _pathname, int _lattitude, int _longitude){
        PhotoPtr photo(new Photo(_name, _pathname,  _lattitude, _longitude));
        table_multimedia[_name] = photo;
        return photo;
    };

    FilmPtr create_film(std::string _name, std::string _pathname, int _duration, int * _chapters, int _nb_chapters){
        FilmPtr film(new Film(_name, _pathname,  _duration, _chapters, _nb_chapters));
        table_multimedia[_name] = film;
        return film;
    };

    GroupePtr create_group(std::string _name){
        GroupePtr groupe(new Groupe(_name));
        table_groupe[_name] = groupe;
        return groupe;
    };

    void search_print_objet(std::string _name, std::ostream & out) {
        map<std::string, MultimediaPtr>::iterator it;
        it = table_multimedia.find(_name);
        if(it != table_multimedia.end()){
            it->second->print_values(out);
        }else{
            out << "Cet objet n'est pas dans la table";
        }
    }

    void search_print_groupe(std::string _name, std::ostream & out) {
        map<std::string, GroupePtr>::iterator it;
        it = table_groupe.find(_name);
        if(it != table_groupe.end()){
            it->second->display(out);
        }
        else{
            out << "Ce groupe n'est pas dans la table";
        }
    }

    void search_play_objet(std::string _name, std::ostream & out){
        map<std::string, MultimediaPtr>::iterator it;
        it = table_multimedia.find(_name);
        if(it != table_multimedia.end()){
            it->second->play();
        }else{
            out << "Cet objet n'est pas dans la table";
        }
    }
};

#endif // TABLES_H
