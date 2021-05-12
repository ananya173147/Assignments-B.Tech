#include "2b.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

void double_Stack::init(int len){
        top = -1;
        stack = (double*)malloc(sizeof(double)*(len));
}

void op_Stack::init(int len){
        top = -1;
        stack = (char*)malloc(sizeof(char)*(len));
}

void double_Stack::push(double var) { 
        top++;
	stack[top] = var; 
        //cout << stack[top] <<" pushed, on top " <<top <<"\n";
}

void op_Stack::push(char var){
        top++;
        stack[top] = var;
        //cout << stack[top] <<" pushed, on top " <<top <<"\n";
}

char op_Stack::pop() { 
        char op = stack[top];
        //cout << op <<" popped, on top " <<top <<"\n";
        top--;
	return op; 
} 

double double_Stack::pop() { 
        double val = stack[top];
        top--;
        //cout << val <<" popped, on top " <<top <<"\n";
	return val; 
}

int double_Stack::gettop(){  
	return top;
} 

int op_Stack::gettop(){  
	return top;
} 

double double_Stack::return_top(){
        //cout <<"top is at "<<top<<endl;
        return stack[top];
}

char op_Stack::return_top(){
        return stack[top];
}

void double_Stack::test(){
        for(int i=0;i<5;i++)
        cout <<stack[i]<<" ";
        cout <<endl;
}

void double_Stack::destroy(){
        free(stack);
}

void op_Stack::destroy(){
        free(stack);
}

int precedence(char op){
	if(op == '+'||op == '-')
	        return 1;
	if(op == '*'||op == '/')
	        return 2;
	return 0;
}

void Express_ll::print_list(node* head) {
if (head==NULL)
    printf("The list is empty");
else{
  node* curr = head;
  while(curr!=NULL) {
   cout<<curr->data;
    curr=curr->next;
  }
  cout<<endl;
}
}

Express_ll::Express_ll(const char* str){
        len = strlen(str);
        ds.init(len);
        os.init(len);
        for(int i=0;i<len;i++){
                node* temp = new node; 
                node* curr; 
                temp->data = str[i]; 
                temp->next = NULL; 
                if (head == NULL) 
                        head = temp; 
                else{ 
                        curr = head; 
                        while (curr->next != NULL) 
                        curr = curr->next; 
                        curr->next = temp; 
                }
        }
        //print_list(head);
}

double Express_ll::eval(){
        node* curr = head;
        node* temp;
        //ds.test();
        while (curr!=NULL){
                if(curr->data >= '0' && curr->data <= '9'){
                        int val = 0;
                        while(curr->data >= '0' && curr->data <= '9'){
				val = (val*10) + (curr->data-'0');
                                temp = curr;
                                if(curr->next!=NULL)
				        curr = curr->next;
                                else if(curr->next==NULL){
                                        break;
                                } 
			}
                        ds.push(val);
                        curr = temp;
		}
                else if (curr->data == '+' || curr->data == '-'|| curr->data == '*' || curr->data == '/'){
                        
                        while(os.gettop()!=-1 && precedence(os.return_top()) >= precedence(curr->data)){
				double val2 = ds.pop();
				double val1 = ds.pop();			
				char op = os.pop();
                                switch(op){
		                        case '+': ds.push(val1+val2); break;
		                        case '-': ds.push(val1-val2); break;
		                        case '*': ds.push(val1*val2); break;
		                        case '/': ds.push(val1/val2); break;
	                        }
			}
			os.push(curr->data);
		}
                curr = curr->next; 
        }
        //ds.test();
        while(os.gettop()!=-1){
		double val2 = ds.pop();
		double val1 = ds.pop();				
		char op = os.pop();
                switch(op){
	                case '+': ds.push(val1+val2); break;
	                case '-': ds.push(val1-val2); break;
		        case '*': ds.push(val1*val2); break;
	                case '/': ds.push(val1/val2); break;
                }
	}
        //ds.test();
        return ds.return_top();
}

void Express_ll::print(){
        os.init(len);
        node* curr = head;
        node* temp;
        string postfix = "";
        while (curr!=NULL){
                if(curr->data >= '0' && curr->data <= '9'){
                        int val = 0;
                        while(curr->data >= '0' && curr->data <= '9'){
				val = (val*10) + (curr->data-'0');
                                temp = curr;
                                if(curr->next!=NULL)
				        curr = curr->next;
                                else if(curr->next==NULL){
                                        break;
                                } 
			}
                        postfix = postfix + to_string(val) + " ";
                        curr = temp;
                }
                else{
                        if(precedence(os.return_top()) < precedence(curr->data)){
                                os.push(curr->data);
                        }
                        else{
                                while(os.gettop()!=-1 && precedence(os.return_top()) >= precedence(curr->data)){
                                        postfix = postfix + os.pop() + " ";
                                }
                                os.push(curr->data);
                        }

                }
                curr = curr->next;
        }

        while(os.gettop()!=-1){
                postfix = postfix + os.pop() + " ";
        }
        cout << postfix << endl;
}