/* Interface Header file  for singly linked list */
#include "list-types.h"


/* Return number of elements in the list */
int size(node* head);

/* Returns 0 if list is empty, 1 if list is not */
int is_empty(node* head);

/* Returns a pointer to the last element in the list (i.e. the tail), NULL if empty list */
node* get_last (node* head);

/*Prints the elements of the list in order starting at the head pointer*/
int print_list(node *head);

/* Provided Update method */

/* Inserts a node with given value into the list before head.
Returns pointer to new head */
node* insert_at_start(node* head, int value);


/* ###   Modify here onwards. You may add new methods below this line ###### */


/* Implement the following methods for the singly linked list */

node* search_list(int key);

/* insert a new node with data key to be at position place_num in the list .
If place_num is larger than listlength +1, print "Error" and return NULL
Else, return pointer to the newly inserted node.
 */
node* insert_kth(node* head, int key, int place_num);


/* Delete the node pointed to by position.
Return the NEXT node in the list (NULL if position is the last node)
*/
node* delete_node(node* head, node* position);

/* Delete entire list */
void delete_list(node* head);

/* Print the elements in the list in reverse order */
void print_reverse_order(node* head);

/* Rotate the list by a number k. E.g. list = 1,2,3,4,5. rotate_list(2) will make
the new list (4,5,1,2,3). Returns pointer to new head of list.
  */
node* rotate_list(node*head, int k);

/* Reverses the list. Returns pointer to new head */
node* reverse_list(node* head);
