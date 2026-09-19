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
