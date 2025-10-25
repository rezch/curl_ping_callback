#include <iostream>
#include <curl/curl.h>


int ping_callback(CURL*, void*, int action)
{
    switch (action) {
    case CURL_PING_SEND:
        std::cout << "=====> GOT: CURL_PING_SEND\n";
        break;
    case CURL_PING_SENDERR:
        std::cout << "=====> GOT: CURL_PING_SENDERR\n";
        return CURLE_PING_TIMEOUT;
    case CURL_PING_RECV:
        std::cout << "=====> GOT: CURL_PING_RECV\n";
        break;
    case CURL_PING_RECVACK:
        std::cout << "=====> GOT: CURL_PING_RECVACK\n";
        break;
    }
    return CURLE_OK;
}

size_t write_callback(char*, size_t size, size_t nmemb, void*)
{
    return size * nmemb;
}

int main()
{
    CURL* curl = curl_easy_init();
    auto url = "https://google.com";

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_UPKEEP_INTERVAL_MS, 0L);
    curl_easy_setopt(curl, CURLOPT_PING_FUNCTION, ping_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    curl_easy_perform(curl);
    curl_easy_upkeep(curl);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}
