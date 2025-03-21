#include "manager.h"
#include "utils.h"

int n_contacts = 0;
link listHead  = NULL;


/*function to add new contact*/
void addContact(const char *input){
    int fieldCount;
    Contact currentContact, comparableContact;
    char *fields[CONTACT_FIELDS] = { NULL } ;

    /*Make a copy of the input string for strtok*/
    char *input_copy = strdup(input); 
    /*Parse the input string using strtok*/
    char *token = strtok(input_copy, " ");

    while(token != NULL && fieldCount < CONTACT_FIELDS) {
        fields[fieldCount++] = token;
        token = strtok(NULL, ":");
    }

    currentContact = newContact(fields[0], fields[1], fields[2]);

    if (!n_contacts){
        HTinit(n_contacts);
        // add to data structures
        return;
    }

    if (checkContact){
        /* add to hashtable
           add to linkedList 
        */   
        return;
    }

    printf("Nome existente.\n");    
    return;              

}

