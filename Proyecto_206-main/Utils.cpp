#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream stream(s);
    std::string token;

    while (std::getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

std::time_t parsearFecha(std::string &strFecha)
    {
        std::tm tmFecha = {};
        std::istringstream stream(strFecha);
        stream >> std::get_time(&tmFecha, "%Y-%m-%d");
        std::time_t tiempo = std::mktime(&tmFecha);
        return tiempo;
    }