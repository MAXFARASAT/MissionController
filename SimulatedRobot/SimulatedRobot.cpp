#include "SimulatedRobot.h"

SimulatedRobot::SimulatedRobot()
{
    current_positon     = { 0,0 };
    start_trajectory    = { 0,0 };
    end_trajectory      = { 0,0 };
}

bool SimulatedRobot::getState()
{
    return state;
}

void SimulatedRobot::setState(bool value)
{
   state = value;
}

std::pair<std::mutex&, std::condition_variable&> SimulatedRobot::GetThreadVariables()
{
    return { mu,cond };
}

std::pair<int, int> SimulatedRobot::getCurrentLocation()
{
    return current_positon;
}
void SimulatedRobot::setTargetTrajectory(std::pair<int, int> start_position_input, std::pair<int, int> end_position_input)
{
    start_trajectory  = start_position_input;
    end_trajectory    = end_position_input;
}

void SimulatedRobot::moveTowardsTarget()
{
    if (state == false)
    {
        return;
    }

    else if (current_positon == end_trajectory)
    {
        std::cout << "Robot has reached the end of the trajectory\n";
        state = false;
        return;
    }

    else if (current_positon == start_trajectory)
    {
        std::cout << "Robot is at the start of trajectory\n";
        //Start changing coordinates to move towards the target
        if (current_positon.first != end_trajectory.first)
        {
            //Start changing the x coordinate till it matches the the target x coordinate
            if (current_positon.first > end_trajectory.first)
            {
                std::cout << "Current Positon X: " << current_positon.first << " > " << "End trajectory X: " << end_trajectory.first<<"\n";
                while (current_positon.first != end_trajectory.first)
                {   
                    lockAndUpdate(current_positon.first, false);
                }
            }
            else
            {
                std::cout << "Current Positon X: " << current_positon.first << " < " << "End trajectory X : "<< end_trajectory.first<<"\n";
                while (current_positon.first != end_trajectory.first)
                {
                    lockAndUpdate(current_positon.first, true);
                }
            }
        }

        if (current_positon.second != end_trajectory.second)
        {
            //Start changing the x coordinate till it matches the the target x coordinate
            if (current_positon.second > end_trajectory.second)
            {
                std::cout << "Current Positon Y: " << current_positon.second << " > " << "End trajectory Y : " <<end_trajectory.second<<"\n";
                while (current_positon.second != end_trajectory.second)
                {
                    lockAndUpdate(current_positon.second, false);
                }
            }
            else
            {
                std::cout << "Current Positon Y: " << current_positon.second << " < " << "End trajectory Y : " << end_trajectory.second << "\n";
                while (current_positon.second != end_trajectory.second)
                {
                    lockAndUpdate(current_positon.second, true);
                }
            }
        }
        moveTowardsTarget();
    }
    else
    {
        //Start changing coordinates to move towards the target
        if (current_positon.first != start_trajectory.first)
        {
            //Start changing the x coordinate till it matches the the target x coordinate
            if (current_positon.first > start_trajectory.first)
            {
                while (current_positon.first != start_trajectory.first)
                {
                    lockAndUpdate(current_positon.first, false);
                }
            }
            else
            {
                while (current_positon.first != start_trajectory.first)
                {
                    lockAndUpdate(current_positon.first, true);
                }
            }
        }

        if (current_positon.second != start_trajectory.second)
        {
            //Start changing the x coordinate till it matches the the target x coordinate
            if (current_positon.second > start_trajectory.second)
            {
                while (current_positon.second != start_trajectory.second)
                {
                    lockAndUpdate(current_positon.second, false);
                }
            }
            else
            {
                while (current_positon.second != start_trajectory.second)
                {
                    lockAndUpdate(current_positon.second, true);
                }
            }
        }
        moveTowardsTarget();
    }
}

void SimulatedRobot::lockAndUpdate(int& value, bool increment)
{
    if (state == false) { return; }
    std::unique_lock<std::mutex> locker(mu);
    int x = end_trajectory.first;
    cond.wait(locker, [x]{return x != INT_MIN;});
    if (increment)
        value++;
    else
        value--;
    locker.unlock();
    std::cout << "Robot on the move, Current Position: X: " << current_positon.first << " Y: " << current_positon.second << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Sleep is introduced to simulate robot taking 1sec per step
}