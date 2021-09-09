#include "configuration/windows_configuration.h"

std::unique_ptr<Window> WindowsConfiguration::BuildMenu(__attribute__((unused)) WindowRepository& window_repository){
    std::vector<std::string> menu_options{"Load", "Quit"};
    auto menu_window = std::make_unique<MenuWindow>("menu", 0, 3, menu_options);
    menu_window->Show();
    return menu_window;
}

std::unique_ptr<Window> WindowsConfiguration::BuildNotificationWindow(__attribute__((unused)) WindowRepository& window_repository){
    auto notification_window = std::make_unique<NotificationWindow>("Notification");
    notification_window->Show();
    return notification_window;
}

std::unique_ptr<Window> WindowsConfiguration::BuildConnectionsWindow(WindowRepository& window_repository){

    auto connection_window = std::make_unique<TableWindow>(
        "Connection Table",
        0,//fill remaining screen 
        0,//fill remaining screen
        //put the window to the right of menu and below notification
        window_repository.WindowByName("menu")->Width() +1,
        window_repository.WindowByName("Notification")->Height() +1);

    connection_window->Title("Connections");
    
    auto connection_columns = std::vector<std::unique_ptr<Column>>();
    connection_columns.emplace_back(std::move(
        std::unique_ptr<Column>(new Column{"Name", 0, 25})));
    connection_columns.emplace_back(std::move(
        std::unique_ptr<Column>(new Column{"Protocol", 0, 10})));
    connection_columns.emplace_back(std::move(
        std::unique_ptr<Column>(new Column{"Status", 0, 20})));
    connection_columns.emplace_back(std::move(
        std::unique_ptr<Column>(new Column{"Latency (ms)", 0, 14})));
    
    connection_window->Columns(std::move(connection_columns));

    return connection_window;
}

std::unique_ptr<Window> WindowsConfiguration::BuildProfilesWindow(WindowRepository& window_repository){

    auto file_selection_window = std::make_unique<TableWindow>(
        "File Selector",
        0,//fill remaining screen 
        0,//fill remaining screen
        //put the window to the right of menu and below notification
        window_repository.WindowByName("menu")->Width() +1,
        window_repository.WindowByName("Notification")->Height() +1);
    
    file_selection_window->Title("Profiles");
    auto columns = std::vector<std::unique_ptr<Column>>();
    columns.emplace_back(std::move(
        std::unique_ptr<Column>(new Column{"Select Profile", 0, 30})));
    file_selection_window->Columns(std::move(columns));

    return file_selection_window;
}

std::unique_ptr<NcursesEngineConfiguration::WindowFactoryDeffinition> WindowsConfiguration::BuildDeffinition(
    std::function<std::unique_ptr<Window> (WindowRepository &)> factory,
    std:: string name){
    auto factory_deffinition = std::make_unique<NcursesEngineConfiguration::WindowFactoryDeffinition>();
    factory_deffinition->factory = factory;
    factory_deffinition->name = name;
    return factory_deffinition;
}

std::vector<std::unique_ptr<NcursesEngineConfiguration::WindowFactoryDeffinition>> 
        WindowsConfiguration::ConnectionTesterWindowFactoryDeffinitions(){
    auto factory_deffinitions = std::vector<std::unique_ptr<NcursesEngineConfiguration::WindowFactoryDeffinition>>();
   
    factory_deffinitions.emplace_back(std::move(BuildDeffinition(&BuildProfilesWindow, "File Selector")));
    factory_deffinitions.emplace_back(std::move(BuildDeffinition(&BuildConnectionsWindow, "Connection Table")));
    factory_deffinitions.emplace_back(std::move(BuildDeffinition(&BuildMenu, "menu")));
    factory_deffinitions.emplace_back(std::move(BuildDeffinition(&BuildNotificationWindow, "Notification")));

    return factory_deffinitions;
}