#pragma once
#define CURL_STATICLIB

#ifdef _DEBUG
#pragma comment(lib, "curl/libcurl_a_debug.lib")
#else
#pragma comment(lib, "curl/libcurl_a.lib")
#endif

#include <string>
#include "curl/curl.h"

class Curl
{
public:
    Curl();
    ~Curl();

    std::string GetUrl(const std::string& url);
private:

    CURL* curl_;
};

