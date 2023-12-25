#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct login {
    char fname[15];
    char lname[20];
    char username[20];
    char password[20];
};

typedef struct
{
    int id;
    char name[50];
    int number;
    double price;
} item;

//Check id
int idExists(int id){
    FILE *file = fopen("items.txt","r");
    item itemcur;

    while (fscanf(file, "%d %s %d %lf\n", &itemcur.id, itemcur.name, &itemcur.number, &itemcur.price) != EOF) {
        if (itemcur.id == id) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void additem(){
    FILE *file = fopen("items.txt","a");
    item newItem;

    printf("Enter item name: \n");
    scanf("%s",newItem.name);
    printf("Enter item ID: \n");
    scanf("%d",&newItem.id);            //     check if id exists

    while(idExists(newItem.id)){
        printf("This ID already exists.Enter another.");
        scanf("%d",&newItem.id);
    }

    printf("Enter item quantity: \n");
    scanf("%d",&newItem.number);

    printf("Enter item price: \n");
    scanf("%lf",&newItem.price);


    fprintf(file, "%d %s %d %.2f\n", newItem.id, newItem.name, newItem.number, newItem.price);
    fclose(file);
    system("cls");
}

void removeitem(){
    FILE *file = fopen("items.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    item itemcur;
    int idToRemove;

    printf("Enter item ID: \n");
    scanf("%d", &idToRemove);

    while (fscanf(file, "%d %s %d %lf\n", &itemcur.id, itemcur.name, &itemcur.number, &itemcur.price) != EOF) {
        if (itemcur.id != idToRemove) {
            fprintf(tempFile, "%d %s %d %.2f\n", itemcur.id, itemcur.name, itemcur.number, itemcur.price);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove("items.txt");                    /*quickfix*/
    rename("temp.txt","items.txt");
    system("cls");

}

void viewitem(){
    FILE *file = fopen("items.txt","r");
    item itemcur;

   while (fscanf(file, "%d %s %d %lf\n", &itemcur.id, itemcur.name, &itemcur.number, &itemcur.price) != EOF) {
        printf("ID: %d\nName: %s\nPrice: %.2f\nQuantity: %d\n\n", itemcur.id, itemcur.name, itemcur.price,itemcur.number);
    }

    fclose(file);
    printf("\n\n\n\nPress enter to continue.\n\n");
    getchar();
    system("cls");
}

void changeItem(){
    FILE *file = fopen("items.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    item itemcur;
    int idToChange;
    double newPrice;
    int newId;
    int newNumber;

    printf("Enter item ID: \n");
    scanf("%d", &idToChange);
    printf("Enter new ID: \n");
    scanf("%d", &newId);
    printf("Enter new price: \n");
    scanf("%lf", &newPrice);
    printf("Enter new quantity: \n");
    scanf("%d", &newNumber);


    while(idExists(newId)){
        printf("This ID already exists.Enter another.");
        scanf("%d",&newId);
    }
    while (fscanf(file, "%d %s %d %lf\n", &itemcur.id, itemcur.name, &itemcur.number, &itemcur.price) != EOF) {
        if (itemcur.id != idToChange) {
            fprintf(tempFile, "%d %s %d %.2f\n", itemcur.id, itemcur.name, itemcur.number, itemcur.price);
        } else {
            itemcur.price = newPrice;
            itemcur.id = newId;
            itemcur.number = newNumber;
            fprintf(tempFile, "%d %s %d %.2f\n", itemcur.id, itemcur.name, itemcur.number, itemcur.price);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove("items.txt");
    rename("temp.txt","items.txt");
    system("cls");
}

void calculateTotalValue(){
    FILE *file = fopen("items.txt","r");
    item itemcur;
    double totalValue = 0;

    while (fscanf(file, "%d %s %d %lf\n", &itemcur.id, itemcur.name, &itemcur.number, &itemcur.price) != EOF) {
        totalValue += itemcur.price * itemcur.number;
    }

    printf("Value of all the items : %.2f\n", totalValue);

    fclose(file);
    printf("\n\n\n\nPress enter to continue.\n\n");
    getchar();
    system("cls");
}

void calculateIndividualValues(){
    FILE *file = fopen("items.txt","r");
    item itemcur;

    while (fscanf(file, "%d %s %d %lf\n", &itemcur.id, itemcur.name, &itemcur.number, &itemcur.price) != EOF) {
        double value = itemcur.price * itemcur.number;
        printf("Value of item %s (ID: %d): %.2f\n", itemcur.name, itemcur.id, value);
    }
    fclose(file);
    printf("\n\n\n\nPress enter to continue.\n\n");
    getchar();
    system("cls");

}

void registerUser(void) {
    struct login l;
    FILE *file;
    file = fopen("login.txt","a");
    if (file == NULL) {
        fputs("Error",stderr);
        exit(1);
    }
    
    printf("\nWelcome, \nplease enter your first name.\n");
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
            system("cls");
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

        printf("\n\n[1]Add Item\n[2]Remove Item\n[3]View Items\n[4]Change Item\n[5]Calculate Total Value\n[6]Calculate Values Individually\n\n\n\n\n[9]Exit\n\n\nEnter option:");
        scanf("%d",&option);
        getchar();
        switch (option)
        {
        case 1:
            additem();
            break;
        case 2:
            removeitem();
            break;
        case 3:
            viewitem();
            break;
        case 4:
            changeItem();
            break;
        case 5:
            calculateTotalValue();
            break;
        case 6:
            calculateIndividualValues();
            break;
        case 9:
            exit(0);
            break;
        default:
            printf("\nInvalid option.\n");
        }

    }

}