#include "utils.h"

Contact inputToContact(char *inputFields[]){
    return newContact(inputFields[0], inputFields[1], inputFields[2]);
}

int checkContact(Contact currentContact, Contact comparableContact){
    
}