#include "unp.h" //include appropriate header file(s) for in-built socket functions
#include <time.h> //required to calculate date and time

int main(int argc, char **argv)
{
	int 				listenfd, connfd; //socket IDs; one for the listening socket and one for the connected socket
	struct sockaddr_in	servaddr; //address structure to hld this server's address
	char				buff[MAXLINE]; //buffer to hold send data
	time_t				ticks; //required to calculate date and time
	
	if (argc != 2) //verifies number of command-line args; two in this instance
	{
		err_quit("usage: <Program Name> <Port No.>");
	}
		
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);	//create socket
												//Note this slightly different to the client code (uses lower case 's') as the
												//error checking is wrapped inside a new function called Socket (upper case 's')

	bzero(&servaddr, sizeof(servaddr)); // zero and fill in server address structure
	servaddr.sin_family			= AF_INET;
	servaddr.sin_addr.s_addr	= htonl(INADDR_ANY); //connect to any local IP address
	servaddr.sin_port			= htons(atoi(argv[1])); //daytime server port number
	
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr)); // connects the socket to an external interface
	
	Listen(listenfd, LISTENQ); // changes the socket to a "passive listening" socket
	
	for ( ; ; )
	{
		connfd = Accept(listenfd, (SA *) NULL, NULL); // accept the next connection request from client
		
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks)); //construct the data to return to the client
		Write(connfd, buff, strlen(buff)); // write data to the client
		
		Close(connfd);
	}//end for()
}//end main()

//Note the use of upper-case letters at the start of the socket primitives names. These are wrapper functions that
//include the error checking functionality for each call. The actual socket primitives use lower case names.