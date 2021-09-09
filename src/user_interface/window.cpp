#include "user_interface/window.h"

Window::Window(std::string name):_name(name){};
Window::Window(std::string name, int x_pos, int y_pos, int max_cols, int max_rows)
:_name(name), _x_pos(x_pos), _y_pos(y_pos), _max_cols(max_cols), _max_rows(max_rows){}

std::string Window::Name(){return _name;}



void Window::Show(){
    if(!_is_visable)
        _clear_next_draw = true;
    _is_visable = true;
}

void Window::Hide(){_is_visable = false;}

void Window::Draw(){
    if(!_is_visable)
        return;
    if(_clear_next_draw)
        ClearWindow();
    if(_was_touched)
        ForceDraw();
}

bool Window::IsVisable(){return _is_visable;}
bool Window::WasTouched(){return _was_touched;}

int Window::Width(){
    return _window->_maxx;
}

int Window::Height(){
    return _window->_maxy;
}

void Window::ClearWindow(){
    wclear(_window);
}