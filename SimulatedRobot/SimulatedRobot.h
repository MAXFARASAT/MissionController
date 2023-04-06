#pragma once
#include <iostream>             //For printing to console
#include <thread>               //For threads 
#include <chrono>               //For time delay
#include <memory>               //For smart pointers
#include <mutex>                //For locking the critical section
#include <condition_variable>   //For asynchronous communication
/// <summary>
/// Class SimulatedRobot: This class contains methods and functionalities for robot operation
/// </summary>

class SimulatedRobot
{
private:
    //Robot parameters
    std::pair<int, int> current_positon;
    std::pair<int, int> start_trajectory;
    std::pair<int, int> end_trajectory;
    std::mutex mu;
    std::condition_variable cond;
    bool state;
public:

    SimulatedRobot();

    ~SimulatedRobot() {}

    /**
    * @brief: Function to get the state of the robot
    * */
    bool getState();
    
    /**
    * @brief: Function to set the state of the robot
    * @param: value
    * */
    void setState(bool value);

    /**
    * @brief: Function to get the multithread parameters for the current thread
    * */
    std::pair<std::mutex&, std::condition_variable&> GetThreadVariables();

    
    /**
     * @brief: Function to make the robot start moving toward the target
     */
    void moveTowardsTarget();

    /**
     * @brief: Function to set the trajectory of the robot
     */
    void setTargetTrajectory(std::pair<int, int> start_position_input, std::pair<int, int> end_position_input);

    /**
    * @brief: Function to get the current location of the robot
    * */
    std::pair<int, int> getCurrentLocation();

    private:
    /**
    * @brief: Function to increment the postion asynchronously
    * */
    void lockAndUpdate(int& value, bool increment);
};