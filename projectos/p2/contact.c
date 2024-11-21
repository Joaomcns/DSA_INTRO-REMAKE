#include <stdio.h> 
#include <stdlib.h> 
#include "contact.h"

void freeContact(Contact a){ 
    free(a->name);
    free(a->email);
    free(a->phoneno);
    free(a);
}
void printContact(Contact a){
    printf("%s %s %s\n", a->name, a->email, a->phoneno);
}
Contact newContact(char* name,char* email, char* phoneno){
    Contact new = (Contact)malloc(sizeof(struct contact));
    new->name = strdup(name);
    new->email = strdup(email);
    new->phoneno = strdup(phoneno);

    return new;
}