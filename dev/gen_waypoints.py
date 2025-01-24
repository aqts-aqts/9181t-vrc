import numpy as np
import matplotlib.pyplot as plt
from path_to_cpp import convert_path_to_cpp

def interpolate_path(waypoints, interval):
    """
    Interpolates a path given a set of waypoints.

    Parameters:
        waypoints (list of tuples): List of (x, y) tuples representing the path.
        interval (float): Desired spacing between interpolated points.

    Returns:
        list of tuples: Interpolated path with additional waypoints.
    """
    interpolated = []

    for i in range(len(waypoints) - 1):
        x1, y1 = waypoints[i]
        x2, y2 = waypoints[i + 1]

        # Calculate distance between points
        distance = np.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

        # Determine number of points to interpolate
        num_points = int(np.ceil(distance / interval))

        # Generate interpolated points
        for j in range(num_points):
            t = j / num_points
            x = x1 + t * (x2 - x1)
            y = y1 + t * (y2 - y1)
            interpolated.append((x, y))

    # Add the last waypoint
    interpolated.append(waypoints[-1])

    return interpolated

if __name__ == "__main__":
    # Example usage
    waypoints = [
        (0, 0),
        (1, 5),
        (5, 10),
        (15, 15),
        (25, 20)
    ]

    interval = 0.1  # Spacing between interpolated points (inches)

    interpolated_path = interpolate_path(waypoints, interval)

    # Save to file
    with open("dev/path.txt", "w") as f:
        for x, y in interpolated_path:
            f.write(f"{x},{y}\n")

    print("Interpolated path saved to 'path.txt'")

    # Plot the original and interpolated paths
    original_x, original_y = zip(*waypoints)
    interpolated_x, interpolated_y = zip(*interpolated_path)

    plt.figure()
    plt.plot(original_x, original_y, 'ro-', label='Original Waypoints')
    plt.plot(interpolated_x, interpolated_y, 'b-', label='Interpolated Path')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Path Interpolation')
    plt.legend()
    plt.grid()
    plt.axis('equal')
    plt.show()

    # Convert to C++ header file
    convert_path_to_cpp("dev/path.txt", "src/paths/path.h")