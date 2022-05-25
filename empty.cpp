#include <bits/stdc++.h>
using namespace std;

vector<vector<string> > hint(vector<vector<string> > cells, int m, int n){
    vector<vector<string> > hintsArr;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if(cells[i][j] == "*"){
                vector<string> v1 = {"*", "+", "-", "|"};
                hintsArr.push_back(v1);
            }
        }
    }
    return hintsArr;
}

vector<string> idfier(vector<vector<string> >& cells, int m, int n){
    int x = 0;
    vector<string> id;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (cells[i][j] != "*"){
                x+=1;
                id.push_back(cells[i][j]);
                cells[i][j] = cells[i][j] + to_string(x);
            }
        }
    }
    return id;
}

vector<string> possibleRegion(vector<vector<string> > cells, int m, int n, int r, int c){
    int minr = 0;
    int maxr = m;
    int minc = 0;
    int maxc = n;
    int i,j,lim;

    vector<string> list;

    i = r-1;
    while (i >= 0){
        if (cells[i][c] != "*"){
            minr = i;
            list.push_back(cells[i][c]);
            break;
        }
        i = i - 1;
    }

    i = r+1;
    while (i < m){
        if (cells[i][c] != "*"){
            maxr = i;
            list.push_back(cells[i][c]);
            break;
        }
        i = i + 1;
    }

    j = c-1;
    while (j >= 0){
        if (cells[r][j] != "*"){
            minc = j;
            list.push_back(cells[r][j]);
            break;
        }
        j = j - 1;
    }       

    j = c+1;
    while (j < n){
        if (cells[r][j] != "*"){
            maxc = j;
            list.push_back(cells[r][j]);
            break;
        }
        j = j + 1;
    }     

    lim = maxc;
    i = r - 1;
    j = c + 1;
    while (i >= minr){
        while (j < lim){
            if (cells[i][j] != "*"){
                list.push_back(cells[i][j]);
                lim = j;
                break;
                }
            j = j + 1;
        }
        i = i - 1;
    }

    lim = minc;
    i = r + 1;
    j = c - 1;
    while (i < maxr){
        while (j >= lim){
            if (cells[i][j] != "*"){
                list.push_back(cells[i][j]);
                lim = j;
                break;
                }
            j = j - 1;
        }
        i = i + 1;
    }

    lim = minc;
    i = r - 1;
    j = c - 1;
    while (i >= minr){
        while (j >= lim){
            if (cells[i][j] != "*"){
                list.push_back(cells[i][j]);
                lim = j;
                break;
                }
            j = j - 1;
        }
        i = i - 1;
    }

    lim = maxc;
    i = r + 1;
    j = c + 1;
    while (i < maxr){
        while (j < lim){
            if (cells[i][j] != "*"){
                list.push_back(cells[i][j]);
                lim = j;
                break;
                }
            j = j + 1;
            }
        i = i +1;
    }

    return list;
}

pair<vector<pair<int,int> >, vector<vector<string> >> hint2(vector<vector<string> > cells, int m, int n){
    vector<pair<int,int> > hintsLoc;
    vector<vector<string> > hintsArr;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if(cells[i][j] == "*"){
                hintsLoc.push_back(make_pair(i,j));
                hintsArr.push_back(possibleRegion(cells,m,n,i,j));
            }
        }
    }
    return make_pair(hintsLoc,hintsArr);
}

vector<vector<string> > combination (vector<vector<string> >& arr){

    vector<vector<string> > temp2;
    int n = arr.size();

    int* indices = new int[n];
 
    for (int i = 0; i < n; i++)
        indices[i] = 0;
 
    while (1) {
        vector<string> temp1;
        for (int i = 0; i < n; i++)
            temp1.push_back(arr[i][indices[i]]);
        temp2.push_back(temp1);
 
        int next = n - 1;
        while (next >= 0 &&
              (indices[next] + 1 >= arr[next].size()))
            next--;
 
        if (next < 0)
            return temp2;

        indices[next]++;
 
        for (int i = next + 1; i < n; i++)
            indices[i] = 0;
    }
}


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

bool verifier (vector<vector<string> >cells, int m, int n){
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
    return valid;
}

bool exist(vector<vector<string> > sol, vector<string> check){
    for (int i = 0; i < sol.size(); i++){
        if (sol[i] == check){
            return true;
        }
    }
    return false;
}

int main(){

    vector<vector<string> > cells;
    vector<vector<string> > solution;
    int m, n;
    m = 3;
    n = 3;

    for (int i = 0; i < m; i++){
        vector<string> v1;
        for (int j = 0; j < n; j++){
            v1.push_back("*");
        }
        cells.push_back(v1);
    }

    vector<vector<string> > possible= hint(cells,m,n);

    vector<vector<string> > posList = combination(possible);
    
    for (int x = 1; x < posList.size(); x++){
        vector<vector<string> > cells2;

        int h = 0;

        for (int i = 0; i < m; i++){
            vector<string> v2;
            for (int j = 0; j < n; j++){
                v2.push_back(posList[x][h]);
                h++;
            }
            cells2.push_back(v2);
        }

        vector<string> id = idfier(cells2, m, n);
        
        pair<vector<pair<int,int> >, vector<vector<string> > > temp = hint2(cells2,m,n);
        
        vector<pair<int,int> > hintsLoc = temp.first;
        
        vector<vector<string> > hintsList= temp.second;
        
        vector<vector<string> > config = cells2;

        vector<vector<string> > comList = combination(hintsList);
        
        for (int i = 0 ; i < comList.size(); i++){

            for (int j = 0; j < hintsLoc.size(); j++){
                config[hintsLoc[j].first][hintsLoc[j].second] = comList[i][j];
            }
            
            if(verifier(config,m,n)){
                vector<string> temp2;
                for (int a = 0; a < config.size(); a++){
                    for (int b = 0; b < config[a].size(); b++){
                        temp2.push_back((config[a][b]));
                    }
                }
                
                if (!solution.empty()){
                    if (!exist(solution, temp2)){
                        solution.push_back(temp2);
                    }
                } else {
                    solution.push_back(temp2);
                }
                
            }
            
        }
    }

    cout << solution.size() << endl;

    for (int i = 0; i < solution.size(); i++){
        int x = 0;
        for (int j = 0; j < m; j++){
            for (int k = 0 ; k < n; k++){
                cout << solution[i][x] << " ";
                x++;
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}

