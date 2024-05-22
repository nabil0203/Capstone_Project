#include <stdio.h>
#include <stdlib.h> // used for case 0, exit(0);

struct medicine
{
    int id;
    char name[50];
    char company[50];
    char drug[50];
    int price, quantity;
};
int itemCount = 0;

void addMedicine()
{
    struct medicine newMedicine;

    printf("\nAdding Medicine:\n");
    printf("\nEnter ID: ");
    scanf("%d", &newMedicine.id);
    printf("Enter Name: ");

    getchar(); // getchar() function is used to read one character at a time from the key board.When this function is executed, the computer will wait for a key to be pressed and assigns the value to the variable when the “enter” key pressed.

    gets(newMedicine.name);
    printf("Enter Company Name: ");
    gets(newMedicine.company);
    printf("Enter Drug: ");
    gets(newMedicine.drug);
    printf("Enter Price: ");
    scanf("%d", &newMedicine.quantity);
    printf("Enter Quantity: ");
    scanf("%d", &newMedicine.price);
    printf("Medicine Added Successfully.\n\n");
    getchar();
    printf("Press m for menu, e for exit: ");
    char choice;
    scanf("%c", &choice);
    if (choice == 'm')
    {
        printf("\e[1;1H\e[2J"); // to clear the terminal, need to watch yt
    }
    else if (choice == 'e')
    {
        printf("\nThank You. Come Again!\n");
        exit(0);
    }
}

void showList()
{

    printf("\nViewing Item\n");
    for (int i = 0; i < itemCount; i++)
    {
        printf("ID: %d, Name: %s, Price: %.2f, Quantity: %d\n", items[i].id, items[i].name, items[i].price, items[i].quantity);
    }
}
// void updateMedicine(){

// }
// void removeMedicine(){

// }
// void purchaseMedicine(){

// }

int main()
{

    int choice;
    while (1)
    {

        printf("\n~~~~~~~~~~~~~ WELCOME ~~~~~~~~~~~~~\n");
        printf("\n~ Medical Store Management System ~\n");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("1. Add Medicine\n");
        printf("2. Show Medicine List\n");
        printf("3. Update Medicine\n");
        printf("4. Remove Medicine\n");
        printf("5. Purchase Medicine\n");
        printf("0. Exit\n");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Enter your Choice: ");

        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addMedicine();
            break;
        case 2:
            showList();
            break;
        // case 3:
        //     updateMedicine();
        //     break;
        // case 4:
        //     removeMedicine();
        //     break;
        // case 5:
        //     purchaseMedicine();
        //     break;
        case 0:
            printf("\nThank You. Come Again!\n");
            exit(0);
        default:
            printf("Invalid choice. Try again.\n\n");
            break;
        }
    }
    return 0;
}