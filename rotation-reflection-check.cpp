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

	cout << "tes";

	if ((rowA != rowB) || (colA != colB)){
		check = false; // A and B cannot be identical since their dimension differ
	}
	else{
		for (int i = 0; i < rowA; i++){
			for (int j = 0; j < colA; j++){
				cout << "BEBI";
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

			printmatrix(A);

			printmatrix(B);
			
            for (int i = 0; i < rowA; i++){
				for (int j = 0; j < colA; j++){
					if (A[i][j] != B[i][j]){
						return false;
					}
				}
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
	for (int i = 0; i < rowA; i++){
		for (int j = 0; j < colA; j++){
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
	for (int i = 0; i < rowA; i++){
		for (int j = 0; j < colA; j++){
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

int main(){
	int rowA, colA, rowB, colB;
	cout << "first configuration" << "\n";
	cin >> rowA >> colA;

	MI A(rowA, VI(colA,"0")); // first 2D array initialization

	for (int i = 0; i < rowA; i++){
		for (int j = 0; j < colA; j++)
			cin >> A[i][j];
	}
	cout << "\n";
	cout << "second configuration" << "\n";
	cin >> rowB >> colB;
	MI B(rowB, VI(colB, "0")); // second 2D array initialization
	for (int i = 0; i < rowB; i++){
		for (int j = 0; j < colB; j++)
			cin >> B[i][j];
	}
	cout << "\n";
	if ((rowA == rowB) && (colA == colB)){
		// the dimension of A and B are identical

		if (identical(A,B) || 
		identical(A,reverserow(B)) || 
		identical(A,reversecol(B)) || 
		identical(A,CWrotate(B)) || 
		identical(A,CCWrotate(B)) || 
		identical(A,CWrotate_horizontalref(B)) || 
		identical(A,horizontalref_CWrotate(B))){
			cout << "similar configurations" << "\n";
		}
		else{
			cout << "different configurations" << "\n";
		}
	}
	else if ((rowA == colB) && (colA == rowB)){
		// B can be obtained by rotation from A
		if (identical(A,CWrotate(B)) || 
		identical(A,CCWrotate(B)) ||
		identical(A,CWrotate_horizontalref(B)) ||
		identical(A,horizontalref_CWrotate(B))){
			cout << "similar configurations" << "\n";
		}
		else{
			cout << "different configurations"<< "\n";
		}
	}
	else{
		// the dimension of A and B are different, B cannot be obtained from A by rotation
		cout << "different configurations" << "\n";
	}
	return 0;
}