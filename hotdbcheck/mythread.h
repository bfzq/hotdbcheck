#pragma once
#ifndef __MYTHREAD__
#define __MYTHREAD__
#include <thread>
#include <vector>
#include <functional>
class MyThread {
public:
	MyThread();
	~MyThread();
public:
	void setting(int tasks);
	bool createThread(std::function<std::thread(void)> f);
private:
	std::vector<std::thread> threads;
	std::vector<std::thread> running;
	int max_tasks;
};
#endif // !__MYTHREAD__



