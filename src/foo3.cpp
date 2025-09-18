#include "foo3.h"

void foo3() {
	std::cout << "work " << __func__ << "\tid_потока = " << std::this_thread::get_id() << std::endl;
}