#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "fifo.h"

Fifo::Fifo(const char *dev) 
{
#define PERM S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
	int ret;
	ret = mkfifo(dev, PERM);
	if (ret < 0) {
		printf("create %s failed: %s\n", dev, strerror(errno));
		exit(-1);
	}

	fd = open(dev, O_RDWR);
	if (fd < 0) {
		printf("open %s failed: %s\n", dev, strerror(errno));
		exit(-2);
	}

	memcpy(path, dev, MAX_PATH_LEN-1);
	path[MAX_PATH_LEN-1] = 0;
}

Fifo::~Fifo()
{
	if (fd > 0) {
		close(fd);
	}
	path[0] = 0;
}


int Fifo::send(char *data, int len)
{
	return ::write(fd, data, len);
}


int Fifo::recv(char *buf, int bufLen)
{
	return ::read(fd, buf, bufLen);
}
