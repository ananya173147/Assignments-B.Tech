#ifndef SET_H
#define SET_H
#include <vector>
using namespace std;

class intset
{
public:
        intset(){};
        void add(int);
        void get_union(const intset&);
        void intersect(const intset&);
        void sym_diff(const intset&);
        void print();
private:
        vector<int> set;
};


#endif