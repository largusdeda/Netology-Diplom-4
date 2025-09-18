#pragma once

#include <queue>  
#include <condition_variable>
#include <mutex>
#include <atomic>

template <typename T>
class SafeQueue {

public:
	SafeQueue() = default;
	SafeQueue(const SafeQueue& other) = delete;
	SafeQueue(const SafeQueue&& other) = delete;

	void push(T work) {
		std::unique_lock<std::mutex> u_lock(q_m);
		works.push(work);
		done.notify_one();
	}

	T pop() {
		std::unique_lock<std::mutex> u_lock(q_m);
		done.wait(u_lock, [this]() { return !works.empty(); });
		T work{ std::move(works.front()) };
		works.pop();

		return work;
	}

	bool empty() {
		std::unique_lock<std::mutex> u_lock(q_m);
		return works.empty();
	}

	void front() {
		std::unique_lock<std::mutex> u_lock(q_m);
		works.front()();
	}

private:
	std::mutex q_m;
	std::queue<T> works;
	std::condition_variable done;

};