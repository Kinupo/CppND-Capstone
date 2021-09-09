#ifndef _PROFILE_PROFILE_LOADER_H_
#define _PROFILE_PROFILE_LOADER_H_

#include <memory>
#include <vector>
#include <string>

#include "file_reader/file_reader.h"
#include "profile/profile.h"

namespace ProfileLoader{

    std::unique_ptr<Profile> LoadProfile(std::string profile_name);
    std::unique_ptr<ConnectionProfile> MapConnectionProfile(
        std::string profile_line);

    std::string FindProfileFileName(std::string profile_name);

    std::vector<std::unique_ptr<std::vector<std::string>>> LoadProfileList();
    
    std::unique_ptr<std::vector<std::string>> ParseProfilesRow(std::string line);
}

#endif