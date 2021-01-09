#include "srvclnt.h"

int main()
{
	int ret1;
	mqd_t mqid1;
	struct mq_attr attr;
	attr.mq_msgsize=256;
	attr.mq_maxmsg=10;
	
	mqid1=mq_open("/mque1",O_WRONLY|O_CREAT,0666,&attr);
	if(mqid1<0)
	{
		perror("mq_open");
		exit(1);
	}
	char str1[]="temp.c";
	int len=strlen(str1);
	ret1=mq_send(mqid1,str1,len+1,5);
	if(ret1<0)
	{
		perror("mq_send");
		exit(2);
	}
	mq_close(mqid1);
	return 0;
}
