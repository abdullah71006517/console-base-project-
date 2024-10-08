#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Product {
    int productID;
    char name[50];
    char category[30];
    int quantity;
    float price;
    struct Product* next;
} Product;

void addProduct(Product** head);
void updateProduct(Product* head);
void removeProduct(Product** head);
void searchProduct(Product* head);
void displayInventory(Product* head);
void sortInventory(Product** head, int choice);
void processOrder(Product** head);
void generateReport(Product* head);
void swap(Product* a, Product* b);

int main() {
    Product* inventory = NULL;
    while(1) {
        int s;
        printf("  enter admin Secureity code:) ");
        scanf("%d", &s);
        if(s == 420) {
            int choice;
            while(1) {
                printf("\n--- beauty product  Management System ---\n");
                printf("1. Add Product\n");
                printf("2. Update Product\n");
                printf("3. Remove Product\n");
                printf("4. Search Product\n");
                printf("5. Display Inventory\n");
                printf("6. Sort product \n");
                printf("7. Process Order\n");
                printf("8. Generate Report\n");
                printf("9. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch(choice) {
                    case 1:
                        addProduct(&inventory);
                        break;
                    case 2:
                        updateProduct(inventory);
                        break;
                    case 3:
                        removeProduct(&inventory);
                        break;
                    case 4:
                        searchProduct(inventory);
                        break;
                    case 5:
                        displayInventory(inventory);
                        break;
                    case 6:
                        sortInventory(&inventory, 1);
                        break;
                    case 7:
                        processOrder(&inventory);
                        break;
                    case 8:
                        generateReport(inventory);
                        break;
                    case 9:
                        printf("Exiting the system. Goodbye!\n");
                        exit(0);
                    default:
                        printf("Invalid choice! Try again.\n");
                }
            }
        } else {
            printf("\n sorry wrong code try again\n ");
        }
    }
    return 0;
}

void addProduct(Product** head) {
    Product* newProduct = (Product*)malloc(sizeof(Product));
    printf("Enter Product ID: ");
    scanf("%d", &newProduct->productID);
    printf("Enter Product Name: ");
    scanf(" %[^\n]%*c", newProduct->name);
    printf("Enter Product Category: ");
    scanf(" %[^\n]%*c", newProduct->category);
    printf("Enter Quantity: ");
    scanf("%d", &newProduct->quantity);
    printf("Enter Price per Unit: ");
    scanf("%f", &newProduct->price);
    newProduct->next = *head;
    *head = newProduct;
    printf("Product added successfully!\n");
}

void updateProduct(Product* head) {
    int id;
    printf("Enter Product ID to update: ");
    scanf("%d", &id);
    Product* temp = head;
    while (temp != NULL) {
        if (temp->productID == id) {
            printf("Product found!\n");
            printf("Enter new Quantity: ");
            scanf("%d", &temp->quantity);
            printf("Enter new Price: ");
            scanf("%f", &temp->price);
            printf("Product updated successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Product not found!\n");
}

void removeProduct(Product** head) {
    int id;
    printf("Enter Product ID to remove: ");
    scanf("%d", &id);
    Product* temp = *head;
    Product* prev = NULL;

    while (temp != NULL && temp->productID != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Product not found!\n");
        return;
    }

    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Product removed successfully!\n");
}

void searchProduct(Product* head) {
    int id;
    printf("Enter Product ID to search: ");
    scanf("%d", &id);
    Product* temp = head;
    while (temp != NULL) {
        if (temp->productID == id) {
            printf("Product found!\n");
            printf("ID: %d\nName: %s\nCategory: %s\nQuantity: %d\nPrice: %.2f\n",
                   temp->productID, temp->name, temp->category, temp->quantity, temp->price);
            return;
        }
        temp = temp->next;
    }
    printf("Product not found!\n");
}

void displayInventory(Product* head) {
    Product* temp = head;
    printf("\n--- Inventory ---\n");
    while (temp != NULL) {
        printf("ID: %d | Name: %s | Category: %s | Quantity: %d | Price: %.2f\n",
               temp->productID, temp->name, temp->category, temp->quantity, temp->price);
        temp = temp->next;
    }
}

void swap(Product* a, Product* b) {
    int tempID = a->productID;
    char tempName[50], tempCategory[30];
    int tempQuantity = a->quantity;
    float tempPrice = a->price;

    a->productID = b->productID;
    b->productID = tempID;

    strcpy(tempName, a->name);
    strcpy(a->name, b->name);
    strcpy(b->name, tempName);

    strcpy(tempCategory, a->category);
    strcpy(a->category, b->category);
    strcpy(b->category, tempCategory);

    a->quantity = b->quantity;
    b->quantity = tempQuantity;

    a->price = b->price;
    b->price = tempPrice;
}

void sortInventory(Product** head, int choice) {
    if (*head == NULL) {
        printf("Inventory is empty!\n");
        return;
    }

    Product* temp;
    int swapped;
    do {
        swapped = 0;
        temp = *head;
        while (temp->next != NULL) {
            if (strcmp(temp->name, temp->next->name) > 0) {
                swap(temp, temp->next);
                swapped = 1;
            }
            temp = temp->next;
        }
    } while (swapped);

    printf("Inventory sorted by product name!\n");
}

void processOrder(Product** head) {
    int id, quantity;
    printf("Enter Product ID for order: ");
    scanf("%d", &id);
    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    Product* temp = *head;
    while (temp != NULL) {
        if (temp->productID == id) {
            if (temp->quantity >= quantity) {
                temp->quantity -= quantity;
                printf("Order processed successfully! Remaining stock: %d\n", temp->quantity);
            } else {
                printf("Insufficient stock!\n");
            }
            return;
        }
        temp = temp->next;
    }
    printf("Product not found!\n");
}

void generateReport(Product* head) {
    Product* temp = head;
    int totalItems = 0;
    float totalValue = 0;

    printf("\n--- Inventory Report ---\n");
    while (temp != NULL) {
        totalItems += temp->quantity;
        totalValue += temp->price * temp->quantity;
        temp = temp->next;
    }
    printf("Total items in stock: %d\n", totalItems);
    printf("Total inventory value: $%.2f\n", totalValue);
}
