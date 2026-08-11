#include<stdio.h>
#include<math.h>

// Clarification
struct Result{
	double iter_result;
	double iter_coe1;
	int iter_time;
};
struct Result Recurse(double num);

int main(void){

	double num; // input
	double sqrt_num; // square root calculated by recursive process
	double func_num; // square root calculated by inner set function

	// Input status validation and iteration times recordance
	int status;
	int times;
	double coef1;
	struct Result final;

	// Start
	printf("\n\n");

	// Validate the input
	printf("Welcome, we are to calculate sqrt by recursive process.\n");
	printf("Enter a non-negative number:");
	status = scanf(" %lf", &num);
	while(status != 1 || num < 0.0){
		printf("Not valid! Enter a non-negative number:");
		status = scanf(" %lf", &num);
	}

	// Compare the result of recursive process and that of sqrt() function
	if (num == 0)
		printf("The square root of 0 is 0.\n");
	else
		func_num = sqrt(num);
		final = Recurse(num);
		sqrt_num = final.iter_result;
		times = final.iter_time;
		coef1 = final.iter_coe1;
		printf("Sqrt(%lf) by function in C is %.6f.\n", num, func_num);
		printf("Sqrt(%lf) by recursion is %.6f.\n", num, sqrt_num);
		printf("Iteration times: %d. (coef1: %.6f)\n", times, coef1);
	
	// End
	printf("\n\n");

	return 0;
}

// Recursive function
struct Result Recurse(double num){

	// initial value sqrt(n*1) <= 0.5*(n+1)
	double iter_init = 0.5*(num+1); 
	double iter_n;
	double iter_nplus;

	// Core coefficients for recursive function
	double coe1 = 0.6;
	double coe2 = 1-coe1;

	// define error
	double error = 1e-6;
	double error_n;

	// Iteration time and results
	struct Result result;

	// Initialization and Iteration
	result.iter_time = 0;
	result.iter_result = iter_init;
	result.iter_coe1 = coe1;
	iter_n = iter_init;
	error_n = error+1; // initial condition for error (greater)
	while(error_n>error || error_n<(-1)*error){
		iter_nplus = coe1*iter_n + coe2*num/iter_n;
		error_n = iter_nplus - iter_n;
		iter_n = iter_nplus;
		result.iter_time += 1;
	}
	result.iter_result = iter_nplus;
	
	return result;

}
