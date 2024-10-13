#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Define parameters
const int nx = 41;  // Number of grid points
const double L = 2.0;  // Length of domain
const double dx = L / (nx - 1);  // Spatial step
const double dt = 0.025;  // Time step
const double c = 1.0;  // Wave speed
const int nt = 25;  // Number of time steps

// Function to initialize u
vector<double> initialize_u() {
    vector<double> u(nx, 1.0);
    for (int i = int(0.5 / dx); i <= int(1.0 / dx); ++i) {
        u[i] = 2.0;
    }
    return u;
}

// Function to compute the FEM matrix for convection
vector<double> fem_convection_matrix() {
    vector<double> matrix(nx, 0.0);
    // Assuming linear elements, the matrix assembly for FEM would go here
    // Compute the stiffness matrix for the problem
    return matrix;
}

// Time-stepping function
void solve_convection(vector<double>& u) {
    vector<double> u_new = u;  // Temporary vector for new values
    for (int n = 0; n < nt; ++n) {
        u_new = u;  // Copy old solution
        // Loop over elements and apply FEM scheme
        for (int i = 1; i < nx - 1; ++i) {
            // FEM update formula (this is simplified, and the actual matrix would be used here)
            u_new[i] = u[i] - c * dt / dx * (u[i] - u[i-1]);
        }
        u = u_new;
    }
}

int main() {
    vector<double> u = initialize_u();
    solve_convection(u);

    // Print final solution
    for (int i = 0; i < nx; ++i) {
        cout << u[i] << " ";
    }
    cout << endl;

    return 0;
}
