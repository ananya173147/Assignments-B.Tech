#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <string>

using namespace std;

int main(){
        string filename, temp;
        int i, n, k, count=1;
        bool flag = false;
        cin >> filename >> n;
        vector <string> s;
        map<string, vector<int>> map;
        for(i=0;i<=n;i++){
                getline(cin,temp);
                map[temp];
                s.push_back(temp);
        }

        ifstream input;
        input.open(filename);
        while(getline(input, temp)){
                for(i=0;i<=n;i++){
                        if(temp==s[i]){
                                k = i;
                                flag = true;
                        }
                }
                if(flag)
                        map[s[k]].push_back(count);
                flag = false;
                count++;
        };

        input.close();

        for (auto it = s.begin(); it != s.end(); it++) {
                for (auto itr = map.begin(); itr != map.end(); itr++) {
                        if(*it==itr->first){
                                //cout << itr->first <<" "; 
                                for(auto j = itr->second.begin();j !=itr->second.end();j++)
                                        cout << *j << " "; 
                                cout <<endl;
                        }
                } 
        }
        return 0;
}