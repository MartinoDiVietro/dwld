#include <filesystem>
#include <stdio.h>
#include <string>


int main(int argc, char* argv[])
{
    if (argc < 2)
    return -1;

    std::filesystem::path percorso{argv[1]};
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




    return 0;
}
