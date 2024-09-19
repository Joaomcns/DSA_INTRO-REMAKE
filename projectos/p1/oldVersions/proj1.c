#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_PEOPLE 4
#define MAX_FIELDS 9
#define MAX_STR 64
#define MAX_EVENTS_ROOM 100
#define MAX_EVENTS 10000 
#define MAX_INPUT_SIZE 342



typedef struct 
{
    char name[MAX_STR];
    int isResponsible;

}Person;

typedef struct 
{   
    char description[MAX_STR];
    char day[9];
    char start[5];
    int duration;
    int finish;
    int room;
    int n_participants;
    Person participants[MAX_PEOPLE];
    
}Event;



/*Global Variables*/

Event room_handler[MAX_EVENTS];
int roomCounter[10] = {0};
int next_slot = 0;

typedef enum {
    START, 
    DURATION, 
    ROOM, 
    ADD_PERSON,
    REMOVE_PERSON
} updateKey;

/*Helper functions*/
void checkParticipants(int structIndex, char* newParticipant, updateKey flag);
void printEvent(Event e);
void prettyPrintEvent(Event e);
int hoursMinutes( char *time);
int finishTime( int dur, char start_time[5]);
int compareEventOverlap(Event current,  Event comparable);
Event saveEvent(char *inputs[], int input_count);

/*Merge Sort implementation */
int compareDates(const char *date1, const char *date2);
int compareEventsToSort(Event e1, Event e2);
void merge(Event events[], int left, int mid, int right);
void mergeSort(Event events[], int left, int right);

/*Commands*/
void updateParticipant(const char *input, updateKey flag);
void updateEvent(const char *input, updateKey flag);
void deleteEvent(const char *input);
void listEventsByRoom(const char *input);
void listEvents(void);
void addEvent(const char *input);





/*change everything to camelcase*/
int main(void) {

    char input[MAX_INPUT_SIZE];
    char command;

    while (fgets(input, MAX_INPUT_SIZE, stdin) != NULL) {
        /*Remove trailing newline character if present*/
        input[strcspn(input, "\n")] = 0;

        command = input[0];


        switch (command) {
            case 'a':
                addEvent(input + 2); /* Pass the input string after "a " */
                break;
            case 'l':
                listEvents();
                break;
            case 's':
                listEventsByRoom(input + 2);
                break;
            case 'r':
                deleteEvent(input + 2);
                break;
            case 'i':
                updateEvent(input + 2, START);
                break;
            case 't':
                updateEvent(input + 2, DURATION);
                break;
            case 'm':
                updateEvent(input + 2, ROOM);
                break;
            case 'A':
                updateParticipant(input + 2, ADD_PERSON);
                break;
            case 'R':
                updateParticipant(input + 2, REMOVE_PERSON);
                break;
            case 'x':
                return EXIT_SUCCESS; /* Termina o programa com sucesso (STDLIB) */
            default:
                printf("ERRO: Comando desconhecido\n");
        }
        
    }
    return EXIT_FAILURE;            

}

/*Helper functions*/

void checkParticipants(int structIndex, char* newParticipant, updateKey flag){
    int i, j,comparable_part, indexToDelete;
    Event currentEvent;
    Event comparable;

    indexToDelete = 0;
    currentEvent = room_handler[structIndex];

    if (flag == ADD_PERSON){
        if (room_handler[structIndex].n_participants == 3){
            printf("Impossivel adicionar participante. Evento %s ja tem 3 participantes.\n",currentEvent.description);
            return;
        }

        for (j = 0; j < room_handler[structIndex].n_participants +1; j++)
        {   
            if (strcmp(newParticipant, room_handler[structIndex].participants[j].name) == 0){
                return;
             }
        }

        strcpy(currentEvent.participants[currentEvent.n_participants + 1].name, newParticipant);

        for ( i = 0; i < next_slot ; i++)
        {
            comparable = room_handler[i];
            if (strcmp(comparable.description, currentEvent.description)==0)
                continue;

            for (comparable_part = 0; comparable_part <= comparable.n_participants; comparable_part++)
            {   
                if (strcmp(newParticipant, comparable.participants[comparable_part].name) == 0){
                    if (((hoursMinutes(currentEvent.start) < comparable.finish) &&  (currentEvent.finish >  hoursMinutes(comparable.start)))){
                        printf("Impossivel adicionar participante. Participante %s tem um evento sobreposto.\n",newParticipant);
                        return;
                    }
                }
            }
        }

        strcpy(room_handler[structIndex].participants[room_handler[structIndex].n_participants + 1].name, newParticipant);
        room_handler[structIndex].n_participants++;
    }
    else {
        for (j = 1; j <=  currentEvent.n_participants ; ++j) {
            if (strcmp(newParticipant, currentEvent.participants[j].name) == 0){
                if (currentEvent.n_participants <= 1){
                    printf("Impossivel remover participante. Participante %s e o unico participante no evento %s.\n", newParticipant, currentEvent.description);
                    return;
                }
                indexToDelete = j;
                break;
            }

        } 

        if (!indexToDelete){
            return;
        }


        for (j = indexToDelete; j < currentEvent.n_participants; ++j) {         
            room_handler[structIndex].participants[j] = room_handler[structIndex].participants[j + 1]; 
        } 
    
        room_handler[structIndex].n_participants--;

    }
}

void printEvent(Event e){
    int i;

    printf("DESC-> %s\n", e.description);
    printf("DAY-> %s\n", e.day);
    printf("START-> %s\n", e.start);
    printf("DUR-> %d\n", e.duration);
    printf("FINISH-> %d\n", e.finish);
    printf("ROOM-> %d\n", e.room);
    
    for (i = 0; i <= MAX_PEOPLE; i++)
    {
        printf("PARTICIPANT %s\n", e.participants[i].name);
    }
    printf("PARTICIPANT NO-> %d\n", e.n_participants);

    

    
}

void prettyPrintEvent(Event e){
    int part;

    printf("%s %s %s %d Sala%d %s\n", e.description, e.day, e.start, e.duration, e.room, e.participants[0].name);
    printf("*");

    for(part=1;part <= e.n_participants ;part++){
        printf(" %s", e.participants[part].name);
    }
    printf("\n");
}

int hoursMinutes(char *time){
    char hours[3];
    char minutes[3];

    strncpy(hours, time,2);
    strncpy(minutes, time + 2,2);

    return (atoi(hours) * 60) + atoi(minutes) ;
    
}


int finishTime( int dur, char *start_time){
    return hoursMinutes(start_time) + dur;
}


int compareEventOverlap(Event current,  Event comparable){
    int current_part, comparable_part, equal_names;
    char isolated_part[MAX_STR];
    equal_names = 0;
    
    if ((strcmp(comparable.day, current.day) == 0)){
        if (comparable.room == current.room) {
            if (((hoursMinutes(current.start) < comparable.finish) &&  (current.finish >  hoursMinutes(comparable.start)))){
                printf("Impossivel agendar evento %s. Sala%d ocupada.\n",current.description , current.room );
                return 1;
            }
        }
        for (current_part = 0; current_part <= current.n_participants; current_part++)
        {   
            strcpy(isolated_part, current.participants[current_part].name);

            for (comparable_part = 0; comparable_part <= comparable.n_participants; comparable_part++)
            {   
                if (strcmp(isolated_part, comparable.participants[comparable_part].name) == 0){
                    if (((hoursMinutes(current.start) < comparable.finish) &&  (current.finish >  hoursMinutes(comparable.start)))){
                        printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n",current.description , isolated_part);
                        equal_names++;
                    }
                }
            }
            
        }

    }    

    if (equal_names > 0)
        return 1;
    
    return 0;
    
}


Event saveEvent(char *inputs[], int input_count){
    int j;
    int extra = 1;
    Event toSave;

    toSave.n_participants = 0;

    strcpy(toSave.description, inputs[0]);
    strcpy(toSave.day, inputs[1]);
    strcpy(toSave.start, inputs[2]);
    toSave.duration = atoi(inputs[3]);
    toSave.finish = finishTime(atoi(inputs[3]),inputs[2]);
    toSave.room = atoi(inputs[4]);

    strcpy(toSave.participants[0].name, inputs[5]);
    toSave.participants[0].isResponsible =  1;
   
    
    if (input_count >= 6) {  
        for (j = 6; j < input_count; j++)
        {  
            strcpy(toSave.participants[extra].name, inputs[j]);
            toSave.participants[extra].isResponsible =  0;
            extra++;
            toSave.n_participants++;
        }

    }  

    return toSave;
    
}

/*Merge Sort Implementation*/


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

/* Function to compare two Events based on your criteria*/
int compareEventsToSort(Event e1, Event e2) {
    int day_cmp, start_cmp = 0;


    /* Compare by day first*/
    day_cmp = compareDates(e1.day, e2.day);
    if (day_cmp != 0) {
        return day_cmp;  /* Return the result of day comparison*/
    }

    /* Compare by start time if day is the same*/
    start_cmp = strcmp(e1.start, e2.start);
    if (start_cmp != 0) {
        return start_cmp;  /* Return the result of start time comparison*/
    }

    /* Compare by room if both day and start time are the same*/
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

/*Commands*/

void updateParticipant(const char *input, updateKey flag){
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

void updateEvent(const char *input, updateKey flag){
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



   


