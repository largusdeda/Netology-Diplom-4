#include "foo2.h"

void foo2() {
	std::cout << "work " << __func__ << "\tid_потока = " << std::this_thread::get_id() << std::endl;
}