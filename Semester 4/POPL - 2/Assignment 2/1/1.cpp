#include "1.h"
#include <cstdlib>
#include <iostream>
#include <vector>

void intset::add(int element){
        bool flag = false;
        for (auto it = set.begin(); it != set.end(); it++) { 
                if(*it==element)
                        flag = true; 
        }
        if(flag == false){      
                set.push_back(element);
                int min_index, temp;
                for (int i = 0; i < set.size(); i++){
		        min_index = i;
		        for (int j = i + 1; j < set.size(); j++){
			        if (set[j] < set[min_index]) 
				min_index = j;
		        }
		temp = set[min_index];
		set[min_index] = set[i];
		set[i] = temp;
	        }
        } 
}

void intset::get_union(const intset& other_intset){
        for(int i=0; i<other_intset.set.size(); i++){
                add(other_intset.set[i]);
        }
}

void intset::intersect(const intset& other_intset){
        for (auto it = set.begin(); it != set.end();){
                bool flag = true;
                for(auto it1 = other_intset.set.begin(); it1 != other_intset.set.end(); it1++){
                        if (*it==*it1)
                                flag = false;
                }
                if (flag==true)
                        it = set.erase(it);
                else
                        ++it;
        }
}

void intset::sym_diff(const intset& other_intset){
        for (auto it = set.begin(); it != set.end();){
                bool flag = true;
                for(auto it1 = other_intset.set.begin(); it1 != other_intset.set.end(); it1++){
                        if (*it==*it1)
                                flag = false;
                }
                if (flag==false)
                        it = set.erase(it);
                else
                        ++it;
        }
}

void intset::print(){
        for (auto it = set.begin(); it !=set.end(); it++) { 
                cout << *it << ' '; 
        } 
        cout << endl; 
}


