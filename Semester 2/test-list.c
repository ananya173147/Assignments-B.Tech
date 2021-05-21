#include "list-interface.h"
#include<stdlib.h>
#include<stdio.h>


int main(int argc, char* argv[])
{
  // First Create a list by adding to NULL list
  node* head = insert_at_start(NULL, 4);
  //Add other elements to this list.
  head = insert_at_start(head, 3);
  head = insert_at_start(head, 2);
  head = insert_at_start(head, 10);

  print_list(head);

  printf("Size of the list is: %d", size(head));

}
