#include <iostream>
#include <curl/curl.h>
#include "downloader.h"

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <videoID>" << std::endl;
        return 1;
    }

    Downloader downloader;
    downloader.StartDownloading(argv[1]);

    return 0;
}