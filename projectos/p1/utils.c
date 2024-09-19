#include "event.h"
#include <string.h>
#include <stdlib.h>


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


void checkParticipants(int structIndex, char* newParticipant, UpdateKey flag){
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


