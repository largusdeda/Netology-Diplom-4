#include "foo1.h"

void foo1() {
	std::cout << "work " << __func__ << "\tid_потока = " << std::this_thread::get_id() << std::endl;
}