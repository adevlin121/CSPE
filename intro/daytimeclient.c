# include "unp.h"

int
main(int argc, char **argv)
{

    int sockfd, n, counter = 0;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    
    if (argc != 3)  
    {
        err_quit("usage: a.out <IPaddress>");
    }
    if( (sockfd = socket(AF_INET , SOCK_STREAM , 0)) < 0)
    {
        err_sys("socket error");
    }
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family == AF_INET;