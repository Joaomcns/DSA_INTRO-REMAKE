/* event.h */
#ifndef EVENT_H
#define EVENT_H

#include <stdio.h>

#define MAX_PEOPLE 4
#define MAX_FIELDS 9
#define MAX_STR 64
#define MAX_EVENTS 10000
#define MAX_EVENTS_ROOM 100

typedef struct {
    char name[MAX_STR];
    int isResponsible;
} Person;

typedef struct {
    char description[MAX_STR];
    char day[9];
    char start[5];
    int duration;
    int finish;
    int room;
    int n_participants;
    Person participants[MAX_PEOPLE];
} Event;

/* Global variables */
extern Event room_handler[MAX_EVENTS];
extern int roomCounter[10];
extern int next_slot;

/* Update key enum */
typedef enum {
    START,
    DURATION,
    ROOM,
    ADD_PERSON,
    REMOVE_PERSON
} UpdateKey;

/* Event-specific function declarations */
void updateParticipant(const char *input, UpdateKey flag);
void updateEvent(const char *input, UpdateKey flag);
void deleteEvent(const char *input);
void listEventsByRoom(const char *input);
void listEvents(void);
void addEvent(const char *input);

#endif /* EVENT_H */
