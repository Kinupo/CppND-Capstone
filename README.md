# CPPND: Capstone Terminal Connection Tester

Tests connectivity to TCP destinations.  The API is extensible to support additional protocols, or custom requirements for the same protocol such as doing a health check on a HTTP site.

## Dependencies for Running Locally
* cmake >= 3.16
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.2 (Linux, Mac)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 10.3
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* ncurses 6.2
  * default on Ubuntu 20.04 after update
  * Linux additional help [https://stackoverflow.com/questions/4678926/cmake-cant-find-curses](https://stackoverflow.com/questions/4678926/cmake-cant-find-curses)
* boost 1.71
  * default on Ubuntu 20.04 after update
  * Detailed instructions [https://onethinglab.com/2019/01/30/how-to-install-latest-boost-library-on-ubuntu/](https://onethinglab.com/2019/01/30/how-to-install-latest-boost-library-on-ubuntu/)
  * Linux [https://www.boost.org/doc/libs/1_77_0/more/getting_started/unix-variants.html](https://www.boost.org/doc/libs/1_77_0/more/getting_started/unix-variants.html)
  * windows: [https://www.boost.org/doc/libs/1_77_0/more/getting_started/windows.html](https://www.boost.org/doc/libs/1_77_0/more/getting_started/windows.html)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `(cd .. && make build)`

## Configuration

1. profiles  
  a. Add a line to the profiles file with the format `profile name`,`profile file name`  
  b. Create profile file with the file name  
  c. Add test configuration line with the format `Display name`,`Host:port`,`Protocol (TCP is the only one supported)`

## Execution Instructions

1. Run `./capstone`.  
2. Click Load from the main menu. *If there is no response when clicking turn on num lock and try again
![main menu](/readme/main_menu.png?raw=true "Main Menu")  
3. Click on the profile to load.  
![Profile selection](/readme/profile_selection.png?raw=true "Profile Selection")  
The test will start immediately.  
![Test Start](/readme/test_start.png?raw=true "Test Start")  
4. Click Load to go back to the profile selection menu.  
![Test Complete](/readme/test_complete.png?raw=true "Test Complete")  
5. Click Quit to exit or send a break command `CTRL+C`  

## Program Flow  
![Program Flow](/readme/program_flow.png?raw=true "Program Flow")  

## Dependency Graph
![Dependency Graph](/readme/dependency_graph.png?raw=true "Dependency Graph")  

## Grading Rubric

### Loops, Functions, I/O
src/file_reader/file_reader.cpp  
src/profile/profile_loader.cpp FindProfileFileName LoadProfile  

### Object Oriented Programming
include/connection_tester/connection.h  
src/connection_tester/connection.cpp  
include/user_interface/window_repository.h
src/user_interface/window_repository.cpp

### Memory Management
src/user_interface/window_repository.cpp  

### Concurrency
src/connection_tester/connection.cpp  TestConnection  
src/connection_tester/protocols/tcp.cpp TestConnection
