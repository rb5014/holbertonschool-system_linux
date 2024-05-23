#include <stdlib.h>
#include "multithreading.h"
#include "list.h"

/**
 * add_prime - Allocates memory for prime factor and add it to list
 * @list: list to add the prime factor in
 * @n: prime factor to add to list

*/
void add_prime(list_t *list, unsigned long n)
{
	unsigned long *prime = malloc(sizeof(*prime));

	if (!prime)
		return;

	*prime = n;
	list_add(list, prime);
}
/**
 * prime_factors - factorizes a number into a list of prime factors.
 * @s: string representation of the number to factorize.
 * This number will be positive and fit into an unsigned long
 * Return: list of prime factors
 */
list_t *prime_factors(char const *s)
{
	list_t *list = NULL;
	unsigned long n, i;

	if (!s)
		return (NULL);

	n = strtoul(s, NULL, 10);
	list = malloc(sizeof(*list));
	if (!list)
		return (NULL);
	list = list_init(list);
	/* Print the number of 2s that divide n */
	while (n % 2 == 0)
	{
		add_prime(list, 2);
		n /= 2;
	}
	/* n must be odd at this point. So we can skip */
	/* one element (Note i = i +2)  */
	for (i = 3; i * i <= n; i +=2)
	{ /* While i divides n, print i and divide n */
		while (n % i == 0)
		{
			add_prime(list, i);
			n /= i;
		}
	}
	/* This condition is to handle the case when n */
	/* is a prime number greater than 2 */
	if (n > 2)
		add_prime(list, n);
	return (list);
}
