#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <termios.h>
#include <errno.h>

#include "serial.h"

Serial::Serial(const char *dev, int speed, int databit, int stopbit, int parity)
	:speed_(speed), databit_(databit), stopbit_(stopbit),parity_(parity)
{
	int devLen;
	if (dev) {
		devLen = strlen(dev);	
		devName = new char[devLen+1];
		memcpy(devName, dev, devLen);
		devName[devLen] = 0;
	}

	fd = open();
	if (fd < 0) {
		fprintf(stderr, "open %s failed\n", devName);
		exit(-1);
	}
}

Serial::~Serial()
{
	if (fd > 0) 
		::close(fd);
	if (devName)
		delete devName;

}

int Serial::open()
{
	const int speed_arr[] = {B38400, B19200, B9600, B4800};
	const int name_arr[] = {38400, 19200, 9600, 4800};

	int fd;
	size_t i;
	struct termios opt;

	fd = ::open(devName, O_RDWR | O_NOCTTY);
	if (fd < 0) {
		perror("open serial");
		return -1;
	}
	tcgetattr(fd, &opt);

	// set speed
	for (i = 0; i < sizeof(name_arr) / sizeof(name_arr[0]); i++) {
		if (speed_ == name_arr[i]) {
			tcflush(fd, TCIOFLUSH);
			cfsetispeed(&opt, speed_arr[i]);
			cfsetospeed(&opt, speed_arr[i]);
			break;
		}
	}

	// enable receiver, local mode
	opt.c_cflag |= (CLOCAL | CREAD);


	// 数据???	opt.c_cflag &= ~CSIZE;
	switch (databit_) {
		case 7:
			opt.c_cflag |= CS7;
			break;
		case 8:
			opt.c_cflag |= CS8;
			break;
		default:
			fprintf(stderr, "unsupported databits\n");
			return -4;
	}

	// check bit
	switch (parity_) {
		case 'n':
		case 'N':
			opt.c_cflag &= ~PARENB;
			break;
		case 'o':
		case 'O':
			opt.c_cflag |= (~PARODD | PARENB);
			break;
		case 'e':
		case 'E':
			opt.c_cflag |= PARENB;
			opt.c_cflag &= ~PARODD;
			break;
		case 'S':
		case 's':
			opt.c_cflag &= ~PARENB;
			opt.c_cflag &= ~CSTOPB;
			break;
		default:
			fprintf(stderr, "unsupported parity\n");
			return -5;
	}

	// stopbit
	switch (stopbit_) {
		case 1:
			opt.c_cflag &= ~CSTOPB;
			break;
		case 2:
			opt.c_cflag |= CSTOPB;
			break;
		default:
			fprintf(stderr, "unsupported stop bit\n");
			return -6;
	}

	if (parity_ != 'n' && parity_ != 'N') {
		opt.c_iflag |= INPCK;
	}

	// disable flow control
	opt.c_cflag &= ~CRTSCTS;

	// disable software flow control
	opt.c_iflag &= ~(IXON | IXOFF | IXANY);

	// row input and output
	opt.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);

	tcflush(fd, TCIFLUSH);
	opt.c_cc[VTIME] = 0;
	opt.c_cc[VMIN] = 1;

	if (tcsetattr(fd, TCSANOW, &opt) != 0) {
		fprintf(stderr, "set serial failed: %s\n", strerror(errno));
		return -2;
	}

	return fd;
}

int Serial::send(char *data, int len)
{
	//ssize_t write(int fd, const void *buf, size_t count);
	return ::write(fd, data, len);
}

int Serial::recv(char *buf, int bufLen)
{
	return ::read(fd, buf, bufLen);
}
