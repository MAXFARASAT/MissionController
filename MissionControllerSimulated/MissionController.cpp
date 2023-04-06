#include "MissionController.h"
MissionController::MissionController()
{
    sr = std::make_shared<SimulatedRobot>();
    default_position    = { 0,0 };
    initial_target      = { 10,10 };
}

MissionController::~MissionController()
{
    sr.reset();
}

void MissionController::sendNavigationCommand(std::pair<int, int>& start_position_input, std::pair<int, int>& end_position_input)
{
    if (sr->getState() == false)
    {
        std::cout << "robot is in stopped state starting again\n";
        sr->setState(true);
    }
    std::unique_lock<std::mutex> lock(sr->GetThreadVariables().first);
    sr->setTargetTrajectory(start_position_input, end_position_input);
    std::cout << "Navigation command sent, New Trajectory "<<start_position_input.first<<","<<start_position_input.second
                                                      <<" to "<<end_position_input.first<<","<<end_position_input.second<<"\n";
    lock.unlock();
    sr->GetThreadVariables().second.notify_all();
}

void MissionController::initiateRobot()
{
    sendNavigationCommand(default_position, initial_target);
    sr->moveTowardsTarget();
}

void MissionController::stopRobot()
{
    std::cout << "Stop command received! Stopped robot at " << getCurrentPosition().first << "," << getCurrentPosition().second << "\n";
    sr->setState(false);
    sr->moveTowardsTarget();
}

void MissionController::startRobot()
{
    std::cout << "Start command received! Started robot at " << getCurrentPosition().first << "," << getCurrentPosition().second << "\n";
    sr->moveTowardsTarget();
}

std::pair<int, int> MissionController::getCurrentPosition()
{
    return sr->getCurrentLocation();
}