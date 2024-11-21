#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "contact.h"
typedef struct node { 
    Contact contact;
    struct node *next; 
}* link;


void HTinit(int m);
void HTinsert(Contact contact); 
void HTdelete(Contact contact); 
Contact HTsearch(Key v);






#endif