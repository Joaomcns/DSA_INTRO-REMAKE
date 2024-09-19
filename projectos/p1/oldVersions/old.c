#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_PARTICIPANTS 3
#define MAX_PEOPLE 4
#define MAX_START 5 
#define N_ROOMS 10
#define MAX_STR 63
#define MAX_EVENTS 100 
#define MAX_INPUT_SIZE 340




typedef struct 
{
    char name[MAX_STR];
    int isResponsible;

}Person;

typedef struct 
{   
    char description[MAX_STR];
    char day[9];
    int start;
    int duration;
    int finish;
    int sala;
    Person participants[MAX_PEOPLE];
    
}Event;


int compareEventOverlap(Event e1, Event e2);
int hoursMinutes( char *time);
int finishTime( int dur, char start_time[MAX_START]);
void saveEvent(Event rooms[N_ROOMS][MAX_EVENTS], char *inputs[], int input_count , int next_slot );
void addEvent(const char *input);


Event room_handler[MAX_EVENTS];



//change everything to camelcase 
int main(void) {

    char input[MAX_INPUT_SIZE];
    char command;

    while (fgets(input, MAX_INPUT_SIZE, stdin) != NULL) {
        /*Remove trailing newline character if present*/
        input[strcspn(input, "\n")] = 0;

        command = input[0];

        switch (command) {
            case 'a':
                addEvent(input + 2); // Pass the input string after "a "
                break;
            case 'b':
                /* Chama a funcao responsavel pela execucao do comando b */
                break;
            case 'x':
                return EXIT_SUCCESS; /* Termina o programa com sucesso (STDLIB) */
            default:
            printf("ERRO: Comando desconhecido\n");
        }
        
    }
    return EXIT_FAILURE;            

}

int compareEventOverlap(Event e1, Event e2){
    
}

int hoursMinutes( char *time){
    char hours[3];
    char minutes[3];

    strncpy(hours, time,2);
    strncpy(minutes, time + 2,2);

    return (atoi(hours) * 60) + atoi(minutes) ;
    
}


int finishTime( int dur, char *start_time){
     return hoursMinutes(start_time) + dur;
}



void saveEvent(Event room_handler[N_ROOMS][MAX_EVENTS], char *inputs[], int input_count, int next_slot){
    int room, j;
    int extra = 0;
    room = atoi(inputs[4]) - 1;

    strcpy(room_handler[room][next_slot].description, inputs[0]);
    strcpy(room_handler[room][next_slot].day, inputs[1]);
    room_handler[room][next_slot].start =  hoursMinutes(inputs[2]);
    room_handler[room][next_slot].duration = (int) atoi(inputs[3]);
    room_handler[room][next_slot].finish = finishTime(atoi(inputs[3]),inputs[2]);
    room_handler[room][next_slot].sala = (int) atoi(inputs[4]);

    strcpy(room_handler[room][next_slot].participants[0].name, inputs[5]);
    room_handler[room][next_slot].participants[0].isResponsible =  1;



    
    
    if (input_count >= 6) {  
        for (j = 6; j < input_count; j++)
        {
            strcpy(room_handler[room][next_slot].participants[extra++].name, inputs[j]);
            room_handler[room][next_slot].participants[extra++].isResponsible =  0;
        }
    
    }  
    
}


void addEvent(const char *input){
    Event comparable_event;/* store event to compare while looping through events*/
    char *fields[6 + MAX_PARTICIPANTS] = { NULL }; /*stores input*/
    int event_count[MAX_EVENTS] = {0}; /*count event occurences in each room */

    /*counters*/
    int field_count, next_slot;
    /*loop vars*/
    int oc_ev, i, j, part;
    /*tracker vars*/
    int current_room;
    int currentFinish = 0;
    /*flags*/
    int invalidResponsable, hasInvalidParticipant;

    /*Make a copy of the input string for strtok*/
    char *input_copy = strdup(input); 
    /*Parse the input string using strtok*/
    char *token = strtok(input_copy, ":");

    /*intializing counters*/
    field_count = next_slot  = 0;

    /*initializing flags*/
    invalidResponsable = hasInvalidParticipant =0 ;

    
    
    while (token != NULL && field_count < 6 + MAX_PARTICIPANTS) {
        fields[field_count++] = token;
        token = strtok(NULL, ":");
    }
    

    current_room = atoi(fields[4]);
    for (oc_ev = 0; oc_ev < MAX_EVENTS; oc_ev++)
    {   
        comparable_event = room_handler[oc_ev];
        /*Checks if the room is occupied */
        if (strcmp(comparable_event.day, fields[1]) == 0 ){
            currentFinish = finishTime(atoi(fields[3]), fields[2]);
            if (((hoursMinutes(fields[2]) < comparable_event.finish) &&  (currentFinish >  comparable_event.finish))){
                printf("Impossivel agendar evento %s. Sala%d ocupada.\n", fields[0], current_room );
                return;
            }
        }
    }
    //TODO
    //check how to print the message
    //validate rooms function
    //repeated checks function

    // for (i = 0; i < N_ROOMS; i++)
    // {   
    //     for (j = 0; j < MAX_EVENTS; j++)
    //     {   
    //         comparable_event = room_handler[i][j];

            // if (strcmp(comparable_event.day, fields[1]) ==0){
            //         for (part = 0; part < MAX_PARTICIPANTS; part++)
            //         {
            //             if (strcmp(fields[part],comparable_event.participants[part].name) == 0) {
            //                 if(!((hoursMinutes(fields[2]) <= comparable_event.finish) &&  (comparable_event.start <= currentFinish))){
            //                     invalidResponsable = 1;
            //                     printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto\n", fields[0], fields[5]);
            //                 }
            //             }
            //             if field_count 
            //             // if (field_count >= 6 ){
            //             //     if(strcmp(fields[6 + part], comparable_event.participants[part].name) == 0){
            //             //         if(((hoursMinutes(fields[2]) <= comparable_event.finish) &&  (comparable_event.start <= currentFinish)))
            //             //             printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto\n", fields[0], fields[6 + part]);
            //             //     }
            //             // }
            //         }
            // }
        //} 
                    

    //}   
    
    // if (invalidResponsable || hasInvalidParticipant)
    //     return;
    next_slot = event_count[current_room];
    saveEvent(room_handler, fields, field_count, next_slot);
    event_count[current_room]++;
}
   


    //heapSort(roomEvents, nEventsRoom);
    //heapSort(room_handler, next_slot);



/*Heap Sort Implementation*/
//int compareDates(const char *date1, const char *date2);
// void swapEvents(Event events[], int i, int j);
// void heapify(Event events[], int n, int i);
// void heapSort(Event events[], int n);

/*HeapSort Implementation*/

// int compareDates(const char *date1, const char *date2) {
//     int day1 = (date1[0] - '0') * 10 + (date1[1] - '0');
//     int month1 = (date1[2] - '0') * 10 + (date1[3] - '0');
//     int year1 = (date1[4] - '0') * 1000 + (date1[5] - '0') * 100 + (date1[6] - '0') * 10 + (date1[7] - '0');

//     int day2 = (date2[0] - '0') * 10 + (date2[1] - '0');
//     int month2 = (date2[2] - '0') * 10 + (date2[3] - '0');
//     int year2 = (date2[4] - '0') * 1000 + (date2[5] - '0') * 100 + (date2[6] - '0') * 10 + (date2[7] - '0');

//     if (year1 != year2)
//         return year1 - year2;
//     if (month1 != month2)
//         return month1 - month2;
//     return day1 - day2;
// }

// void swapEvents(Event events[], int i, int j) {
//     Event temp = events[i];
//     events[i] = events[j];
//     events[j] = temp;
// }


// void heapify(Event events[], int n, int i) {
//     int largest = i;          /* Initialize largest as root */
//     int left = 2 * i + 1;     /* left = 2*i + 1 */
//     int right = 2 * i + 2;    /* right = 2*i + 2 */

//     /* Compare left child with root */ 
//     if (left < n && (compareDates(events[left].day, events[largest].day) > 0 ||
//         (compareDates(events[left].day, events[largest].day) == 0 && strcmp(events[left].start, events[largest].start) > 0)
        
//         )) {
//         largest = left;
//     }

//     /* Compare right child with the largest so far */
//     if (right < n && (compareDates(events[right].day, events[largest].day) > 0 ||
//         (compareDates(events[right].day, events[largest].day) == 0 && strcmp(events[right].start, events[largest].start) > 0))) {
//         largest = right;
//     }

//     /* If largest is not root, swap and continue heapifying*/ 
//     if (largest != i) {
//         swapEvents(events, i, largest);
//         heapify(events, n, largest);
//     }
// }


// /* Main function to perform heap sort */
// void heapSort(Event events[], int n) {

//     int i;
//     /* Build heap (rearrange array)*/
//     for (i = n / 2 - 1; i >= 0; i--) {
//         heapify(events, n, i);
//     }

//     /*One by one extract an element from heap */
//     for (i = n - 1; i > 0; i--) {
//         /* Move current root to end */
//         swapEvents(events, 0, i);

//         /* Call max heapify on the reduced heap */
//         heapify(events, i, 0);
//     }
// }