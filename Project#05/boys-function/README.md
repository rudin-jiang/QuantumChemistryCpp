# Boys Function

Boys function $F_n(x)$ plays an important role in in the evaluation of molecular integrals over Gaussian functions. The Boys function is defined by

$$
F_n(x) = \int_{0}^{1} t^{2n} \exp(-xt^2)  {\rm d} t
$$

This article will discuss some properties and implementations of this function.


## Properties of Boys Function


## 常用的计算方法



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

