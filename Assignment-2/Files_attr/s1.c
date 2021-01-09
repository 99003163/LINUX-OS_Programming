#include "SC.h"

int main()
{
	int ret1,nbytes;
	struct mq_attr attr;
	struct stat s_b;
	attr.mq_msgsize=256;
	attr.mq_maxmsg=10;
	mqd_t mq_id;
	/* Open a Message Queue in Server Process */
	mq_id=mq_open("/mque",O_CREAT | O_RDWR,0666,&attr);
	if(mq_id<0)
	{
		perror("mq_open");
		exit(1);
	}

	char buf[20];
	int maxlen=256,prior;
	
	printf("Waiting for message from Client .......\n");
	nbytes=mq_receive(mq_id,buf,1024,&prior);
	if(nbytes<0)
	{
		perror("mq_recv");
		exit(2);
	}
	
	lstat(buf, &s_b);
	
	ret1 = mq_send(mq_id,(const char *)&s_b,sizeof(s_b),100);
	if(ret1 < 0)
	{
		perror("mq_send");
		exit(2);
	}
	/* Close the Queue */
	mq_close(mq_id);
	return 0;
}
