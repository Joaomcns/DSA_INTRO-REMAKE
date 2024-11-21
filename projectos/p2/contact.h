#ifndef CONTACT_H
#define CONTACT_H
#define key(a) (a->name)

struct contact {
    char *name;
    char *email;
    char *phoneno;
};

typedef struct contact* Contact;

typedef char Key; /* tipo da chave */

void freeContact(Contact a); 
void printContact(Contact a); 
Contact newContact(char* name,char* email, char* phoneno);

#endif