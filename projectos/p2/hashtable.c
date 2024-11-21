#include <stdio.h> 
#include <stdlib.h> 
#include "hashtable.h"
#include "list.h"

static link *heads;
static int M;

int hashU(char *v, int M) {
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
        h = (a*h + *v) % M;
    return h; 
}


void HTinit(int m) {
    int i;
    M = m;
    heads = (link*)malloc(M*sizeof(link)); 
    for (i = 0; i < M; i++) heads[i] = NULL;
}

void HTinsert(Contact contact) {
    int i = hashU(key(contact), M);
    heads[i] = insertBeginList(heads[i], contact);
}
void HTdelete(Contact contact) {
    int i = hash(key(contact), M);
    heads[i] = removeItemList(heads[i], contact); 
}    
   
Contact HTsearch(Key v) {
    int i = hash(v, M);
    return searchList(heads[i], v);
}

void HTfree(){

}

