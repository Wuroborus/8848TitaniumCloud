#include <Python.h>
#include <iostream>

/**
 * sudo apt install python-dev
 * how to compile:
 * g++ fakefake.cpp -g -o my_python -I/usr/include/python2.7/ -L/usr/lib/python2.7 -lpython2.7
 * 
 * where to change:
 * 1. import module
 * 2. import function
 * 3. arguments
 **/

int main()
{
    int res = 3;

    Py_Initialize();
    
    /****************** don't delete"*********************/
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    /****************** don't delete"*********************/

    PyObject *pModule, *pFunc, *pArgs, *pValue;

    // import module
    pModule = PyImport_ImportModule("fake");
    // use the file name without expand name;

    if(!pModule)
    {
        std::cout << "fake.py can't open" << std::endl;
        return -1;
    }

    // import function
    pFunc = PyObject_GetAttrString(pModule, "encodefile");

    if(!pFunc)
    {
        std::cout << "encodefile can't import" << std::endl;
        return -1;
    }

    // arguments
    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, PyString_FromString("test.txt"));

    // call
    pValue = PyObject_CallObject(pFunc, pArgs);

    res = PyInt_AsLong(pValue);

    Py_Finalize();

    // std::cout << res << std::endl;

    return res;
}