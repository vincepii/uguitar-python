#ifndef UG_CPP_H
#define UG_CPP_H

#include <string>
#include <vector>
#include <python2.7/Python.h>

namespace ug {

static const std::string MODULE_NAME = "uguitar.ug_simplesearch";
static const std::string FUNCTION_NAME = "search";

struct TabDescriptor {
    std::string _uri;
    std::string _rating;
    std::string _ratingCounter;
    std::string _type;
    std::string _isPlus;

    friend std::ostream& operator<<(std::ostream& os, const TabDescriptor& desc);
};

class UgWrapper {

    PyObject *_pyModule;
    PyObject *_pyFunc;

public:
    UgWrapper();
    ~UgWrapper();

    std::vector<TabDescriptor> searchTabs(std::string searchArgument);
};

} // end of namespace ug

#endif
