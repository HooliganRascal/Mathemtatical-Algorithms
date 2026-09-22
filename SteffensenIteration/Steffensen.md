# Steffensen
---
## Newton
Equations:
    $$f(x)=x^{2}-2=0$$
Lagrange Mean Value Theorem: $f(x)$ has to be very smooth, $f'(x)$ is **continuous**
    $$\exists c\in[a,b],\qquad s.t.f'(c) = \frac{f(a)-f(b)}{a-b}$$
Newton, assume $\alpha$ is the zero point ($f(\alpha) = 0$)
    $$f(x)\approx f(\alpha) + f'(x)(x-\alpha) = f'(x)(x-\alpha)$$
Simplify it:
    $$\alpha \approx x - \frac{f(x)}{f'(x)}$$
Iteration:
    $$x_{k+1} = x_{k}-\frac{f(x_{k})}{f'(x_{k})} = \varphi(x_{k})$$
Square root iteration:
    $$x_{k+1} = x_{k}-\frac{x_{k}^{2}-2}{2x_{k}} = \frac{1}{2}\left(x_{k}+\frac{2}{x_{k}}\right)$$

## Another way
Equation:
    $$x = \frac{2}{x}$$
Implies, $c\in(0,1)$
    $$x = cx + (1-c)x = cx + (1-c)\frac{2}{x}$$
Iteration:
    $$x_{k+1} = cx_{k} + (1-c)x_{k} = cx_{k} + (1-c)\frac{2}{x_{k}}$$

---
Proof of Convergence:
- Take the subtraction:
    $$\vert x_{k+1}-x_{k}\vert = \left\vert c-\frac{2-2c}{x_{k}x_{k-1}}\right\vert \vert x_{k}-x_{k-1}\vert$$
- Analyse the coefficient:
    $$x_{0} > 0\implies x_{k+1} = cx_{k} + (1-c)\frac{2}{x_{k}}\geq 2\sqrt{2c(1-c)}$$
    Thus:
    $$x_{k+1}x_{k} \geq 8c(1-c)\implies \delta = c-\frac{2-2c}{x_{k}x_{k-1}}\geq c-\frac{1}{4c}$$
    On the other hand, $c\in(0,1)$, thus
    $$\delta < c < 1$$
    If $c > \displaystyle\frac{\sqrt 2-1}{2}\approx 0.207106$, then 
    $$-1 < c-\frac{1}{4c} \leq c-\frac{2-2c}{x_{k}x_{k-1}} = \delta < c < 1$$
    Thus $\vert \delta \vert < 1$, we have:
    $$\vert x_{k+1}-x_{k}\vert = \left\vert \delta\right\vert \vert x_{k}-x_{k-1}\vert = \left\vert \delta\right\vert^{2} \vert x_{k-1}-x_{k-2}\vert = \cdots \left\vert \delta\right\vert^{k} \vert x_{1}-x_{0}\vert$$
    Which means:
    $$\lim_{k\rightarrow\infty}\vert x_{k+1}-x_{k}\vert = 0$$
    Finally:
    $$
    \lim_{k\rightarrow\infty}x_{k+1} = \lim_{k\rightarrow\infty}x_{k} = \lim_{k\rightarrow\infty} \varphi(x_{k}) = \alpha
    $$
- Proved: If $\displaystyle\frac{\sqrt 2-1}{2} < c < 1$, the algorithm converges!

---
If $c=0.5$: Newton
    $$x_{k+1} = \frac{1}{2}\left(x_{k}+\frac{2}{x_{k}}\right)$$
$c$ can be different

## Advanced way
Accelaration: $\varphi(\alpha)=\alpha$
    $$
    \begin{align*}
    x_{k+1} - \alpha &= \varphi(x_{k})- \varphi(\alpha)= 
    \varphi'(\xi_{k})(x_{k}-\alpha)\\
    x_{k+2} - \alpha &= \varphi(x_{k+1})- \varphi(\alpha)= 
    \varphi'(\xi_{k+1})(x_{k+1}-\alpha)\\
    \end{align*}
    $$
For the iteration converges:
    $$\lim_{k\rightarrow\infty}\xi_{k+1}=\lim_{k\rightarrow\infty}\xi_{k} = \alpha$$
Thus:
    $$
    \frac{x_{k+2}-\alpha}{x_{k+1}-\alpha} = 
    \frac{x_{k+1}-\alpha}{x_{k}-\alpha}
    $$
Multiply:
    $$(x_{k+2}-\alpha)(x_{k}-\alpha) =(x_{k+1}-\alpha)^{2}$$
Expand it:
    $$x_{k+2}x_{k}-\alpha(x_{k+2}+x_{k}) = x_{k+1}^{2}-2\alpha x_{k+1}$$
Combine:
    $$\alpha = \frac{x_{k+2}x_{k}-x_{k+1}^{2}}{x_{k+2}-2x_{k+1}+x_{k}} =
    x_{k}-\frac{(x_{k+1}-x_{k})^{2}}{x_{k+2}-2x_{k+1}+x_{k}}$$
At last:
    $$\alpha = 
    x_{k}-\frac{(\varphi(x_{k})-x_{k})^{2}}{\varphi(\varphi(x_{k}))-2\varphi(x_{k})+x_{k}}
    $$
New Iteration:
    $$x^{*}_{k+1} = \psi(x_{k}) = 
    x_{k}-\frac{(\varphi(x_{k})-x_{k})^{2}}{\varphi(\varphi(x_{k}))-2\varphi(x_{k})+x_{k}}
    $$
Convergent order: $\geq 2$ (Not going to prove it)

## Algorithm setup
- Normal way:
    $$x_{k+1} = cx_{k} + (1-c)\frac{2}{x_{k}}$$
- Advanced way:
    $$x^{*}_{k+1} = \psi(x_{k}) = 
    x_{k}-\frac{(\varphi(x_{k})-x_{k})^{2}}{\varphi(\varphi(x_{k}))-2\varphi(x_{k})+x_{k}}
    $$
    where 
    $$\varphi(x_{k})= cx_{k} + (1-c)\frac{2}{x_{k}}$$
- Code:
```C++
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
```

Result:
```Console
Enter a positive number to calculate the square root: 2
Enter an initial value that is greater than 0: 1.5

Enter a coefficient to iterate and enter 'q' to quit: 0.5
Original result: 1.414213562373
Original Times: 5
Advanced Result: 1.414213562373
Advanced Times: 3

Enter a coefficient to iterate and enter 'q' to quit: 0.6
Original result: 1.414213562373
Original Times: 17
Advanced Result: 1.414213562373
Advanced Times: 4

Enter a coefficient to iterate and enter 'q' to quit: 0.9
Original result: 1.414213562377
Original Times: 107
Advanced Result: 1.414213562373
Advanced Times: 4

Enter a coefficient to iterate and enter 'q' to quit: 0.99
Original result: 1.414213562422
Original Times: 1055
Advanced Result: 1.414213562373
Advanced Times: 5

Enter a coefficient to iterate and enter 'q' to quit: q
```
