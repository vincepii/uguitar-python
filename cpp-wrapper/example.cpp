// Requires python-dev library
// Compile with g++ example.cpp -Wall -lpython2.7
// Make sure that this dir is in the PYTHONPATH

#include <python2.7/Python.h>

int main(int argc, char *argv[])
{
    Py_Initialize();

    // Get the module name
    PyObject *pName = PyString_FromString("uguitar.ug_simplesearch");
    if (!pName) {
        fprintf(stderr, "Cannot create string object for module");
        return 1;
    }

    // Import
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    // Check for import errors
    if (!pModule) {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return 1;
    }

    // Get the function
    PyObject *pFunc = PyObject_GetAttrString(pModule, "search");
    if (!pFunc) {
        Py_DECREF(pModule);
        fprintf(stderr, "Cannot create string object for function\n");
        return 1;
    }

    if (!PyCallable_Check(pFunc)) {
        PyErr_Print();
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        return 1;
    }

    // Function is callable

    PyObject *pArgs = PyTuple_New(1);
    PyObject *pSearchString = PyString_FromString("metallica one");
    if (!pSearchString) {
        Py_DECREF(pArgs);
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        fprintf(stderr, "Cannot get search string");
        return 1;
    }

    int ret = PyTuple_SetItem(pArgs, 0, pSearchString);
    if (ret != 0) {
        fprintf(stderr, "Error while setting tuple argument");
        Py_DECREF(pArgs);
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        return 1;
    }

    PyObject *tabsList = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    Py_DECREF(pSearchString);
    if (!tabsList) {
        PyErr_Print();
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        return 1;
    }

    int len = PySequence_Size(tabsList);
    fprintf(stdout, "Number of tabs: %d\n", len);

    for (int i = 0; i < len; ++i) {
        PyObject *tabDescriptor = PySequence_GetItem(tabsList, i);
        if (!tabDescriptor) {
            fprintf(stderr, "Error while iterating over list\n");
            Py_DECREF(pFunc);
            Py_DECREF(pModule);
            Py_DECREF(tabsList);
            return 1;
        }
        PyObject *uri = PyObject_GetAttr(tabDescriptor, PyString_FromString("_uri"));
        if (!uri) {
            fprintf(stderr, "Cannot get attribute from python object\n");
            continue;
        }

        printf("Result %d\n", i + 1);
        printf("\tURI: %s\n", PyString_AsString(uri));
        printf("\n");
        Py_DECREF(uri);
        Py_DECREF(tabDescriptor);
    }

    Py_DECREF(tabsList);
    Py_DECREF(pFunc);
    Py_DECREF(pModule);

    Py_Finalize();
    return 0;
}
