#include "mythread.h"



MyThread::MyThread()
{
}


MyThread::~MyThread()
{
}

void MyThread::setting(int tasks) {
	max_tasks = tasks;
}

bool MyThread::createThread(std::function<std::thread(void)> f) {
	if (true)
	{

	}
	threads.push_back(f());
	return false;
}
