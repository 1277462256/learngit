#include<windows.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

#define SERVPORT  65535
#define  BACKLOG   20
#define MAXDATASIZE  1000
char buf[MAXDATASIZE] = { 0 };
void main()
{
	int recvbytes;
	int sockfd,client_fd;
	struct sockaddr_in  my_addr;
	struct sockaddr_in  remote_addr;
	char *msg = "you can change send?";
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		printf("Error at WSAStartup()\n");
		getchar();
	}
	if ((sockfd=socket(PF_INET,SOCK_STREAM,0))==-1)
	{
		printf("socket����ʧ��");
		getchar();
		exit(1);
	}
	
	my_addr.sin_family = AF_INET;      //��ʼ�����ֲ���
	my_addr.sin_port = SERVPORT;
	my_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	memset(&(my_addr.sin_zero), 0, 8);
	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr ))==-1)
	{
		printf("bind����ʧ��");
		getchar();
		exit(1);
	}
	
	if (listen(sockfd, BACKLOG) == -1)
	{
		printf("listen����ʧ��");
		getchar();
		exit(1);
	}

	while (1)
	{
		int sin_size = sizeof(struct sockaddr_in);

		if ((client_fd=accept(sockfd, (struct sockaddr*)&remote_addr, &sin_size)) == -1)
		{
			printf("accept����ʧ��");
			continue;
		}
		printf("��˵��%s",msg);
	if (send(client_fd, msg, strlen(msg), 0) == -1)
	{
		printf("����ʧ��");
		closesocket(client_fd);
		getchar();
		exit(0);
		
	}printf("���ͳɹ�");
	

		if ((recvbytes = recv(client_fd, buf, MAXDATASIZE, 0)) == -1)
		{
			printf("����ʧ��,%d", WSAGetLastError());
			getchar();
			exit(1);
		}
		buf[recvbytes] = '\0';
		printf("�Է�˵%s", buf);
	}
	getchar();
	closesocket(client_fd);
	}

