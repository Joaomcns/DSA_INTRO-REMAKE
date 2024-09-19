/* utils.h */
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "event.h"

/* Helper function declarations */
int hoursMinutes(char *time);
int finishTime(int dur, char *start_time);
int compareEventOverlap(Event current, Event comparable);
void printEvent(Event e);
void prettyPrintEvent(Event e);
void checkParticipants(int structIndex, char *newParticipant, UpdateKey flag);
Event saveEvent(char *inputs[], int input_count);

#endif /* UTILS_H */
