#ifndef _USER_INTERFACE_WINDOW_REPOSITORY_H_
#define _USER_INTERFACE_WINDOW_REPOSITORY_H_

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <functional>

#include "user_interface/window.h"

class WindowRepository{
    private:
        std::map<std::string, std::shared_ptr<Window>> _windows_map;
        std::map<std::string, std::function
            <std::unique_ptr<Window>(WindowRepository&)>> _window_factories;
    public:
        WindowRepository();

        //Regester a factory for generating windows of type name.  Function must return unique 
        //pointer of type Window and accept a WindowRepository parameter.
        //The WindowRepository parameter allows the factory to refrence other windows for 
        //relitive positioning.
        void RegisterFactory(
            std::string name,
            std::function<std::unique_ptr<Window>(WindowRepository&)> factory);

        void AddWindow(std::unique_ptr<Window> window);
        void AddWindows(std::vector<std::unique_ptr<Window>> windows);

        //Finds a window by name.  If it is not present it will try to build the window if the 
        //factory method is registered.  This can result in a cycle if two windows refer to each other.
        template<class T>
        std::shared_ptr<T> WindowByName(std::string name);
        std::shared_ptr<Window> WindowByName(std::string name);
};

//Needs to be in the header for refrence outside of this class
template<class T>
std::shared_ptr<T> WindowRepository::WindowByName(std::string name){
	if(_windows_map.find(name) == _windows_map.end())
		AddWindow(_window_factories[name](*this));
	return std::dynamic_pointer_cast<T>(_windows_map[name]);
}

#endif