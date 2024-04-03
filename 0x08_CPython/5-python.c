#include <Python.h>

/**
* print_python_int - Print information about a Python Int object.
*
* This function prints information about a Python Int object
*
* @p: A pointer to the Python Int object.
*/
void print_python_int(PyObject *p)
{
	Py_ssize_t size, i;
	PyLongObject *long_object;
	unsigned long result = 0;

	if (PyLong_Check(p) == 0)
	{
		printf("Invalid Int Object\n");
		return;
	}
	long_object = (PyLongObject *)p;
	size = long_object->ob_base.ob_size;
	if (size < 0)
	{
		printf("-");
		size = -size;
	}
	if (size > 3 || (size == 3 && long_object->ob_digit[2] > 15))
	{
		printf("C unsigned long int overflow\n");
		return;
	}
	for (i = size - 1; i >= 0; i--)
	{
		result = result * (1 << PyLong_SHIFT) + long_object->ob_digit[i];
	}
	printf("%lu\n", result);
}
