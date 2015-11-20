#include "unp.h"
#include <string.h>
#include <stdio.h>
#define HOME_PAGE "202: <html></html><body></body>\n"

int main(int argc, char **argv)
{
	int		n, listenfd, connfd;
	struct	sockaddr_in servaddr;
	char	wbuff[MAXLINE], rbuff[MAXLINE], cmd[16], path[64], vers[16];
	
	if(argc != 2)
	{
		err_quit("usage: a.out <Port>");
	}
	
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family		 = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));
	
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
	
	Listen(listenfd, LISTENQ);
	
	for( ; ; )
	{
		connfd = Accept(listenfd, (SA *) NULL, NULL);
		
		while((n = read(connfd, rbuff, MAXLINE)) >0)
		{
			rbuff[n] = 0; //null terminate
			
			if(fputs(rbuff, stdout) == EOF)
			{
				err_sys("fputs error");
			}
			
			if(strstr(rbuff,"\r\n\r\n")>0)  //looks for a needle in a haystack chat *strstr(const
											//char *haystack, const char *needle); It returns a pointer
											//to the location the needle within the haystack otherwise 
											//if not found it returns zero
											//strcmp returns zero if "index" is a path.
			{
				break;
			}//end if
		}//end while
		
		if (n < 0)
		{
			err_sys("read error");
			
			sscanf(rbuff, "%s %s %s", cmd, path, vers);
			
			if(!strcmp(path, "/index"))
			{
				snprintf(wbuff, sizeof(wbuff), "%s", HOME_PAGE); //using a hash-define string
				Write(connfd, wbuff, strlen(wbuff));
			}
			
			else
			{
				printf("%s could not be found\n", path); //print to local screen for testing
				snprintf(wbuff, sizeof(wbuff), "ERROR 404: page not found\r\n"); //using a string ; could also have used a has defined string
				Write(connfd, wbuff, strlen(wbuff));
			}//end else
		}//end if
		
		Close(connfd);
		
	}//end for
}//end main
