#include <micro_ros_arduino.h>
#include "RoboClaw.h"

// Initialize RoboClaw with hardware Serial1
RoboClaw roboclaw(&Serial1, 10000);

// Micro-ROS variables
rcl_subscription_t subscriber;
std_msgs__msg__Float32 motor_speed_msg;
rcl_node_t node;
rclc_executor_t executor;

// Micro-ROS transport
#define MICROROS_TRANSPORT Serial

// RoboClaw address (default is 0x80)
#define ROBOCLAW_ADDRESS 0x80

// Motor speed (0 to 127)
float motor_speed = 0.0;

void motor_speed_callback(const void *msg) {
    const std_msgs__msg__Float32 *speed_msg = (const std_msgs__msg__Float32 *)msg;
    motor_speed = speed_msg->data;

    // Clamp speed between -127 and 127
    motor_speed = max(-127.0, min(127.0, motor_speed));

    // Send the command to RoboClaw
    if (motor_speed >= 0) {
        roboclaw.ForwardM1(ROBOCLAW_ADDRESS, (uint8_t)motor_speed);
    } else {
        roboclaw.BackwardM1(ROBOCLAW_ADDRESS, (uint8_t)(-motor_speed));
    }

    Serial.print("Motor speed updated: ");
    Serial.println(motor_speed);
}

void setup() {
    // Initialize serial ports
    MICROROS_TRANSPORT.begin(115200); // Micro-ROS communication
    Serial1.begin(38400);             // RoboClaw communication
    roboclaw.begin(38400);

    Serial.begin(9600);
    Serial.println("Starting motor control with Micro-ROS...");

    // Initialize Micro-ROS
    set_microros_transports();

    rcl_allocator_t allocator = rcl_get_default_allocator();

    // Initialize Micro-ROS node
    rclc_support_t support;
    rclc_support_init(&support, 0, NULL, &allocator);
    rclc_node_init_default(&node, "motor_controller_node", "", &support);

    // Initialize Micro-ROS subscriber
    rclc_subscription_init_default(
        &subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
        "motor_speed");

    // Initialize executor
    rclc_executor_init(&executor, &support.context, 1, &allocator);
    rclc_executor_add_subscription(&executor, &subscriber, &motor_speed_msg, &motor_speed_callback, ON_NEW_DATA);
}

void loop() {
    // Run the Micro-ROS executor
    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));

    // Add a small delay to prevent excessive CPU usage
    delay(10);
}