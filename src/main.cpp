#include <memory>
#include <string>

#include "configuration/connection_tester_configuration.h"
#include "connection_tester/connection_tester.h"

#include "profile/profile_loader.h"
//load ncurses dependent includes after connection tester due to issues with boost
#include "configuration/windows_configuration.h"
#include "configuration/ncurses_engine_config.h"

void FileSelectorHandler(WindowRepository &window_repository, ConnectionTester &connection_tester){

      auto table_selection = window_repository.WindowByName<TableWindow>("File Selector")->Selected();
      if(table_selection.size() != 0){
        
        auto connection_profiles = ProfileLoader::LoadProfile(table_selection.at(0));
        window_repository.WindowByName("File Selector")->Hide();
        window_repository.WindowByName("Connection Table")->Show();

        std::vector<std::unique_ptr<Connection>> connections;
        for(auto &profile:connection_profiles->connections)
          connections.emplace_back(std::move(connection_tester.MakeConnection(
            profile->name, 
            profile->address, 
            profile->protocal)));
        
        connection_tester.TestConnections(std::move(connections));
      }
}

std::vector<std::unique_ptr<std::vector<std::string>>> FindUpdatedTestStatus(ConnectionTester &connection_tester){
  
      auto connection_test_status = connection_tester.Status();
      std::vector<std::unique_ptr<std::vector<std::string>>> connection_table_data;
      for(auto& status:*connection_test_status){
        auto status_row = std::make_unique<std::vector<std::string>>();
        status_row->emplace_back(status->name);
        status_row->emplace_back(status->protocol_name);
        status_row->emplace_back(status->status);
        status_row->emplace_back(std::to_string(status->duration_ms) + " ms");
        connection_table_data.emplace_back(std::move(status_row));
      }
      return connection_table_data;
}

bool HandleMainMenuSelection(WindowRepository &window_repository){

    auto menu_selection = window_repository.WindowByName<MenuWindow>("menu")->Selected();
    if(menu_selection == "Quit")
      return true;
    else if (menu_selection == "Load"){
      
      //Load Profiles into the profile selction window
      auto profile_window = window_repository.WindowByName<TableWindow>("File Selector");
      profile_window->TableData(std::move(ProfileLoader::LoadProfileList()));

      //display profile loader, hide connection table (they share the same screen space)
      profile_window->Show();
      window_repository.WindowByName("Connection Table")->Hide();
    }

    return false;
}

void UpdateWindowData(WindowRepository &window_repository, ConnectionTester &connection_tester){
    if(window_repository.WindowByName("File Selector")->IsVisable()){
      FileSelectorHandler(window_repository, connection_tester);
    } 
    //needs to be after File Selector handler so the connection table will update as soon
    //as the test starts
    if(window_repository.WindowByName("Connection Table")->IsVisable()){
      
      auto connection_table_data = FindUpdatedTestStatus(connection_tester);
      window_repository.WindowByName<TableWindow>("Connection Table")->TableData(std::move(connection_table_data));
      
    }
}

int main() {
  
  bool should_quit = false;
  auto window_names = std::shared_ptr<std::vector<std::string>>(new std::vector<std::string>
    {"Connection Table", "File Selector", "menu", "Notification"});

  auto window_repository = NcursesEngineConfiguration::GenerateWindowRepository(
    WindowsConfiguration::ConnectionTesterWindowFactoryDeffinitions());
  auto ncurses_engine = NcursesEngineConfiguration::GenerateConectionTestEngine(
    *window_repository, 
    window_names);

  auto connection_tester = ConnectionTesterConfiguration::GenerateConnectionTester();

  while (!should_quit) {
    try {
    ncurses_engine->Draw();
    ncurses_engine->ProcessInput();

    should_quit = HandleMainMenuSelection(*window_repository);
    UpdateWindowData(*window_repository, *connection_tester);
    } catch (const std::runtime_error& runtime_excepton){
      window_repository->WindowByName<NotificationWindow>("Notification")->
        DisplayMessage("Exception Caught: " + std::string(runtime_excepton.what()));
    } catch (const std::exception& excepton){
      window_repository->WindowByName<NotificationWindow>("Notification")->
        DisplayMessage("Exception Caught: " + std::string(excepton.what()));
    }
    //event store
    //event dispatcher
  }

  return 0;
}