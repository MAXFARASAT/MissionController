#pragma once
#include "../SimulatedRobot/SimulatedRobot.h" //For simulatedrobot
/// <summary>
/// MissionController:This class contains fucntions and methods for robot mission control
/// </summary>
class MissionController
{
    //Mission control parameters
    std::shared_ptr<SimulatedRobot> sr  = nullptr;
    std::pair<int,int> default_position = { 0,0 };
    std::pair<int,int> initial_target   = { 10,10 };
    std::pair<int, int> stop_target;
    std::thread robotThread;
public:
    MissionController();
    ~MissionController();

    /**
     * @brief getCurrentPosition: Function to current position of the robot
     * */
    std::pair<int,int> getCurrentPosition();

    /**
     * @brief: Function to initiate the starting of the robot
    */
    void initiateRobot();

    /**
    * @brief: Funtion to send stop command to the robot
    * */
    void stopRobot();

    /**
    * @brief: Funtion to send start command to the robot
    * */
    void startRobot();

    /**
     * @brief: Function to send navigation command to the robot to follow a new trajectory
     * @param: std::pair<int, int>& start_position_input
     * @param: std::pair<int, int>& end_position_input
    */
    void sendNavigationCommand(std::pair<int, int>& start_position_input, std::pair<int, int>& end_position_input);
};