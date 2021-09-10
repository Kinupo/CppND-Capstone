#include "user_interface/windows/notification_window.h"

NotificationWindow::NotificationWindow(std::string name) : Window(name){
    _window = newwin(3,0, 0,0);
}
NotificationWindow::~NotificationWindow(){}

void NotificationWindow::ClearWindow(){};

void NotificationWindow::ForceDraw(){

    std::string message;
    int max_lenght =(Width() -2);
    if( _message.size() > max_lenght)
        message = _message.substr(0, max_lenght);
    else
        message = _message;
    mvwprintw(_window, 1, 1, message.c_str());
    wclrtoeol(_window);

    box(_window, 0, 0);
	wnoutrefresh(_window);

    _was_touched = false;
}

void NotificationWindow::DisplayMessage(std::string message){
    _message = message;
    _was_touched = true;
}

//TODO: check if click was on window, clear message if clicked
bool NotificationWindow::ProcessClick(MEVENT& mouse_event){return false;}