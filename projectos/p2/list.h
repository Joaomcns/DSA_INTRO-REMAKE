#ifndef LLIST_H
#define LLIST_H
#include "hashtable.h"


void insertContact(link head, Contact contact);
void removeContact(link head, Contact contact);
contact searchContact(link head, Key v);
link destroyList(link head);

#endif