#ifndef FOLDERER_H_INCLUDED
#define FOLDERER_H_INCLUDED

#include <filesystem>
#include <vector>


class Folderer {
public:
      Folderer(const std::filesystem::path& playdir_) : playdir(playdir_) {}
      const std::vector<std::string> create_dir(std::vector<std::string>& Artist, std::vector<std::string>& Album) const;
      int ytdlp(std::vector<std::string>& Url, const std::vector<std::string> percorsi) const;


private:
    const std::filesystem::path playdir;
    std::string ytdlp_{"yt-dlp --abort-on-error --quiet -R 10 --file-access-retries 10 --fragment-retries 20 -x --audio-format mp3 --audio-quality 0 --embed-metadata --embed-thumbnail  --output \"%(artist)s - %(album)s - %(playlist_index)02d %(title)s.%(ext)s\" -P "};

};



#endif // FOLDERER_H_INCLUDED
