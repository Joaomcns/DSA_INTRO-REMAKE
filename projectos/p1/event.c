#include "event.h"
#include "utils.h"
#include "sort.h"

/*Global variables definition*/
Event room_handler[MAX_EVENTS];
int roomCounter[10] = {0};
int next_slot = 0;

/*Commands*/
void updateParticipant(const char *input, UpdateKey flag){
    int exists = 0;
    int i;
    char *inputCopy = strdup(input); 
    char *inputDescription = strtok(inputCopy, ":");
    char *inputChangeable= strtok(NULL,":");

    for ( i = 0; i < next_slot; i++)
    {
        if (strcmp(room_handler[i].description, inputDescription) == 0){
            exists = 1;
            checkParticipants(i, inputChangeable, flag);
        }
   }

    if (!exists) {
        printf("Evento %s inexistente.\n", inputDescription); 
        return;
    }
}

void updateEvent(const char *input, UpdateKey flag){
    int i,j;
    int changeableIndex = 0;
    int exists = 0;

    char *inputCopy = strdup(input); 
    char *inputDescription = strtok(inputCopy, ":");
    char *inputChangeable= strtok(NULL,":");

    Event currentEvent, comparableEvent;


    for ( i = 0; i < next_slot; i++)
    {
        if (strcmp(room_handler[i].description, inputDescription) == 0){
            exists = 1;
            currentEvent = room_handler[i];
            changeableIndex = i;
            if (flag == START) {
                strcpy(currentEvent.start, inputChangeable);
                currentEvent.finish = finishTime(room_handler[i].duration,currentEvent.start);
            }
            else if (flag == DURATION){
                currentEvent.duration = atoi(inputChangeable);
                currentEvent.finish = finishTime(currentEvent.duration,room_handler[i].start);
            }
            else{
                currentEvent.room = atoi(inputChangeable);
            }
        }
            
    }

    if (!exists) {
        printf("Evento %s inexistente.\n", inputDescription); 
        free(inputCopy);
        return;
    }


    for(j = 0; j < MAX_EVENTS; j++){
        comparableEvent = room_handler[j];

        if (strcmp(comparableEvent.description, currentEvent.description) == 0){
            continue;
        }

        if (compareEventOverlap(currentEvent,comparableEvent)== 1){
            free(inputCopy);
            return;
        }      
    }

    room_handler[changeableIndex] = currentEvent;
    
}


void deleteEvent(const char *input){
    int indexToDelete = -1;
    int i, j;
    
    for (i = 0; i < next_slot; ++i) { 
        if (strcmp(room_handler[i].description, input) == 0) { 
            indexToDelete = i; 
            break; 
        } 
    } 
    if (indexToDelete == -1) { 
        printf("Evento %s inexistente.\n", input); 
        return;
    } 

    for (j = indexToDelete; j < next_slot - 1; ++j) { 
            room_handler[j] = room_handler[j + 1]; 
    } 
  
    next_slot--; 
}


void listEventsByRoom(const char *input){
    Event roomEvents[MAX_EVENTS_ROOM];
    int inputRoom = atoi(input);
    int nEventsRoom = roomCounter[inputRoom - 1];


    int i, j;

    for ( i = 0; i < next_slot; i++)
    {   
        if (room_handler[i].room == inputRoom){
            roomEvents[nEventsRoom] = room_handler[i];
            nEventsRoom++;
        }
    }

    mergeSort(roomEvents, 0, nEventsRoom-1);


    for ( j = 0; j < nEventsRoom; j++)
    {   
        prettyPrintEvent(roomEvents[j]);
    }

}


void listEvents(void){
    int i;
    mergeSort(room_handler, 0, next_slot-1);

    for ( i = 0; i < next_slot; i++)
    {
        prettyPrintEvent(room_handler[i]);
    }
}


void addEvent(const char *input){
    Event comparable_event;/* store event to compare while looping through events*/
    Event current_event;
    char *fields[MAX_FIELDS] = { NULL }; /*stores input*/

    /*counters*/
    int fieldCount, invalidParts;
    /*loop vars*/
    int i;

    /*Make a copy of the input string for strtok*/
    char *input_copy = strdup(input); 
    /*Parse the input string using strtok*/
    char *token = strtok(input_copy, ":");

    /*intializing counters*/
    fieldCount = invalidParts = 0;    
    
    while (token != NULL && fieldCount < MAX_FIELDS) {
        fields[fieldCount++] = token;
        token = strtok(NULL, ":");
    }

    current_event = saveEvent(fields, fieldCount);   

    for(i = 0; i < next_slot; i++)
    {   
        comparable_event = room_handler[i];  
        if (compareEventOverlap(current_event,comparable_event)== 1)
            invalidParts++;
    }

    if (invalidParts)
        return;

    room_handler[next_slot] = current_event;
    next_slot++;
}



   


