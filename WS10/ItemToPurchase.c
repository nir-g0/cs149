#include "ItemToPurchase.h"
#include <stdio.h>
#include <string.h>


void MakeItemBlank(ItemToPurchase* input) {
    strcpy(input->itemName,"none");
    input->itemPrice = 0;
    input->itemQuantity = 0;
}

void PrintItemCost(ItemToPurchase input) {
    printf("%s %d @ $%d = $%d\n", input.itemName, input.itemQuantity, input.itemPrice, input.itemPrice * input.itemQuantity);
}

