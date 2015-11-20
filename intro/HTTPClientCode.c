#include "unp.h"

int main(int argc, char **argv)
{
	int					sockfd, n;
	char				recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;
	char				buff[MAXLINE];
	
	if(argc != 4)
	{
		err_quit("usage: ./httpclient <IPaddress> <Port Number> <Resource Name>"); //to run the program use this command
	}
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		err_sys("socket error");
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons (atoi(argv[2])); //port number from the command line
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) //inet_pton converts the IP address from the command line
	{
		err_quit("inet_pton error for %s", argv[1]);
	}
	
	if(connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
	{
		err_sys("connect effor");
	}
	
	snprintf(buff, sizeof(buff), "GET /%s HTTP/1.1\r\nHost: www.comp.dit.ie\r\n\r\n", argv[3]); //create the client request
							// in the outgoing buffer 'buff'. Note the hostname must be changed to reflect the proper hostname.
							// Also note that the resource name is passed in from the command line
	Write(sockfd, buff, strlen(buff)); //write contents of send buffer to the socket
	
	while((n = read(sockfd, recvline, MAXLINE)) > 0) //read the data returned by the server into the receive buffer
	{
		recvline[n] = 0; //null terminate the receive buffer
		if(fputs(recvline, stdout) == EOF) //print the contents of the receive buffer to the screen
		{
			err_sys("fputs error");
		}
	}
	
	if (n < 0)
	{
		err_sys("read error");
	}
	
	exit(0);
}
