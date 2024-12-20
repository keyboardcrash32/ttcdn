#ifndef DOWNLOADER_H_INCLUDED
#define DOWNLOADER_H_INCLUDED

#include <string>
#include <curl/curl.h>

class Downloader
{
public:
    Downloader();
    ~Downloader();

    void StartDownloading(const std::string& videoID);

private:
    CURL *m_curl;
};

#endif // DOWNLOADER_H_INCLUDED