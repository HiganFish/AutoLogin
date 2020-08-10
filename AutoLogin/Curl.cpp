#include "Curl.h"

int writer(char* data, size_t size, size_t nmemb, std::string* result)
{
    if (result == nullptr)
    {
        return 0;
    }

    result->append(data, size * nmemb);

    return size * nmemb;
}

Curl::Curl()
{
    curl_ = curl_easy_init();
}

Curl::~Curl()
{
    curl_easy_cleanup(curl_);
}

std::string Curl::GetUrl(const std::string& url)
{
    std::string result;
    if (!curl_)
    {
        return result;
    }

    curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, writer);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &result);

    curl_easy_perform(curl_);

    return result;
}