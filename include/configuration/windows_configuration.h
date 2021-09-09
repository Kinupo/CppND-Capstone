#ifndef _CONFIGURATION_WINDOWS_CONFOGIRATION_H_
#define _CONFIGURATION_WINDOWS_CONFOGIRATION_H_

#include <memory>
#include <vector>

#include "user_interface/window.h"
#include "user_interface/windows/menu_window.h"
#include "user_interface/windows/notification_window.h"
#include "user_interface/windows/table_window.h"

#include "configuration/ncurses_engine_config.h"

namespace WindowsConfiguration{

    std::unique_ptr<Window> BuildMenu(__attribute__((unused)) WindowRepository& window_repository);
    std::unique_ptr<Window> BuildNotificationWindow(__attribute__((unused)) WindowRepository& window_repository);
    std::unique_ptr<Window> BuildConnectionsWindow(WindowRepository& window_repository);
    std::unique_ptr<Window> BuildProfilesWindow(WindowRepository& window_repository);

    std::vector<std::unique_ptr<NcursesEngineConfiguration::WindowFactoryDeffinition>> 
        ConnectionTesterWindowFactoryDeffinitions();
    std::unique_ptr<NcursesEngineConfiguration::WindowFactoryDeffinition> BuildDeffinition(
        std::function<std::unique_ptr<Window> (WindowRepository &)> factory,
        std:: string name);
}

#endif