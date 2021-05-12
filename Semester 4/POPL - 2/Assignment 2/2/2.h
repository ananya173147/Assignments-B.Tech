#ifndef EXP_H
#define EXP_H
#include <cstdlib>
using namespace std;

class double_Stack { 
private: 
	double* stack; 
	int top; 
public: 
	void push(double);
        void init(int);
	double pop();
	int gettop();
        double return_top();
        void test();
        void destroy();
}; 

class op_Stack { 
private: 
	char* stack; 
	int top; 
public: 
	void push(char);
        void init(int);
	char pop();
	int gettop();
        char return_top();
        void destroy();
};

class Express { 
private: 
        const char* input_string;
	double_Stack ds;
        op_Stack os; 
	int len; 

public: 
	Express(const char* str);
	double eval();
        void print(); 
}; 

#endif