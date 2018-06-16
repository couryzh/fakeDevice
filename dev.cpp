#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
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

void Device::printBuf(const char *info, char *buf, int len)
{
	printf("------%s\n", info);
	for (int i=0; i<len; i++) {
		printf("%02x ", buf[i]);
	}
	printf("\n");
}

void Device::loopTest()
{
	time_t t;
	unsigned data;
	while (1) {
		t = time(NULL);
		data = (unsigned)t;
		memcpy(sendBuf, &data, sizeof(data));
		serial->send(sendBuf, sizeof(data));	
		printBuf("send", sendBuf, sizeof(data));

		int recvLen = serial->recv(recvBuf, 64);
		printBuf("recv", recvBuf, recvLen);
		
		sleep(2);
	}
}
