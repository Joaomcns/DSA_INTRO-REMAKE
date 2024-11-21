#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "contact.h"

#define MAX_INPUT_SIZE 1601

int main(void) {

    char input[MAX_INPUT_SIZE];
    char command;

    while (fgets(input, MAX_INPUT_SIZE, stdin) != NULL) {
        /*Remove trailing newline character if present*/
        input[strcspn(input, "\n")] = 0;

        command = input[0];


        switch (command) {
            case 'a':
                addContact(input + 2); /* Pass the input string after "a " */
                break;
            case 'l':
                // listContacts();
                break;
            case 'p':
                // searchContacts(input + 2);
                break;
            case 'r':
                // deleteContact(input + 2);
                break;
            case 'e':
                // updateEmail(input + 2);
                break;
            case 'c':
                // countEmails(input + 2);
                break;
            case 'x':
                return EXIT_SUCCESS; /* Termina o programa com sucesso (STDLIB) */
            default:
                printf("ERRO: Comando desconhecido\n");
        }
        
    }
    return EXIT_FAILURE;            

}
