#ifndef _USER_INTERFACE_WINDOW_H_
#define _USER_INTERFACE_WINDOW_H_

#include <string>

#include <ncurses.h>

class Window {
    protected:
        std::string _name;

        int _max_cols;
        int _max_rows;

        int _x_pos;
        int _y_pos;

        bool _was_touched = true;
        bool _clear_next_draw = true;
        
        void virtual ClearWindow();
        //Draw ignorning if touched.  This method should set was touched to false.
        void virtual ForceDraw() = 0;

        WINDOW * _window;
    private:
        bool _is_visable = false;
    public:
        Window(std::string name);
        Window(std::string name, int x_pos, int y_pos, int max_cols, int max_rows);

        std::string Name();

        //Draw if touched
        void Draw();
        
        void Show();
        void Hide();

        bool IsVisable();
        bool WasTouched();
        
        int Height();
        int Width();

        //retun true if mouse click was in the window
        bool virtual ProcessClick(MEVENT& mouse_event) = 0;
};

#endif