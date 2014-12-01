// Requires python-dev library
// Compile with 
// g++ ug_cpp.cpp -lpython2.7 -Wall example.cpp -g
// Make sure that the python project directory is in the PYTHONPATH
// export PYTHONPATH=<path>/<to>/uguitar-python:$PYTHONPATH

#include <python2.7/Python.h>
#include <iostream>

#include "ug_cpp.h"

int main(int argc, char *argv[]) {
    ug::UgWrapper ug;
    std::vector<ug::TabDescriptor> tabs = ug.searchTabs("metallica one");
    for (unsigned int i = 0; i < tabs.size(); ++i) {
        std::cout << "Result " << i + 1 << std::endl;
        std::cout << tabs[i] << std::endl;
        // or just access tabs[i]._uri, tabs[i]._rating ...
    }
}
