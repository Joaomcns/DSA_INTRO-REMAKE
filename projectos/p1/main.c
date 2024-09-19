#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "event.h"

#define MAX_INPUT_SIZE 342

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
