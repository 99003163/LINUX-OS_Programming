#include "srvclnt.h"

int main()
{
	int ret1, n_bytes;
	mqd_t mqid;
	struct mq_attr attr;
	attr.mq_msgsize=256;
	attr.mq_maxmsg=10;
	
	mqid=mq_open("/mque",O_CREAT | O_RDWR,0666,&attr);
	if(mqid<0)
	{
		perror("mq_open");
		exit(1);
	}

	char str1[20] = "AAsendAA";
	/* Send a message to Queue */
	ret1=mq_send(mqid,str1,20,5);
	if(ret1<0)
	{
		perror("mq_send");
		exit(2);
	}

	char buf[8192];
	int max_len=256,prior;
	/* Receive the message from Server through Queue */
	n_bytes=mq_receive(mqid,buf,max_len,&prior);
	if(n_bytes<0)
	{
		perror("mq_recv");
		exit(2);
	}
	buf[n_bytes]='\0';
	printf("msg from server : %s\n",buf);
	/* Close the Queue */
	mq_close(mqid);

	return 0;
}
