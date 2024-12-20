#include <iostream>
#include <curl/curl.h>
#include "downloader.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <videoID>" << std::endl;
        return 1;
    }

    Downloader downloader;
    if (downloader.StartDownloading(argv[1]))
    {
        std::cout << "Downloaded successfully!" << std::endl;
        return 0;
    }
    else
    {
        std::cerr << "Download failure, check logs above" << std::endl;
        return 1;
    }

    return 0;
}