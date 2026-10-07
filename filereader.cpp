#include "filereader.h"

Filereader::Filereader(const std::string& file) {

		inputFile.open(file);
		if (inputFile.is_open()){
		//std::string lines;
		std::string urls;
		std::string years;
		std::string artists;
		std::string albums;

                    while(std::getline(inputFile, urls, ';')){
                    std::getline(inputFile, years, ';');
                    std::getline(inputFile, artists, ';');
                    std::getline(inputFile, albums);
                 url.push_back(urls);
                 year.push_back(std::stoi(years));
                 artist.push_back(artists);
                 album.push_back(albums);
}
}
}

std::vector<std::string>& Filereader::getArtist() {

            return artist;
}


std::vector<std::string>& Filereader::getAlbum() {

           return album;
}

std::vector<std::string>& Filereader::getUrl() {

           return url;
}


std::vector<int>& Filereader::getYear() {

             return year;
}







