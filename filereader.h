#ifndef FILEREADER_H_INCLUDED
#define FILEREADER_H_INCLUDED

#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
#include <vector>



class Filereader {

public:
      Filereader(const std::string& file);

      std::vector<std::string>& getArtist();
      std::vector<std::string>& getAlbum();
      std::vector<std::string>& getUrl();
      std::vector<int>& getYear();

private:
    std::vector<std::string> url;
    std::vector<int> year;
    std::vector<std::string> artist;
    std::vector<std::string> album;
    std::ifstream inputFile;

};


#endif // FILEREADER_H_INCLUDED
