#include "dev.h"

Device::Device(const char *serialDev)
{
	serial = new Serial(serialDev);
	proto = new SimpleProtocol();
}


Device::~Device()
{
	delete serial;
	delete proto;
}

int Device::comm()
{
	int recvLen, sendLen;
	while (1) {
		recvLen = serial->recv(recvBuf, 64);	

		sendLen = proto->handle(recvBuf, recvLen, sendBuf);

		serial->send(sendBuf, sendLen);
	}
}
