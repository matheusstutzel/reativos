#include<MySerial.h>


//char *portname = "/dev/ttyACM"
int fd;
char buf[256];
 
void startSerial(char * portname){
	/* Open the file descriptor in non-blocking mode */
 	fd = open(portname, O_RDWR | O_NOCTTY);

    /* Set up the control structure */
    struct termios toptions;

    /* Get currently set options for the tty */
    tcgetattr(fd, &toptions);
 
    /* Set custom options */

    /* 9600 baud */
    cfsetispeed(&toptions, B9600);
    cfsetospeed(&toptions, B9600);
    /* 8 bits, no parity, no stop bits */
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    /* no hardware flow control */
    toptions.c_cflag &= ~CRTSCTS;
    /* enable receiver, ignore status lines */
    toptions.c_cflag |= CREAD | CLOCAL;
    /* disable input/output flow control, disable restart chars */
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
    /* disable canonical input, disable echo,
    disable visually erase chars,
    disable terminal-generated signals */
    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    /* disable output processing */
    toptions.c_oflag &= ~OPOST;
    /* wait for 12 characters to come in before read returns */
    /* WARNING! THIS CAUSES THE read() TO BLOCK UNTIL ALL */
    /* CHARACTERS HAVE COME IN! */
    toptions.c_cc[VMIN] = 6;
    /* no minimum time to wait before read returns */
    //toptions.c_cc[VTIME] = 0;

    /* commit the options */
    tcsetattr(fd, TCSANOW, &toptions);
    /* Wait for the Arduino to reset */
    usleep(1000*1000);
}
int readSerial(){
 /* Flush anything already in the serial buffer */
 tcflush(fd, TCIFLUSH);
 /* read up to 128 bytes from the fd */
 int n = read(fd, buf, 128);
 if(buf[0]<1+'0' || buf[0]>2+'0') return 0;
 if(buf[1]<0+'0' || buf[1]>9+'0') return 0;
 if(buf[2]<0+'0' || buf[2]>9+'0') return 0;
 if(buf[3]<0+'0' || buf[3]>9+'0') return 0;

 if(buf[0]==1+'0')return (buf[1]-'0')*100+(buf[2]-'0')*10+(buf[3]-'0');
 if(buf[0]==2+'0')return -(buf[3]-'0');
	return 0;
}


