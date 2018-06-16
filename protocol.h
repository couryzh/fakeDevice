#ifndef PROTOCOL_H
#define PROTOCOL_H

class Protocol {
public:
	Protocol() {}
	virtual ~Protocol() {}

	virtual int handle(char *recvBuf, int recvLen, char *sendBuf) = 0;
};

#endif
