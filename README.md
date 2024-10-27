# 1D Linear Convection Solver Using Finite Element Method (FEM)
## **1. Introduction**
<br/> This solver is designed to compute the 1D linear convection equation using the Finite Element Method (FEM). Convection equations model the propagation of quantities like heat or fluid, and FEM provides a structured way to discretize and solve such PDEs over irregular or complex geometries.

## **2. Mathematical Definition**
<br/> The 1D linear convection equation is given by:

$$\frac{\partial u}{\partial t}+c \frac{\partial u}{\partial x}=0$$

<br/> where $u(x,t)$ is the quantity being convected (e.g., temperature or velocity), and $c$ is the convection speed. This equation describes how an initial wave propagates with constant speed.

## **3. Discretization Using FEM**
### 3.1. Domain Discretization:
The spatial domain $[0,L]$ is discretized into linear elements. In each element, the solution $u$ is approximated by a set of basis functions. Typically, for 1D problems, linear shape functions $N_i$ are used, and $u(x)$ is expressed as:

$$ u\left(x\right) \approx \sum_{i=1}^{n}{u_i N_i(x)} $$

<br/> where $u_i$ are the nodal values of the velocity field.

### 3.2. Weak Formulation:
Applying the Galerkin method, the weak form of the 1D convection equation is derived by multiplying the original equation with a test function and integrating over the domain. The weak form is:

$$\int_{\Omega}{\left(\frac{\partial u}{\partial t} N_j+c \frac{\partial u}{\partial x}N_j\right)dx}=0$$

### 3.3. Convection and Inertia Matrices:
Substituting the velocity field into the weak form leads to the formation of the inertia (Mass) matrix $𝑀$ and convection (Stiffness) matrix $K$. The weak form becomes a system of linear equations:

$$M^T \frac{du}{dt}+cK^{T}u=0$$

The matrices are:
<br/> *Inertia Matrix M:* $$M_{ij}=\int_{\Omega}{N_i N_jdx}$$
<br/> *Convection Matrix K:* $$K_{ij}=\int_{\Omega}{N_i \frac{\partial N_j}{\partial x}dx}$$

This equation is discretized in both space and time.

### 3.4. Matrix Assembly: 
The global inertia and convection matrices are assembled for the entire domain. These matrices represent the spatial derivatives of the solution, while the time-stepping technique handles time integration.

## **4. Methodology:**
### 4.1. Mesh Generation:
The 1D domain is divided into elements with nodes at each boundary. In our example, we use 41 grid points between $x=0$ and $x=2$, and the solution is evolved over 25 time steps.

### 4.2. Time Stepping: 
The time-stepping loop solves the system iteratively using the explicit forward Euler method. At each time step, the system of equations is updated using the matrix formulation, and the solution is advanced in time:

$$\frac{du}{dt} \approx \frac{u^{n+1}-u^{n}}{\Delta t} $$

<br/> Substituting into the weak form and rearranging yields the update rule for each time step:

$$u^{n+1} = u^{n} - \Delta t (M^{T})^{-1} cK^{T} u^{n} $$

<br/> Thus, the FEM-based linear convection solution is advanced in time by solving this linear system at each time step, with $M$ and $K$ precomputed based on the mesh. This method leads to a matrix-vector multiplication form, which is solved iteratively.

### 4.3. Boundary Conditions:
Dirichlet boundary conditions are implicitly assumed by the use of fixed values at the boundaries. At $x=0$, the value of $u(0)$ remains fixed according to the initial conditions.
At $x=L$ (the other boundary), the value of $u(L)$ is also fixed, maintaining a constant boundary state.

## **5. Results and Conclusion:**
<br/> This FEM-based solver provides a structured approach to solving the 1D linear convection equation, making it highly flexible for different geometries and boundary conditions. By saving the solution in Gmsh or another visualization tool, the results can be easily analyzed.

### LICENSE
```bash
Licensed under the Creative Commons Attribution-NoDerivatives 4.0 International License.
To view a copy of this license, visit https://creativecommons.org/licenses/by-nd/4.0/.
```
