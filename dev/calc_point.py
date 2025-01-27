import math

def calculate_new_point(x, y, theta, d):
    # Normalize theta to be within [0, 360)
    theta = theta % 360
    
    # Convert theta to radians
    theta_rad = math.radians(theta)
    
    # Calculate the new point
    dx = x + d * math.cos(theta_rad)
    dy = y + d * math.sin(theta_rad)
    
    return dx, dy

x, y = map(float, input("X Y: ").split())
theta = int(input("Angle: "))
d = int(input("Distance: "))
new_x, new_y = calculate_new_point(x, y, theta, d)
print(f"New point: ({new_x}, {new_y})")