# ttcdn
TTCDN - TikTok CDN Downloader (CLI).

## Description
This software does not use [TikTok Research API](https://developers.tiktok.com/products/research-api/) and instead downloads the videos directly from the TikTok CDN.

TTCDN takes a numeric ID of the video as an argument, the ID itself can be grabbed from a link: `https://www.tiktok.com/@user/video/xxxxxxxxxxxxxxxxxxx`, where `xxxxxxxxxxxxxxxxxxx` is a video ID

## Build (Linux)
1. Install dependencies: CMake, nlohmann::json, libcurl
2. Build:

       git clone https://github.com/keyboardcrash32/ttcdn.git
       cd ttcdn
       cmake -B build -S .
       cd build
       make

3. Done!
