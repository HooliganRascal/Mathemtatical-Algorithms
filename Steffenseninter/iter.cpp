#include<iostream>
#include<cmath>

using namespace std;

// struct definition
struct iter{
	double result;
	int times;
};

// constant
const double besqrt = 2;
const double coeff = 0.5; // 0.21 < coeff < 1
const double error = 1e-12;

// function prototype
iter original(double init);
iter advanced(double init);
double phi(double x);
double psi(double x);

int main(void){

	double initial = 0.0;

	// control display
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(12);

	// input
	cout << "Initial number to iterate for sqrt(" << besqrt << "): ";
	cin >> initial;

	// outut
	iter iteration1 = original(initial);
	iter iteration2 = advanced(initial);

	// display
	cout << "When coeff = " << coeff << ", 1-coeff = " << 1-coeff << endl;
	cout << "Limit of error is " << error << endl;
	cout << "For calculate sqrt(" << besqrt << ")" << endl;

	cout << "Original iteration consequence: " << endl;
	cout << "Iteration times: " << iteration1.times << endl;
	cout << "Iteration result: " << iteration1.result << endl;

	cout << "Advanced iteration consequence: " << endl;
	cout << "Iteration times: " << iteration2.times << endl;
	cout << "Iteration result: " << iteration2.result << endl;

	return 0;
}

// phi(x)
double phi(double x){
	return (coeff*x + (1.0-coeff)*besqrt/x);
}

// psi(x)
double psi(double x){
	 return (x-((phi(x)-x)*(phi(x)-x))/(phi(phi(x))-2*phi(x)+x));
}

// original iteration
iter original(double init){

	int n = 0;
	double xk = init;
	double xkplus1 = phi(init);
	iter consequence;

	while(fabs(xkplus1-xk)>error){
		xk = xkplus1; 
		xkplus1 = phi(xk);
		++n;
	}

	consequence.times = n;
	consequence.result = xkplus1;

	return consequence;
}

// advanced iteration
iter advanced(double init){

	int n = 0;
	double xk = init;
	double xkplus1 = psi(init);
	iter consequence;

	while(fabs(xkplus1-xk)>error){
		xk = xkplus1; 
		xkplus1 = psi(xk);
		++n;
	}

	consequence.times = n;
	consequence.result = xkplus1;

	return consequence;
}
