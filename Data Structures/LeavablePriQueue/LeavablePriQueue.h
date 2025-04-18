#pragma once
#include "..//PriQueue//priQueue.h"
#include "..//..//Classes//Car.h"

class LeavablePriQueue :
    public priQueue<Car*>
{
public:
    bool LeaveQueue(Car* &Removed, int &timetoreach, int PID);
    bool GetPlacedItem(Car*&, int);
};

