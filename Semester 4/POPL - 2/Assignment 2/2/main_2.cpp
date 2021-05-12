#include "2.h"
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

int main(){
        string s;
        cin >> s;
        const char* expression;
        expression = s.c_str();
	Express* expr = new Express(expression); 
	cout << fixed << setprecision(2) << expr->eval() <<endl; 
        expr->print(); //postfix notation
        
        return 0;
}