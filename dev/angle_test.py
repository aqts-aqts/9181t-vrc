import math

def get_turn_angle(target_x, target_y, start_x, start_y, current_rotation = 0):
    dx = target_x - start_x
    dy = target_y - start_y
    
    if not dx and not dy:
        return 0

    angle = 270 - math.degrees(math.atan2(dy, dx))

    while angle - current_rotation > 180:
        angle -= 360
    while angle - current_rotation <= -180:
        angle += 360
    
    return angle

print(get_turn_angle(10, 0, 0, 0, 720))