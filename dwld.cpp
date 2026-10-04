#include <taglib/tag.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <taglib/fileref.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <regex>
#include <fstream>


void set_year(const char* filename, int anno){

    TagLib::FileRef f(filename);

    if (!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();

        // Imposta l'anno desiderato
        tag->setYear(anno);

        // Salva i cambiamenti
        if (f.file()->save()) {
            std::cout << "Anno aggiornato con successo.\n";
        } else {
            std::cout << "Errore nel salvataggio del file.\n";
        }
    } else {
        std::cout << "Impossibile aprire il file o leggere i tag.\n";
    }
}

void set_ntrack(const char* filename, int ntrack) {
    TagLib::FileRef f(filename);
    if (!f.isNull() && f.tag()) {
        TagLib::Tag* tag = f.tag();

        tag->setTrack(ntrack);  // Imposta il numero traccia a 5

        if (f.file()->save()) {
            std::cout << "Numero traccia aggiornato con successo." << std::endl;
        } else {
            std::cerr << "Errore durante il salvataggio del file." << std::endl;
        }
    } else {
        std::cerr << "Impossibile aprire il file o leggere i tag." << std::endl;
    }

}


void rename(std::filesystem::path dir) {

        std::regex vietati{"[\\\\/:*?*<>|]"};
        std::regex_replace(dir.filename().string(), vietati, "-");
        std::cout << "File rinominato con successo." << std::endl;

}



int main(int argc, char* argv[]) {

//char risposta{};
if (argc < 2) {
		std::cerr << "No input file!" << std::endl;
		std::cerr << "Usage: " << std::endl;
		std::cerr << argv[0] << " <filename> " << std::endl;
		return EXIT_FAILURE;
	}

	std::ifstream inputFile;
	try {
		inputFile.open(argv[1]);
	}
	catch (std::exception& e) {
		// Whatever exception is raised, end up here
		std::cerr << "Cannot open " << argv[1] << " got: " << std::endl;
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
std::string riga;
std::string prova;
 int anno{0};
 std::string url{};
 std::filesystem::path artista{};
 std::filesystem::path album{};

	if (inputFile.is_open()) {
while (inputFile >> url >> anno >> artista >> album){
// std::cout << url << " " << anno << " " << artista << " " << album;
char aspetta{};
std::string ytdlp{"yt-dlp --extract-audio --audio-format mp3 --audio-quality 0 --embed-metadata --embed-thumbnail  --output \"~/Album/%(artist)s - %(album)s - %(playlist_index)02d %(title)s.%(ext)s\" "};

        std::filesystem::path dir{"/data/data/com.termux/files/home/Album"};
        const char* cdir{};
        int i{1};

        std::vector<std::filesystem::directory_entry> files;

        std::string str{};
        std::string comando = ytdlp + url;
        system(comando.c_str());
        std::cin >> aspetta;


        try {
        if (std::filesystem::exists(dir) && std::filesystem::is_directory(dir)) {
            for (const auto& entry : std::filesystem::directory_iterator(dir)) {
                if (std::filesystem::is_regular_file(entry.status())) {
                    files.push_back(entry);
                }
            }

            // Ordina i file in ordine alfabetico
            std::sort(files.begin(), files.end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b) {
                return a.path().filename() < b.path().filename();
            });

            // Stampa i file ordinati
            for (const auto& file : files) {


                str = file.path().string();
                cdir = str.c_str();
                rename(str);
                set_year(cdir, anno);
                set_ntrack(cdir, i);

                i++;
            }

        } else {
            std::cerr << "Il percorso non esiste o non è una directory." << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Errore filesystem: " << e.what() << std::endl;
    }

    const std::filesystem::path percorso =  "/data/data/com.termux/files/home/storage/music/Playlist" / artista;

    if (std::filesystem::create_directory(percorso))
        std::cout << "Directory creata!" << std::endl;
        else
        std::cout << "Direcotry esistente!" << std::endl;


    const std::filesystem::path percorso_album = percorso / album;
    if (std::filesystem::create_directory(percorso_album)){
        std::cout << "Directory creata!" << std::endl;
    }
        else
        std::cout << "Direcotry esistente!" << std::endl;

        std::filesystem::copy(dir, percorso_album, std::filesystem::copy_options::recursive);

            std::filesystem::remove_all(dir);

        std::string virg{"\""};
        std::string comando_cover = "cover " + virg + percorso_album.string() + virg;

        system(comando_cover.c_str());

        }
        inputFile.close();
	}

    return 0;

}
