# ttcdn
TTCDN - TikTok CDN Downloader (CLI).

## Description
TTCDN does not use [TikTok Research API](https://developers.tiktok.com/products/research-api/) and instead downloads the videos directly from the TikTok CDN.

## Build (Linux)
1. Install dependencies: CMake, nlohmann::json, libcurl
2. Build:

       git clone https://github.com/keyboardcrash32/ttcdn.git
       cd ttcdn
       cmake -B build -S .
       cd build
       make

3. Done!
