#include "unp.h"

int main(int argc, char **argv)
{
	int sockfd, n, count=0;
	char sendbuff[MAXLINE + 1], recbuff[MAXLINE + 1], vote;
	struct sockaddr_in servaddr;
	int[5] names;
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
		
		snprintf("Thank you for voting.\n
					The current votes are:\n
					Jordie: %d\nKieron: %d\nFerne: %d\nGeorge: %d\n Vicky: %d",
					names[0], names[1], names[2], names[3], names[4]);
					
		Close(connfd);
	}
}//end main