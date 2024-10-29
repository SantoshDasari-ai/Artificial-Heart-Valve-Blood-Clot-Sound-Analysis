import matplotlib.pyplot as plt
import numpy as np

# Define the parameters
L = 0.3  # Length of the beam in meters
P = 100  # Point load in Newtons
RA = 66.67  # Reaction force at A in Newtons
RB = 33.33  # Reaction force at B in Newtons

# Define positions
x_support_A = 0
x_load = 0.1  # Position of the load from the left support in meters
x_support_B = 0.3

# Shear Force values at different segments
x_shear = [0, 0.1, 0.1, 0.3]  # x positions for shear diagram
V_shear = [66.67, 66.67, -33.33, -33.33]  # Shear force values at each segment

# Bending Moment values at different segments
x_moment = [0, 0.1, 0.3]  # x positions for moment diagram
M_moment = [0, 6.67, 0]  # Moment values at each segment

# Plot Free Body Diagram
plt.figure(figsize=(12, 8))

# Subplot 1: Free Body Diagram
plt.subplot(3, 1, 1)
plt.title('Free Body Diagram')
plt.plot([0, L], [0, 0], 'k', lw=8)  # Beam line
plt.plot(0, 0, 'k^', markersize=12, label='Pin Support (RA = 66.67 N)')
plt.plot(L, 0, 'ko', markersize=12, label='Roller Support (RB = 33.33 N)')
plt.arrow(x_load, 0.2, 0, -0.15, head_width=0.02, head_length=0.05, fc='r', ec='r')  # Point Load
plt.text(x_load, 0.22, '100 N', color='r', fontsize=10)
plt.xlim(-0.05, 0.35)
plt.ylim(-0.2, 0.3)
plt.axis('off')
plt.legend(loc='upper right')

# Subplot 2: Shear Force Diagram
plt.subplot(3, 1, 2)
plt.title('Shear Force Diagram')
plt.plot(x_shear, V_shear, drawstyle='steps-post', color='blue', lw=2)
plt.fill_between(x_shear, V_shear, step='post', color='lightblue', alpha=0.6)
plt.axhline(0, color='black', lw=0.5, linestyle='--')
plt.xlabel('Length of Beam (m)')
plt.ylabel('Shear Force (N)')
plt.xlim(0, L)
plt.ylim(-50, 80)
plt.grid(True)

# Subplot 3: Bending Moment Diagram
plt.subplot(3, 1, 3)
plt.title('Bending Moment Diagram')
plt.plot(x_moment, M_moment, drawstyle='steps-post', color='green', lw=2)
plt.fill_between(x_moment, M_moment, step='post', color='lightgreen', alpha=0.6)
plt.axhline(0, color='black', lw=0.5, linestyle='--')
plt.xlabel('Length of Beam (m)')
plt.ylabel('Bending Moment (Nm)')
plt.xlim(0, L)
plt.ylim(-1, 8)
plt.grid(True)

# Adjust layout and show plot
plt.tight_layout()
plt.show()
