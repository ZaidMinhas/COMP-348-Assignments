#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//function in generate.c
void generate(int col_count, int *columns ,int row_count ,char *fileName);

//Function that asks user to select generate or exit
int MenuOption(){
    printf("TableGen Menu\n");
    printf("-------------\n");
    printf("1. Generate new table\n");
    printf("2. Exit\n\n");
    printf("Selection: ");
    int a;
    do{
        scanf("%d", &a);
    } while(a != 1 && a != 2);
    
    system("clear");
    return a;
}

//Main function that loops until user exits
int main(){
    while (1){
        int input = MenuOption();
        if (input == 2){
            printf("Goodbye and thanks for using TableGen\n");
            return 0;
        }
        printf("Column Options\n");
        printf("--------------\n");
        printf("1. User ID\t 5. Phone Number\n");
        printf("2. First name\t 6. Email address\n");
        printf("3. Last name\t 7. SIN\n");
        printf("4. Country\t 8. Password\n");
        printf("\nEnter column list (comma-seperated, no spaces): ");
    
        //User enters string ie 1,2,3,5 or 3,2,5,6
        char str_col[100];
        
        scanf("%s", &str_col);
        char *token = strtok(str_col, ",");
    
        //Extracted columns from string
        int columns[100];
        int col_count = 0;
        while (token != NULL) {
            int num = atoi(token);
            columns[col_count++] = num;
            token = strtok(NULL, ",");
        }

        int row_count = 0;
        printf("Enter row count (1 < n < 1M): ");
        scanf("%d", &row_count);
    
        char name[100];
        printf("Enter output file name (no suffix): ");
        scanf("%s", name);

        printf("Summary of properties:\n");
        printf(" Columns: %d", columns[0]);
        for (int i = 1; i < col_count; i++){
            printf(",%d", columns[i]);
        }
        printf("\n Row count: %d\n", row_count);
        printf(" File name: %s\n", name);
        
        //Generate data and Output file
        generate(col_count, columns, row_count,name);
        

        char proceed;
        printf("\nPress 'c' or 'C' to continue ");
        do{
            scanf("%c", &proceed);
        } while ( (proceed != 'c') && (proceed != 'C'));
    }
    

}