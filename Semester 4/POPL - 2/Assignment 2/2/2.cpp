#include "2.h"
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

Express::Express(const char* str) { 
	input_string = str; 
	len = strlen(input_string); 
        ds.init(len);
        os.init(len);
} 
double Express::eval(){
        int i;
        //ds.test();
        for (i=0;i<len;i++){
                if(input_string[i] >= '0' && input_string[i] <= '9'){
                        int val = 0;
                        while(input_string[i] >= '0' && input_string[i] <= '9'){
				val = (val*10) + (input_string[i]-'0');
				i++;
			}
                        ds.push(val);
                        i--;
                }
                else{
                        while(os.gettop()!=-1 && precedence(os.return_top()) >= precedence(input_string[i])){
				double val2 = ds.pop();
                                //cout<<"val2 is "<<val2<<endl;
				double val1 = ds.pop();	
                                //cout<<"val1 is "<<val1<<endl;			
				char op = os.pop();
                                switch(op){
		                        case '+': ds.push(val1+val2); break;
		                        case '-': ds.push(val1-val2); break;
		                        case '*': ds.push(val1*val2); break;
		                        case '/': ds.push(val1/val2); break;
	                        }
			}
			os.push(input_string[i]);
		}
        }
        //ds.test();
        while(os.gettop()!=-1){
		double val2 = ds.pop();
                //cout<<"val2 is "<<val2<<endl;
		double val1 = ds.pop();		
                //cout<<"val1 is "<<val1<<endl;			
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

void Express::print(){
        os.init(len);
        string postfix = "";
        for(int i=0;i<len;i++){
                if(input_string[i] >= '0' && input_string[i] <= '9'){
                        int val = 0;
                        while(input_string[i] >= '0' && input_string[i] <= '9'){
				val = (val*10) + (input_string[i]-'0');
				i++;
			}
                        postfix = postfix + to_string(val) + " ";
                        i--; 
                }
                else{
                        if(precedence(os.return_top()) < precedence(input_string[i])){
                                os.push(input_string[i]);
                        }
                        else{
                                while(os.gettop()!=-1 && precedence(os.return_top()) >= precedence(input_string[i])){
                                        postfix = postfix + os.pop() + " ";
                                }
                                os.push(input_string[i]);
                        }

                }
        }

        while(os.gettop()!=-1){
                postfix = postfix + os.pop() + " ";
        }
        cout << postfix << endl;
}