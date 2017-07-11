#ifndef MySerial
#define MySerial 10
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
 
void startSerial(char * portname);
int readSerial();
#endif
