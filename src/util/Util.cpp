#include "Util.h"
#include <fstream>


char* Util::resourceToChar(const std::string &resource) {
    std::ifstream infile(resource.c_str());
    infile.seekg(0, infile.end);
    size_t length = infile.tellg();
    infile.seekg(0, infile.beg);
    char* stream = new char[length + 1];
    infile.read(stream, length);
    stream[length] = '\0';
    return stream;
}
