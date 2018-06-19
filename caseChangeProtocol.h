#ifndef CASE_CHANGE_PROTOCOL_H
#define CASE_CHANGE_PROTOCOL_H

#include "protocol.h"

class CaseChangeProtocol: public Protocol {
public:
	CaseChangeProtocol() {}
	~CaseChangeProtocol() {}

	int handle(char *recvBuf, int recvLen, char *sendBuf);
};

#endif
