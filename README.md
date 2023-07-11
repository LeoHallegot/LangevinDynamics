# LangevinDynamics

This code has been made during my internship at the Laboratoire de Biochimie Théorique (LBT-IBPC) at Paris.
The original aim of this code is to simulate a 1D Langevin Dynamics for a single particle in a potential created by the user.
The integration of the Langevin equation is done with a BAOA integrator[[1]](#1) as implemented in the colvar module of namd [[2]](#2)[[3]](#3).
Only a double well (Ax⁴-Bx²+C) and a harmonic potential has been implemented. It is also possible to bias the simulations using 
Adiabatic Bias Molecular Dynamics [[4]](#4), Steered Molecular Dynamics. More potentials and biases could be added.

This software has been used to simulate a toy model whose purpose is to test the optle[[5]](#5)[[6]](#6) biased free energy estimator during its developpement.


I am using this code to test new features and improve my C++ skills, mostly in the "refactor branch". My goal is to have a more general code accepting 2 and 3D dynamics and maybe even multiple particles.



## Reference

<a id="1">[1]</a> 
 S. Kieninger and B. G. Keller (2022)
 Gromacs stochastic dynamics and baoab are equivalent configurational sampling algorithms.
 Journal of Chemical Theory and Computation, 18(10):5792–5798.
<a id="1">[1]</a> 
 G. Fiorin, M. L. Klein, and J. Hénin. (2013)
 Using collective variables to drive molecular dynamics simulations.
 Molecular Physics, 111(22-23):3345–3362.
<a id="1">[3]</a>
 J. C. Phillips, D. J. Hardy, J. D. C. Maia, J. E. Stone, J. V. Ribeiro, R. C. Bernardi, R. Buch,G. Fiorin, J. Hénin, W. Jiang, R. McGreevy, M. C. R. Melo, B. K. Radak, R. D. Skeel, A. Singharoy,Y. Wang, B. Roux, A. Aksimentiev, Z. Luthey-Schulten, L. V. Kalé, K. Schulten, C. Chipot, and E. Tajkhorshid.
 Scalable molecular dynamics on CPU and GPU architectures with NAMD.
 The Journal of Chemical Physics, 153(4), 07 2020. 044130

<a id="1">[4]</a> 
 M. Marchi and P. Ballone (1999)
 Adiabatic bias molecular dynamics: A method to navigate the conformational space of complex molecular system
 The Journal of Chemical Physics, 110(8):3697–3702,
 
<a id="1">[5]</a> 
 K. Palacio-Rodriguez and F. Pietrucci (2022)
 Free energy landscapes, diffusion coefficients, and kineticrates from transition paths.
 ournal of Chemical Theory and Computation, 18(8):4639–4648,

<a id="1">[6]</a> 
 https://github.com/physix-repo/optLE
