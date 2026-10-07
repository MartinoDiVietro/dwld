#include "filereader.h"
#include "folderer.h"
#include "tagger.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>



int main(int argc, char* argv[])
{
    if (argc < 3) {
		std::cerr << "No input file!" << std::endl;
		std::cerr << "Usage: " << std::endl;
		std::cerr << argv[0] << " <path/to/filename> <Playlist Directory> <Playlist Items> (eg. 1-5)" << std::endl;
		return EXIT_FAILURE;
		}

	Filereader filereader(argv[1]);

	Folderer folderer(argv[2]);
	const std::vector<std::string>& path = folderer.create_dir(filereader.getArtist(), filereader.getAlbum());
	folderer.ytdlp(filereader.getUrl(), path);

	Tagger tagger(filereader.getYear(), path);
	tagger.order();

    return 0;
}
