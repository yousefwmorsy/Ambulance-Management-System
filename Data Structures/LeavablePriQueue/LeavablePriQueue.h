#pragma once
#include "..//PriQueue//priQueue.h"
#include "..//..//Classes//Car.h"

class LeavablePriQueue :
    public priQueue<Car>
{
public:
    void LeaveQueue(int x, int PID);
};

