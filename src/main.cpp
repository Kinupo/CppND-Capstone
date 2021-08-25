#include <memory>
#include <string>

#include "configuration/ncurses_engine_config.h"

void LoadProfile(){}
void RunConnetionTest(){}

std::vector<std::unique_ptr<Row>> LoadProfileList(){
  auto rows = std::vector<std::unique_ptr<Row>>();
  auto row = std::unique_ptr<Row>(new Row());
  row->data.emplace_back("Profile 1");
  rows.emplace_back(std::move(row));
  return rows;
}

int main() {

  bool should_quit = false;
  
  auto window_repository = NcursesEngineConfiguration::GenerateWindowRepository();
  auto ncurses_engine = NcursesEngineConfiguration::GenerateConectionTestEngine(*window_repository);

  ncurses_engine->Draw();
  while (!should_quit) {
    
    ncurses_engine->Draw();
    ncurses_engine->ProcessInput();

    auto window = window_repository->WindowByName("menue");
    auto menu_window = std::dynamic_pointer_cast<MenuWindow>(window);
    auto menu_selection = menu_window->Selected();
    if(menu_selection == "Quit")
      should_quit = true;
    else if (menu_selection == "Load"){
      auto window = window_repository->WindowByName("File Selector");
      auto profile_window = std::dynamic_pointer_cast<TableWindow>(window);
      profile_window->Show();
      auto rows = LoadProfileList();
      profile_window->TableData(std::move(rows));

      window_repository->WindowByName("Connection Table")->Hide();
    }

    //handle menu selection
    //handle profile load
  }

  return 0;
}