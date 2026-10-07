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
