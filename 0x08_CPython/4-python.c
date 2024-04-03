#include <Python.h>

/**
* print_python_string - Print information about a Python String object.
*
* This function prints information about a Python String object
*
* @p: A pointer to the Python Float object.
*/
void print_python_string(PyObject *p)
{
	printf("[.] string object info\n");
	if (PyUnicode_CheckExact(p) == 0)
	{
		printf("  [ERROR] Invalid String Object\n");
		return;
	}
	printf("  type: %s\n",
		PyUnicode_IS_COMPACT_ASCII(p) ? "compact ascii" : "compact unicode object");
	printf("  lenght: %zi\n", PyUnicode_GetSize(p));
	printf("  value: %s\n", PyUnicode_AsUTF8(p));
}
