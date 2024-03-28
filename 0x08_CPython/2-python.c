#include <Python.h>

/**
* print_python_bytes - Print information about a Python Bytes object.
*
* This function prints information about a Python Bytes object, including its
* size and the first 10 bytes in hexadecimal format.
*
* @p: A pointer to the Python Bytes object.
*/
void print_python_bytes(PyObject *p)
{
	Py_ssize_t i, size;
	char *str = NULL;


	if (PyBytes_CheckExact(p) == 0)
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	PyBytes_AsStringAndSize(p, &str, &size);

	printf("[.] bytes object info\n");
	printf("  size: %zi\n", size);
	printf("  trying string: %s\n", str);
	printf("  first %zi bytes:", size >= 10 ? 10 : size + 1);
	for (i = 0; (i < size + 1) && (i < 10); i++)
		printf(" %02hhx", str[i]);
	printf("\n");
}

/**
* print_python_list - Print information about a Python List object.
*
* This function prints information about a Python List object, including its
* size, allocation, and the types of its elements.
* If the element is a PyBytes object, call print_python_bytes function
* @p: A pointer to the Python List object.
*/
void print_python_list(PyObject *p)
{
	PyListObject *list = (PyListObject *)p;
	Py_ssize_t i, size = PyList_Size(p);
	PyObject *item;


	if (PyList_CheckExact(p) == 0)
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}
	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %zi\n", size);
	printf("[*] Allocated = %zi\n", list->allocated);

	for (i = 0; i < size; i++)
	{
		item = PyList_GetItem(p, i);
		printf("Element %zi: %s\n", i, item->ob_type->tp_name);
		if (PyBytes_CheckExact(item))
			print_python_bytes(item);
	}
}

