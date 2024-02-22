# Damped Gyromagnetic Switching

Switching of a magnetic particle is commonly used in data storage. The switching dynamics are typically described by the Landau-Lifshitz-Gilbert Equation (LLGE). For a spherical particle, the switching can be simplified using polar coordinates. Use equations (8) and (18),  from Mallinson's paper, to solve for the trajectory theta(t) and phi(t) for  M on the unit sphere.  

Start with small angle theta_start with respect to z, and apply a field along -z
For the same timestep delta_t, use Euler, Heun and RK45 to estimate theta(t) and phi(t) 
You can use the RK45 code available here after suitably modifying it for your problem
Assume H >> Hk so you can ignore Hk, and alpha < 0.2.
Stop your simulation when theta > theta_stop
Assuming RK45 (with small time steps) is the most accurate, calculate the R^2 error for Euler and Heun methods
Inputs: theta_start theta_stop alpha delta_t
Output: alpha delta_t R^2_Euler R^2 Heun
Plot all the 3 trajectories on the unit sphere and label your axis
For RK45 plot the switching time (between theta_stop = 170deg and theta_start=10deg) versus alpha
Optional: Read and understand the physics of Mallinson's paper. Repeat the simulation for Hk ~ 0.1 H
