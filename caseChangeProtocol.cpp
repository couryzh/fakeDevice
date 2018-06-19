#include "caseChangeProtocol.h"

int CaseChangeProtocol::handle(char *recvBuf, int recvLen, char *sendBuf)
{
	if (recvLen >= 1) {
		if (recvBuf[0] >= 'a' && recvBuf[0] <='z') {
			sendBuf[0] = recvBuf[0] - 'a' + 'A';
		} else if (recvBuf[0] >= 'A' && recvBuf[0] <='Z') {
			sendBuf[0] = recvBuf[0] - 'A' + 'a';
		} else {
			sendBuf[0] = recvBuf[0];
		}
		return 1;
	}

	return 0;
}
