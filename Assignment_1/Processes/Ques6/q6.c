#include<unistd.h>
	#include <string.h>
	#include<stdio.h>
	#include<stdlib.h>
	#include <sys/wait.h>
	#include <string.h>
	
	
	
	int main()
	{
		int ret,reti;
		int chld1=fork();
		int chld2,chld3,chld4,chld5;
		char *s;
		char *ss;
		ss="./s.out";
		s="s.out"; 
		if(chld1<0||chld2<0||chld3<0)
		{
		perror("fork");
		exit(1);
		}
		if(chld1==0)
		{ 
		execlp("gcc","gcc","-c","cube.c",NULL);
		printf("Compilation of cube.c is completed\n");
	    	}
	    	else
	    	{
	    	waitpid(chld1, &reti, 0);
	    	//chld2=fork();
	    	}
	
		chld2=fork();
		if(chld2==0)
		{
	    	execlp("gcc","gcc","-c","sub.c",NULL);
		printf("Compilation of sub.c is completed\n");
		}
	    	else
	    	{
		waitpid(chld2, &reti, 0);
	    	}
		chld3=fork();
		if(chld3==0)
		{
	    	execlp("gcc","gcc","-c","test.c",NULL);
		printf("Compilation of test.c is completed\n");
		}
	    	else
	    	{
		waitpid(chld3, &reti, 0);
	    	}
		chld4=fork();
		if(chld4==0)
		{
	  	execlp("gcc","gcc","sub.o","cube.o","test.o","-o","s.out",NULL);
		printf("Linking is completed\n");
		printf("Execution:\n");
		}
	    	else
	    	{
		waitpid(chld4, &reti, 0);
		  } 
		execl("./s.out", "./s.out", NULL); 	 
		exit(0);
	}
