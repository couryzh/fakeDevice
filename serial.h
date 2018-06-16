#ifndef SERIAL_H
#define SERIAL_H

class Serial {
public:
	Serial(const char *dev, int speed=9600, int databit=8, int stopbit=1, int parity='n');

	~Serial();
	int send(char *data, int len);
	int recv(char *buf, int bufLen); 


private:
	int open();

private:
	int fd;
	char *devName;
	int speed_;
	int databit_;
	int stopbit_;
	int parity_;
};

#endif
