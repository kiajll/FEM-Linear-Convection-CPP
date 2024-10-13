# 1D Linear Convection Solver Using Finite Element Method
**1. Introduction**
<br/> This solver is designed to compute the 1D linear convection equation using the Finite Element Method (FEM). Convection equations model the propagation of quantities like heat or fluid, and FEM provides a structured way to discretize and solve such PDEs over irregular or complex geometries.

**2. Mathematical Definition**
<br/> The 1D linear convection equation is given by:

$$\frac{\partial u}{\partial t}+c \frac{\partial u}{\partial x}=0$$

<br/> where $u(x,t)$ is the quantity being convected (e.g., temperature or velocity), and $c$ is the convection speed. This equation describes how an initial wave propagates with constant speed.

**3. Discretization Using FEM**
<br/> *3.1. Domain Discretization:* The spatial domain $[0,L]$ is discretized into linear elements. In each element, the solution $u$ is approximated by a set of basis functions. Typically, for 1D problems, linear shape functions $N_i$ are used, and $u(x)$ is expressed as:

$$ u\left(x\right) \approx \sum_{i=1}^{n}{u_i N_i(x)} $$

<br/> where $u_i$ are the nodal values of the solution at each grid point.

<br/> *3.2. Weak Formulation:* Applying the Galerkin method, the weak form of the 1D convection equation is derived by multiplying the original equation with a test function and integrating over the domain. This results in a system of linear equations for each element. The weak form is:

$$\int_{\Omega}{\left(\frac{\partial u}{\partial t} N_j+c \frac{\partial u}{\partial x}N_j\right)dx}=0$$

This equation is discretized in both space and time.

<br/> *3.3. Matrix Assembly:* The global stiffness and mass matrices are assembled for the entire domain. These matrices represent the spatial derivatives of the solution, while the time-stepping technique handles time integration.

**4. Methodology:**
<br/> *4.1. Mesh Generation:* The 1D domain is divided into elements with nodes at each boundary. In our example, we use 41 grid points between $x=0$ and $x=2$, and the solution is evolved over 25 time steps.

<br/> *4.2. Time Stepping:* The time-stepping loop solves the system iteratively using the explicit forward Euler method. At each time step, the system of equations is updated using the matrix formulation, and the solution is advanced in time:

$$u^{n+1}=u^{n}-\frac{c\Delta t}{\Delta x} (u_i - u_{i-1})$$

<br/> *4.3. Boundary Conditions:* You will typically use Dirichlet or periodic boundary conditions for a simple convection problem.

**5. Conclusion:**
<br/> This FEM-based solver provides a structured approach to solving the 1D linear convection equation, making it highly flexible for different geometries and boundary conditions. By saving the solution in Gmsh or another visualization tool, the results can be easily analyzed.
