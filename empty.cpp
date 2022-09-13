#include <bits/stdc++.h>
using namespace std;

typedef vector<string> VI; //vector of integers
typedef vector<VI> MI; //matrix of integers

void printmatrix(MI A){
	// function for printing matrix neatly
	int rowA = A.size(); int colA = A[0].size();
	for (int i = 0; i < rowA; i++){
		for (int j = 0; j < colA; j++){
			cout << A[i][j] << " ";
		}
		cout << "\n";
	}
}

bool identical(MI A, MI B){
	// checking whether A and B are identical matrices
	int rowA = A.size(); int colA = A[0].size();
	int rowB = B.size(); int colB = B[0].size();
	bool check = true; // initialization for checking variable
	if ((rowA != rowB) || (colA != colB)){
		check = false; // A and B cannot be identical since their dimension differ
	}
	else{
		for (int i = 0; i < rowA; i++){
			for (int j = 0; j < colA; j++){
				if (A[i][j][0] != B[i][j][0]){
					check = false;
					break;
				}
			}
		}

		if (check){
            char arr[50];
            for (int j = 0; j < 50; j++){
                arr[j] = '0';
            }


			for (int i = 0; i < rowA; i++){
				for (int j = 0; j < colA; j++){
					if(arr[A[i][j][1] - '0'] == '0'){
						arr[A[i][j][1] - '0'] = B[i][j][1];
					}
				}
			}

            for (int i = 0; i < rowA; i++){
				for (int j = 0; j < colA; j++){
					B[i][j][1] = arr[B[i][j][1] - '0'];
				}
			}
			
            if (A != B){
				return false;
			}
        }
	}
	return check;
}

MI transpose(MI A){
	// transposing a matrix A, i.e., Atrans[i][j] = A[j][i]
	int rowA = A.size(); int colA = A[0].size();
	int rowAtrans = colA; int colAtrans = rowA;
	MI Atrans(rowAtrans, VI(colAtrans,"0")); // matrix initialization
	for (int i = 0; i < rowAtrans; i++){
		for (int j = 0; j < colAtrans; j++)
			Atrans[i][j] = A[j][i];
	}
	return Atrans;
}

MI reverserow(MI A){
	// reversing every row of A
	// Arevrow[i][j] = A[i][n-1-j], where n is the number of column of A
	int rowA = A.size(); int colA = A[0].size();
	for (int i = 0; i < rowA; i++)
		reverse(A[i].begin(),A[i].end());
	return A;
}

MI reversecol(MI A){
	// reversing every column A
	// Arevcol[i][j] = A[m-1-i][j], where m is the number of row of A
	int rowA = A.size(); int colA = A[0].size();
	MI Arevcol(rowA, VI(colA,"0")); // matrix initialization
	for (int i = 0; i < rowA; i++){
		for (int j = 0; j < colA; j++){
			Arevcol[i][j] = A[rowA-1-i][j];
		}
	}
	return Arevcol;
}

MI CWrotate(MI A){
	// rotating a matrix A 90 degree in clockwise direction
	// transpose the matrix and reverse each row
	int rowA = A.size(); int colA = A[0].size();
	int rowACW = colA; int colACW = rowA;
	MI ACW(rowACW, VI(colACW,"0")); // rotated matrix initialization
	ACW = reverserow(transpose(A));
	for (int i = 0; i < rowACW; i++){
		for (int j = 0; j < colACW; j++){
			if (ACW[i][j][0] == '-'){
				ACW[i][j][0] = '|';
			} else if (ACW[i][j][0] == '|'){
				ACW[i][j][0] = '-';
			}
		}
	}

	return ACW;
}

MI CCWrotate(MI A){
	// rotating a matrix A 90 degree in counter-clockwise direction
	// reverse each row and transpose the matrix
	int rowA = A.size(); int colA = A[0].size();
	int rowACCW = colA; int colACCW = rowA;
	MI ACCW(rowACCW, VI(colACCW,"0")); // rotated matrix initialization
	ACCW = transpose(reverserow(A));
	for (int i = 0; i < rowACCW; i++){
		for (int j = 0; j < colACCW; j++){
			if (ACCW[i][j][0] == '-'){
				ACCW[i][j][0] = '|';
			} else if (ACCW[i][j][0] == '|'){
				ACCW[i][j][0] = '-';
			}
		}
	}
	return ACCW;
}

MI OneEighty (MI A){
	// rotating a matrix A 180 degree in clockwise (or counter-clockwise) direction
	// we can compose CWrotate or CCWrotate twice
	int rowA = A.size(); int colA = A[0].size();
	MI Aoneeighty(rowA, VI(colA,"0")); // rotated matrix initialization
	Aoneeighty = CWrotate(CWrotate(A));
	return Aoneeighty;
}

MI CWrotate_horizontalref(MI A){
	// rotating a matrix A 90 degree in clockwise direction and reflecting the result horizontally
	int rowA = A.size(); int colA = A[0].size();
	int rowACW = colA; int colACW = rowA;
	MI ACW(rowACW, VI(colACW,"0")); // rotated matrix initialization
	ACW = CWrotate(A);
	MI ACWhor(rowACW, VI(colACW,"0")); // reflection matrix initialization
	ACWhor = reversecol(ACW);
	return ACWhor;
}

MI horizontalref_CWrotate(MI A){
	// reflecting a matrix A horizontally and then rotating the result 90 degree in clockwise direction
	int rowA = A.size(); int colA = A[0].size();
	int rowAhor = rowA; int colAhor = colA;
	MI Ahor(rowAhor, VI(colAhor,"0")); // reflection matrix initialization
	Ahor = reversecol(A);
	MI AhorCW(colAhor, VI(rowAhor,"0")); // rotated matrix initialization
	AhorCW = CWrotate(Ahor);
	return AhorCW;
}

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

bool exist(vector<vector<string> > sol, vector<string> check){
    for (int i = 0; i < sol.size(); i++){
        if (sol[i] == check){
            return true;
        }
    }
    return false;
}

bool similar(vector<vector<string> > sol, vector<string> check){
    for (int i = 0; i < sol.size(); i++){
        bool sim = true;
        for (int j = 0; j < sol[i].size() && sim; j++){
            if (sol[i][j][0] != check[j][0]){
                sim = false;
            }
        }

        if (sim){
            char arr[50];
            for (int j = 0; j < 50; j++){
                arr[j] = '0';
            }
            for (int j = 0; j < sol[i].size();j++ ){
                if(arr[sol[i][j][1] - '0'] == '0'){
                    arr[sol[i][j][1] - '0'] = check[j][1];
                }
            }
            for (int j=0; j < check.size();j++){
                check[j][1] = arr[check[j][1] - '0'];
            }
            for (int j = 0; j < check.size(); j++){
                if (sol[i] == check){
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}

int main(){

    vector<vector<string> > cells;
    vector<vector<string> > solution;
    int m, n;
    
    cin >> m >> n;

    //for (int TEMPO = 0; TEMPO < 3; TEMPO++){

    auto begin = std::chrono::high_resolution_clock::now();

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
                        if (!similar(solution, temp2)){
                             solution.push_back(temp2);
                        }
                    }
                } else {
                    solution.push_back(temp2);
                }
                
            }
            
        }
    }

    cout << solution.size() << endl;

    int noOfSol = 0;

    for (int i = 0; i < solution.size(); i++){

        MI A(m, VI(n,"0")); // first 2D array initialization
        int x = 0;
        for (int j = 0; j < m; j++){
            for (int k = 0; k < n; k++){
                A[j][k] = solution[i][x];
                x++;
            }
        }

        bool sim = false;

        for (int j = i+1; j < solution.size() && !sim; j++){

            if (i != j){

                MI B(m, VI(n, "0")); // second 2D array initialization
                int y = 0;
                for (int k = 0; k < m; k++){
                    for (int l = 0; l < n; l++){
                        B[k][l] = solution[j][y];
                        y++;
                    }
                }

                if (identical(A,B) || 
                identical(A,reverserow(B)) || 
                identical(A,reversecol(B)) || 
                identical(A,CWrotate(B)) || 
                identical(A,CCWrotate(B)) || 
                identical(A,CWrotate_horizontalref(B)) || 
                identical(A,horizontalref_CWrotate(B))){
                    sim = true;
                }
            } 
        }
        
        if (!sim){
            noOfSol++;
        }

    }

    cout << noOfSol << endl; 

    /**
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
    **/

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    
    printf("Time measured: %.5f seconds.\n", elapsed.count() * 1e-9);

    return 0;
}

