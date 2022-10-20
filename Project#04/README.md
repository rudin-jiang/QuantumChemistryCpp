# Project #04: The Hartree-Fock SCF procedure

这个项目不是hartree-fock的详细推导，详细的推导 can be found in Chapters 2 and 3 of *Modern Quantum Chemistry*.[<sup>[1]</sup>](#ref1) 这里我们会回顾一下Hartree-Fock的框架脉络，然后就开始写代码。

## Hartee-Fock Method Review

可以用一句话总结Hartree-Fock方法：用一个Slater行列式表示电子波函数，对准确的电子哈密顿进行变分（这里的精确是在BO近似，不考虑相对论效应的情况下说的），得到能量极小值。下面简单解释一下这句话


## AtomList


## Molecule Class




## Units

* 在输入文件中，原子的坐标我们用的单位是埃 $\AA$
* 在具体计算的时候，我们使用的单位都用原子单位
  



## Reference

* <a id="ref1"></a> [1] [*Modern Quantum Chemistry*. Attila Szabo and Neil S. Ostlund. Dover Publications, 1996.](https://www.amazon.com/Modern-Quantum-Chemistry-Introduction-Electronic/dp/0486691861)