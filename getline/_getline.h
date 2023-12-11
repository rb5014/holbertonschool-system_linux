#ifndef LAPS_H
#define LAPS_H

#define READ_SIZE 1024

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char *_getline(const int fd);
#endif
