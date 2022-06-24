#include <bits/stdc++.h>
using namespace std;

int exist(vector<pair<string, pair< pair<int,int>, pair<int,int> > > > v, string h){
    for (int i = 0; i < v.size(); i++){
        if (h == v[i].first){
            return i;
        }
    }
    return -1;
}

vector<pair<string, pair< pair<int,int>, pair<int,int> > > > findHint (vector<vector<string> > cells, int m, int n){
    vector<pair<string, pair< pair<int,int>, pair<int,int> > > > l;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (l.empty()){
                l.push_back(make_pair(cells[i][j],make_pair(make_pair(i,j),make_pair(i,j))));
            } else {
                int e = exist(l,cells[i][j]);
                if (e == -1){
                    l.push_back(make_pair(cells[i][j],make_pair(make_pair(i,j),make_pair(i,j))));
                } else {
                    l[e].second.second.first = i;
                    l[e].second.second.second = j;
                }
            }
        }
    }

    return l;
}

bool verify (string check, vector<vector<string> > cells, int m, int n, int r1, int c1, int r2, int c2){
    if ((check[0] == '-' && (r2-r1 >= c2-c1)) ||
        (check[0] == '|' && (r2-r1 <= c2-c1)) ||
        (check[0] == '+' && (r2-r1 != c2-c1))){
            return false;
        }

    for (int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if (((i < r1 || i > r2 || j < c1 || j > c2) && check == cells[i][j]) ||
                ((i >= r1 && i <= r2 && j >= c1 && j <= c2) && check != cells[i][j])){
                return false;
                }
        }
    }

    return true;
}

bool corner(vector<vector<string> > cells, int m, int n){
    for (int i = 0; i < m-1; i++){
        for (int j = 0; j < n-1; j++){
            if (cells[i][j] != cells[i+1][j] &&
                cells[i][j] != cells[i][j+1] &&
                cells[i][j] != cells[i+1][j+1] &&
                cells[i+1][j] != cells[i][j+1] &&
                cells[i+1][j] != cells[i+1][j+1] &&
                cells[i][j+1] != cells[i+1][j+1]){
                    return false;
                }
        }
    }
    return true;
}

int main(){
    int m = 10, n = 10;

    vector<vector<string> > cells;
    for (int i = 0; i < m; i++){
        vector<string> v1;
        for (int j = 0; j < n; j++){
            string temp;
            cin >> temp;
            v1.push_back(temp);
        }
        cells.push_back(v1);
    }

    vector<pair<string, pair< pair<int,int>, pair<int,int> > > > hintList;
    hintList = findHint(cells,m,n);

    
    /**
    //======= Testing Purpose =======//
    for (int i = 0; i < hintList.size(); i++){
        cout << hintList[i].first 
        << " (" << hintList[i].second.first.first <<","<< hintList[i].second.first.second << ") ("
        << hintList[i].second.second.first <<","<< hintList[i].second.second.second << ")" << endl;
    }

    cout << hintList.size();
    **/

    for (int t = 0; t < 5; t++){
    auto begin = std::chrono::high_resolution_clock::now();

    bool valid = true;
    for (int i = 0; i < hintList.size() && valid; i++){
        string check = hintList[i].first;
        int r1 = hintList[i].second.first.first;
        int c1 = hintList[i].second.first.second;
        int r2 = hintList[i].second.second.first;
        int c2 = hintList[i].second.second.second;

        valid = (verify(check,cells,m,n,r1,c1,r2,c2));
    }

    if (valid && corner(cells,m,n)){
        cout << "Valid" << endl;
    } else {
        cout << "Invalid" << endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    
    printf("Time measured: %.5f seconds.\n", elapsed.count() * 1e-9);
    }
    return 0;
}

