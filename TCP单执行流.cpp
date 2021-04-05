#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet.in.h>
#include <arpa/inet.h>
#include<string.h>
#include<iostream>
int main()
{
	//1.�����׽���
	int listen_sockfd = sock(AF_INET, SOCK_STREAM, 0);
	if (listen_sockfd < 0)
	{
		perror("create listen_sockfd false!");
		return -1;
	}
	//2.�󶨵�ַ��Ϣ 
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");
	addr.sin_port = htons(19999);
	int ret = bind(listen_sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret < 0)
	{
		perror("bind false!");
		return -1;
	}
	//3.����
	int ret = listen(listen_sockfd, 8); 
	if(ret < 0)
	{
		perror("listen false!");
		return -1;
	}
	//4.����������
	int new_sock = accept(listen_sock, NULL, NULL);
	if(new_sock < 0)
	{
		perror("accept false!");
		return -1;
	}
	while(1)
	{
		//5.������Ϣ 
		char buf[1024]={0};
		ssize_t recv_size = recv(new_sock, buf, sizeof(buf) - 1, 0);
		//5.1�������� 
		if (recv_size < 0)
		{
			perror("recv");
			continue;
		}
		//5.2 �Զ˹ر� 
		else if(recv_size == 0)
		{
			printf("peer shutdown!/n");
			close(new_sock);
			close(listen_sock);
			return 0;
		}
		// 5.3�ɹ����� 
		else
		{
			printf("client says: %s\n",buf);
			memset(buf, '\0', sizeof(buf));
			printf("enter mesage to client: \n");
			std::cin >> buf;
		}
		//6.������Ϣ
		ssize_t send_size = send(new_sock,buf ,strlen(buf), 0);
		if (send_size < 0)
		{
			perror("send");
			continue;
		}	 
	}
	close(new_sock);
	close(listen_sockfd);
	return 0;
}

