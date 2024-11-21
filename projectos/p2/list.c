#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "list.h"


void insertNode(link head, Contact contact){
    link new = (link)malloc(sizeof(struct node));
    new->contact = contact;
    new->next = head;
    head = new;
}

void removeNode(link head, Contact contact){
    link t, prev;
    for(t = head, prev = NULL; t != NULL;prev = t, t = t->next) { 
        if(strcmp(t->contact->name, contact->name) == 0) {
            if(t == head)
                head = t->next;
            else
                prev->next = t->next;
            free(t->contact->name);
            free(t->contact->email);
            free(t->contact->phoneno);
            free(t);
        } 
    }
    return head;

}

Contact searchNode(link head, Key v){
    link t;
    for (t=head; t!=NULL; t=t->next){
        if(strcmp(t->contact->name, v)){
            return t->contact;
        }
    }
    return NULL;
}

link destroyList(link head){
    
}