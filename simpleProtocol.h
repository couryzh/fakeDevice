#ifndef SIMPLE_PROTOCOL_H
#define SIMPLE_PROTOCOL_H

#include "protocol.h"

class SimpleProtocol: public Protocol {
public:
	SimpleProtocol() {}
	~SimpleProtocol() {}

	int handle(char *recvBuf, int recvLen, char *sendBuf);
};

#endif
