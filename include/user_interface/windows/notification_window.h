#ifndef _USER_INTERFACE_WINDOWS_NOTIFICATION_WINDOW_H_
#define _USER_INTERFACE_WINDOWS_NOTIFICATION_WINDOW_H_

#include <string>

#include "user_interface/window.h"

class NotificationWindow : public Window {
    private:
        std::string _message = "";
    public:
        NotificationWindow(std::string name);
        ~NotificationWindow();
        
        void ClearWindow();
        void ForceDraw();

        void DisplayMessage(std::string message);

        bool ProcessClick(MEVENT& mouse_event);
}; 

#endif