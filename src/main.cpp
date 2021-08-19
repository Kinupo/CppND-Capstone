#include <memory>
#include <string>

#include "user_interface/ncurses_engine.h"
#include "user_interface/windows/menu_window.h"
#include "user_interface/windows/notification_window.h"
#include "user_interface/windows/table_window.h"

int main() {

  std::vector<std::string> menu_options{"Load", "Quit"};

  NcursesEngine ncurses_engine;
  NotificationWindow notification_window;
  MenuWindow menu_window(0, 3, menu_options);
  TableWindow connection_window(
    0,//fill remaining screen 
    0,//fill remaining screen
    menu_window.Width() +1, 
    notification_window.Height() + 1);

  TableWindow file_selection_window(
    0,//fill remaining screen 
    0,//fill remaining screen
    menu_window.Width() +1, 
    notification_window.Height() + 1);

  notification_window.Draw(COLS, LINES);
  menu_window.Draw(COLS, LINES);
  connection_window.Draw();
  while (1) {

    
    notification_window.DisplayMessage(menu_window.Selected());
    // notification_window.DisplayMessage(std::to_string(notification_window.Height()));
    notification_window.Draw(COLS, LINES);
    menu_window.ProcessClick();
  }

  endwin();
  return 0;
}