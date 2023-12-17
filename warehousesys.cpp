/* 
                                                    add item saving 
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct login {
    char fname[15];
    char lname[20];
    char username[20];
    char password[20];
};

void registerUser(void) {
    struct login l;
    FILE *file;
    file = fopen("login.txt","a");
    if (file == NULL) {
        fputs("Error",stderr);
        exit(1);
    }
    
    printf("\nWelcome, please enter your first name.\n");
    scanf("%s", l.fname);
    printf("\nEnter Surname:\n");
    scanf("%s", l.lname);
    printf("\nEnter Username:\n");
    scanf("%s", l.username);
    printf("\nEnter Password:\n");
    scanf("%s", l.password);

    fwrite(&l, sizeof(l), 1, file);
    fclose(file);

    printf("\n\nConfirming details..\n..\n..\nWelcome, %s!\n\n", l.fname);
    printf("\n\nSuccess\n");
    printf("Press any key to continue.");
    getchar();
    system("cls");
    login();
}

void login(void) {
    char username[20], password[20];
    FILE *file;
    file = fopen("login.txt","r");
    if (file == NULL) {
        fputs("Error",stderr);
        exit(1);
    }

    struct login l;
    printf("\n Enter your login credentials\n\n");
    printf("Username:   \n");
    scanf("%s", username);
    printf("\nPassword: \n");
    scanf("%s", password);

    while (fread(&l, sizeof(l), 1, file)) {
        if (strcmp(username, l.username) == 0 && strcmp(password, l.password) == 0) {
            printf("\nSuccess\n");
        } else {
            printf("\nIncorrect login.\n");
        }
    }
    fclose(file);
    return;
}

int main() {
    char username[20], password[20];
    int option;

    printf("-------------------------------\n");
    printf("-------------------------------\n");
    printf("-------------------------------\n\n\n");

    printf("Please login before proceeding: \n");
    printf("\n\n[1] Register\n[2] Login\n");
    scanf("%d", &option);
    getchar();
    if (option == 1) {
        system("cls");
        registerUser();
    } else if (option == 2) {
        system("cls");
        login();
    }

    while(true){

        printf("\n\n[1]Add Item\n[2]Remove Item\n[3]View Items\n[4]Exit\n");
        scanf("%d",&option);
        getchar();
        switch (option)
        {
        case 1:
            /* code */
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            return 0;
            break;
        
        default:
            printf("\nInvalid option.\n");
        }

    }

}