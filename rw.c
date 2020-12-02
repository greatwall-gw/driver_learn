
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(void)
{
	int fd;
	int size = 0;
	fd = open("/dev/hello0", O_RDWR);
	if (!fd)
	{
		perror("open");
		exit(-1);
	}
	char buf[64] = {0};
	size = read(fd, buf, sizeof(buf));
	if (size < 0)
	{
		perror("read");
		close(fd);
		exit(-1);
	}

	printf("read buf is: %s\nsize is: %d\n", buf, size);

	char wbuf[] = "write data to kernel!";
	size = write(fd, wbuf, sizeof(wbuf));
	if (size < 0)
	{
		perror("write");
		close(fd);
		exit(-1);
	}

	close(fd);

	return 0;
}