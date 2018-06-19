#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "dev.h"

Device::Device(const char *path)
{
	fifo = new Fifo(path);
	proto = new CaseChangeProtocol();
}


Device::~Device()
{
	delete fifo;
	delete proto;
}

int Device::comm()
{
	int recvLen, sendLen;

	while (1) {
		sleep(1);
		recvLen = fifo->recv(recvBuf, 64);	
		if (recvLen <= 0) continue;
		printf("recvLen=%d\n", recvLen);
		printBuf("recv", recvBuf, recvLen);

		sendLen = proto->handle(recvBuf, recvLen, sendBuf);

		printf("sendLen=%d\n", sendLen);
		printBuf("send", sendBuf, sendLen);
		fifo->send(sendBuf, sendLen);
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

