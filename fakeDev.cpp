#include "dev.h"

#define DEV_NAME "/tmp/fifo"

int main()
{
	Device  dev(DEV_NAME);

	dev.comm();
	return 0;
}
