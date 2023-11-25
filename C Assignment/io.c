#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Person.h"

/*
* For the next four functions
* The nth line of each file is required
* so the loop runs n times to get that line of text
*/
char* get_FirstName(int n){
    FILE *fp;
    fp = fopen("first_names.txt", "r");
    char *f_name = malloc(50);
    for (int i = 0; i <= n; i++){
        fgets(f_name, 50, fp);
    }

    fclose(fp);
    return f_name;
}

char* get_LastName(int n){
    FILE *fp;
    fp = fopen("last_names.txt", "r");
    
    char *l_name = malloc(50);
    for (int i = 0; i <= n; i++){
        fgets(l_name, 50, fp);
    }
    fclose(fp);
    return l_name;
}

char* get_Country(int n){
    FILE *fp;
    fp = fopen("countries.txt", "r");

    char *country = malloc(50);
    for (int i = 0; i <= n; i++){
        fgets(country, 50, fp);
    }
    fclose(fp);
    return country;
}

char* get_EmailSuffix(int n){
    FILE *fp;
    fp = fopen("email_suffixes.txt", "r");

    char *email_suffix = malloc(50);
    for (int i = 0; i <= n; i++){
        fgets(email_suffix, 50, fp);
    }

    fclose(fp);
    return email_suffix;
}


void WriteTable(char *headers[], char *fileName, int col_count,int *columns, Person *p, int row_count){

    //create a .csv file
    FILE *fptr;
    strcat(fileName, ".csv");
    fptr = fopen(fileName, "w");

    if (fptr == NULL){
        perror("Cannot create/write to file");
        return;
    }

    //Write file header names
    for (int i = 0; i < col_count; i++){
        fprintf(fptr, "%s", headers[i]);
        free(headers[i]);
        if (i < col_count-1){
            fprintf(fptr, ", ");
        }
    }

    //New line after header
    fprintf(fptr, "\n");

    //Write every record to file one row at a time
    for (int row = 0; row < row_count; row++){
        for (int col = 0; col < col_count; col++){
            switch (columns[col]){
                case 1:
                    fprintf(fptr, "%d", (p+row)->user_id);
                    break;

                case 2:
                    fprintf(fptr, "%s", (p+row)->first_name);
                    break;

                case 3:
                    fprintf(fptr, "%s", (p+row)->last_name);
                    break;

                case 4:
                    fprintf(fptr, "%s", (p+row)->country);
                    break;

                case 5:
                    fprintf(fptr, "%s", (p+row)->phone);
                    break;

                case 6:
                    fprintf(fptr, "%s", (p+row)->email);
                    break;

                case 7:
                    fprintf(fptr, "%s", (p+row)->SIN);
                    break;

                case 8:
                    fprintf(fptr, "%s", (p+row)->password);
                    break;
            }
        
        //Dont insert comma for last column
        if (col < col_count-1){
            fprintf(fptr, ", ");
        }
        
    }
        //End each record with new line
        fprintf(fptr, "\n");
    }

    printf("\nTable written successfull to %s\n", fileName);
    fclose(fptr);
}
