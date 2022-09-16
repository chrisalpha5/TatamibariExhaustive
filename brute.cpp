#include <bits/stdc++.h>
using namespace std;

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
    int minr = -1;
    int maxr = m;
    int minc = -1;
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
    while (i > minr){
        j = c + 1;
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
    while (i < maxr){
        j = c - 1;
        while (j > lim){
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
    while (i > minr){
        j = c - 1;
        while (j > lim){
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
    while (i < maxr){
        j = c + 1;
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

pair<vector<pair<int,int> >, vector<vector<string> >> hint(vector<vector<string> > cells, int m, int n){
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

int existId(vector<pair<string, pair< pair<int,int>, pair<int,int> > > > v, string h){
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
                int e = existId(l,cells[i][j]);
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

int verifier(vector<vector<string> > cells, int m, int n){
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

    for (int t = 0; t < 5; t++){

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
        return true;
    } else {
        return false;
    }
}

int main()
{

    int m, n;
    vector<vector<string> > cells;

    //INPUT//
    cin >> m >> n;
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
    

   auto begin = std::chrono::high_resolution_clock::now();

    vector<string> id = idfier(cells, m, n);

    pair<vector<pair<int,int> >, vector<vector<string> > > temp = hint(cells,m,n);
    
    vector<pair<int,int> > hintsLoc = temp.first;

    vector<vector<string> > hintsList= temp.second;

    vector<vector<string> > config = cells;

    vector<vector<string> > comList = combination(hintsList);

    vector<vector<int> > solution;

    bool Sol = true;

    for (int i = 0 ; i < comList.size() && Sol; i++){

        for (int j = 0; j < hintsLoc.size(); j++){
            config[hintsLoc[j].first][hintsLoc[j].second] = comList[i][j];
        }
        
        if(verifier(config,m,n)){
            vector<int> temp2;
            for (int a = 0; a < config.size(); a++){
                for (int b = 0; b < config[a].size(); b++){
                    temp2.push_back((config[a][b][1]) - 48);
                }
            }
            solution.push_back(temp2);
            Sol = false;
        }
    }

    sort(solution.begin(),solution.end());

    for (int i = 0; i < solution.size(); i++){
        int x = 0;
        for (int a = 0; a < m; a++){
            for(int b = 0; b < n; b++){
                cout << id[solution[i][x]-1] + to_string(solution[i][x]) << " ";
                x = x + 1;
            }
            cout << endl;
        }
        cout << endl;
    }

    cout << solution.size() << endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    return 0;
}
