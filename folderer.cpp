#include "folderer.h"

#include <iostream>
#include <string>


const std::vector<std::string> Folderer::create_dir(std::vector<std::string>& Artist, std::vector<std::string>& Album) const {

            std::filesystem::path art;
            std::filesystem::path alb;
            std::vector<std::string> percorsi(Artist.size());
            for(size_t i = 0; i < Artist.size(); i++){

             art = Artist[i];
             alb = Album[i];

std::filesystem::path art_dir = playdir / Artist[i];
std::filesystem::path alb_dir = art_dir / Album[i];

percorsi[i] = alb_dir.string();

    if (std::filesystem::create_directory(art_dir))
        std::cout << "Directory Artista " << Artist[i] << " creata" << std::endl;
        else
        std::cout << "Direcotry Artista " << Artist[i] << " esistente!" << std::endl;


    if (std::filesystem::create_directory(alb_dir)){
        std::cout << "Directory Album " << Album[i] << " creata" << std::endl;
    }
        else
        std::cout << "Directory Album " << Album[i] << " esistente" << std::endl;

}
    return percorsi;
}


void Folderer::ytdlp(std::vector<std::string>& Url, const std::vector<std::string> percorsi) const {

         std::string comando{};
     for(size_t i = 0; i < Url.size(); ++i){
         comando = ytdlp_ + " \"" + percorsi[i] + "\" " + " \"" + Url[i] + "\" " ;
              std::system(comando.c_str());
}
}
