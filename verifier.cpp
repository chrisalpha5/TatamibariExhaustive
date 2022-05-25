#include <bits/stdc++.h>
using namespace std;


int calcRow(vector<vector<string> > cells, vector<vector<bool> >& checked, string check, int a, int b, int m){
    int r = 1;
    for (int i = a+1; i < m; i++){
        if (cells[i][b] == check){
            checked[i][b] = true;
            r += 1;
        } else {
            break;
        }
    }
    return r;
}

int calcCol(vector<vector<string> > cells, vector<vector<bool> >& checked, string check, int a, int b, int n){
    int c = 1;
    for (int i = b+1; i < n; i++){
        if (cells[a][i] == check){
            checked[a][i] = true;
            c += 1;
        } else {
            break;
        }
    }
    return c;
}

bool calcRem(vector<vector<string> > cells, vector<vector<bool> >& checked, string check, int a, int b, int r, int c){
    for (int i = a+1; i < a+r; i++){
        for (int j = b+1; j < b+c; j++){
            checked[i][j] = true;
            if (cells[i][j] != check){
                return false;
            }
        }
    }
    return true;
}

bool checkCorner(vector<vector<string> > cells, int a, int b, int r, int c, int m, int n){
    if ((a+r != m) && (b+c !=n)){
        if ((cells[a+r][b+c] != cells[a+r-1][b+c]) && (cells[a+r][b+c] != cells [a+r][b+c-1])){
            return false;
        }
    }
    return true;
}

bool checkRed(vector<vector<string> > cells, vector<vector<bool> >& checked, string check, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (!(checked[i][j]) && check == cells[i][j]){
                return false;
            }
        }
    }
    return true;
}

int main(){

    int m = 10, n = 10;
    //cin >> m >> n;
    bool TEMPO = true;
    while (TEMPO){

    //INPUT//
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
    //END OF INPUT//

    for (int x = 0; x < 5; x++){

    auto begin = std::chrono::high_resolution_clock::now();

    vector<vector<bool> > checked;
    for (int i = 0; i < m; i++){
        vector<bool> v1 (n, false);
        checked.push_back(v1);
    }

    bool valid = true;

    for (int a = 0; a < m; a++){
        for (int b = 0; b < n; b++){
            if (valid && !(checked[a][b])){
                string check = cells[a][b];
                checked[a][b] = true;

                int r = calcRow(cells, checked, check, a, b, m);
                int c = calcCol(cells, checked, check, a, b, n);

                if (valid && (check[0] == '-' && r>=c) || (check[0] == '|' && r<=c) || (check[0] == '+' && r!=c)){
                    valid = false;
                } else {
                    valid = calcRem(cells, checked, check, a, b, r, c);
                }

                if (valid){
                    valid = checkCorner(cells,a,b,r,c,m,n);
                }

                if (valid){
                    valid = checkRed(cells,checked,check,m,n);
                }

            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    
    printf("Time measured: %.5f seconds.\n", elapsed.count() * 1e-9);

    }

    /**
    if (valid){
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    **/

    }
}
