#ifndef ITEMTOPURCHASE_H
#define ITEMTOPURCHASE_H

typedef struct ItemToPurchase {
    char itemName[50];
    int itemPrice;
    int itemQuantity;
}ItemToPurchase;

void MakeItemBlank(struct ItemToPurchase* input);
void PrintItemCost(struct ItemToPurchase input);

#endif
