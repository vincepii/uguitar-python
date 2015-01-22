#ifndef UG_CPP_H
#define UG_CPP_H

#include <string>
#include <vector>
#include <boost/python.hpp>

namespace ug {

static const boost::python::str MODULE_NAME = "uguitar.ug_simplesearch";
static const boost::python::str FUNCTION_NAME = "search";

struct TabDescriptor {
    std::string _artist;
    std::string _title;
    std::string _uri;
    std::string _rating;
    std::string _ratingCounter;
    std::string _type;
    bool _isPlus;

    friend std::ostream& operator<<(std::ostream& os, const TabDescriptor& desc);
};

class UgWrapper {

    boost::python::object _pyModule;
    boost::python::object _pyFunc;

public:
    UgWrapper();
    ~UgWrapper();

    std::vector<TabDescriptor> searchTabs(std::string searchArgument);
};

} // end of namespace ug

#endif
