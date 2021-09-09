#ifndef _FILE_READER_FILE_READER_H_
#define _FILE_READER_FILE_READER_H_

#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
#include <map>

namespace FileReader {
        //read all lines in a file into an array
        std::unique_ptr<std::vector<std::string>> ReadAllLines(const std::string file_name);

        //returns lines containing the keys in a map with the original key and value of the line where the key was found
        //only the first line is where the key is found is returned
        std::unique_ptr<std::map<std::string, std::string>> ReadLines(
                const std::string file_name,
                const std::vector<std::string> keys);

};

#endif