#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdexcept>

int get_cache_index(const std::string &key, int num_caches) {
    std::hash<std::string> hasher;
    return hasher(key) % num_caches;
}

std::string request_from_main_db(const std::string &db_url, const std::string &key) {
    httplib::Client cli(db_url.c_str());
    auto res = cli.Get(("/" + key).c_str());
    if (!res || res->status != 200) {
        throw std::runtime_error("Failed to get value from main DB");
    }
    return res->body;
}

std::string request_from_cache(const std::string &cache_url, const std::string &key) {
    httplib::Client cli(cache_url.c_str());
    auto res = cli.Get(("/" + key).c_str());
    if (!res || res->status == 502) {
        throw std::runtime_error("Cache unavailable");
    }
    return res->body;
}

void write_to_cache(const std::string &cache_url, const std::string &key, const std::string &value) {
    httplib::Client cli(cache_url.c_str());
    httplib::Params params;
    params.emplace("value", value);
    cli.Post(("/" + key).c_str(), params);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    std::ifstream config_file(argv[1]);
    if (!config_file.is_open()) {
        std::cerr << "Failed to open config file" << std::endl;
        return 1;
    }

    std::string db_url;
    int num_caches;
    config_file >> db_url >> num_caches;

    db_url += "/db/";

    std::string cache_base_url = "http://localhost:80/cache/";

    std::unordered_map<std::string, std::string> cache_map;

    std::string key;
    while (std::cin >> key) {
        try {
            int cache_index = get_cache_index(key, num_caches);
            std::string cache_url = cache_base_url + std::to_string(cache_index + 1);
            std::string value = request_from_cache(cache_url, key);
            std::cout << value << std::endl;
        } catch (...) {
            std::string value = request_from_main_db(db_url, key);
            std::cout << value << std::endl;

            int cache_index = get_cache_index(key, num_caches);
            std::string cache_url = cache_base_url + std::to_string(cache_index + 1);
            try {
                write_to_cache(cache_url, key, value);
            } catch (...) {
            }
        }
    }

    return 0;
}
