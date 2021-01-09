#include "srvclnt.h"

int main()
{
	int ret1,nbytes;
	struct mq_attr attr;
	attr.mq_msgsize=256;
	attr.mq_maxmsg=10;
	mqd_t mqid1;
	
	mqid1=mq_open("/mque1",O_RDONLY|O_CREAT,0666,&attr);
	if(mqid1<0)
	{
		perror("mq_open");
		exit(1);
	}
	char buf1[8192];
	int maxlen=256,prior;
	nbytes=mq_receive(mqid1,buf1,maxlen,&prior);
	if(nbytes<0)
	{
		perror("mq_recv");
		exit(2);
	}
	buf1[nbytes]='\0';
	int k;
    printf("%s",buf1);
	
	k=execlp("/bin/gcc","gcc",buf1,0);
    if(k<0)
		{
			perror("execlp");
			exit(1);
		}
		exit(5);
		
	printf("receive msg:%s,nbytes=%d,prior=%d\n",buf1,nbytes,prior);
	mq_close(mqid1);
	return 0;
}
