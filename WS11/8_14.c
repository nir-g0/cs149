#include <stdio.h>
#include <string.h>

typedef struct ContactNode_struct {
   char contactName[100];
   char contactPhoneNumber[100];
   struct ContactNode_struct* nextNodePtr;
   
} ContactNode;

void InitializeContactNode(ContactNode* node, char* name, char* phoneNumber){
   strcpy(node->contactName, name);
   strcpy(node->contactPhoneNumber, phoneNumber);
}

char* GetName(ContactNode* node){
   return node->contactName;
}

char* GetPhoneNumber(ContactNode* node){
   return node->contactPhoneNumber;  
}

void InsertAfter(ContactNode* before, ContactNode* after){
   ContactNode* temp = before->nextNodePtr;
   before->nextNodePtr = after;
   after->nextNodePtr = temp;
}

ContactNode* GetNext(ContactNode* node){
   return node->nextNodePtr;
}

void PrintContactNode(ContactNode* node){
   printf("Name: %s\nPhone number: %s\n\n", node->contactName, node->contactPhoneNumber);  
}

int main(void) {
   ContactNode* one = (ContactNode*) malloc(sizeof(ContactNode));
   ContactNode* two = (ContactNode*) malloc(sizeof(ContactNode));
   ContactNode* three = (ContactNode*) malloc(sizeof(ContactNode));

   
   one = (ContactNode*) malloc(sizeof(ContactNode));
   
   char name[100];
   char phone[100];
   
   fgets(name, 100, stdin);
   name[strlen(name)-1] = '\0';
   fgets(phone, 100, stdin);
   phone[strlen(phone)-1] = '\0';
   InitializeContactNode(one, name, phone);
   printf("Person 1: %s, %s\n", GetName(one), GetPhoneNumber(one));
   
   fgets(name, 100, stdin);
   name[strlen(name)-1] = '\0';
   fgets(phone, 100, stdin);
   phone[strlen(phone)-1] = '\0';
   InitializeContactNode(two, name, phone);
   InsertAfter(one, two);
   printf("Person 2: %s, %s\n", GetName(two), GetPhoneNumber(two));

   
   fgets(name, 100, stdin);
   name[strlen(name)-1] = '\0';
   fgets(phone, 100, stdin);
   phone[strlen(phone)-1] = '\0';
   InitializeContactNode(three, name, phone);
   InsertAfter(two, three);
   printf("Person 3: %s, %s\n", GetName(three), GetPhoneNumber(three));

   printf("\nCONTACT LIST\n");
   
   ContactNode* current = one;
   while(current != NULL){
      PrintContactNode(current);
      current = GetNext(current);
   }
   
   free(one);
   free(two);
   free(three);
   
   return 0;
}

