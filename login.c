#include<stdio.h>
#include<string.h>
#include <time.h>
#define MAX_INPUT 100

int displayUsers(FILE *fptr);
int registerUser(FILE *fptr);
int loginUser(FILE *fptr);
void getDate(int* dateptr);
int adminMode(FILE *fptr);
int adminCheck(FILE *fptr);
int endProgram(FILE *fptr);
int checkMode(char mode, FILE *fptr);



typedef struct database
{
    char rollNo[MAX_INPUT];
    char email[MAX_INPUT];
    char username[MAX_INPUT];
    char password[MAX_INPUT];
    char dateOfReg[MAX_INPUT];
} db;


int main()
{

    char mode;
    FILE *fptr;
    fptr = fopen("db.txt", "a+");
    if (fptr == NULL)
    {
        printf("Database doesn't exist");
        return endProgram(fptr);
    }
    printf("Enter \'r\' to register or \'l\' to login: ");
    scanf("%c", &mode);
    return checkMode(mode, fptr);


}


int displayUsers(FILE *fptr)
{

    db users;
    int index = 0;
    while (!feof(fptr))
    {
        fscanf(fptr, "%s %s %s %s %s ",users.rollNo, users.email, users.username, users.password, users.dateOfReg);
        printf("\n\tRecord\t%d\n",++index);
        printf("Roll No:\t%s\n", users.rollNo);
        printf("Username:\t%s\n", users.username);
        printf("Email:\t%s\n", users.email);
        printf("Date of Registration:\t%s\n", users.dateOfReg);
        printf("------------------------------\n");
    }
    return adminMode(fptr);
    
}

int checkMode(char mode, FILE *fptr)
{
    
    if (mode == 'r' || mode == 'R')
    {
        return registerUser(fptr);
    }
    else if(mode == 'l' || mode == 'L')
    {
        return loginUser(fptr);
    }
    else if(mode == 'a' || mode == 'A')
        return adminCheck(fptr);
    else
        printf("Enter a valid mode");
        return endProgram(fptr);
    
}


int endProgram(FILE *fptr)
{
    if(fclose(fptr))
    {
        printf("Error closing the database connection");
        return 0;
    }
    else
        return 0;

}


int adminCheck(FILE *fptr)
{
    char password[] = "monopoly";
    char adminPass[MAX_INPUT];
    printf("Enter admin password: ");
    scanf("%s", &adminPass);
    if (strcmp(adminPass, password) == 0)
    {
        return adminMode(fptr);
    }
    else
        printf("Invalid Password");
        return endProgram(fptr);
    
}

int adminMode(FILE *fptr)
{
    char action;
    printf("d-display users, s-search users, e-exit: ");
    scanf(" %c", &action);
    if (action == 'e' || action == 'E')
    {
        printf("Thank You!");
        return endProgram(fptr);
    }
    else if(action == 'd' || action == 'D')
    {
        
        return displayUsers(fptr);
    }
    else
        printf("Enter a valid input\n");
        return adminMode(fptr);
}


void getDate(int* dateptr)
{
    int date[3];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    dateptr[0] = tm.tm_mday;
    dateptr[1] = tm.tm_mon + 1;
    dateptr[2] = tm.tm_year + 1900;
}

int loginUser(FILE *fptr)
{
    char username[MAX_INPUT];
    char password[MAX_INPUT];
    db users;
    printf("Enter your username: ");
    scanf("%s", username);
    while (!feof(fptr))
    {
        fscanf(fptr, "%*s %*s %s %s %*s ", users.username, users.password);
        if (strcmp(users.username, username) == 0)
        {
            printf("Enter your password: ");
            scanf("%s", password);
            if (strcmp(users.password, password) == 0)
            {
                printf("Welcome %s", username);
                return endProgram(fptr);   
            }
            else
                printf("Invalid Password");
                return endProgram(fptr);
            
        }  
    }
    printf("Invalid Username");
    return endProgram(fptr);
    
    
}


int registerUser(FILE *fptr)
{
    char rollNo[MAX_INPUT];
    char email[MAX_INPUT];
    char username[MAX_INPUT];
    char password[MAX_INPUT];
    char dateOfReg[MAX_INPUT];
    int dateBuff[3];
    printf("Enter your rollNo: ");
    scanf("%s", rollNo);
    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);
    getDate(dateBuff);
    sprintf(dateOfReg, "%d/%d/%d", dateBuff[0], dateBuff[1], dateBuff[2]);
    fprintf(fptr, "%s %s %s %s %s\n", rollNo, email, username, password, dateOfReg);
    
    return endProgram(fptr);
}
