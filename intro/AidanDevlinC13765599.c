//Aidan Devlin
//C13765599

#include "unp.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	int listenfd, n, count=0;
	char sendbuff[MAXLINE + 1], recbuff[MAXLINE + 1], vote;
	struct sockaddr_in servaddr;
	int names[5];
	int vote =0;
	int i = 0;
	
	for(i=0; i<5; i++)
	{
		names[i] = 0;
	}
	
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));
	
	Bind(listenfd, LISTENQ);
	
	for( ; ; )
	{
		connfd = Accept(listenfd, (SA *) NULL, NULL);
		
		while((n = read(connfd, rbuff, MAXLINE))>0)
		{
			rbuff[n] = 0;
			sscanf(rbuff, "%d", vote);
			
			names[vote]++;
		
			snprintf("Thank you for voting.\nThe current votes are:\n
				Jordie: %d\nKieron: %d\nFerne: %d\nGeorge: %d\n Vicky: %d",
				names[0], names[1], names[2], names[3], names[4]);
		}
					
		Close(connfd);
	}
}//end main