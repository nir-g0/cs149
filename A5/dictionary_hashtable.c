/**
* The reason for using a hashtable is to store the commands in
hash slots by their pids.
* This way you can lookup a command by a pid and retrieve all the
info you need:
* command, index (this index means the line number in the text
file you read),
* start time, and anything else you might need.
*
* A hashtable (as you might remember from CS146)
* has slots and each slot contains a linked list of nodes
* (these are the entries that contain all the command info).
* Thus the hashtable (see hashtab array variable below) is
* implemented as an array of nlists. Each array position is a
* slot and a linked list of nlist nodes starts at each array
slot.
* Each array position is a hahstable slot.
*
* You find the hashtable slot for a pid by using a hash function,
* which will map the pid to a hashtable slot (array position).
*
* You can copy this entire code directly in your .c code. No need
to have
* many files.
*
*
* This nlist is a node, which stores one command's info in the
hashtable.
* TODO: You will need to adopt this code a little.
*
* The char *name and char *defn you can remove.
* The nlist *next field is a pointer to the next node in the
linked list.
* There is one hashtable slot in each array position,
* consequently there is one linked list of nlists under a
hashtable slot.
*/
struct nlist { /* table entry: */
struct nlist *next; /* next entry in chain */
char *name; /* defined name, can remove */
char *defn; /* replacement text, can remove */
/* starttime */

