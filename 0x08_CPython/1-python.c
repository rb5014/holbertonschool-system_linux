#include <Python.h>

/**
* print_python_list - Print information about a Python List object.
*
* This function prints information about a Python List object, including its
* size, allocation, and the types of its elements.
*
* @p: A pointer to the Python List object.
*/
void print_python_list(PyObject *p)
{
	PyListObject *list = (PyListObject *)p;
	Py_ssize_t i;

	p = p;
	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %li\n", PyList_Size(p));
	printf("[*] Allocated = %li\n", list->allocated);

	for (i = 0; i < PyList_Size(p); i++)
		printf("Element %li: %s\n", i, Py_TYPE(PyList_GetItem(p, i))->tp_name);
}
