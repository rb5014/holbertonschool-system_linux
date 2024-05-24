#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


/**
 * add_prime - Allocates memory for prime factor and add it to list
 * @list: list to add the prime factor in
 * @n: prime factor to add to list
 * Return: 1 on success, 0 otherwise
 */
int add_prime(list_t *list, unsigned long n)
{
	unsigned long *prime = malloc(sizeof(*prime));

	if (!prime)
		return (0);

	*prime = n;
	list_add(list, prime);
	return (1);
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

	list = list_init(list); /* Initialize the list structure */

	/* Handle the case when n is divisible by 2 */
	while (n % 2 == 0)
	{
		if (!add_prime(list, 2))
			return (NULL);
		n /= 2;
	}

	/* n must be odd at this point. So we can skip one element (Note i = i +2) */
	for (i = 3; i * i <= n; i += 2)
	{
		while (n % i == 0)
		{
			if (!add_prime(list, i))
				return (NULL);
			n /= i;
		}
	}

	/* Handle the case when n is a prime number greater than 2 */
	if (n > 2)
		if (!add_prime(list, n))
			return (NULL);

	return (list);
}
