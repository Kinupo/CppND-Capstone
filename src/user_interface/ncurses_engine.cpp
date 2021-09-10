#include "user_interface/ncurses_engine.h"

void NcursesEngine::InitilizeNcurses(){

	initscr();
	clear();
	noecho();
	cbreak();//no buffer
 	curs_set(0);//hide cursor
	
	/* Get all the mouse events */
	mousemask(ALL_MOUSE_EVENTS, NULL);
}

NcursesEngine::NcursesEngine() {
    InitilizeNcurses();
	_input_window = newwin(1,1,80,0);
	    //enable mouse clicks to report correct position
    keypad(_input_window, TRUE); 
}

NcursesEngine::~NcursesEngine() {
	endwin();
}

void NcursesEngine::Draw(){
	for(auto& window:_windows)
		if(window->IsVisable())
			window->Draw();
}

void NcursesEngine::AddWindows(std::vector<std::shared_ptr<Window>> windows){
	for(auto& window:windows)
		AddWindow(std::move(window));
}

void NcursesEngine::AddWindow(std::shared_ptr<Window> window){
	_windows.emplace_back(window);
}

void NcursesEngine::ProcessInput(){
	
	//sends all input to this window. can be an issue if you want to echo to another window
	//TODO: make input window selectable for keybord entry
	wmove(_input_window, 0,0);

	MEVENT mouse_event;

	//delay by 100ms, if no input rgetch returns ERR.
	//This alows the display update loop to keep updaiting while waiting on input.
    halfdelay(15);
    
	auto click = wgetch(_input_window);
    if(click == KEY_MOUSE && getmouse(&mouse_event) == OK){
		//todo:sort by z index and end on first success. FIX: a window is returning true when it should not
		for(auto window:_windows)
			if(window->ProcessClick(mouse_event))
				// break;
				;
	}
}