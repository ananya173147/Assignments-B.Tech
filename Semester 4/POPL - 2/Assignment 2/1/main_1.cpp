#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "1.h"

using namespace std;

int main(){
        int n,m,p,q,i,j,k;
        string s;
        cin >> n >> m;

        intset sets_array[m];
        for (i=0; i < n; i++){
                cin >> s >> p >> q;
                if (s=="A")
                        sets_array[p].add(q);                        
                
                else if (s=="U")
                        sets_array[p].get_union(sets_array[q]);   

                else if (s=="I")
                        sets_array[p].intersect(sets_array[q]);

                else if (s=="S"){
                        intset temp = sets_array[p];
                        sets_array[p].get_union(sets_array[q]);
                        temp.intersect(sets_array[q]);
                        sets_array[p].sym_diff(temp);
                }        
                        
        } 
     
for (i=0; i < m; i++) {  
        sets_array[i].print();
} 
        return 0;
}