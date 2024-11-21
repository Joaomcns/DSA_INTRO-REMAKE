#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "contact.h"
typedef struct node { 
    Contact contact;
    struct node *next; 
}* link;


void STinit(int m);
void STinsert(Contact contact); 
void STdelete(Contact contact); 
Contact STsearch(Key v);






#endif