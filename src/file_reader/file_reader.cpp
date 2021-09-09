#include "file_reader/file_reader.h"

std::unique_ptr<std::vector<std::string>> FileReader::ReadAllLines(const std::string file_name){
    
  std::unique_ptr<std::vector<std::string>> lines(new std::vector<std::string>);

  std::ifstream in_file(file_name);
  if(!in_file.is_open())
    throw std::runtime_error(file_name + " could not be oppened by FileReader");

  std::string line;
  while(std::getline(in_file, line))
    lines.get()->push_back(line);
  in_file.close();
  
  return lines;
}

 std::unique_ptr<std::map<std::string, std::string>> FileReader::ReadLines(
                const std::string file_name,
                const std::vector<std::string> keys){
    
    std::ifstream in_file(file_name);
    if(!in_file.is_open())
      throw std::runtime_error(file_name + " could not be oppened by FileReader");

    auto results = std::make_unique<std::map<std::string, std::string>>();

    std::string line;    
    while(std::getline(in_file, line)){
      for(auto key:keys)
        if(std::string::npos != line.find(key))
          (*results)[key] = line;
    }
    
    in_file.close();
    return results;
}
