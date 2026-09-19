# Principle Component Analysis

## Question
- Given $m$ vectors in space $\mathbb R^{n}$:
    $$\bm X = 
    \begin{bmatrix}
    \bm x_{1} & \bm x_{2} & \cdots & \bm x_{m}
    \end{bmatrix}
    = 
    \begin{bmatrix}
    x_{1,1} & x_{1,2} & \cdots & x_{1,m}\\
    x_{2,1} & x_{2,2} & \cdots & x_{2,m}\\
    \vdots & \vdots & \ddots & \vdots\\
    x_{n,1} & x_{n,2} & \cdots & x_{n,m}
    \end{bmatrix}
    $$
- Find a matrix $\bm D\in \mathbb R^{n\times p}$ where $p < n$ such that:
    $$\bm D^{*} = \arg\min\sqrt{\sum_{i}(\bm x_{i}-\bm D\bm D^{\mathrm T}\bm x_{i})^{2}}$$

## Solution
- The best suited $\bm D^{*}$ is combined with the eigen vectors of the corresponding first $p$ lasgest eigen values of $\bm X\bm X^{\mathrm T}$
- If $p < n$, the **eigen** is *relatively* constrained leaving some `some to one` elements to think
- It's like doing something to make a transformation:
    $$\bm D^{\mathrm T}\bm X = \bm C$$
    - If $p=1$, then $\bm c$ is a scalar
    - If $1 < p < n$, $\bm c$ is a shorter vector storing the principle component
    - If $p=n$, the algorithm is bullshit
- The ratio of the eigen values used in the algorithm is the key of the ratio of recovery!
- Solving steps:
    - Given $\bm X\bm X^{\mathrm T}$
    - Find the eigen values and corresponding eigen vectors
    - Select $p$, and take the first $p$ eigen vectors, combine them **from left to right** to be $\bm D$ 
    - Test the Frobenius norm of $\bm X-\bm D\bm D^{\mathrm T}\bm X$ 

## Algorithms

