#include "list-types.h"
#include <stdio.h>
#include <stdlib.h>

/* Returns number of elements in the list, given pointer to head  */
int size(node* head) {
  int count=0;
  node* current = head;
  while(current!=NULL){
    count++;
    current = current->next;
  }
  return count;
}

/* Prints list data elements in order, separated by a single space */
void print_list(node* head) {
if (head==NULL)
    printf("The list is empty");
else{
  node* curr = head;
  while(curr!=NULL) {
    printf("%d ",curr->data);
    curr=curr->next;
  }
  printf("\n");
}
}
/* Returns 1 if list is empty, 0 if not */
int is_empty(node* head) {
  if(head==NULL)
    return 1;
  else return 0;
}


/* Returns pointer to the last element in the list */
node* get_last(node* head){
  node* curr=head;
  if(curr==NULL) { //if empty list
    return NULL;
  }

  while(curr->next!=NULL) {
    curr= curr->next;
  }
  return curr;
}

/* Inserts a node with given value into the list before head.
Returns pointer to new head (which is the node inserted) */
node* insert_at_start(node* head, int value){
    node* new_node = (node*) malloc(sizeof(node));
    new_node->data = value;
    new_node->next = head;
    return new_node; // return pointer to newly inserted node.
}

/* Implement the other functions specified in list-interface below this line  */

//1. Searching for a node in the list and returning pointer to current element
node* search_list(node* head, int key){
    if (!head)
        return head;
    node* curr=head;
    while(curr!=NULL && curr->data!=key)
        curr = curr->next;
    return curr;
}

//2. Inserting an element at the k-th position in the list and returning pointer to the newly inserted node
node* insert_kth(node* head, int key, int place_num){
    if (!head)
        return head;
    int count=0;
    node* current = head;
    while(current!=NULL){
    count++;
    current = current->next;
    }

int length=count;
//I'm counting positions as from 0th to nth position when the size of list is n...
if (place_num>length||place_num<0)
    {
        printf("Error\n");
        return NULL;
    }

node* curr=head;
node* new_node;
node* temp;
new_node=(node*)malloc(sizeof(node));
new_node->data=key;

if (head == NULL)
{
    new_node->next = NULL;
    head = new_node;
    return new_node;
}

if (place_num==0)
{
    new_node->next=head;
    head=new_node;
    return new_node;
}

else if (place_num>=length) {
temp=head;
while (temp->next!=NULL)
{temp=temp->next;}
new_node->next=NULL;
temp->next = new_node;
return head;
}

else{
temp=head;
int position=0;
while (temp->next!=NULL && position<place_num-1)
{++position;
temp = temp->next;}
new_node->next=temp->next;
temp->next=new_node;
return head;
}
}

//3. Deleting a node when its pointer is given and return the next node in the list
node* delete_node(node* head, node* position){
if (!head)
    return head;
node* curr=head;
if(position==head){
node*temp=head;
head=head->next;
free(temp);
return head;
}
while(curr->next!=position)
{
    curr=curr->next;
}
if(curr->next==position)
{
    node* temp=curr->next;
    curr->next=curr->next->next;
    free(temp);
    return curr->next;
}
}

//4. Deleting the entire list
void delete_list(node* head){
if(head==NULL)
    printf("The list is empty");
else{
node* curr=head;
node* temp;
while (curr!=NULL)
   {
       temp=curr->next;
       free(curr);
       curr=temp;
   }
head=NULL;
printf("The list has been deleted\n");
}
}


//5. Printing in reverse order
void print_reverse_order(node* head){
if (head==NULL)
    return;
print_reverse_order(head->next);
printf("%d ", head->data);

}


//6. Rotating a list by a number k and returning pointer to new head of the list
node* rotate_list(node*head, int k){
if (!head)
    return head;
node* temp=head;
int length = 1;
while(temp->next!=NULL){
temp=temp->next;
length++;
}

if(k>length)
	k=k%length;

k=length-k;

if(k==0)
	return head;

node* curr = head;
int count=1;
while(count<k&&curr!=NULL){
curr=curr->next;
count++;
}

if(curr==NULL)
	return head;

node* knode=curr;
temp->next=head;
head=knode->next;
knode->next=NULL;
return head;
}

//7. Reversing the list and returning pointer to the new head
node* reverse_list(node* head){
node* prev=NULL;
node* curr=head;
node* next=NULL;
while(curr!=NULL)
{
    next=curr->next;
    curr->next=prev;
    prev=curr;
    curr=next;
}
head=prev;
}








