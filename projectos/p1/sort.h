/* sort.h */
#ifndef SORT_H
#define SORT_H

#include "event.h"

/* Sorting function declarations */
int compareDates(const char *date1, const char *date2);
int compareEventsToSort(Event e1, Event e2);
void merge(Event events[], int left, int mid, int right);
void mergeSort(Event events[], int left, int right);

#endif /* SORT_H */
