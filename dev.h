#ifndef DEV_H
#define DEV_H

#include "serial.h"
#include "simpleProtocol.h"

class Device {
public:
	Device(const char *serialDev);
	~Device();

	int comm();

private:
	Serial *serial;
	Protocol *proto;

	char recvBuf[64];
	char sendBuf[64];
};

#endif
