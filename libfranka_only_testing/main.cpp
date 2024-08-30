#include <iostream>
#include <franka/robot.h>
#include <franka/exception.h>

int main() {
    
    try {
        franka::Robot robot("192.168.1.2");  // Adjust the IP to match your robot's network settings

        // Get first 10 lines of robot state
        size_t count = 0;
        robot.read([&count](const franka::RobotState& robot_state) {
            std::cout << robot_state << std::endl;
            return count++ < 10;
        });

    } catch (const franka::Exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }


    return 0;
}
