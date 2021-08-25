#include <memory>
#include <string>

#include "configuration/ncurses_engine_config.h"
#include "profile/profile_loader.h"

void LoadProfile(){}
void RunConnetionTest(){}


std::string ReadMenuSelection(WindowRepository& window_repository){
    auto menu_window = window_repository.WindowByName<MenuWindow>("menue");
    return menu_window->Selected();
}

int main() {

  bool should_quit = false;

  auto window_repository = NcursesEngineConfiguration::GenerateWindowRepository();
  auto ncurses_engine = NcursesEngineConfiguration::GenerateConectionTestEngine(*window_repository);

  while (!should_quit) {
    
    ncurses_engine->Draw();
    ncurses_engine->ProcessInput();

    auto menu_selection = ReadMenuSelection(*window_repository);
    if(menu_selection == "Quit")
      should_quit = true;
    else if (menu_selection == "Load"){
      auto profile_window = window_repository->WindowByName<TableWindow>("File Selector");
      // auto profile_window = std::dynamic_pointer_cast<TableWindow>(window);
      profile_window->Show();
      auto rows = ProfileLoader::LoadProfileList();
      profile_window->TableData(std::move(rows));

      window_repository->WindowByName("Connection Table")->Hide();
    }

    //handle menu selection
    //handle profile load
    //event store
    //event dispatcher
    //protocols
    //connections
  }

  return 0;
}