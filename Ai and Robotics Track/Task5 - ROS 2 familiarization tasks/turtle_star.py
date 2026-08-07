import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import time

class TurtleStar(Node):
    def __init__(self):
        super().__init__('turtle_star')
        self.publisher_ = self.create_publisher(Twist, '/turtle1/cmd_vel', 10)
        self.timer = self.create_timer(0.1, self.timer_callback)
        self.state = 'forward'
        self.side_count = 0
        self.state_timer = time.time()

    def timer_callback(self):
        msg = Twist()
        elapsed = time.time() - self.state_timer

        if self.state == 'forward':
            msg.linear.x = 2.0
            msg.angular.z = 0.0
            if elapsed > 2.0:
                self.state = 'turn'
                self.state_timer = time.time()

        elif self.state == 'turn':
            msg.linear.x = 0.0
            msg.angular.z = 1.5708
            if elapsed > 1.6:
                self.state = 'forward'
                self.state_timer = time.time()
                self.side_count += 1
                if self.side_count >= 5:
                    self.publisher_.publish(Twist())
                    self.get_logger().info('Star complete')
                    rclpy.shutdown()
                    return

        self.publisher_.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = TurtleStar()
    rclpy.spin(node)
    node.destroy_node()

if __name__ == '__main__':
    main()
