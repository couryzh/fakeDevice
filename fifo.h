#ifndef FIFO_H
#define FIFO_H

class Fifo {
public:
	Fifo(const char *dev);
	~Fifo(); 
	
	int send(char *data, int len);
	int recv(char *buf, int bufLen);

private:
#define MAX_PATH_LEN 64
	int fd;
	char path[MAX_PATH_LEN];
};

#endif
