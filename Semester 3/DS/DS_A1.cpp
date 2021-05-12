#include<iostream>
#include<sstream>
#include<iterator>

using namespace std;

typedef struct node {
	struct node* parent;
	struct node* left_child;
	struct node* right_child;
  std::string data;
} node;

int compare(string str1,string str2){
  int i;
  for(i=0;i<7;i++){
    if(str1[i]>str2[i])
      return 0;
    else if(str1[i]<str2[i])
      return 1;
    else if(i==6 && str1[6]==str2[6])
      return 2;
    }
}

node* search(node* p, string x, string path){
  node* curr = p;
  if (curr==NULL){
      cout << 0 << "\n";
      return NULL;
  }
  else if(compare(curr->data,x)==2){
      cout << 1 << " " << path << "\n";
      return NULL;
  }
  else if(compare(curr->data,x)==0){
    path = path + "L";
    return search(p->left_child,x,path);
  }
  else if(compare(curr->data,x)==1){
    path = path + "R";
    return search(p->right_child,x,path);
  }
}

node* insert(node* p, string x) {
  if (p==NULL){
    node* n = new node;
    n->data = x;
    n->left_child = NULL;
    n->right_child = NULL;
    n->parent = NULL;
    return n;
  }
  if (compare(x,p->data)==1){
    node* left = insert(p->left_child,x);
    p->left_child = left;
    left->parent = p;
  }
    
  else if (compare(x,p->data)==0){
    node* right = insert(p->right_child,x);
    p->right_child = right;
    right->parent = p;
  } 
  return p;
}

int main(){
  string firstLine;
  string numberPlate;
  char choice;

  //Fetching only the first line of input.
  getline(cin,firstLine);
  stringstream stringSplitter(firstLine);
  
  // Parsing the string word by word.
  int count=0;
  node* root_node = NULL;
    while(stringSplitter >> numberPlate){
    if(count==0){
      root_node = insert(NULL, numberPlate);
      count++;
    }
    else{
      insert(root_node, numberPlate);
    }
  }
  // Main input handler to serve requests.
  while(cin >> choice >> numberPlate){
    if(choice=='S'){                                           
      // Call your BST Search function here with argument: numberPlate
      search(root_node,numberPlate,"");
    }
  }
  
  return(0);
}
