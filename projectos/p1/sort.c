#include "event.h"
#include <string.h>
#include <stdlib.h>

int compareDates(const char *date1, const char *date2) {
    int day1 = (date1[0] - '0') * 10 + (date1[1] - '0');
    int month1 = (date1[2] - '0') * 10 + (date1[3] - '0');
    int year1 = (date1[4] - '0') * 1000 + (date1[5] - '0') * 100 + (date1[6] - '0') * 10 + (date1[7] - '0');

    int day2 = (date2[0] - '0') * 10 + (date2[1] - '0');
    int month2 = (date2[2] - '0') * 10 + (date2[3] - '0');
    int year2 = (date2[4] - '0') * 1000 + (date2[5] - '0') * 100 + (date2[6] - '0') * 10 + (date2[7] - '0');

    if (year1 != year2)
        return year1 - year2;
    if (month1 != month2)
        return month1 - month2;
    return day1 - day2;
}

/* Function to compare two Events */
int compareEventsToSort(Event e1, Event e2) {
    int day_cmp, start_cmp = 0;


    /* Compare by day */
    day_cmp = compareDates(e1.day, e2.day);
    if (day_cmp != 0) {
        return day_cmp;  
    }

    /* Compare by start time if day is the same*/
    start_cmp = strcmp(e1.start, e2.start);
    if (start_cmp != 0) {
        return start_cmp; 
    }

    return e1.room - e2.room;
}

/* Merge function to merge two halves of the array*/
void merge(Event events[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    /* Create temporary arrays*/
    Event L[MAX_EVENTS];
    Event R[MAX_EVENTS];

    /* Copy data to temporary arrays L[] and R[]*/
    for (i = 0; i < n1; i++) {
        L[i] = events[left + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = events[mid + 1 + j];
    }

    /* Merge the temporary arrays back into events[left..right]*/
    i = 0;  /* Initial index of first subarray*/
    j = 0;  /* Initial index of second subarray*/
    k = left;  /* Initial index of merged subarray*/
    while (i < n1 && j < n2) {
        if (compareEventsToSort(L[i], R[j]) <= 0) {
            events[k] = L[i];
            i++;
        } else {
            events[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there are any*/
    while (i < n1) {
        events[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there are any*/
    while (j < n2) {
        events[k] = R[j];
        j++;
        k++;
    }
}

/* Merge Sort function*/
void mergeSort(Event events[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        /* Sort first and second halves*/
        mergeSort(events, left, mid);
        mergeSort(events, mid + 1, right);

        /* Merge the sorted halves*/
        merge(events, left, mid, right);
    }
}
