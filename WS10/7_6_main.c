#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ItemToPurchase.h"

int main() {
    ItemToPurchase item1, item2;
    char c;

    // Item 1 input
    printf("Item 1\nEnter the item name:\n");
    fgets(item1.itemName, 50, stdin);
    item1.itemName[strlen(item1.itemName) - 1] = '\0';

    printf("Enter the item price:\n");
    scanf("%d", &item1.itemPrice);

    printf("Enter the item quantity:\n");
    scanf("%d", &item1.itemQuantity);
    
   c = getchar();
   while(c != '\n' && c != EOF) {
     c = getchar();
   }
    
    // Input for item 2
    printf("\nItem 2\n");
    printf("Enter the item name:\n");
    fgets(item2.itemName, 50, stdin);
    item2.itemName[strlen(item2.itemName) - 1] = '\0';


    printf("Enter the item price:\n");
    scanf("%d", &item2.itemPrice);

    printf("Enter the item quantity:\n");
    scanf("%d", &item2.itemQuantity);

    printf("\nTOTAL COST\n");
    PrintItemCost(item1);
    PrintItemCost(item2);

    printf("\nTotal: $%d\n", item1.itemPrice * item1.itemQuantity + item2.itemPrice * item2.itemQuantity);

    return 0;
}

