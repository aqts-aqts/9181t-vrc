import numpy as np
import matplotlib.pyplot as plt

class PurePursuitController:
    def __init__(self, waypoints, lookahead_distance, wheelbase):
        self.waypoints = waypoints  # List of (x, y) waypoints
        self.lookahead_distance = lookahead_distance
        self.wheelbase = wheelbase  # Length of the vehicle's wheelbase

    def find_lookahead_point(self, position):
        """
        Find the lookahead point on the path closest to the lookahead distance.
        """
        min_distance = float('inf')
        lookahead_point = None

        for i in range(len(self.waypoints)):
            point = self.waypoints[i]
            distance = np.linalg.norm(np.array(point) - np.array(position))

            if abs(distance - self.lookahead_distance) < min_distance:
                min_distance = abs(distance - self.lookahead_distance)
                lookahead_point = point

        return lookahead_point

    def calculate_steering_angle(self, position, heading):
        """
        Calculate the steering angle based on the lookahead point.
        """
        lookahead_point = self.find_lookahead_point(position)

        if lookahead_point is None:
            return 0.0  # No valid lookahead point found

        # Transform lookahead point to vehicle coordinate frame
        dx = lookahead_point[0] - position[0]
        dy = lookahead_point[1] - position[1]

        # Rotate to align with vehicle heading
        local_x = dx * np.cos(-heading) - dy * np.sin(-heading)
        local_y = dx * np.sin(-heading) + dy * np.cos(-heading)

        if local_x <= 0:  # Lookahead point is behind the vehicle
            return 0.0

        # Calculate curvature and steering angle
        curvature = 2 * local_y / (self.lookahead_distance ** 2)
        steering_angle = np.arctan(self.wheelbase * curvature)

        return steering_angle

# Example Usage
def simulate_pure_pursuit():
    # Define waypoints
    waypoints = [(0, 0), (2, 1), (4, 2), (6, 2), (8, 2), (10, 2)]

    # Vehicle parameters
    lookahead_distance = 1.5  # Reduced lookahead distance for smoother behavior
    wheelbase = 1.0

    # Initial vehicle state
    position = [0, 0]
    heading = 0.0  # radians
    velocity = 1.0  # meters per second

    # Initialize controller
    controller = PurePursuitController(waypoints, lookahead_distance, wheelbase)

    # Simulation parameters
    dt = 0.1  # Time step
    positions = [list(position)]

    for _ in range(200):  # Increased simulation steps for better visualization
        # Break if we reach the final waypoint
        if np.linalg.norm(np.array(position) - np.array(waypoints[-1])) < 0.5:
            print("Final waypoint reached. Stopping simulation.")
            break

        # Calculate steering angle
        steering_angle = controller.calculate_steering_angle(position, heading)

        # Update vehicle state using a simple bicycle model
        position[0] += velocity * np.cos(heading) * dt
        position[1] += velocity * np.sin(heading) * dt
        heading += (velocity / wheelbase) * np.tan(steering_angle) * dt

        positions.append(list(position))

    # Plot results
    positions = np.array(positions)
    waypoints = np.array(waypoints)

    plt.figure()
    plt.plot(waypoints[:, 0], waypoints[:, 1], 'r--', label='Waypoints')
    plt.plot(positions[:, 0], positions[:, 1], 'b-', label='Vehicle Path')
    plt.scatter(waypoints[:, 0], waypoints[:, 1], c='red')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.legend()
    plt.title('Pure Pursuit Path Tracking')
    plt.axis('equal')
    plt.show()

if __name__ == "__main__":
    simulate_pure_pursuit()