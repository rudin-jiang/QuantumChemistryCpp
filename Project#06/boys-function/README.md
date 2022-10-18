# Boys Function
Boys function $F_n(x)$ plays an important role in the evaluation of molecular integrals over Gaussian functions. The Boys function is defined by

$$
F_n(x) = \int_{0}^{1} t^{2n} \exp (-xt^2) \  {\rm d} t
$$

where $x \geq 0$ and $n \in \mathbb{Z}$.

（This article will discuss some properties and implementations of this function.）

## Properties of Boys Function
* Because the integrand functions are positive in the integration interval, the integral values are positive.
$$F_n(x) > 0$$

* The derivative of Boys function is the negative of another boys function, so the derivative of Boys function is negative.
$$\frac{{\rm d} F_n(x)}{{\rm d} x} = -F_{n+1}(x) < 0$$

* Boys function is monotonically decreasing with respect to $n$.
$$F_{n+1}(x) < F_n(x)$$

* Boys function is monotonically decreasing with respect to $x$. For $\Delta x > 0$, we have
$$F_n(x + \Delta x) < F_n(x)$$

* The values at $x = 0$ may be expressed in closed form 
$$F_n(0) = \int_{0}^{1} t^{2n} \  {\rm d} t = \frac{1}{2 n + 1}$$

* For large values of $x$, we may determine the Boys function approximately from
$$F_n(x) = \int_{0}^{1} t^{2n} \exp(-x t^2) \  {\rm d} t \approx \int_{0}^{\infty} t^{2n} \exp(-x t^2) \  {\rm d} t = \frac{(2n-1)!!}{2^{n+1}}\sqrt{\frac{\pi}{x^{2n+1}}}$$


## 常用的计算方法
由于 Boys 函数在分子积分中使用频率很高，高效地计算 Boys 函数的数值尤为重要。常用的计算方法一般是根据 $x$ 的数值大小分段计算，常见的计算方法如下。

* 当 $x \rightarrow 0$ 时，使用 $F_n(0)$ 近似 $F_n(x)$
$$F_n(x \rightarrow 0) \approx F_n(0) = \frac{1}{2n+1}$$

* 当 $x$ 很小时，将 $F_n(x)$ 在 $x = 0$ 处作泰勒展开
$$F_n(x) = \sum_{k = 0}^{\infty} \frac{(-x)^k}{k!\,(2n+2k+1)}$$

* 当 $x$ 很大时，使用近似表达式
$$F_n(x) \approx  \frac{(2n-1)!!}{2^{n+1}}\sqrt{\frac{\pi}{x^{2n+1}}}$$

* 对一些列等间隔的 $x_t$ 打表函数值，当需要计算 $F_n(x)$ 时，找到距离 $x$ 最近的 $x_t$ ，令 $\Delta x = x - x_t$ ， 在 $x_t$ 处作泰勒展开
$$F_n(x_t + \Delta x) = \sum_{k = 0}^{\infty} \frac{F_{n+k}(x_t)\,(-\Delta x)^{k}}{k!}$$

* 如果已经知道 $F_n(x_0)$ 想求解 $F_{n'}(x_0)$ ，即相同的 $x$ 不同的 $n$ 时，可以使用向上递归关系或向下递归关系
$$
\begin{align}
F_{n+1}(x) &= \frac{(2n+1) F_n(x) - \exp(-x)}{2x} \nonumber \\
F_{n}(x) &= \frac{2xF_{n+1}(x) + \exp(-x)}{2n+1} \nonumber
\end{align}
$$

上面的介绍的算法没有具体指出公式的适用范围，只是泛泛地说 $x$ 很大或很小。具体的适用范围与所期望的计算精度有关，需要经过测试确定。


## （The Method We Use）

在实现一个具体的 Boys 函数算法之前，我们首先要考虑实现的函数的适用范围，即 $n$ 和 $x$ 在什么范围内程序保证正确。在不考虑优化的情况下，计算分子积分时所需使用的 $F_n(x)$ 的自变量范围是
$$
\begin{align}
0 \leq n &\leq 4 l_{max} \nonumber\\
0 \leq x &< \infty \nonumber
\end{align}
$$ 其中 $l_{max}$ 为所使用到的基函数最大的角量子数。考虑到现在已有的基函数的类型有 $S$、$P$、$D$、$F$、$G$、$H$ 和 $I$ ，因此取 $l_{max} = 6$ ，所以 $n \leq 24$ 。（放宽边界）选定 $0 \leq n \leq 32$ 为程序认为合法的输入范围，因此所需实现的自变量的范围是
$$
\begin{align}
0 \leq n &\leq 32 \nonumber\\
0 \leq x &< \infty \nonumber
\end{align}
$$

（经过测试，选用如下算法）
* 当 $0 \leq x \leq 150$ 时，使用打表的方法， $x$ 间隔 $0.1$ 打表，即在 $x = 0.0, 0.1, 0.2, \cdots, 150.0$ 处，对 $n = 0 \sim 40$ 打表。前面说程序确保 $0 \leq n \leq 32$ 为合法的输入，这里对 $n$ 多打几项作为最后几个 $n$ 的导数使用。当计算函数值时，对 $k = 0 \sim 6$ 前 $7$ 项求和，即
$$F_n(x_t + \Delta x) \approx \sum_{k = 0}^{6} \frac{F_{n+k}(x_t)\,(-\Delta x)^{k}}{k!}$$

* 当 $x > 150$ 时，使用近似表达式计算
$$F_n(x) \approx  \frac{(2n-1)!!}{2^{n+1}}\sqrt{\frac{\pi}{x^{2n+1}}}$$



（TODO）



## Get Function Values with High Precision



* Matlab
    ```matlab
    function ret = boysfun(n, x)
        f = @(t) (t.^(2*n) .* exp(-x .* t.^2));
        ret = integral(f,0,1,'RelTol', 0.0, 'AbsTol', 0.0);
    end
    ```

* Mathematica
    ```mathematica
    boysfun[n_, x_] := NIntegrate[t^(2*n) * Exp[-x*t^2], {t,0,1}, PrecisionGoal -> 14];
    ```




## Unit Testing






## Benchmark









## Reference

* MEST

