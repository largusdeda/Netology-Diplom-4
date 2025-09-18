#include "thread_pool.h"

ThreadPool::ThreadPool() {
	for (int i{ 0 }; i < cores; ++i) {
		v_threads.push_back(std::thread(&ThreadPool::work, this));
	}
}

ThreadPool::~ThreadPool() {
	for (auto& thread : v_threads) {
		if (thread.joinable())
			thread.join();
	}
}

void ThreadPool::work() {
	while (!is_submit) {
		std::unique_lock<std::mutex> u_lock(t_m);
		if (!sq_works.empty()) {
			sq_works.front();
			sq_works.pop();
		}
		else {
			std::this_thread::yield();
		}
	}
}

void ThreadPool::submit(std::vector<std::function<void()>>& v_func, int submits) {
	using namespace std::chrono_literals;

	for (int i{ 0 }; i < submits; i++) {
		for (size_t j{ 0 }; j < v_func.size(); j++) {
			sq_works.push(v_func.at(j));
		}
		std::this_thread::sleep_for(1s);
	}
	is_submit = true;
}