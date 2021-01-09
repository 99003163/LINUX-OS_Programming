#include "pc.h"

int main()
{
	int file_sz=4096; 
	int fd,offset1=0;
	fd=shm_open("/shm1",O_CREAT|O_RDWR,0666);
	if(fd<0)
	{
		perror("open");
		exit(1);
	}
    ftruncate(fd, file_sz);
	void *p_base;
	p_base=mmap(0,file_sz, PROT_READ, MAP_SHARED,fd,offset1);
	if(p_base==MAP_FAILED)
	{
		fprintf(stderr,"mapping failed\n");
		exit(1);
	}
	sem_t *ps,*qs;
	ps=sem_open("/s1",O_CREAT, 0777, 1);
	qs=sem_open("/s2",O_CREAT, 0777, 0);
	char buff[64];
	sem_wait(qs);
	sem_wait(ps);
        strncpy(buff,p_base,10);
	printf("buff=%s\n",buff);
	strcpy(buff,p_base+10);
	printf("buff=%s\n",buff);
	sem_post(ps);
	sem_unlink("s1");
	sem_unlink("s2");
	munmap(p_base,file_sz);
	return 0;
}
