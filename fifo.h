#ifndef FIFO_H
#define FIFO_H

class Fifo {
public:
	Fifo(const char *dev);
	~Fifo(); 
	
	int send(char *data, int len);
	int recv(char *buf, int bufLen);

private:
	void initRdTerminal(const char *dev);
	void initWrTerminal(const char *dev);

	bool isExist(const char *dev);
	void rdPathSuffix(char **suffix);
	void wrPathSuffix(char **suffix);

private:
#define MAX_PATH_LEN 64
	int rfd;
	int wfd;
	char path[2][MAX_PATH_LEN];
};

#endif
