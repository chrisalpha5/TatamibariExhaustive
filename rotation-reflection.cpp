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
	return ACW;
}

MI CCWrotate(MI A){
	// rotating a matrix A 90 degree in counter-clockwise direction
	// reverse each row and transpose the matrix
	int rowA = A.size(); int colA = A[0].size();
	int rowACCW = colA; int colACCW = rowA;
	MI ACCW(rowACCW, VI(colACCW,"0")); // rotated matrix initialization
	ACCW = transpose(reverserow(A));
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
	int row, col;
	cin >> row >> col;
	MI A(row, VI(col,"0")); // matrix initialization
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++)
			cin >> A[i][j];
	}
	cout << "\n";
	/*
	MI Atrans(col, VI(row,0)); // transpose matrix initialization
	Atrans = transpose(A);
	printmatrix(Atrans);
	cout << "\n";
	MI Arevrow(row, VI(col,0)); // reversed row matrix initialization
	Arevrow = reverserow(A);
	printmatrix(Arevrow);
	cout << "\n";
	*/
	cout << "vertical reflection" << "\n";
	MI Avertical_ref(row, VI(col,"0")); // vertical reflection matrix initialization
	Avertical_ref = reverserow(A);
	printmatrix(Avertical_ref);
	cout << "\n";
	cout << "horizontal reflection" << "\n";
	MI Ahorizontal_ref(row, VI(col,"0")); // horizontal reflection matrix initialization
	Ahorizontal_ref = reversecol(A);
	printmatrix(Ahorizontal_ref);
	cout << "\n";
	cout << "90 degree CW rotation" << "\n";
	MI ACW(col, VI(row,"0")); // rotated CW matrix initialization
	ACW = CWrotate(A);
	printmatrix(ACW);
	cout << "\n";
	cout << "90 degree CCW rotation" << "\n";
	MI ACCW(col, VI(row,"0")); // rotated CCW matrix initialization
	ACCW = CCWrotate(A);
	printmatrix(ACCW);
	cout << "\n";
	cout << "180 degree CW/CCW rotation" << "\n";
	MI Aoneeighty(row, VI(col,"0")); // rotated 180 degree matrix initialization
	Aoneeighty = OneEighty(A);
	printmatrix(Aoneeighty);
	cout << "\n";
	cout <<"90 degree CW rotation followed by horizontal reflection" << "\n";
	MI ACWhor(col, VI(row,"0")); // rotated CW + horizontal reflection matrix initialization
	ACWhor = CWrotate_horizontalref(A);
	printmatrix(ACWhor);
	cout << "\n";
	cout <<"horizontal reflection followed by 90 degree CW rotation" << "\n";
	MI AhorCW(col, VI(row,"0")); // horizontal reflection + CW rotation matrix initialization
	AhorCW = horizontalref_CWrotate(A);
	printmatrix(AhorCW);
	cout << "\n";
	return 0;
}