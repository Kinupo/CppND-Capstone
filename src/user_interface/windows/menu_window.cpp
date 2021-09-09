#include "user_interface/windows/menu_window.h"

int MaxStringLenght(std::vector<std::string> options){
    int max_string_length = 0;
    for(auto option:options){
        max_string_length = max_string_length >= option.length() 
            ? max_string_length
            : option.length();
    }
    return max_string_length;
}

MenuWindow::MenuWindow(std::string name, int x_pos, int y_pos, std::vector<std::string> options)
        : Window(name, x_pos, y_pos, MaxStringLenght(options) +4, options.size() +2),
        _menu_options(options)
{
    _window = newwin(_max_rows, _max_cols, _y_pos, _x_pos);
}

MenuWindow::~MenuWindow(){}

void MenuWindow::ClearWindow(){}

void MenuWindow::ForceDraw(){
    clrtoeol();
    
    int max_options_to_display = _menu_options.size() > _max_rows ? _max_rows: _menu_options.size();
    for(int row = 1;row <= max_options_to_display; row++)
        mvwprintw(_window, row, 2, _menu_options.at(row-1).c_str());
    
    box(_window, 0, 0);
	wnoutrefresh(_window);

    _was_touched = false;
}

std::string MenuWindow::Selected(){
    auto current_selected = _selected;
    _selected = "";
    return current_selected;
}

bool MenuWindow::ProcessClick(MEVENT& mouse_event){
    
    if(mouse_event.bstate & (BUTTON1_CLICKED | BUTTON1_PRESSED | BUTTON1_RELEASED)){

        auto x_mouse_position = mouse_event.x + 1;
        auto y_mouse_position = mouse_event.y + 1;

        if(y_mouse_position > (_y_pos +1) 
            && y_mouse_position < (_max_rows + _y_pos)
            && x_mouse_position > (_x_pos +1) 
            && x_mouse_position < (_max_cols + _x_pos)){
            _selected = _menu_options.at(y_mouse_position -_y_pos -2);
            return true;
        } else {
            _selected = "";
        }
    }
    return false;
}


