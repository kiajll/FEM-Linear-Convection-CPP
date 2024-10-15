#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>  // Use Eigen library for matrix operations

using namespace std;
using namespace Eigen;

const int nx = 20;  // Number of nodes
const double L = 2.0;  // Length of domain
const double dx = L / (nx - 1);  // Spatial step
const double dt = 0.025;  // Time step
const double c = 1.0;  // Wave speed
const int nt = 25;  // Number of time steps

// Initialize the solution and force vectors
VectorXd initialize_u() {
    VectorXd u(nx);
    u.setOnes();
    u.segment(int(0.5 / dx), int((1.0 / dx) - (0.5 / dx))).setConstant(2.0);
    return u;
}

// Assemble the stiffness matrix
MatrixXd assemble_stiffness_matrix() {
    MatrixXd K = MatrixXd::Zero(nx, nx);
    for (int i = 1; i < nx - 1; ++i) {
        K(i, i) = 2 / dx;
        K(i, i - 1) = -1 / dx;
        K(i - 1, i) = -1 / dx;
    }
    return K;
}

// Assemble the mass matrix
MatrixXd assemble_mass_matrix() {
    MatrixXd M = MatrixXd::Zero(nx, nx);
    for (int i = 1; i < nx - 1; ++i) {
        M(i, i) = 2.0 / 3.0 * dx;
        M(i, i - 1) = 1.0 / 6.0 * dx;
        M(i - 1, i) = 1.0 / 6.0 * dx;
    }
    return M;
}

// Time-stepping function using FEM
void solve_convection(VectorXd& u, const MatrixXd& M, const MatrixXd& K) {
    MatrixXd A = M + c * dt * K;  // A = M + dt * c * K
    for (int n = 0; n < nt; ++n) {
        VectorXd f = M * u;  // Multiply M by current u
        u = A.colPivHouseholderQr().solve(f);  // Solve the system
    }
}

int main() {
    // Initialize solution and matrices
    VectorXd u = initialize_u();
    MatrixXd K = assemble_stiffness_matrix();
    MatrixXd M = assemble_mass_matrix();

    // Solve the convection problem
    solve_convection(u, M, K);

    // Print results
    for (int i = 0; i < nx; ++i) {
        cout << "x[" << i << "] = " << i * dx << ", u[" << i << "] = " << u[i] << endl;
    }

    return 0;
}
