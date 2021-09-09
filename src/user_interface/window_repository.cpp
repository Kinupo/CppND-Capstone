#include "user_interface/window_repository.h"

WindowRepository::WindowRepository(){}

void WindowRepository::AddWindows(std::vector<std::unique_ptr<Window>> windows){
	for(auto& window:windows)
		AddWindow(std::move(window));
}

void WindowRepository::AddWindow(std::unique_ptr<Window> window){
	std::shared_ptr<Window> shared_window = std::move(window);
	_windows_map[shared_window->Name()] = shared_window;
}

std::shared_ptr<Window> WindowRepository::WindowByName(std::string name){
	if(_windows_map.find(name) == _windows_map.end())
		AddWindow(_window_factories[name](*this));
	return _windows_map[name];
}

void WindowRepository::RegisterFactory(
	std::string name,
	std::function<std::unique_ptr<Window>(WindowRepository&)> factory){
		_window_factories[name] = factory;
}
