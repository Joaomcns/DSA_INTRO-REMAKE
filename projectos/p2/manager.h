#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "contact.h"
#include "hashtable.h"
#include "list.h"

#define CONTACT_FIELDS 3

void addContact(const char *input);

#endif