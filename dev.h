#ifndef DEV_H
#define DEV_H

#include "fifo.h"
#include "caseChangeProtocol.h"

class Device {
public:
	Device(const char *serialDev);
	~Device();

	int comm();

private:
	void printBuf(const char *info, char *buf, int len);

private:
	Fifo * fifo;
	Protocol *proto;

	char recvBuf[64];
	char sendBuf[64];
};

#endif
