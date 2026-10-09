#include <filesystem>
#include <iostream>
#include <string>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <format>

void rename_artista(std::filesystem::path p, std::string a){

         TagLib::FileRef f(p.c_str());

    if (!f.isNull() && f.tag()){
        TagLib::Tag *tag = f.tag();


        tag->setArtist(a.c_str());

        if (f.file()->save()) {
            std::cout << "Nome artista aggiornato con successo.\n";
        } else {
            std::cout << "Errore nel salvataggio del file.\n";
        }
    } else {
        std::cout << "Impossibile aprire il file o leggere i tag.\n";
    }

}


void rename_album(std::filesystem::path p, std::string a){

         TagLib::FileRef f(p.c_str());

         if (!f.isNull() && f.tag()){
            TagLib::Tag *tag = f.tag();


        tag->setAlbum(a.c_str());

        if (f.file()->save()) {

            std::cout << "Nome album aggiornato con successo.\n";

        } else {
            std::cout << "Errore nel salvataggio del file.\n";
        }
    } else {
        std::cout << "Impossibile aprire il file o leggere i tag.\n";
    }

}




void rename_file(std::filesystem::path p){

std::string filename{};
std::filesystem::path parent_dir{};




    TagLib::FileRef f(p.c_str());

    if (!f.isNull() && f.tag()){
        TagLib::Tag *tag = f.tag();

       std::string artista = tag->artist().toCString(true);
       std::string album = tag->album().toCString(true);
       std::string title = tag->title().toCString(true);
       unsigned int ntrack = tag->track();
       std::string strntrack = std::format("{:02d}", ntrack);

       filename = artista + " - " + album + " - " + strntrack + " " + title + ".mp3";

       parent_dir = p.parent_path();

        std::filesystem::path newname = parent_dir / filename;
        std::filesystem::rename(p, newname);
}

else
        std::cout << "Impossibile aprire il file o leggere i tag.\n";


}


int main(int argc, char* argv[])

{
    if (argc < 3)
    return -1;

    std::filesystem::path percorso{argv[1]};
    std::string artista{};
    std::string album{};
    std::string parametro{};
    std::filesystem::path newname{};



         if (!(argv[2] == nullptr)){

             artista = argv[2];

                     for (const auto& entry : std::filesystem::directory_iterator(percorso)){
                          rename_artista(entry, artista);
        }
}


         if (!(argv[3] == nullptr)){

             album = argv[3];

                     for (const auto& entry : std::filesystem::directory_iterator(percorso)){
                          rename_album(entry, album);
        }
}
                     for (const auto& entry : std::filesystem::directory_iterator(percorso)){
                          rename_file(entry);
                     }

    return 0;
}
