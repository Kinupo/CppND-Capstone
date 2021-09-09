#ifndef _USER_INTERFACE_NCURSES_ENGINE_H_
#define _USER_INTERFACE_NCURSES_ENGINE_H_

#include <vector>
#include <memory>

#include <curses.h>

#include "user_interface/window.h"

class NcursesEngine {
    private:
        void InitilizeNcurses();
        std::vector<std::shared_ptr<Window>> _windows;
        WINDOW * _input_window;
    public:
        NcursesEngine();
        ~NcursesEngine();
        
        void AddWindow(std::shared_ptr<Window> window);
        void AddWindows(std::vector<std::shared_ptr<Window>> windows);

        void Draw();

        void ProcessInput();
        // void SetInputWindow(std::shared_ptr<Window> window);
};

#endif