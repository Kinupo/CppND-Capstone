    #include "configuration/ncurses_engine_config.h"
    
std::unique_ptr<WindowRepository> NcursesEngineConfiguration::GenerateWindowRepository(
    std::vector<std::unique_ptr<NcursesEngineConfiguration::WindowFactoryDeffinition>> deffinitions){
    
    auto window_repository = std::make_unique<WindowRepository>();
    for(auto& deffinition:deffinitions)
        window_repository->RegisterFactory(deffinition->name, deffinition->factory);

    return window_repository;
}

/*Only call this once.  It configures ncurses which is a global configuration.*/
std::unique_ptr<NcursesEngine> NcursesEngineConfiguration::GenerateConectionTestEngine(
    WindowRepository& window_repository,
    std::shared_ptr<std::vector<std::string>> window_names){
    
    auto ncurses_engine = std::make_unique<NcursesEngine>();
    for(auto window_name:*window_names)
        ncurses_engine->AddWindow(window_repository.WindowByName(window_name));

    return ncurses_engine;
}