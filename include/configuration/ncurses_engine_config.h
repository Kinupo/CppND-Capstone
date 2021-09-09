#ifndef _CONFIGURATION_NCURSES_ENGINE_CONFIG_H_
#define _CONFIGURATION_NCURSES_ENGINE_CONFIG_H_

#include <vector>
#include <memory>

#include "user_interface/ncurses_engine.h"
#include "user_interface/window_repository.h"

namespace NcursesEngineConfiguration{

    struct WindowFactoryDeffinition{
        std::string name;
        std::function<std::unique_ptr<Window>(WindowRepository&)> factory;
    };

    std::unique_ptr<WindowRepository> GenerateWindowRepository(
        std::vector<std::unique_ptr<NcursesEngineConfiguration::WindowFactoryDeffinition>> deffintions);
    std::unique_ptr<NcursesEngine> GenerateConectionTestEngine(
        WindowRepository& window_repository,
        std::shared_ptr<std::vector<std::string>> window_names);

};

#endif