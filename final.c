#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ITEMS 100

struct Item
{
    char id[50];
    char name[50];
    char company[50];
    char drug[50];
    float price;
    int quantity;
};

struct Item items[MAX_ITEMS];
int itemCount = 0;
int databaseLoaded = 0;

void addMedicine()
{
    printf("\nAdding Item\n");

    struct Item newItem;

    getchar();

    printf("Enter ID: ");
    gets(newItem.id);

    printf("Enter Name: ");
    gets(newItem.name);

    printf("Enter Company Name: ");
    gets(newItem.company);

    printf("Enter Drug: ");
    gets(newItem.drug);

    printf("Enter Price: ");
    scanf("%f", &newItem.price);

    printf("Enter Quantity: ");
    scanf("%d", &newItem.quantity);

    items[itemCount++] = newItem;

    printf("\n---New Item Added Successfully---\n");
}

void saveItemsToFile()
{
    FILE *fp = fopen("item.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < itemCount; i++)
    {
        fprintf(fp, "%s %s %s %s %.2f %d\n", items[i].id, items[i].name, items[i].company, items[i].drug, items[i].price, items[i].quantity);
    }

    fclose(fp);
}

void loadItemsFromFile()
{
    system("cls");
    FILE *fp = fopen("item.txt", "r");
    if (fp == NULL)
    {
        // Initialize the itemCount variable to 0
        itemCount = 0;
        return;
    }

    itemCount = 0;
    while (fscanf(fp, "%s %s %s %s %f %d", items[itemCount].id, items[itemCount].name, items[itemCount].company, items[itemCount].drug, &items[itemCount].price, &items[itemCount].quantity) == 6)
    {
        itemCount++;
    }
    fclose(fp);
    databaseLoaded = 1;
}

void showList()
{
    printf("\nViewing Item:-\n");
    if (itemCount == 0)
    {
        printf("No medicine found.\n");
    }
    else
    {
        for (int i = 0; i < itemCount; i++)
        {
            printf("ID: %s || Name: %s || Company: %s || Drug: %s || Price: %.2f || Quantity: %d\n", items[i].id, items[i].name, items[i].company, items[i].drug, items[i].price, items[i].quantity);
        }
    }
}

void updateMedicine()
{
    char id[50];
    printf("Enter Medicine ID to update: ");
    scanf("%s", id);
    for (int i = 0; i < itemCount; i++)
    {
        if (strcmp(items[i].id, id) == 0)
        {
            printf("Enter Updated Price: ");
            scanf("%f", &items[i].price);
            printf("Enter Updated Quantity: ");
            scanf("%d", &items[i].quantity);
            printf("\n---Item Updated Successfully---\n");
            saveItemsToFile();
            return;
        }
    }
    printf("---Medicine not found!---\n");
}

void removeMedicine()
{
    printf("\nDeleting Item\n");
    char idToDelete[50];
    printf("Enter ID of item to delete: ");
    scanf("%s", idToDelete);

    int found = 0;
    for (int i = 0; i < itemCount; i++)
    {
        if (strcmp(items[i].id, idToDelete) == 0) // strcmp function used to compares two strings alphabetically
        {
            found = 1;
            for (int j = i; j < itemCount - 1; j++)
            {
                items[j] = items[j + 1];
            }
            itemCount--;
            break;
        }
    }

    if (found)
    {
        printf("\n---Item Removed Successfully---\n");
        saveItemsToFile();
    }
    else
    {
        printf("---Item with ID %s not found.---\n", idToDelete);
    }
}

void calculateBill()
{
    printf("\nCalculating Bill\n");
    float totalBill = 0.0;

    printf("Enter the ID of the item to purchase: ");
    char itemID[50];
    scanf("%s", itemID);

    printf("Enter the quantity of the item: ");
    int quantity;
    scanf("%d", &quantity);

    int found = 0;
    for (int j = 0; j < itemCount; j++)
    {
        if (strcmp(items[j].id, itemID) == 0)
        {
            found = 1;
            if (quantity <= items[j].quantity)
            {
                printf("Item %s: %s x %d = %.2f\n", itemID, items[j].name, quantity, items[j].price * quantity);

                totalBill = totalBill + (items[j].price * quantity);

                items[j].quantity = items[j].quantity - quantity;
            }
            else
            {
                printf("---Stock not available. Only %d units available.---\n", items[j].quantity);
            }
            break;
        }
    }
    if (!found)
    {
        printf("---Item with ID %s not found.---\n", itemID);
    }

    printf("Total Bill: %.2f\n", totalBill);
}

int main()
{

    printf("\n~~~~~~~~~~~~~~~ WELCOME ~~~~~~~~~~~~~~~\n");
    printf("\n~~~ Medical Store Management System ~~~\n");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    
    int loadChoice;
    printf("\nDo you want to load Previous Database? (1 for Yes, 0 for No): ");
    scanf("%d", &loadChoice);

    if (loadChoice == 1)
    {
        loadItemsFromFile();
        if (itemCount == 0)
        {
            printf("\nNo data found in the Database. Starting with the Main Menu-\n");
        }
        else
        {
            printf("\nDatabase loaded Successfully.\n");
        }
    }
    else
    {
        printf("\nDatabase will not be loaded. Starting with the Main Menu- \n");
        itemCount = 0;
    }

    int choice;
    while (1)
    {

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\n~~~~~~~ Main Menu ~~~~~~~~\n");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("1. Add Medicine\n");
        printf("2. Show Medicine List\n");
        printf("3. Update Medicine\n");
        printf("4. Remove Medicine\n");
        printf("5. Calculate bill\n");
        printf("0. Exit\n\n~");
        printf("\nEnter your Choice: ");

        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addMedicine();
            saveItemsToFile();
            break;
        case 2:
            showList();
            break;
        case 3:
            updateMedicine();
            break;
        case 4:
            removeMedicine();
            break;
        case 5:
            calculateBill();
            break;
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