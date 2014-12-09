#include "ug_cpp.h"

#include <stdexcept>
#include <iostream>

namespace ug {

UgWrapper::UgWrapper() {
    Py_Initialize();

    // Get the module name
    PyObject *pName = PyString_FromString(MODULE_NAME.c_str());
    if (!pName) {
        throw std::runtime_error("Cannot create string object for module");
    }

    // Import
    _pyModule = PyImport_Import(pName);
    Py_DECREF(pName);

    // Check for import errors
    if (!_pyModule) {
        PyErr_Print();
        throw std::runtime_error("Failed to load module");
    }

    // Get the function
    _pyFunc = PyObject_GetAttrString(_pyModule, FUNCTION_NAME.c_str());
    if (!_pyFunc) {
        Py_DECREF(_pyModule);
        throw std::runtime_error("Cannot create string object for function");
    }

    if (!PyCallable_Check(_pyFunc)) {
        PyErr_Print();
        Py_DECREF(_pyFunc);
        Py_DECREF(_pyModule);
        throw std::runtime_error("Function is not callable");
    }
}

UgWrapper::~UgWrapper() {
    Py_XDECREF(_pyFunc);
    Py_XDECREF(_pyModule);
}

std::vector<TabDescriptor> UgWrapper::searchTabs(std::string searchArgument) {
    PyObject *pArgs = PyTuple_New(1);
    PyObject *pSearchString = PyString_FromString(searchArgument.c_str());
    if (!pSearchString) {
        Py_DECREF(pArgs);
        throw std::runtime_error("Cannot get search string");
    }

    int ret = PyTuple_SetItem(pArgs, 0, pSearchString);
    if (ret != 0) {
        Py_DECREF(pArgs);
        throw std::runtime_error("Error while setting tuple argument");
    }

    PyObject *tabsList = PyObject_CallObject(_pyFunc, pArgs);
    Py_DECREF(pArgs);
    Py_DECREF(pSearchString);
    if (!tabsList) {
        PyErr_Print();
        throw std::runtime_error("Error while calling function");
    }

    int len = PySequence_Size(tabsList);

    std::vector<TabDescriptor> descriptors;
    // Fields of the python descriptor
    PyObject *artistString = PyString_FromString("_artist");
    PyObject *titleString = PyString_FromString("_title");
    PyObject *uriString = PyString_FromString("_uri");
    PyObject *ratingString = PyString_FromString("_rating");
    PyObject *ratingCounterString = PyString_FromString("_ratingCounter");
    PyObject *typeString = PyString_FromString("_type");
    PyObject *isPlusString = PyString_FromString("_isPlus");


    for (int i = 0; i < len; ++i) {
        PyObject *tabDescriptor = PySequence_GetItem(tabsList, i);
        if (!tabDescriptor) {
            Py_DECREF(tabsList);
            throw std::runtime_error("Error while iterating over list");
        }

        PyObject *artist = PyObject_GetAttr(tabDescriptor, artistString);
        PyObject *title = PyObject_GetAttr(tabDescriptor, titleString);
        PyObject *uri = PyObject_GetAttr(tabDescriptor, uriString);
        PyObject *rating = PyObject_GetAttr(tabDescriptor, ratingString);
        PyObject *ratingCounter = PyObject_GetAttr(tabDescriptor, ratingCounterString);
        PyObject *type = PyObject_GetAttr(tabDescriptor, typeString);
        PyObject *isPlus = PyObject_GetAttr(tabDescriptor, isPlusString);

        TabDescriptor ts;
        ts._artist = PyString_AsString(artist);

        ts._title = PyString_AsString(title);

        ts._uri = PyString_AsString(uri);

        if (rating == Py_None) {
            ts._rating = "N/A";
        } else {
            ts._rating = PyString_AsString(rating);
        }
        if (ratingCounter == Py_None) {
            ts._ratingCounter = "N/A";
        } else {
            ts._ratingCounter = PyString_AsString(ratingCounter);
        }
        ts._type = PyString_AsString(type);
        // Python bool is subclass of int
        long isPlusLong = PyInt_AsLong(isPlus);
        ts._isPlus = (isPlusLong != 0);

        descriptors.push_back(ts);

        Py_DECREF(artist);
        Py_DECREF(title);
        Py_DECREF(uri);
        Py_DECREF(rating);
        Py_DECREF(ratingCounter);
        Py_DECREF(type);
        Py_DECREF(isPlus);
        Py_DECREF(tabDescriptor);
    }

    Py_DECREF(artistString);
    Py_DECREF(titleString);
    Py_DECREF(uriString);
    Py_DECREF(ratingString);
    Py_DECREF(ratingCounterString);
    Py_DECREF(typeString);
    Py_DECREF(isPlusString);
    Py_DECREF(tabsList);

    Py_Finalize();
    return descriptors;
}

std::ostream& operator<<(std::ostream& os, const TabDescriptor& desc) {
    os << "URI: " << desc._uri << std::endl;
    os << "Artist: " << desc._artist << std::endl;
    os << "Title: " << desc._title << std::endl;
    os << "Rating: " << desc._rating << std::endl;
    os << "Votes: " << desc._ratingCounter << std::endl;
    os << "Type: " << desc._type << std::endl;
    return os;
}

} // end of namespace ug
