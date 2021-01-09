#include "srvclnt.h"

int main()
{
	int ret1,n_bytes;
	struct mq_attr attr;
	attr.mq_msgsize=256;
	attr.mq_maxmsg=10;
	mqd_t mqid;
	mqid=mq_open("/mque",O_CREAT | O_RDWR,0666,&attr);
	if(mqid<0)
	{
		perror("mq_open");
		exit(1);
	}

	char buf[8192];
	int max_len=256,prior;
	printf("Waiting for message from Client .......\n");
	n_bytes=mq_receive(mqid,buf,max_len,&prior);
	if(n_bytes<0)
	{
		perror("mq_recv");
		exit(2);
	}
	buf[n_bytes]='\0';
	printf("msg sent from client : %s\n",buf);

	for (int i=0; buf[i]!='\0'; i++)
    {
        if (buf[i]>='A' && buf[i]<='Z')
            buf[i] = buf[i] + 'a' - 'A';
        else if (buf[i]>='a' && buf[i]<='z')
            buf[i] = buf[i] + 'A' - 'a';
    }


	ret1 = mq_send(mqid,buf,100,100);
	if(ret1 < 0)
	{
		perror("mq_send");
		exit(2);
	}

	mq_close(mqid);
	return 0;
}
