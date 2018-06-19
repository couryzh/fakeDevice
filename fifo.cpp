#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "fifo.h"

Fifo::Fifo(const char *dev) 
{
	initRdTerminal(dev);
	initWrTerminal(dev);
}

void Fifo::initRdTerminal(const char *dev)
{
#define PERM S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH
	char *suffix;
	char *realPath;
	int ret;

	realPath = &path[0][0];
	rdPathSuffix(&suffix);
	snprintf(realPath, MAX_PATH_LEN, "%s%s", dev, suffix);	
	printf("rd realPath: %s\n", realPath);
	if (!isExist(realPath)) {
		ret = mkfifo(realPath, PERM);
		if (ret < 0) {
			printf("create %s failed: %s\n", realPath, strerror(errno));
			exit(-1);
		}
	}

	rfd = open(realPath, O_RDONLY);
	if (rfd < 0) {
		printf("open %s failed: %s\n", realPath, strerror(errno));
		exit(-2);
	}

}


void Fifo::initWrTerminal(const char *dev)
{
#define PERM S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH
	char *suffix;
	char *realPath;
	int ret;

	realPath = &path[1][0];
	wrPathSuffix(&suffix);
	snprintf(realPath, MAX_PATH_LEN, "%s%s", dev, suffix);	
	printf("wr realPath: %s\n", realPath);
	if (!isExist(realPath)) {
		ret = mkfifo(realPath, PERM);
		if (ret < 0) {
			printf("create %s failed: %s\n", realPath, strerror(errno));
			exit(-1);
		}
	}

	wfd = open(realPath, O_WRONLY);
	if (wfd < 0) {
		printf("open %s failed: %s\n", realPath, strerror(errno));
		exit(-2);
	}
}

void Fifo::rdPathSuffix(char **suffix)
{
	static char *defaultSuffix = (char *)"0";
	*suffix = defaultSuffix;
}

void Fifo::wrPathSuffix(char **suffix)
{
	static char *defaultSuffix = (char *)"1";
	*suffix = defaultSuffix;
}


bool Fifo::isExist(const char *dev) 
{
	return access(dev, F_OK)  == 0;
}

Fifo::~Fifo()
{
	if (rfd > 0) 
		close(rfd);
	if (wfd > 0) 
		close(wfd);
	path[0][0] = 0;
	path[1][0] = 0;
}


int Fifo::send(char *data, int len)
{
	return ::write(wfd, data, len);
}


int Fifo::recv(char *buf, int bufLen)
{
	return ::read(rfd, buf, bufLen);
}
