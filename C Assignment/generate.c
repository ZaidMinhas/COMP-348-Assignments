# include <stdio.h>
# include <string.h>
# include <stdlib.h>
#include <time.h>
#include "Person.h"

void sort(Person *,int , int );
void WriteTable( char *headers[], char *fileName, int col_count,int *columns, Person *p, int row_count);
char* get_FirstName(int);
char* get_LastName(int);
char* get_Country(int);
char* get_EmailSuffix(int);

//Since ID starts from 0 and increases by every record made
static int ID = 0;

/*
*Flags to mark if a field has been generated
*incase field duplication so that new data isnt generated
*or when emails are being generated without names being made first
*/
static int ID_flag = 0;
static int fname_flag = 0;
static int lname_flag = 0;
static int country_flag = 0;
static int phone_flag = 0;
static int email_flag = 0;
static int sin_flag = 0;
static int pass_flag = 0;

//Increase value of static field ID
void generate_UserID(Person *p){
    if (ID_flag) return;
    ID_flag = 1;
    p->user_id = ++ID;
    
}

//generate random number and get name from io.c
void generate_FirstName(Person *p){
    if (fname_flag) return;
    fname_flag = 1;
    int random_number = rand() % 1000;
    char* first_name = get_FirstName(random_number);
    

    strncpy(p->first_name, first_name, strlen(first_name));
    p->first_name[strlen(first_name) - 1] = '\0';
    free(first_name);

}

//generate random number and get name from io.c
void generate_LastName(Person *p){
    if (lname_flag) return;
    lname_flag = 1;
    int random_number = rand() % 1000;
    char* last_name = get_LastName(random_number);

    strncpy(p->last_name, last_name, strlen(last_name));
    p->last_name[strlen(last_name) - 1] = '\0';
    free(last_name);
}

//generate random number and get country from io.c
void generate_Country(Person *p){
    if (country_flag) return;
    country_flag = 1;
    int random_number = rand() % 195;
    char* country = get_Country(random_number);

    strncpy(p->country, country, strlen(country));
    p->country[strlen(country) - 1] = '\0';

    free(country);
}

//generate email from names and random suffix from io.c
void generate_Email(Person *p){
    if (!fname_flag) generate_FirstName(p);
    if (!lname_flag) generate_LastName(p);
    if (email_flag) return;
    email_flag = 1;

    int random_number = rand() % 100;
    char* email_suffix = get_EmailSuffix(random_number);
    char email[100];

    snprintf(email, 100, "%c%s@%s", p->first_name[0], p->last_name, email_suffix);
    strncpy(p->email, email, strlen(email));
    p->email[strlen(email) - 1] = '\0';

    free(email_suffix);

}

//Generate random 9 digit string
void generate_SIN(Person *p){
    if(sin_flag) return;
    sin_flag = 1;

    sprintf(p->SIN, "");
    for (int i = 0; i < 9; i++){
        sprintf(p->SIN + strlen(p->SIN), "%d", rand()%10);
    }
}

//Generate random phone number
void generate_PhoneNumber(Person *p){
    if (phone_flag) return;
    phone_flag = 1;

    //get random phone index
    int phone_index[10] = {398, 270, 925, 867, 209, 429, 908, 997,444, 219};
    sprintf(p->phone, "%d-", phone_index[rand() % 10]);

    //generate 4 digit phone line
    for (int i = 0; i < 4; i++){
        sprintf(p->phone + strlen(p->phone), "%d", rand()%10);
    }
}

//Generate random password
void generate_Password(Person *p){
    if (pass_flag) return;
    pass_flag = 1;

    //Generate length of password from 6 to 16
    int pass_len = (rand() % 11) + 6;

    //password cannot have space ascii
    sprintf(p->password, "");
    for (int i = 0; i < pass_len; i++){
        char c;
        do {
            c = rand()%94 + 33;
        }while (c == 44);
        sprintf(p->password + strlen(p->password), "%c", c);
    }

}
void generate(int col_count, int *columns ,int row_count, char *fileName){

    //column names to be used in header of csv file
    char *column_header[col_count];
    //what operation to do on each column is assigned to this list
    void (*op[col_count])(Person *);

    //Random number that will be used in the generators above
    srand(time(NULL));
    //Set ID to 0 for when code is continued
    ID = 0;


    for (int col = 0; col < col_count; col++){
        column_header[col] = (char *)malloc(15);
        switch (columns[col]){
            case 1:
            strcpy(column_header[col], "User ID");
            op[col] = generate_UserID;        
            break;

            case 2:
            strcpy(column_header[col], "First Name");
            op[col] = generate_FirstName;
            break;

            case 3:
            strcpy(column_header[col], "Last Name");
            op[col] = generate_LastName;
            break;

            case 4:
            strcpy(column_header[col], "Country");
            op[col] = generate_Country;
            break;

            case 5:
            strcpy(column_header[col], "Phone");
            op[col] = generate_PhoneNumber;
            break;

            case 6:
            strcpy(column_header[col], "Email");
            op[col] = generate_Email;
            break;

            case 7:
            strcpy(column_header[col], "SIN");
            op[col] = generate_SIN;
            break;

            case 8:
            strcpy(column_header[col], "Password");
            op[col] = generate_Password;
            break;
        }
    }
    
    //All records are stored in this pointer
    Person *p = malloc((row_count+1)*sizeof(Person));

    //assign data to this record
    for (int row = 0; row < row_count; row++){
        for (int col = 0; col < col_count; col++){
            op[col](p+row);  
        }
        // set all flags to 0 when each record is done
        ID_flag = 0; fname_flag = 0; lname_flag = 0; country_flag = 0; phone_flag = 0; email_flag = 0; sin_flag = 0; pass_flag = 0; 
        
    }

    //if sort column is ID then table is already sorted
    if (columns[0] != 1) {
        sort(p, row_count, columns[0]);
    }

    //Write header names and all data to file
    WriteTable(column_header,  fileName, col_count, columns, p, row_count);
    free(p);
}