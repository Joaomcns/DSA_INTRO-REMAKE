#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "list.h"



link createContact(link head,Contact contact){
    head = (link)malloc(sizeof(struct node));
    head->contact = contact;

}

void insertBeginList(link head, Contact contact){
    link new = (link)malloc(sizeof(struct node));
    new->contact = contact;
    new->next = head;
    head = new;
}

link removeItemList(link head, Contact contact){
    link t, prev;
    for(t = head, prev = NULL; t != NULL;prev = t, t = t->next) { 
        if(strcmp(t->contact->name, contact->name) == 0) {
            if(t == head)
                head = t->next;
            else
                prev->next = t->next;
            freeContact(t->contact);
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
    link temp;
    while (head != NULL){
        temp  = head;
        head = head->next;
        free(temp);
    }
    return head;
}