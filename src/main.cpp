#include <iostream>
#include <vector>
#include <functional>

#include "thread_pool.h"

#include "foo1.h"
#include "foo2.h"
#include "foo3.h"
#include "foo4.h"

int main() {
#ifdef _WIN32
	setlocale(LC_ALL, "rus");
#endif

	std::vector<std::function<void()>> v_func{ foo1, foo2 };
	int submits{ 10 };

	{
		ThreadPool tp;

		std::thread t(&ThreadPool::submit, &tp, std::ref(v_func), submits);
		if (t.joinable())
			t.join();
	}

	v_func.insert(v_func.end(), { foo3, foo4 });
	std::cout << std::endl;

	{
		ThreadPool tp;

		std::thread t(&ThreadPool::submit, &tp, std::ref(v_func), submits);
		if (t.joinable())
			t.join();
	}

	return EXIT_SUCCESS;
}