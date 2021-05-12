#include "2b.h"
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
        Express_ll* expr_ll = new Express_ll(expression);
        cout << fixed << setprecision(2) << expr_ll->eval() << endl;
        expr_ll->print(); //postfix notation
        return 0;
}