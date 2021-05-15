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

void del_list(void);

int get_anzentries(void);

int printall(enum DIRECTION direction);

int main(void) {
    put_entry(0, 1);
    put_entry(1, 2);
    put_entry(8, 3);
    printall(FORWARD);
    return 0;
}

int put_entry(int position, int aktdata) {
    int i = 0;
    listEntry **tracer = &start;
    listEntry *newEntry = create_entry(aktdata);

    // if postion is 0 put entry on start
    if (position == 0) {
        newEntry->next = *tracer;
        *tracer = newEntry;
        return 0;
    }

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
}

int printall(enum DIRECTION direction) {
    int i = 0;
    listEntry **tracer = &start;
    if (direction == FORWARD) {
        while (*tracer) {
            printf("Position: %d, Data: %d\n", i, (*tracer)->data);
            i++;
            tracer = &(*tracer)->next;
        }
    }
}

listEntry *create_entry(int data) {
    listEntry *newp;
    newp = (listEntry *) malloc(sizeof(listEntry));
    newp->data = data;
    newp->next = NULL;
    return newp;
}

void del_list(void) {
    listEntry **tracer = &start;
    listEntry *old = start;
    while (*tracer) {
        old = tracer;
        tracer = &(*tracer)->next;
        free(old);
    }
}

/* Unterprogramm zum Loeschen eines Nutzdatenelements
*  Parameter: position   = Loeschpos.;
*  Return:    0          = Loeschen OK
*         negative Werte = Fehler
*/
int del_entry(int position) {
    int i = 0;
    listEntry **tracer = &start;
    listEntry *old;
    while (*tracer && i < position - 1) {
        tracer = &(*tracer)->next;
        i++;
    }
    if (!(*tracer))
        return -1;
    old = (*tracer)->next;
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
    int i = 0;
    listEntry **tracer = &start;
    while (*tracer && (*tracer)->data != value) {
        tracer = &(*tracer)->next;
        i++;
    }
    if (*tracer)
        return i;
    else
        return 0;
}

