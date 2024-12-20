#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <regex>

#include "downloader.h"

using json = nlohmann::json;

Downloader::Downloader()
{
    m_curl = curl_easy_init();
}

Downloader::~Downloader()
{
    curl_easy_cleanup(m_curl);
}

size_t writeStreamData(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    std::ostringstream *stream = (std::ostringstream *)userdata;

    size_t count = size * nmemb;
    stream->write(ptr, count);

    return count;
}

size_t writeFileData(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    std::ofstream *stream = (std::ofstream *)userdata;

    size_t count = size * nmemb;
    stream->write(ptr, count);

    return count;
}

bool Downloader::StartDownloading(const std::string &videoID)
{
    if (videoID.empty())
    {
        std::cerr << "videoID is empty" << std::endl;
        return false;
    }

    std::cout << "Fetching JSON from api22-normal-c-alisg.tiktokv.com..." << std::endl;

    std::string url = "https://api22-normal-c-alisg.tiktokv.com/aweme/v1/feed/?aweme_id=" + videoID +
                      "&iid=7318518857994389254&device_id=7318517321748022790&channel=googleplay"
                      "&app_name=musical_ly&version_code=300904&device_platform=android&device_type=ASUS_Z01QD"
                      "&version=9";

    std::ostringstream jsonResult;

    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, writeStreamData);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &jsonResult);
    curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64; rv:133.0) Gecko/20100101 Firefox/133.0");
    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());

    CURLcode res = curl_easy_perform(m_curl);
    if (res != CURLE_OK)
    {
        std::cerr << "Failed to fetch JSON. cURL error: " << curl_easy_strerror(res) << std::endl;
    }

    std::string resultStr = jsonResult.str();

    json jsonData;
    try
    {
        jsonData = json::parse(resultStr);
    }
    catch (const json::parse_error &e)
    {
        std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
        return false;
    }

    std::string videoUrl;
    try
    {
        if (!jsonData.contains("aweme_list") ||
            !jsonData["aweme_list"].is_array() || jsonData["aweme_list"].empty())
        {
            throw std::runtime_error("Invalid or missing 'aweme_list' in JSON.");
        }

        videoUrl = jsonData["aweme_list"][0]["video"]["play_addr"]["url_list"][0].get<std::string>();
        videoUrl = std::regex_replace(videoUrl, std::regex(R"(\\u0026)"), "&");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Invalid JSON structure or missing video URL: " << e.what() << std::endl;
        return false;
    }

    std::cout << "Downloading video from " << videoUrl << std::endl;

    curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64; rv:133.0) Gecko/20100101 Firefox/133.0");
    curl_easy_setopt(m_curl, CURLOPT_URL, videoUrl.c_str());

    const std::string filename = "output.mp4";
    std::ofstream file = std::ofstream(filename, std::ofstream::binary);
    if (!file.is_open())
    {
        std::cerr << "Failed to open output file" << std::endl;
        return false;
    }

    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, writeFileData);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &file);

    res = curl_easy_perform(m_curl);
    if (res != CURLE_OK)
    {
        std::cerr << "Failed to download video. cURL error: " << curl_easy_strerror(res) << std::endl;

        file.close();
        return false;
    }

    file.close();

    return true;
}