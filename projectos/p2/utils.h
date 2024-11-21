/* utils.h */
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "manager.h"

/* Helper function declarations */
Contact inputToContact(char *inputFields[]);
int checkContact(Contact currentContact, Contact comparableContact);


#endif /* UTILS_H */