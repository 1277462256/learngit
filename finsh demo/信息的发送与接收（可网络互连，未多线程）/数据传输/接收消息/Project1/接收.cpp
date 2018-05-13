#include<windows.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

#define SERVPORT  65535
#define MAXDATASIZE   100
void main(int argc,char *argv[])
{
	int sockfd, recvbytes;
	char buf[MAXDATASIZE] = { 0 };
	
	struct sockaddr_in serv_addr;

	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		printf("Error at WSAStartup()\n");
		getchar();
	}
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("socket����ʧ��");
		getchar();
		exit(1);
	}
	serv_addr.sin_family = AF_INET;      //��ʼ�����ֲ���
	serv_addr.sin_port = SERVPORT;
	serv_addr.sin_addr.s_addr = inet_addr("183.152.255.93");
	if (serv_addr.sin_addr.s_addr == INADDR_NONE)
	{
		printf("ip����ʧ��");
		getchar();
	}
	memset(&(serv_addr.sin_zero), 0, 8);
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr))== -1)
	{
		printf("connectʧ��");
		getchar();
	}
	
	if ((recvbytes = recv(sockfd, buf, MAXDATASIZE, 0)) == -1)
	{
		printf("����ʧ��");
			getchar();
			exit(1);
	}
	buf[recvbytes] = '\0';
	printf("connect�ɹ�");
	printf("%s", buf);
	closesocket(sockfd);
	getchar();
}