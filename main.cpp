#include "Test/Test.h"

int main()
{   
    std::unique_ptr<TestRobot> test = std::make_unique<TestRobot>();
    test->runTestSequence();
    return 0;
}