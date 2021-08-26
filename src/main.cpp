#include <memory>
#include <string>

#include "configuration/ncurses_engine_config.h"
#include "profile/profile_loader.h"
#include "configuration/windows_configuration.h"

void RunConnetionTest(){}

int main() {

  bool should_quit = false;
  auto window_names = std::shared_ptr<std::vector<std::string>>(new std::vector<std::string>
    {"Connection Table", "File Selector", "menue", "Notification"});

  auto window_repository = NcursesEngineConfiguration::GenerateWindowRepository(
    WindowsConfiguration::ConnectionTesterWindowFactoryDeffinitions());
  auto ncurses_engine = NcursesEngineConfiguration::GenerateConectionTestEngine(
    *window_repository, 
    window_names);

  while (!should_quit) {
    
    ncurses_engine->Draw();
    ncurses_engine->ProcessInput();

    auto menu_selection = window_repository->WindowByName<MenuWindow>("menue")->Selected();
    if(menu_selection == "Quit")
      should_quit = true;
    else if (menu_selection == "Load"){
      //Load Profiles into the profile selction window
      auto profile_window = window_repository->WindowByName<TableWindow>("File Selector");
      profile_window->TableData(std::move(ProfileLoader::LoadProfileList()));

      //display profile loader, hide connection table (they share the same screen space)
      profile_window->Show();
      window_repository->WindowByName("Connection Table")->Hide();
    } else if(window_repository->WindowByName("File Selector")->IsVisable()){
      auto table_selection = window_repository->WindowByName<TableWindow>("File Selector")->Selected();
      //  auto notification_window = window_repository->WindowByName<NotificationWindow>("Notification");
      // notification_window->DisplayMessage("Not selected");
      if(table_selection.size() != 0){
        auto profile = ProfileLoader::LoadProfile(table_selection.at(0));
        // notification_window->DisplayMessage();
        window_repository->WindowByName("File Selector")->Hide();
        window_repository->WindowByName("Connection Table")->Show();
      }
    }
 
    //event store
    //event dispatcher
    //protocols
    //connections
  }

  return 0;
}