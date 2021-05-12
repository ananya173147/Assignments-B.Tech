#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct node {
	int data;
	struct node* parent;
	struct node* left_child;
	struct node* right_child;
} node;

struct node* search(struct node* p, int x){
struct node* curr = p;
if (curr==NULL){
    printf("%d does not exist\n",x);
    return NULL;
}
else if(curr->data==x){
    printf("%d exists\n", curr->data);
    return curr;
}
else if(curr->data>x)
    return search(p->left_child,x);
else
    return search(p->right_child,x);
}

/* Insert(node, val) -> Inserts val into the BST rooted at node, and returns pointer to the node inserted. */
struct node* insert(struct node* p, int x) {
//Creating a new node if the root node is null
if (p==NULL){
    struct node* n = (struct node*)malloc(sizeof(struct node));;
    n->data = x;
    n->left_child = n->right_child = NULL;
    n->parent = p;
    return n;
}
else if (x<p->data)
    p->left_child = insert(p->left_child,x);

else
    p->right_child = insert(p->right_child,x);

}
int main(){
  char firstLine[2000];
  char inputLine[2000];
  size_t length=0, counter=0, plateLength=6;
  char choice, numberPlate[7];
  printf("DONE");
  // Fetching only the first line of input.
  length = strlen(fgets(firstLine,length,stdin));
  printf("DONE");
  printf("%zu",length);

  // Parsing the string word by word.
  while(counter<length){
    strncpy(numberPlate,firstLine[counter],plateLength);
    numberPlate[plateLength] = '\0';
    counter += plateLength+1; // The +1 takes care of the space between words.

    // Call your BST Insert function here with argument: numberPlate

  }

  // Main input handler to serve requests.
  while(fgets(inputLine, length, stdin) != -1){
    sscanf(inputLine,"%c %s",&choice, numberPlate);
    if(choice=='S'){

      // Call your BST Search function here with argument: numberPlate

    }
    //free(inputLine); inputLine=NULL;
    length=0;
  }
  return 0;

}
