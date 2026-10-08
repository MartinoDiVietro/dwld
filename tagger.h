#ifndef TAGGER_INCLUDED
#define TAGGER_INCLUDED

#include <string>
#include <vector>
#include <filesystem>

#include <taglib/tag.h>
#include <taglib/fileref.h>


class Tagger {
public:
      Tagger(std::vector<int>& year_, const std::vector<std::string>& path_) : year(year_), path(path_) {}
      void setter(int anno);
      void order();
      void cover() const;


private:
       std::vector<int> year;
       std::vector<std::string> path;
       std::vector<std::filesystem::directory_entry> tmp_files;

};



#endif // TAGGER_INCLUDED
