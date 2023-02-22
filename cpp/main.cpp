//
// main.cpp
// Created on 21/10/2018
//

#include "multimedia.h"
#include "photo.h"
#include "video.h"
#include "film.h"
#include "groupe.h"
#include "tables.h"
#include "tcpserver.h"

#include <iostream>
#include <list>
#include <cstring>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>


using PhotoPtr = std::shared_ptr<Photo>;
using VideoPtr = std::shared_ptr<Video>;
using FilmPtr = std::shared_ptr<Film>;
using GroupePtr = std::shared_ptr<Groupe>;
using MultimediaPtr = std::shared_ptr<Multimedia>;
using namespace std;

// QUESTION 11 
// Protocole choisi :
// Mot 1 : Play ou Search 
// Si Play : en mot 2 mettre le nom du multimedia à jouer
// Si Search en mot 2 mettre le type de chose à chercher (Multimedia ou Groupe) et en mot 3 le nom de l'entité

const int PORT = 3331;

int main(int argc, char* argv[])
{
    Tables * tables = new Tables();

    int chapters_1[3] = {1,2,3};
    //FilmPtr film1 = tables->create_film("video", "video.mp4", 4, chapters_1, 3);
    PhotoPtr photo1 = tables->create_photo("photo1", "photo.png", 10, 15);
    GroupePtr groupe1 = tables->create_group("SF");
    groupe1->push_back(film1);

    auto* server =
  new TCPServer( [&](std::string const& request, std::string& response) {

    
    // the request sent by the client to the server
    cout << "request: " << request << std::endl;
    

    // On récupère les différents mots de la requête
    stringstream rs;
    rs << request;
    array<string, 3> mots;
    rs >> mots[0];
    rs >> mots[1];
    rs >> mots[2];
    
    // On stockera les réponses dedans
    stringstream ss;

    if(mots[0] == "Search"){
        if(mots[1] == "Groupe"){
            tables->search_print_groupe(mots[2], ss);
        }
        else if(mots[1] == "Multimedia"){
            tables->search_print_objet(mots[2], ss);
        }
        else{
            ss << "Type d'objet incorrect.";
        }
    }
    else if(mots[0 ]== "Play"){
        tables->search_play_objet(mots[1], ss);
    }
    else{
        ss << "La requête n'est pas conforme au protocole.";
    }
    
    response = ss.str();
    // return false would close the connection with the client
    return true;
  });
   
  // lance la boucle infinie du serveur
  std::cout << "Starting Server on port " << PORT << std::endl;

  int status = server->run(PORT);

  // en cas d'erreur
  if (status < 0) {
    std::cerr << "Could not start Server on port " << PORT << std::endl;
    return 1;
  }

  return 0;
}

// Question 10
    // On vérifie bien qu'on peut jouer des objets et afficher un objet ou un groupe qui est dans la table, et qu'il y a un msg d'erreur si l'élément n'est pas dans la table
    // En mettant les constructeurs en protected et en rajoutant la classe Tables comme friend, on permet de garantir la cohérence de la base de données (on ne peut créer des objets et des groupes que dans la classe Tables)
    /*
    Tables * tables = new Tables();

    int chapters_1[3] = {1,2,3};
    FilmPtr film1 = tables->create_film("video", "video.mp4", 4, chapters_1, 3);
    PhotoPtr photo1 = tables->create_photo("photo1", "photo.png", 10, 15);

    tables->search_play_objet("video");
    tables->search_play_objet("photo1");
    tables->search_play_objet("autre");

    GroupePtr groupe1 = tables->create_group("Groupe 1");
    groupe1->push_back(film1);

    tables->search_print_groupe("Groupe 1");*/

    
// Question 9

// On vérifie bien que les objets sont détruits quand ils n'appartiennent plus à aucun groupe
/*
int chapters[3] = {1, 4, 6};
MultimediaPtr film(new Film("video", "video.mp4", 30, chapters, 3));
int chapters_2[4] = {1,2,3,4};
MultimediaPtr film_2(new Film("avengers", "avengers.mp4", 50, chapters_2, 4));

MultimediaPtr photo_chat(new Photo("chat", "chat.png", 3, 5));
MultimediaPtr photo_chien(new Photo("chien", "chien.png", 6, 2));
MultimediaPtr video_1(new Video("tuto", "tuto.png",  5));

Groupe * groupe_1 = new Groupe();
Groupe * groupe_2 = new Groupe();


groupe_1->push_back(photo_chat);
groupe_1->push_back(film);

groupe_2->push_back(film_2);
groupe_2->push_back(video_1);
groupe_2->push_back(film);
groupe_2->push_back(photo_chien);

groupe_1->display(std::cout);
groupe_2->display(std::cout);

groupe_1->pop_back();
groupe_1->pop_back();

groupe_2->pop_back();
groupe_2->pop_back();
groupe_2->pop_back();
groupe_2->pop_back();

Question 8 :

int chapters[3] = {1, 4, 6};
Multimedia * film = new Film("video", "video.mp4", 30, chapters, 3);
int chapters_2[4] = {1,2,3,4};
Film * film_2 = new Film("avengers", "avengers.mp4", 50, chapters_2, 4);

Photo * photo_chat = new Photo("chat", "chat.png", 3, 5);
Photo * photo_chien = new Photo("chien", "chien.png", 6, 2);
Video * video_1 = new Video("tuto", "tuto.png",  5);

Groupe * groupe_1 = new Groupe();
Groupe * groupe_2 = new Groupe();

groupe_2->push_back(film_2);
groupe_2->push_back(video_1);
groupe_2->push_back(film);
groupe_2->push_back(photo_chien);

groupe_2->display(std::cout);

Question 6 :

int chapters[3] = {1, 4, 6};
Film * film = new Film("video", "video.mp4", 30, chapters, 3);
film->print_chapters_duration(std::cout);

int new_chapsters[4] = {1, 2, 3, 4};
film->set_chapters(new_chapsters, 4);

film->print_chapters_duration(std::cout);

Question 5

Multimedia ** tab = new Multimedia*[4];
tab[0] = new Photo("photo", "photo.png", 0, 0);
tab[1] = new Video("video", "video.mp4", 30);
tab[2] = new Photo("photo", "photo.png", 0, 0);
tab[3] = new Video("video", "video.mp4", 30);

for(int i = 0; i < 4; i++){
    tab[i]->play();
}

Question 4

Photo * photo = new Photo("photo", "photo.png", 0, 0);
photo->play();

Video * video = new Video("video", "video.mp4", 30);
video->play();

*/
