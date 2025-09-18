#pragma once

#include <vector>
#include <functional>
#include <mutex>
#include <thread>
#include <chrono>

#include "safe_queue.h"

class ThreadPool {

public:
	ThreadPool();
	ThreadPool(const ThreadPool& other) = delete;
	ThreadPool(const ThreadPool&& other) = delete;

	~ThreadPool();

	void work();

	void submit(std::vector<std::function<void()>>& v_func, int submits);

private:
	const unsigned int cores{ std::thread::hardware_concurrency() };
	std::mutex t_m;
	std::vector<std::thread> v_threads;
	SafeQueue<std::function<void()>> sq_works;
	bool is_submit{ false };

};