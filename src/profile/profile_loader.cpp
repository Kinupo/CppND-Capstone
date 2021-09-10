    #include "profile/profile_loader.h"
    
    std::unique_ptr<std::vector<std::string>> ProfileLoader::ParseProfilesRow(std::string line){
        auto row = std::make_unique<std::vector<std::string>>();
        row->emplace_back(line.substr(0, line.find_first_of(',')));
        row->emplace_back(line.substr(line.find_first_of(',')));
        return row;
    }

    std::vector<std::unique_ptr<std::vector<std::string>>> ProfileLoader::LoadProfileList(){
        auto lines = FileReader::ReadAllLines("../profiles/profiles");

        auto rows = std::vector<std::unique_ptr<std::vector<std::string>>>();
        for(auto line:*lines){
            if(line.npos != line.find_first_of(','))
            rows.emplace_back(std::move(ParseProfilesRow(line)));
        }

        return rows;
    }

    std::string ProfileLoader::FindProfileFileName(std::string profile_name){
        auto profile_names = std::vector<std::string>();
        profile_names.emplace_back(profile_name);
        auto profile_file_names = FileReader::ReadLines("../profiles/profiles", profile_names);
        return (*profile_file_names)[profile_name]
            .substr((*profile_file_names)[profile_name].find_first_of(',') +1);
    }

    std::unique_ptr<ConnectionProfile> ProfileLoader::MapConnectionProfile(
        std::string profile_line){

            auto profile_connection = std::make_unique<ConnectionProfile>();
            
            int end_of_first_field = profile_line.find_first_of(',');
            int end_of_second_field = profile_line.find_last_of(',');
            //TODO:: check for invalid data
            profile_connection->address =
                profile_line.substr(
                    end_of_first_field +1,
                    end_of_second_field - end_of_first_field -1);
            profile_connection->name = 
                profile_line.substr(
                    0, 
                    end_of_first_field);
            profile_connection->protocal = 
                profile_line.substr(end_of_second_field +1);
            
            return profile_connection;
    }

    std::unique_ptr<Profile> ProfileLoader::LoadProfile(std::string profile_name){
        
        auto profile_file = FileReader::ReadAllLines("../profiles/" + FindProfileFileName(profile_name));
        
        auto profile = std::make_unique<Profile>();
        profile->name = profile_name;
        profile->connections = std::vector<std::unique_ptr<ConnectionProfile>>();
        for(auto line:*profile_file){
            //skip line without at least one entry
            if(line.find_first_of(',') == std::string::npos)
                continue;
            profile->connections.emplace_back(std::move(MapConnectionProfile(line)));
        }

        return profile;
    }