#ifndef LAPS_H
#define LAPS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*** STRUCTURES ***/
/**
 * struct RacingCar - Structure holding car id and number of laps achieved
 * @id: car id
 * @laps: number of laps achieved by this car
*/
struct RacingCar
{
	int id;
	int laps;
} RacingCar;

size_t _strlen(const char *str);

void race_state(int *id, size_t size);
void check_ids(int *id, size_t size);
void update_ids(int new_car_id, int position);
#endif
