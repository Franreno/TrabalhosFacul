import numpy as np
import sys

x = float(sys.argv[1])
y = float(sys.argv[2])

r = np.sqrt( (x**2) + (y**2) )
theta_rad = np.arctan(y/x)
theta_degree = (theta_rad * 180) / np.pi

print("%.3f |%.3f "  %(r,theta_degree) )