#include <stdlib.h>

/* Define the comparison function type */
typedef int (*cmp_func)(const void*, const void*);

/**
 * swap - Swap elements in memory
 * @a: Pointer to the first element to be swapped
 * @b: Pointer to the second element to be swapped
 * @size: Size of each element in bytes
 *
 * Description:
 * This function swaps the contents of two memory locations 'a' and 'b'.
 * The size parameter specifies the size of each element in bytes.
 */
static void swap(void *a, void *b, int size)
{
	int i;
	char tmp;
	char *pa = a;
	char *pb = b;

	for (i = 0; i < size; ++i)
	{
		tmp = pa[i];
		pa[i] = pb[i];
		pb[i] = tmp;
	}
}

/**
 * partition - Partition an array for quicksort
 * @array: Pointer to the array to be partitioned
 * @low: Starting index of the partition
 * @high: Ending index of the partition
 * @size: Size of each element in bytes
 * @cmp: Pointer to the comparison function used for sorting
 *
 * Description:
 * This function partitions the array into two segments based on a pivot
 * element. It uses the comparison function 'cmp' to determine the order
 * of elements. The partitioning is a step in the QuickSort algorithm.
 *
 * Return: Index of the pivot element after partitioning.
 */
static int partition(void *array, int low, int high, int size, cmp_func cmp)
{
	void *pivot = (char *)array + high * size;
	int i = low, j;

	for (j = low; j < high; ++j)
	{
		if (cmp((char *)array + j * size, pivot) < 0)
		{
			if (i != j)
			{
				swap((char *)array + i * size, (char *)array + j * size, size);
			}
			++i;
		}
	}

	swap((char *)array + i * size, (char *)array + high * size, size);
	return (i);
}

/**
 * _qsort_helper - Recursive helper for quicksort
 * @array: Pointer to the array to be sorted
 * @low: Starting index of the segment to be sorted
 * @high: Ending index of the segment to be sorted
 * @size: Size of each element in bytes
 * @cmp: Pointer to the comparison function used for sorting
 *
 * Description:
 * This function is a recursive helper for the QuickSort algorithm. It sorts
 * the segment of the array between indices 'low' and 'high' using the
 * comparison function 'cmp'.
 */
static void
_qsort_helper(void *array, int low, int high, int size, cmp_func cmp)
{
	if (low < high)
	{
		int pivot = partition(array, low, high, size, cmp);

		if (pivot > 0)
		{
			_qsort_helper(array, low, pivot - 1, size, cmp);
		}
		_qsort_helper(array, pivot + 1, high, size, cmp);
	}
}

/**
 * _qsort - Sort an array of elements using QuickSort
 * @array: Pointer to the array to be sorted
 * @count: Number of elements in the array
 * @size: Size of each element in bytes
 * @cmp: Pointer to the comparison function used for sorting
 *
 * Description:
 * This function sorts an array of elements using the QuickSort algorithm.
 * The comparison function 'cmp' should return an integer less than, equal to,
 * or greater than zero if the first argument is considered to be respectively
 * less than, equal to, or greater than the second.
 */
void _qsort(void *array, int count, int size, cmp_func cmp)
{
	_qsort_helper(array, 0, count - 1, size, cmp);
}
