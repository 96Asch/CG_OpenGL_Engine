#include "Util.h"
#include <fstream>


char* Util::resourceToChar(const std::string &resource) {
    std::ifstream infile(resource.c_str());
    if(!infile) {
        fprintf(stderr, "Resource at: %s could not be read\n", resource.c_str());
        exit(-1);
    }
    infile.seekg(0, infile.end);
    size_t length = infile.tellg();
    infile.seekg(0, infile.beg);
    char* stream = new char[length + 1];
    infile.read(stream, length);
    stream[length] = '\0';
    return stream;
}

std::string Util::resourceToString(const std::string &resource) {
    std::string shader = "";
    try {
		std::streamoff size;
		std::ifstream file(resource.c_str());
		if (!file.is_open())
		{
			throw(std::runtime_error("Unable to open the file."));
		}
		file.seekg(0, std::ios::end);
		size = file.tellg();
		file.seekg(0, std::ios::beg);
		size -= file.tellg();
		shader.resize((size_t)size, '\0');
		file.read(&shader[0], size);
		file.close();
	}
	catch(std::exception & e) {
		fprintf(stderr, "ERROR READING FILE: %s ,%s\n",resource.c_str(), e.what());
        exit(-1);
    }
    return shader;
}

size_t Util::split(const std::string &string,
                   const char &delimiter,
                   std::vector<std::string> &list) {
    size_t current = 0;
    size_t next = string.find(delimiter);
    list.clear();

    while(next != std::string::npos) {
        list.push_back(string.substr(current, next - current));
        current = next + 1;
        next = string.find(delimiter, current);
    }

    list.push_back(string.substr(current,
                                 std::min(next, string.size()) - current + 1));
    return list.size();
}
