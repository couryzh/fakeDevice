#include <stdlib.h>
#include <string.h>
#include "simpleProtocol.h"

int SimpleProtocol::handle(char *recvBuf, int recvLen, char *sendBuf)
{
	int num, sendLen;
	float fval;	

	sendLen = 0;
	switch (recvBuf[0]) {
		case 1:
			num = rand();	
			fval = 20 + num * 10.0 / RAND_MAX;
			sendBuf[0] = 1;
			memcpy(&sendBuf[1], &fval, sizeof(fval));
			sendLen = 1 + sizeof(fval);
			break;
		case 2:
			num = rand();	
			fval = 50 + num * 20.0 / RAND_MAX;
			sendBuf[0] = 2;
			memcpy(&sendBuf[1], &fval, sizeof(fval));
			sendLen = 1 + sizeof(fval);
			break;
		default:
			break;
	}

	return sendLen;
}
