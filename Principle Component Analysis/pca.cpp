#include<iostream>
#include<cmath>

// Constant setting
const int n=5;
const int m=4;
const int p=1;

// Function declaration
double Frob(double** X, double** D);

// Main function
int main(void){

	using namespace std;

	cout << "Hello World!" << endl;
	return 0;
}

double Frob(double** X, double** D){

	double Fnorm = 0;
	double Dt[p][n] = {0};
	double DDt[n][n] = {0};
	double DDtX[n][n] = {0};
	
	// Calculate Dt
	for(int i=0; i<n; ++i){
		for(int j=0; j<p; ++j){
			Dt[j][i]=D[i][j];
		}
	}

	// Calculate DDt
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			for(int k=0; k<p; k++){
				DDt[i][j] += D[i][k]*Dt[k][j];
			}
		}
	}

	// Calculate DDtX
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			for(int k=0; k<n; k++){
				DDtX[i][j] += DDt[i][k]*X[k][j];
			}
		}
	}

	// Calculate Frobenius norm
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			Fnorm += (X[i][j]-DDtX[i][j])*(X[i][j]-DDtX[i][j]);
		}
	}
	Fnorm = sqrt(Fnorm);

	return Fnorm;
}
	
