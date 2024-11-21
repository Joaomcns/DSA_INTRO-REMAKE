#ifndef LLIST_H
#define LLIST_H
#include "hashtable.h"

link initList();
link insertBeginList(link head, Contact contact);
link removeListItem(link head, Contact contact);
contact searchList(link head, Key v);
link destroyList(link head);

#endif