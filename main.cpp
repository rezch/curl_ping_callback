#include <iostream>
#include <curl/curl.h>
#include <thread>


int ping_callback(CURL*, void*, int action)
{
    const char* msg[] = {
        "CURL_PING_SEND",
        "CURL_PING_SENDERR",
        "CURL_PING_RECV",
        "CURL_PING_RECVACK",
        "CURL_PING_CONNOPEN",
        "CURL_PING_CONNCLOSE",
    };
    std::cout << "=====> GOT: " << msg[action - 1] << "\n";
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
    curl_easy_setopt(curl, CURLOPT_MAXAGE_CONN, 1L);
    curl_easy_setopt(curl, CURLOPT_UPKEEP_INTERVAL_MS, 0L);
    curl_easy_setopt(curl, CURLOPT_PING_FUNCTION, ping_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    curl_easy_perform(curl);
    curl_easy_upkeep(curl);

    curl_easy_setopt(curl, CURLOPT_FRESH_CONNECT, 1L);
    curl_easy_perform(curl);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    curl_easy_perform(curl);

    curl_easy_cleanup(curl);
}
