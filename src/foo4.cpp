#include "foo4.h"

void foo4() {
	std::cout << "work " << __func__ << "\tid_потока = " << std::this_thread::get_id() << std::endl;
}