#include<iostream>
#include<cmath>

using namespace std;

// constant
const int level = 12;
const double error = pow(10,-level);

// struct definition
struct input{
	double target;
	double xk;
	double coeff;
} ini;
struct output{
	double xkplus1;
	int times;
} fin1, fin2;


// function prototype
output original(input* init);
output advanced(input* init);
double phi(input* init);
double psi(input* init);

// main function
int main(void){

	// control display
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(level);

	// input
	double reset;
	cout << "Enter a positive number to calculate the square root: ";
	cin >> ini.target;
	cout << "Enter an initial value that is greater than 0: ";
	cin >> ini.xk;
	reset = ini.xk;
	cout << endl;

	// outut
	cout << "Enter a coefficient to iterate and enter 'q' to quit: ";
	while(cin >> ini.coeff){

		// original iteration
		fin1=original(&ini);
		cout << "Original result: " << fin1.xkplus1 << endl;
		cout << "Original Times: " << fin1.times << endl;
		ini.xk = reset;

		// Steffensen iteration
		fin2=advanced(&ini);
		cout << "Advanced Result: " << fin2.xkplus1 << endl;
		cout << "Advanced Times: " << fin2.times << endl;
		ini.xk = reset;
		
		// again
		cout << endl;
		cout << "Enter a coefficient to iterate and enter 'q' to quit: ";
	}

	return 0;
}

// phi(x)
double phi(input* init){
	return ((init->coeff)*(init->xk) + 
			(1.0-(init->coeff))*(init->target)/(init->xk));
}

// psi(x)
double psi(input* init){
	double pphi = ((init->coeff)*(phi(init)) + 
			(1.0-(init->coeff))*(init->target)/(phi(init)));
	if((pphi-2*phi(init)+(init->xk))==0.0){
		return phi(init);
	}
	else{
		return (init->xk)-
			((phi(init)-(init->xk))*(phi(init)-(init->xk)))/
			(pphi-2*phi(init)+(init->xk));
	}
}

// original iteration
output original(input* init){

	output fina;

	// iteration
	fina.xkplus1 = phi(init);

	// test
	if(fabs((init->xk)-(fina.xkplus1))<error){
		fina.times = 1;
		return fina;
	}
	else{
		init->xk = fina.xkplus1;
		fina = original(init);
		++fina.times;
		return fina;
	}
}

// advanced iteration
output advanced(input* init){

	output fina;

	// iteration
	fina.xkplus1 = psi(init);

	// test
	if(fabs((init->xk)-(fina.xkplus1))<error){
		fina.times = 1;
		return fina;
	}
	else{
		init->xk = fina.xkplus1;
		fina = advanced(init);
		++fina.times;
		return fina;
	}
}
