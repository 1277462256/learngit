#include<WinSock2.h>
#include<stdio.h>
#include<string.h>
#include<direct.h>
#pragma comment(lib,"Ws2_32.lib")
#define  port   3000
#define  BUF_LINE  1024
#define  MAX_LINE  128
#define  HTML_NAME  "happy new yer.html"
#define SERVER "Server: csr_http1.1\r\n"

char *firstfile1 ="<!DOCTYPE html>"
"<html>"
"<head>"
"<title>��������վ</title>"
"</head>"
"<body>"
"<h1>��������վ</h1>"
"<p>�����޷���ʾ</p>"
"</body>"
"</html>"
;
char *firstfile= "<!DOCTYPE html>   <html>   <head>  <meta name = 'keywords' connect = '��������վ'>  <!����������><meta name = 'author'connect = '����'>             <!������Ϣ>"
"<meta http - equiv = 'cache-control' content = 'no - cache'>"
"<meta http - equiv = 'pragma' content = 'no - cache'>  <!��ֹ�ӻ����е���>"
"<meta http - equiv = 'refresh' content ='100000'  >  <!ҳ��ˢ��ʱ��>"
"<!meta http - equiv = 'page-enter' content = 'revelations(duration=300,transition=19)'>"
"<title>��������վ</title>"
"<link rel = 'icon'  href = 'http://oygwu7lhj.bkt.clouddn.com/favicon.ico'/>"
"</head>"
"<body>"
"<div id = 'headr' style = 'width:1400px;heigth:500px;background-color:#c7c7c7'>"
"<img src='0-9.jpg'>"
"<h1 align = 'center' style = 'color:red'>��ӭ������������վ</h1>"
"</div>"
"</body>"
"</html> "
;
char *secondfile = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>"
"����һ������"
"</title>"
"</head>"
"<body>"
"<img src='http://10.4.17.96/0-9.jpg'/>"
"</body>"
"</html>";



void nofp(SOCKET);
int send_not_found(SOCKET);
void file_ok(SOCKET resock, long int flen);
int send_file(SOCKET resock, FILE *fp);

DWORD WINAPI simplewebconstruct(LPVOID lparam)
{
	char recv_buf[BUF_LINE];
	char method[MAX_LINE];
	char url[MAX_LINE];
	char path[BUF_LINE];
 
	memset(recv_buf, 0, sizeof(recv_buf));
	SOCKET resock = (SOCKET)lparam;
	if (recv(resock, recv_buf, sizeof(recv_buf), 0) == SOCKET_ERROR)
	{
		printf("����ʧ��\n");
	}
	int i = 0;
	int j = 0;
	while ((!(' '== recv_buf[i])) && (i < (sizeof(method)-1)))
	{

		method[j] = recv_buf[i];
		
		i++; j++;
	}
	method[j] ='\0';
	printf("method: %s\n", method);
	if (_stricmp(method, "GET") && _stricmp(method, "head"))
	{
		closesocket(resock);
		printf("������ҳ��ʽ\n");
		return -1;
	}
	j = 0;
	while ((' ' == recv_buf[i]) && (i < (sizeof(method)-1)))
		i++; 
	while ((' ' != recv_buf[i]) && (i < (sizeof(method)-1)) && (j<(sizeof(method)-1)))
	{
		if (recv_buf[i]=='/')
		{
			url[j] = '\\';
		}
		else
		{
			url[j] = recv_buf[i];
		}
		i++; j++;
	}
	url[j] = '\0';
	printf("%s\n",url);
	_getcwd(path, sizeof(path));
	strcat_s(path,url);
	printf("%s\n", path);
	
	FILE *fp;
	fopen_s(&fp,path,"rb+");
	if (fp == NULL)
	{
		nofp(resock);
	if (0 == _stricmp(method, "GET"))
	{
		send_not_found(resock);
	}
	closesocket(resock);
	printf("�˳�\n");
	return 0;
	}

	printf("׼���ļ�\n");
	fseek(fp, 0, SEEK_SET);
	fseek(fp, 0, SEEK_END);
	long flen = ftell(fp);
	printf("file length: %ld\n", flen);
	fseek(fp, 0, SEEK_SET);

	// ����200 OK HEAD
	file_ok(resock, flen);

	// �����GET���������������Դ
	if (0 == _stricmp(method, "GET"))
	{
		send_file(resock, fp);
		printf("���ͳɹ�");
	
	}
	fclose(fp);

	closesocket(resock); //�ͷ������׽��֣�������ÿͻ���ͨ��
	printf("close ok.\n");
	printf("***********************\n\n\n\n");

	return -1;
}

void nofp(SOCKET resock)
{ 
	char send_buf[MAX_LINE];
	sprintf_s(send_buf, "HTTP/1.1 200 OK\r\n");
	send(resock, send_buf, strlen(send_buf), 0);
	//  sprintf(send_buf, "Date: %s\r\n", ctime(&timep));
	//  send(sAccept, send_buf, strlen(send_buf), 0);
	sprintf_s(send_buf, "Connection: keep-alive\r\n");
	send(resock, send_buf, strlen(send_buf), 0);
	sprintf_s(send_buf, SERVER);
	send(resock, send_buf, strlen(send_buf), 0);
	/*sprintf_s(send_buf, "Content-Length: %d\r\n", 80000);
	send(resock, send_buf, strlen(send_buf), 0);*/
	sprintf_s(send_buf, "Content-Type: text/html\r\n");
	send(resock, send_buf, strlen(send_buf), 0);
	sprintf_s(send_buf, "\r\n");
	send(resock, send_buf, strlen(send_buf), 0);
}
void file_ok(SOCKET resock,long flen)
{
	char send_buf[MAX_LINE];
	sprintf_s(send_buf, "HTTP/1.1 200 OK\r\n");
	send(resock, send_buf, strlen(send_buf), 0);
	sprintf_s(send_buf, "Connection: keep-alive\r\n");
	send(resock, send_buf, strlen(send_buf), 0);
	/*sprintf_s(send_buf, "Cache-Control:max-age=31536000\r\n");
	send(resock, send_buf, strlen(send_buf), 0);*/
	//  sprintf(send_buf, "Date: %s\r\n", ctime(&timep));
	//  send(sAccept, send_buf, strlen(send_buf), 0);
	sprintf_s(send_buf, SERVER);
	send(resock, send_buf, strlen(send_buf), 0);
	sprintf_s(send_buf, "Content-Length: %ld\r\n", flen);
	send(resock, send_buf, strlen(send_buf), 0);
	sprintf_s(send_buf, "Content-Type: image/jpeg\r\n");
	send(resock, send_buf, strlen(send_buf), 0);
	/*sprintf_s(send_buf, "Accept-Encoding: gzib\r\n");
	send(resock, send_buf, strlen(send_buf), 0);*/
	sprintf_s(send_buf, "\r\n");
	send(resock, send_buf, strlen(send_buf), 0);
}
int send_file(SOCKET resock,FILE *fp)
{
	char send_buf[MAX_LINE];
	int count = 0;
	while (1)
	{
		memset(send_buf, 0, sizeof(send_buf));    //������0
		
		//fgets(send_buf, sizeof(send_buf), fp);
		////printf("send_buf: %s\n",send_buf);
		// count = count + strlen(send_buf);
		//if (SOCKET_ERROR == send(resock, send_buf, sizeof(send_buf), 0))
		//{
		//	printf("send() Failed:%d\n", WSAGetLastError());
		//	return -1;

		//}
		//if (feof(fp))
		//{
		//	printf("%d", count);
		//	fclose(fp);
		//	return 0;
		//}
		int refile = fread(send_buf, sizeof(send_buf[MAX_LINE]), 1, fp);
		if (SOCKET_ERROR == send(resock, send_buf, refile, 0))
		{
			printf("send() Failed:%d\n", WSAGetLastError());
			return -1;
		}
		if (feof(fp))
		{
			fclose(fp);
			return 0;
		}


	}
}
int send_not_found(SOCKET resock)
{
	char send_buf[BUF_LINE];
	FILE *fp;
	fopen_s(&fp, HTML_NAME, "rb");
	fseek(fp, 0, SEEK_SET);
	fseek(fp, 0, SEEK_END);
	fseek(fp, 0, SEEK_SET);
	while (1)
	{
		memset(send_buf, 0, sizeof(send_buf));    //������0
		fgets(send_buf, sizeof(send_buf), fp);
		//printf("send_buf: %s\n",send_buf);
		if (SOCKET_ERROR == send(resock, send_buf, strlen(send_buf), 0))
		{
			printf("send() Failed:%d\n", WSAGetLastError());
			return -1;
		}
		if (feof(fp))
		{
			fclose(fp);
			return 0;
		}
		
			
	}
	
}
	


int main()
{
    sockaddr_in  my_addr, client;
	SOCKET sockfd,resock;
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	printf("�����׽��ֳɹ�\n");
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sockfd, (sockaddr *)&my_addr, sizeof(sockaddr_in));
	printf("�󶨳ɹ�\n");
	listen(sockfd,20);
	printf("�����ɹ�\n");
	while (1)
	{
		int sizelen = sizeof(sockaddr_in);
		resock = accept(sockfd, (struct sockaddr *)&client, &sizelen);
		/*printf("%s/n", inet_ntoa( client.sin_addr));*/
		printf("���ӳɹ�\n");
		DWORD ThreadID;
		CreateThread(NULL, 0, simplewebconstruct, (LPVOID)resock, 0, &ThreadID);
		printf("����************************\n");
	}
	closesocket(resock);
	WSACleanup();
	return 0;
}