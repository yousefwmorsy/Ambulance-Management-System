#pragma once
#include "..//Queue//LinkedQueue.h"
#include "..//..//Classes//Request.h"
class LeavableQueue : public LinkedQueue<Request*>
{
public:
	bool LeaveQueue(Request* &Removed, int PID);
};

