#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ITEMS 100

struct Item {
    int id;
    char name[50];
    char company[50];
    char drug[50];
    int price, quantity;
};

struct Item items[MAX_ITEMS];
int itemCount = 0;
int databaseLoaded = 0;

// Function prototypes
void addMedicine();
void saveItemsToFile();
void loadItemsFromFile();
void showList();
void removeMedicine();
void calculateBill();
void updateMedicine();

void addMedicine() {
    printf("\nAdding Item\n");
    struct Item newItem;

    printf("Enter ID: ");
    scanf("%d", &newItem.id);
    getchar();  // Consume the newline character left by scanf

    printf("Enter Name: ");
    fgets(newItem.name, sizeof(newItem.name), stdin);
    newItem.name[strcspn(newItem.name, "\n")] = '\0';  // Remove the newline character

    printf("Enter Company Name: ");
    fgets(newItem.company, sizeof(newItem.company), stdin);
    newItem.company[strcspn(newItem.company, "\n")] = '\0';  // Remove the newline character

    printf("Enter Drug: ");
    fgets(newItem.drug, sizeof(newItem.drug), stdin);
    newItem.drug[strcspn(newItem.drug, "\n")] = '\0';  // Remove the newline character

    printf("Enter Price: ");
    scanf("%d", &newItem.price);

    printf("Enter Quantity: ");
    scanf("%d", &newItem.quantity);

    items[itemCount++] = newItem;
    saveItemsToFile();  // Save to file immediately after adding
}

void saveItemsToFile() {
    FILE *fp = fopen("items.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < itemCount; i++) {
        fprintf(fp, "%d\n%s\n%s\n%s\n%d\n%d\n", items[i].id, items[i].name, items[i].company, items[i].drug, items[i].price, items[i].quantity);
    }
    fclose(fp);
}

void loadItemsFromFile() {
    FILE *fp = fopen("items.txt", "r");
    if (fp == NULL) {
        itemCount = 0;
        return;
    }

    itemCount = 0;
    while (fscanf(fp, "%d\n", &items[itemCount].id) == 1) {
        fgets(items[itemCount].name, sizeof(items[itemCount].name), fp);
        items[itemCount].name[strcspn(items[itemCount].name, "\n")] = '\0';  // Remove the newline character

        fgets(items[itemCount].company, sizeof(items[itemCount].company), fp);
        items[itemCount].company[strcspn(items[itemCount].company, "\n")] = '\0';  // Remove the newline character

        fgets(items[itemCount].drug, sizeof(items[itemCount].drug), fp);
        items[itemCount].drug[strcspn(items[itemCount].drug, "\n")] = '\0';  // Remove the newline character

        fscanf(fp, "%d\n%d\n", &items[itemCount].price, &items[itemCount].quantity);
        itemCount++;
    }
    fclose(fp);
    databaseLoaded = 1;
}

void showList() {
    printf("\nViewing Item\n");
    if (itemCount == 0) {
        printf("No medicine found.\n");
    } else {
        for (int i = 0; i < itemCount; i++) {
            printf("ID: %d, Name: %s, Company: %s, Drug: %s, Price: %d, Quantity: %d\n", items[i].id, items[i].name, items[i].company, items[i].drug, items[i].price, items[i].quantity);
        }
    }
}

void removeMedicine() {
    printf("\nDeleting Item\n");
    int idToDelete;
    printf("Enter ID of item to delete: ");
    scanf("%d", &idToDelete);

    int found = 0;
    for (int i = 0; i < itemCount; i++) {
        if (items[i].id == idToDelete) {
            found = 1;
            for (int j = i; j < itemCount - 1; j++) {
                items[j] = items[j + 1];
            }
            itemCount--;
            break;
        }
    }

    if (found) {
        printf("Item with ID %d deleted.\n", idToDelete);
        saveItemsToFile();
    } else {
        printf("Item with ID %d not found.\n", idToDelete);
    }
}

void calculateBill() {
    printf("\nCalculating Bill\n");
    float totalBill = 0.0;

    printf("Enter the ID of the item to purchase: ");
    int itemID;
    scanf("%d", &itemID);

    printf("Enter the quantity of the item: ");
    int quantity;
    scanf("%d", &quantity);

    int found = 0;
    for (int j = 0; j < itemCount; j++) {
        if (items[j].id == itemID) {
            found = 1;
            if (quantity <= items[j].quantity) {
                printf("Item %d: %s x %d = %d\n", itemID, items[j].name, quantity, items[j].price * quantity);
                totalBill = totalBill + (items[j].price * quantity);
                items[j].quantity -= quantity;
            } else {
                printf("Stock not available. Only %d units available.\n", items[j].quantity);
            }
            break;
        }
    }
    if (!found) {
        printf("Item with ID %d not found.\n", itemID);
    }

    printf("Total Bill: %.2f\n", totalBill);
    saveItemsToFile();  // Save the updated quantity to file
}

void updateMedicine() {
    int id;
    printf("Enter Medicine ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < itemCount; i++) {
        if (items[i].id == id) {
            printf("Enter Updated Price: ");
            scanf("%d", &items[i].price);
            printf("Enter Updated Quantity: ");
            scanf("%d", &items[i].quantity);
            printf("Medicine details updated successfully!\n");
            saveItemsToFile();
            return;
        }
    }
    printf("Medicine not found!\n");
}

int main() {
    int loadChoice;
    printf("Do you want to load the database? (1 for Yes, 0 for No): ");
    scanf("%d", &loadChoice);

    if (loadChoice == 1) {
        loadItemsFromFile();
        if (itemCount == 0) {
            printf("No data found in the database.\n");
        } else {
            printf("Database loaded successfully.\n");
        }
    } else {
        printf("\nDatabase will not be loaded. Starting with an empty inventory.\n");
        itemCount = 0;
    }

    int choice;
    while (1) {
        printf("\n~~~~~~~~~~~~~~~ WELCOME ~~~~~~~~~~~~~~~\n");
        printf("\n~~~ Medical Store Management System ~~~\n");
        printf("\n~\n\n");
        printf("1. Add Medicine\n");
        printf("2. Show Medicine List\n");
        printf("3. Update Medicine\n");
        printf("4. Remove Medicine\n");
        printf("5. Calculate bill\n");
        printf("0. Exit\n");
        printf("\n~\n");
        printf("Enter your Choice: ");

        scanf("%d", &choice);
        getchar();  // Consume the newline character left by scanf
        switch (choice) {
        case 1:
            addMedicine();
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