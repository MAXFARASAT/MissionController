#pragma once
#include "../MissionControllerSimulated/MissionController.h" //For misssioncontroller
/// <summary>
/// TestRobot:This class contains test data and methods for testing the robot mission control 
/// and robot operation
/// </summary>
class TestRobot
{
	public:
			TestRobot();
			~TestRobot(); 
	
	private:
		//Test Data
		std::pair<int, int> trajectory_1_start;
		std::pair<int, int> trajectory_1_end;

		std::pair<int, int> trajectory_2_start;
		std::pair<int, int> trajectory_2_end;

		std::pair<int, int> trajectory_3_start;
		std::pair<int, int> trajectory_3_end;

		std::pair<int, int> trajectory_4_start;
		std::pair<int, int> trajectory_4_end;

		MissionController* missionController = nullptr;
	
	public:
		/**
		* @brief: Function to run the test sequence for testing the robot
		*/
		void runTestSequence();
};