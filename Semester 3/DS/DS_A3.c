/*
Assignment 3
Roll Number: CS19B1004
Name: Ananya Mantravadi

*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node {
	struct node* parent;
	struct node* left_child;
	struct node* right_child;
    char data[7];
    } node;

int compare(char str1[],char str2[]){
  int i;
  for(i=0;i<7;i++){
    if(str1[i]>str2[i])
      return 1;
    else if(str1[i]<str2[i])
      return -1;
    else if(i==6 && str1[6]==str2[6])
      return 0;
    }
}

struct node* search(struct node* p, char x[],char* path){
    if(strlen(path)%100==0)
        path = (char*)realloc(path,sizeof(path)+100);

    if (p==NULL){
        printf("0\n");
        return NULL;
        }
    else if(compare(p->data,x)==0){
        printf("%s\n",path);
        return NULL;
        }
    else if(compare(p->data,x)>0){
        strcat(path,"L");
        return search(p->left_child,x,path);
    }
    else if(compare(p->data,x)<0){
        strcat(path,"R");
        return search(p->right_child,x,path);
    }
};

struct node* insert(struct node* p, char x[]){
  if (p==NULL){
    struct node *n = (struct node*)malloc(sizeof(struct node));
    for(int i=0;i<7;i++)
        n->data[i]=x[i];
    n->left_child = NULL;
    n->right_child = NULL;
    n->parent = NULL;
    return n;
  }
  if(compare(p->data,x)>0){
    p->left_child = insert(p->left_child,x);
    p->left_child->parent = p;
  }
  else if(compare(p->data,x)<0){
    p->right_child = insert(p->right_child,x);
    p->right_child->parent = p;
  }
  else if(compare(p->data,x)==0)
    return p;
return p;
};

struct node* predecessor(struct node* p,char x[],struct node* n){

    while(p!=NULL){
        if(compare(p->data,x)<0){
            for(int i=0;i<7;i++)
                n->data[i]=p->data[i];
            p = p->right_child;
            return predecessor(p,x,n);
        }
        else if(compare(p->data,x)>0){
            p = p->left_child;
            return predecessor(p,x,n);
        }
        else if(compare(p->data,x)==0 && p->left_child!=NULL){
            p=p->left_child;
            while(p->right_child!=NULL){
                p = p->right_child;
            }
            printf("%s\n",p->data);
            return NULL;
        }
        else if(compare(p->data,x)==0){
            break;
        }
    }
    if(n->data[0]==0)
        printf("0\n");
    else if(n->data[0]!=0){
        printf("%s\n",n->data);
        return NULL;
    }
    else if(p==NULL){
        printf("0\n");
        return NULL;
    }
};

struct node* successor(struct node* p,char x[],struct node* n){

    while(p!=NULL){
        if(compare(p->data,x)<0){
            p = p->right_child;
            return successor(p,x,n);
        }
        else if(compare(p->data,x)>0){
            for(int i=0;i<7;i++)
                n->data[i]=p->data[i];
            p = p->left_child;
            return successor(p,x,n);
        }
        else if(compare(p->data,x)==0 && p->right_child!=NULL){
            p=p->right_child;
            while(p->left_child!=NULL){
                p = p->left_child;
            }
            printf("%s\n",p->data);
            return NULL;
        }
        else if(compare(p->data,x)==0){
            break;
        }
    }
    if(n->data[0]==0)
        printf("0\n");
    else if(n->data[0]!=0){
        printf("%s\n",n->data);
        return NULL;
    }
    else if(p==NULL){
        printf("0\n");
        return NULL;
    }
};

struct node* succ(struct node* p,char x[],struct node* n){              //successor function without printf statements
    while(p!=NULL){
        if(compare(p->data,x)<0){
            p = p->right_child;
            return succ(p,x,n);
        }
        else if(compare(p->data,x)>0){
            for(int i=0;i<7;i++)
                n->data[i]=p->data[i];
            p = p->left_child;
            return succ(p,x,n);
        }
        else if(compare(p->data,x)==0 && p->right_child!=NULL){
            p=p->right_child;
            while(p->left_child!=NULL){
                p = p->left_child;
            }
            return p;
        }
        else if(compare(p->data,x)==0){
            break;
        }
    }
    if(n->data[0]!=0)
        return n;
    else if(p==NULL)
        return NULL;
};

struct node* splice(struct node* root, struct node* p, char x[]){
    if(p->right_child==NULL&&p->left_child==NULL){
        if(p->parent!=NULL){
            if(p->parent->right_child==p)
                p->parent->right_child = NULL;
            else if (p->parent->left_child==p)
                p->parent->left_child = NULL;
            p->parent = NULL;
        }
        else if(p->parent==NULL)
            root = NULL;
        return root;
    }
    else if(p->right_child==NULL&&p->left_child!=NULL){
        p->left_child->parent = p->parent;
        if(p->parent!=NULL){
            if(p->parent->left_child==p)
                p->parent->left_child = p->left_child;
            else if(p->parent->right_child==p)
                p->parent->right_child = p->left_child;
        }
        else if(p->parent==NULL)
            root = p->left_child;
        return root;
    }
    else if(p->right_child!=NULL&&p->left_child==NULL){
        p->right_child->parent = p->parent;
        if(p->parent!=NULL){
            if(p->parent->left_child==p)
                p->parent->left_child = p->right_child;
            else if(p->parent->right_child==p)
                p->parent->right_child = p->right_child;
        }
        else if(p->parent==NULL)
            root = p->right_child;
        return root;
    }
    else{
        struct node* temp = (struct node*)malloc(sizeof(struct node));
        struct node* na = (struct node*)malloc(sizeof(struct node));
        na->data[0]=0;
        temp = succ(root,p->data,na);
        char arr[7];
        for(int i=0;i<7;i++)
            arr[i]=temp->data[i];
        splice(root,temp,arr);
        for(int i=0;i<7;i++)
            p->data[i]=temp->data[i];
        free(temp);
        free(na);
    }
};


struct node* del(struct node* root,struct node* p, char x[]){
    if (p==NULL){
        printf("-1\n");
        return root;
        }
    else if(compare(p->data,x)==0){
        if(p->right_child==NULL&&p->left_child==NULL){                          //case when the node to be deleted has no children
            root = splice(root,p,x);
            free(p);
            printf("0 \n");
            return root;
        }
        else if(p->right_child!=NULL&&p->left_child!=NULL){                     //case when the node to be deleted has two children
            struct node* temp = (struct node*)malloc(sizeof(struct node));
            struct node* na = (struct node*)malloc(sizeof(struct node));
            na->data[0]=0;
            temp = succ(root,p->data,na);
            char arr[7];
            for(int i=0;i<7;i++)
                arr[i]=temp->data[i];
            printf("2 %s\n",temp->data);
            splice(root,temp,arr);
            for(int i=0;i<7;i++)
                p->data[i]=temp->data[i];
            free(temp);
            free(na);
            return root;
        }
        else if(p->right_child==NULL&&p->left_child!=NULL){                     //case when the node to be deleted has only left child
            root = splice(root,p,x);
            printf("1 %s\n",p->left_child->data);
            free(p);
            return root;
        }
        else if(p->right_child!=NULL&&p->left_child==NULL){                     //case when the node to be deleted has only right child
            root = splice(root,p,x);
            printf("1 %s\n",p->right_child->data);
            free(p);
            return root;
        }
    }
    else if(compare(p->data,x)>0){
        return del(root,p->left_child,x);
    }
    else if(compare(p->data,x)<0){
        return del(root,p->right_child,x);
    }
};

void inorder(struct node* p){
    if(p==NULL){
        return;
    }
    else{
        inorder(p->left_child);
        printf("%s ",p->data);
        inorder(p->right_child);
    }
};

void postorder(struct node* p){
    if(p==NULL){
        return;
    }
    else{
        postorder(p->left_child);
        postorder(p->right_child);
        printf("%s ",p->data);
    }
};

int main(){
    char choice, numberPlate[7];
    _Bool requests = 0;
    int count = 0;
    struct node* root_node = NULL;
  // Fetching till we hit the first request
    while(scanf("%s",numberPlate)!=-1){
        if(!requests){
            if(strlen(numberPlate) == 1){ // Detecting start of request lines.
            choice = numberPlate[0];
            requests = 1;
            }
        else{
            if(count==0){
                root_node = insert(NULL, numberPlate);
                count=1;
            }
            else{
                insert(root_node, numberPlate);
            }
        }
        }
        else break; // choice and numberPlate have values to be processed!!
   }
    do{ // Ugly do-while to process first request line before first scanf.
        if(choice == 'S'){
            char* path;
            path = (char*)malloc(100);
            strcat(path,"1 ");
            search(root_node,numberPlate,path);
            free(path);
        }
        else if(choice == '<'){
            struct node* pre_node = (struct node*)malloc(sizeof(struct node));
            pre_node->data[0]=0;
            predecessor(root_node,numberPlate,pre_node);
            free(pre_node);
        }
        else if(choice == '>'){
            struct node* suc_node = (struct node*)malloc(sizeof(struct node));
            suc_node->data[0]=0;
            successor(root_node,numberPlate,suc_node);
            free(suc_node);
        }
        else if(choice == '+'){
            root_node = insert(root_node,numberPlate);
        }
        else if(choice == '-'){
            root_node = del(root_node,root_node,numberPlate);
        }
        else if(choice == 'I'){
            inorder(root_node);
            printf("\n");
        }
        else if(choice == 'P'){
            postorder(root_node);
            printf("\n");
        }

   }while(scanf("%*[\n]%c %6s",&choice, numberPlate)!=-1);

   return(0);
}
