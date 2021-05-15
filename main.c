/******************************************************************
* Projekt: Algorithmen und Datenstrukturen
* Dateiname: main.c
* Beschreibung: ???
* Autor: Max Mustermann
* Matr.-Nr.: 911911
* Erstellt: 1.1.1970
******************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define NOT_IMPLEMENTED_ERROR -1000

enum DIRECTION {
    FORWARD,
    REVERSE
} direction;

typedef struct _listEntry {
    int data;
    struct _listEntry *next;
} listEntry;

listEntry *start = NULL;

int put_entry(int position, int aktdata);

listEntry *create_entry(int data);

int del_entry(int position);

int find_entry(int value);

int del_list(void);

int get_anzentries(void);

int printall(enum DIRECTION direction);

int main(void) {
    put_entry(1, 1);
    put_entry(2, 2);
    put_entry(3, 3);
    put_entry(4, 4);
    put_entry(5, 5);
    put_entry(5, 6);
    put_entry(5, 7);

    printall(FORWARD);

    printf("Position: %d\n", find_entry(7));
    printf("size: %d\n", get_anzentries());
    return 0;
}

int put_entry(int position, int aktdata) {
    int i = 1;
    listEntry **tracer = &start;
    listEntry *newEntry = create_entry(aktdata);
    if (newEntry == NULL)
        return -1;

    // if postion is 0 put entry on start
    if (position == 0) {
        newEntry->next = *tracer;
        *tracer = newEntry;
        return 0;
    } else if (get_anzentries() == 0 && position == 1) {
        return put_entry(0, aktdata);
    } else if (position < 0)
        return -1;
    else if(position > 200000000)
        return -1;

    while ((i < position) && (*tracer)) {
        tracer = &(*tracer)->next;
        i++;
    }
    // if pointer is null and position not reached
    if (i != position) {
        *tracer = newEntry;
        printf("position not valid, added at the end of the list at position %d\n", i);
    } else {
        newEntry->next = *tracer;
        *tracer = newEntry;
    }
    return 0;
}

int printall(enum DIRECTION direction) {
    int i = 1;
    listEntry **tracer = &start;
    if (direction == FORWARD) {
        while (*tracer) {
            printf("Position: %d, Data: %d\n", i, (*tracer)->data);
            i++;
            tracer = &(*tracer)->next;
        }
    }
    return 0;
}

listEntry *create_entry(int data) {
    listEntry *newp;
    newp = (listEntry *) malloc(sizeof(listEntry));
    if (newp == NULL)
        return NULL;
    newp->data = data;
    newp->next = NULL;
    return newp;
}

int del_list(void) {
    listEntry **tracer = &start;
    listEntry *old;
    while (*tracer) {
        old = *tracer;
        *tracer = (*tracer)->next;
        free(old);
    }
    return 0;
}

/* Unterprogramm zum Loeschen eines Nutzdatenelements
*  Parameter: position   = Loeschpos.;
*  Return:    0          = Loeschen OK
*         negative Werte = Fehler
*/
int del_entry(int position) {
    if (position <= 0)
        return -1;
    int i = 0;
    listEntry **tracer = &start;
    listEntry *old;
    while (*tracer && i < position - 1) {
        tracer = &(*tracer)->next;
        i++;
    }
    if (!(*tracer))
        return -1;
    old = *tracer;
    *tracer = (*tracer)->next;
    free(old);
    return 0;
}

/* Unterprogramm zur Ermittlung der Elementanzahl
*  Parameter: keine
*  Return:    aktuelle Anzahl der Element
*/
int get_anzentries(void) {
    int i = 0;
    listEntry **tracer = &start;
    if (!*tracer)
        return 0;
    while (*tracer) {
        tracer = &(*tracer)->next;
        i++;
    }
    return i;
}


/* Unterprogramm zum Suchen eines Elementes
*  Parameter: value      = Zahl, nach der gesucht wird
*  Return:    0          = nicht gefunden
*         negative Werte = Fehler
*/
int find_entry(int value) {
    int i = 1;
    listEntry **tracer = &start;
    while (*tracer && (*tracer)->data != value) {
        tracer = &(*tracer)->next;
        i++;
    }
    if (*tracer)
        return i;
    else
        return -1;
}

