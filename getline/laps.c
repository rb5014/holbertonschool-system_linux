#include "laps.h"

static struct RacingCar *racing_cars;
static size_t nb_racing_cars;


/**
 * update_ids - update racing_cars ids with a new one
 * @new_car_id: new car id to add with laps 0 in a RacingCar struct
 * @position:  position in the array of the new car
 */
void update_ids(int new_car_id, int position)
{
	int i;

	racing_cars = realloc(racing_cars, sizeof(RacingCar) * (++nb_racing_cars));
	for (i = nb_racing_cars - 2; i >= position; i--)
	{
		racing_cars[i + 1] = racing_cars[i];
	}
	racing_cars[position].id = new_car_id;
	racing_cars[position].laps = 0;
}


/**
 * check_ids - check for new ids (new cars)
 * @id: Array of int representing the “identifier” of each car
 * @size: size of the array
*/
void check_ids(int *id, size_t size)
{
	size_t i, j, pos_new;

	for (i = 0; i < size; i++)
	{
		for (j = 0, pos_new = 0; j < nb_racing_cars; j++)
		{
			if (id[i] == racing_cars[j].id)
			{
				racing_cars[j].laps++;
				break;
			}
			else if (id[i] > racing_cars[j].id)
				pos_new = j + 1;
		}
		if (j == nb_racing_cars) /* id[i] wasn't found if loop processed entirely */
		{
			update_ids(id[i], pos_new);
			printf("Car %i joined the race\n", id[i]);
		}

	}
}

/**
 * race_state - keeps track of the number of laps
 * made by several cars in a race
 * @id: Array of int representing the “identifier” of each car
 * @size: size of the array
*/
void race_state(int *id, size_t size)
{
	size_t i;

	if (size == 0)
	{
		free(racing_cars);
		return;
	}
	check_ids(id, size);
	printf("Race state:\n");
	for (i = 0; i < nb_racing_cars; i++)
	{
		printf("Car %i [%i laps]\n", racing_cars[i].id, racing_cars[i].laps);
	}
}
