#ifndef _USER_INTERFACE_WINDOWS_MENU_WINDOW_H_
#define _USER_INTERFACE_WINDOWS_MENU_WINDOW_H_

#include <string>
#include <vector>

#include <ncurses.h>

#include "user_interface/window.h"

class MenuWindow : public Window {
    private:        
        std::string _selected = "";
        std::vector<std::string> _menu_options;

        bool WasTouched();
        
    public:
        MenuWindow(std::string name, int x_pos, int y_pos, std::vector<std::string> options);
        ~MenuWindow();

        void ForceDraw();
        void ClearWindow();

        std::string Selected();

        bool ProcessClick(MEVENT& mouse_event);
}; 

#endif