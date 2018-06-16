#include "dev.h"

#define DEV_NAME "/dev/ttyS0"

int main()
{
	Device  dev(DEV_NAME);

	dev.comm();
	return 0;
}
