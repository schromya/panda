#include <iostream>
#include <franka/robot.h>
#include <franka/exception.h>

#include <examples_common.h>



int main() {
    
    try {
        franka::Robot robot("192.168.1.2");  // Adjust the IP to match your robot's network settings

        setDefaultBehavior(robot);

        
        // Rads
        std::array<double, 7> q_goal = {{0, -M_PI_4, 0, -3 * M_PI_4, 0, M_PI_2, M_PI_4}}; // Move bot to home
            // {{0, -M_PI_4, 0, -1.3, 0, 3.5, M_PI_4}}; // Move robot to almost vertical
        MotionGenerator motion_generator(0.1, q_goal);
        robot.control(motion_generator);

        std::cout << "Finished moving to initial joint configuration." << std::endl;

    } catch (const franka::Exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }


    return 0;
}
