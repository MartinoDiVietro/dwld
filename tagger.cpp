#include "tagger.h"

#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <iostream>

void Tagger::order() {
    int i{0};
    for(const auto& dirAlbum : path){
if (std::filesystem::exists(dirAlbum) && std::filesystem::is_directory(dirAlbum)) {
            for (const auto& entry : std::filesystem::directory_iterator(dirAlbum)) {
                if (std::filesystem::is_regular_file(entry.status())) {
                    tmp_files.push_back(entry);
                }
            }
            std::sort(tmp_files.begin(), tmp_files.end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b) {
                return a.path().filename() < b.path().filename(); });
}
              setter(i);
              tmp_files.clear();
              i++;
    }
}



void Tagger::setter(int anno) {

    const char* filename{};
    std::string prova{};
    std::filesystem::directory_entry prova1;
     int ntrack{1};

    for(size_t i = 0; i < tmp_files.size(); i++){
            prova1 = tmp_files[i];
    prova = prova1.path().string();
    filename = prova.c_str();
    std::cout << tmp_files[i] << std::endl;
    TagLib::FileRef f(filename);

    if (!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();

        // Imposta l'anno desiderato
        tag->setYear(year[anno]);
        tag->setTrack(ntrack);

        // Salva i cambiamenti
        if (f.file()->save()) {
            std::cout << "Anno aggiornato con successo.\n";
        } else {
            std::cout << "Errore nel salvataggio del file.\n";
        }
    } else {
        std::cout << "Impossibile aprire il file o leggere i tag.\n";
    }
    ntrack++;

}
}


void Tagger::cover() const {

      std::filesystem::path percorso;
      for (const auto& iter : path){
            percorso = iter;
    std::string parametro{};

    std::string comando{};
    std::string comando1{"ffmpeg -i "};
    std::string comando2{" -an -vcodec copy \"cover.jpg\""};
    std::string virg{"\""};
    std::string stringa2{" -i \"cover_700x700.jpg\" -map 0:0 -map 1:0 -c copy -id3v2_version 3 -metadata:s:v title=\"Album cover\" -metadata:s:v comment=\"Cover (700x700)\" \"tmp.mp3\""};
    std::string stringa3{"mv tmp.mp3 "};


    for (const auto& entry : std::filesystem::directory_iterator(percorso)) {

        parametro = entry.path();

        comando = comando1 + virg + parametro + virg + comando2;

        system(comando.c_str());

        system("ffmpeg -i \"cover.jpg\" -vf \"crop=700:700:(in_w-700)/2:(in_h-700)/2\" \"cover_700x700.jpg\"");

        comando = comando1 + virg + parametro + virg + stringa2;
        system(comando.c_str());

        comando = stringa3 + virg + parametro + virg;
        system(comando.c_str());

        system("rm cover.jpg cover_700x700.jpg");


    }
      }
}
