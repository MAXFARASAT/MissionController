#include "Test.h"
TestRobot::~TestRobot()
{ 
	std::cout << "Tests destroyed\n";
	delete missionController;
}

TestRobot::TestRobot()
{
	std::cout << "Tests intialized\n";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	
	missionController = new MissionController();

	trajectory_1_start	= { 1,2 };
	trajectory_1_end	= { 7,8 };

	trajectory_2_start	= { 3,4 };
	trajectory_2_end	= { 12,13 };

	trajectory_3_start	= { 1,2 };
	trajectory_3_end	= { 7,8 };

	trajectory_4_start = { 4,5 };
	trajectory_4_end =   { 10,10 };
}

void TestRobot::runTestSequence()
{
	std::thread robotThread(&MissionController::initiateRobot, missionController);
	std::this_thread::sleep_for(std::chrono::seconds(4)); // we give a delay between different navigation commands
	missionController->sendNavigationCommand(trajectory_1_start, trajectory_1_end);
	std::this_thread::sleep_for(std::chrono::seconds(4));
	
	missionController->sendNavigationCommand(trajectory_2_start, trajectory_2_end);
	std::this_thread::sleep_for(std::chrono::seconds(4));
	
	missionController->stopRobot(); //We stop the robot and give a delay of 5 seconds between stop and start
	std::this_thread::sleep_for(std::chrono::seconds(3));
	
	missionController->startRobot(); //We start the robot and give it new navigation details and robot should stop when it reaches end of trajectory
	missionController->sendNavigationCommand(trajectory_4_start, trajectory_4_end);
	
	if(robotThread.joinable())
		robotThread.join();
	delete missionController;
	missionController = nullptr;
}