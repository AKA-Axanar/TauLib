#define CURL_STATICLIB
#include "Tau_curl.h"
#include <curl.h>
#include "Str.h"
#include "DirFile.h"

#include <iostream>
//#include <regex>
//#include <ranges>
//#include <algorithm>
//#include <filesystem>

using namespace std;
//namespace fs = std::filesystem;

#if 0
//#pragma comment (lib, "Normaliz.lib")
//#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Wldap32.lib")
//#pragma comment (lib, "advapi32.lib")
//#pragma comment (lib, "Crypt32.lib")

// Callback function to write response contents to string.
// Parameters:
//    buffer: pointer to the received data
//    size: size of the memory block pointed to by 'buffer'
//    nmemb: number of memory blocks (usually 1)
//    param: pointer to the string to store result in
// Returns:
//    the total number of bytes written
size_t Tau_Curl::WriteCallback(void* buffer, size_t size, size_t nmemb, void* param)
{
    size_t totalsize = size * nmemb;
    std::string* text = static_cast<std::string*>(param);
    text->append(static_cast<char*>(buffer), totalsize);
    return totalsize;
}

// Reads a URL and returns its contents as a string
// Parameters:
//    url: the URL to read
// Returns:
//    a string containing the contents of the URL
std::string Tau_Curl::ReadURL(const std::string& url)
{
    std::string result;
    CURL* curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (res != CURLE_OK) {
            std::cerr << "CURL error: " << curl_easy_strerror(res) << '\n';
        }
    }
    curl_global_cleanup();
    return result;
}
#endif

