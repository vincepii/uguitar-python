#include "ug_cpp.h"

#include <stdexcept>
#include <iostream>

using namespace std;
using namespace boost::python;

namespace ug {

UgWrapper::UgWrapper() {
    Py_Initialize();
    try {
        boost::python::object _pyModule = boost::python::import(MODULE_NAME);
        boost::python::object _pyFunc = _pyModule.attr(FUNCTION_NAME);
    } catch (boost::python::error_already_set& e) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        handle<> hType(ptype);
        object extype(hType);
        handle<> hTraceback(ptraceback);
        object traceback(hTraceback);

        //Extract error message
        string strErrorMessage = extract<string>(pvalue);

        //Extract line number (top entry of call stack)
        // if you want to extract another levels of call stack
        // also process traceback.attr("tb_next") recurently
        long lineno = extract<long> (traceback.attr("tb_lineno"));
        string filename = extract<string>(traceback.attr("tb_frame").attr("f_code").attr("co_filename"));
        string funcname = extract<string>(traceback.attr("tb_frame").attr("f_code").attr("co_name"));

        std::cout << strErrorMessage;
    }
}

UgWrapper::~UgWrapper() {
    Py_Finalize();
}

std::vector<TabDescriptor> UgWrapper::searchTabs(std::string searchArgument) {

    std::vector<TabDescriptor> descriptors;
    boost::python::object results;
    try {
        results = _pyFunc(searchArgument);
    } catch (boost::python::error_already_set& e) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        handle<> hType(ptype);
        object extype(hType);
        handle<> hTraceback(ptraceback);
        object traceback(hTraceback);

        //Extract error message
        string strErrorMessage = extract<string>(pvalue);

        //Extract line number (top entry of call stack)
        // if you want to extract another levels of call stack
        // also process traceback.attr("tb_next") recurently
        long lineno = extract<long> (traceback.attr("tb_lineno"));
        string filename = extract<string>(traceback.attr("tb_frame").attr("f_code").attr("co_filename"));
        string funcname = extract<string>(traceback.attr("tb_frame").attr("f_code").attr("co_name"));

        std::cout << strErrorMessage;
    }

    int size = boost::python::extract<double>(results.attr("length"));
    std::cout << "Size: " << size << std::endl;

//    PyObject *pArgs = PyTuple_New(1);
//    PyObject *pSearchString = PyString_FromString(searchArgument.c_str());
//    if (!pSearchString) {
//        Py_DECREF(pArgs);
//        throw std::runtime_error("Cannot get search string");
//    }
//
//    int ret = PyTuple_SetItem(pArgs, 0, pSearchString);
//    if (ret != 0) {
//        Py_DECREF(pArgs);
//        throw std::runtime_error("Error while setting tuple argument");
//    }
//
//    PyObject *tabsList = PyObject_CallObject(_pyFunc, pArgs);
//    Py_DECREF(pArgs);
//    Py_DECREF(pSearchString);
//    if (!tabsList) {
//        PyErr_Print();
//        throw std::runtime_error("Error while calling function");
//    }
//
//    int len = PySequence_Size(tabsList);
//
//    std::vector<TabDescriptor> descriptors;
//    // Fields of the python descriptor
//    PyObject *artistString = PyString_FromString("_artist");
//    PyObject *titleString = PyString_FromString("_title");
//    PyObject *uriString = PyString_FromString("_uri");
//    PyObject *ratingString = PyString_FromString("_rating");
//    PyObject *ratingCounterString = PyString_FromString("_ratingCounter");
//    PyObject *typeString = PyString_FromString("_type");
//    PyObject *isPlusString = PyString_FromString("_isPlus");
//
//
//    for (int i = 0; i < len; ++i) {
//        PyObject *tabDescriptor = PySequence_GetItem(tabsList, i);
//        if (!tabDescriptor) {
//            Py_DECREF(tabsList);
//            throw std::runtime_error("Error while iterating over list");
//        }
//
//        PyObject *artist = PyObject_GetAttr(tabDescriptor, artistString);
//        PyObject *title = PyObject_GetAttr(tabDescriptor, titleString);
//        PyObject *uri = PyObject_GetAttr(tabDescriptor, uriString);
//        PyObject *rating = PyObject_GetAttr(tabDescriptor, ratingString);
//        PyObject *ratingCounter = PyObject_GetAttr(tabDescriptor, ratingCounterString);
//        PyObject *type = PyObject_GetAttr(tabDescriptor, typeString);
//        PyObject *isPlus = PyObject_GetAttr(tabDescriptor, isPlusString);
//
//        TabDescriptor ts;
//        ts._artist = PyString_AsString(artist);
//
//        ts._title = PyString_AsString(title);
//
//        ts._uri = PyString_AsString(uri);
//
//        if (rating == Py_None) {
//            ts._rating = "N/A";
//        } else {
//            ts._rating = PyString_AsString(rating);
//        }
//        if (ratingCounter == Py_None) {
//            ts._ratingCounter = "N/A";
//        } else {
//            ts._ratingCounter = PyString_AsString(ratingCounter);
//        }
//        ts._type = PyString_AsString(type);
//        // Python bool is subclass of int
//        long isPlusLong = PyInt_AsLong(isPlus);
//        ts._isPlus = (isPlusLong != 0);
//
//        descriptors.push_back(ts);
//
//        Py_DECREF(artist);
//        Py_DECREF(title);
//        Py_DECREF(uri);
//        Py_DECREF(rating);
//        Py_DECREF(ratingCounter);
//        Py_DECREF(type);
//        Py_DECREF(isPlus);
//        Py_DECREF(tabDescriptor);
//    }
//
//    Py_DECREF(artistString);
//    Py_DECREF(titleString);
//    Py_DECREF(uriString);
//    Py_DECREF(ratingString);
//    Py_DECREF(ratingCounterString);
//    Py_DECREF(typeString);
//    Py_DECREF(isPlusString);
//    Py_DECREF(tabsList);
//

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
