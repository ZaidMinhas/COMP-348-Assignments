#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include "Person.h"

int compareFirstName(const void *x_void, const void *y_void){
    const Person *x = (Person *)x_void;
    const Person *y = (Person *)y_void;
    
    return strcasecmp(x->first_name, y->first_name);
}

int compareLastName(const void *x_void, const void *y_void){
    const Person *x = (Person *)x_void;
    const Person *y = (Person *)y_void;

    return strcasecmp(x->last_name, y->last_name);
}

int compareCountry(const void *x_void, const void *y_void){
    const Person *x = (Person *)x_void;
    const Person *y = (Person *)y_void;

    return strcasecmp(x->country, y->country);
}

int comparePhoneNum(const void *x_void, const void *y_void){
    const Person *x = (Person *)x_void;
    const Person *y = (Person *)y_void;

    return strcasecmp(x->phone, y->phone);
}

int compareEmail(const void *x_void, const void *y_void){
    const Person *x = (Person *)x_void;
    const Person *y = (Person *)y_void;

    return strcasecmp(x->email, y->email);
}

int compareSIN(const void *x_void, const void *y_void){
    const Person *x = (Person *)x_void;
    const Person *y = (Person *)y_void;

    return strcasecmp(x->SIN, y->SIN);
}

int comparePass(const void *x_void, const void *y_void){
    const Person *x = (Person *)x_void;
    const Person *y = (Person *)y_void;

    return strcasecmp(x->password, y->password);
}



void sort(Person *table,int rows, int sort_col){
    int (*comp)(const void *, const void*);

    switch (sort_col)
    {
    case 2:
        comp = compareFirstName;
        break;
    
    case 3:
        comp = compareLastName;
        break;
    
    case 4:
        comp = compareCountry;
        break;
    
    case 5:
        comp = comparePhoneNum;
        break;
    
    case 6:
        comp = compareEmail;
        break;
    
    case 7:
        comp = compareSIN;
        break;

    case 8:
        comp = comparePass;
        break;
    }
    
    qsort(table, rows, sizeof(Person), comp);
}