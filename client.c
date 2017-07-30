#include "define_head_file.h"
#define BUF_SIZE 1024

//登录
void login(int client_fd)
{
	char ID[1024];
    char password[1024];
    char buf[1024];
    while(1)
	{
    printf("请输入账号：");
    gets(ID); 
    send(client_fd,ID,strlen(ID),0);
    bzero(ID,sizeof(ID));
    printf("请输入密码：");
    gets(password);       
    send(client_fd,password,strlen(password),0); 
    bzero(password,sizeof(password));
    recv(client_fd,buf,sizeof(buf)-1,0);
    printf("%s\n",buf);
    if(strcmp(buf,"登录成功")==0)
    	break;
	}
}

//上传文件
void upload(int client_fd)
{
	printf("请选择需要上传的文件\n");
    char fname[1024];
    gets(fname);
    FILE *fp = fopen(fname, "rb");  //以二进制方式打开文件
    if(fp == NULL)
    	{
        	printf("Cannot open file, press any key to exit!\n");
        	system("pause");
        	exit(0);
    	}
    char buffer[BUF_SIZE] = {0};  //缓冲区
    int nCount;
    while( (nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0 )
    		{
        		send(client_fd, buffer, nCount, 0);
    		}
    shutdown(client_fd, 0);  //文件读取完毕，断开输出流，向服务端发送FIN包
    recv(client_fd, buffer, BUF_SIZE, 0);  //阻塞，等待服务端接收完毕
    fclose(fp);
    printf("上传成功\n");
}

int main(int argc,char const *argv[])
{
	int  client_fd=socket(AF_INET,SOCK_STREAM,0);
	if(client_fd==-1)
	{
		perror("soket fail\n");
		exit(-1);
	}
	//定义服务端地址结构
	struct  sockaddr_in  ser_addr;
	ser_addr.sin_family=AF_INET;
	ser_addr.sin_port=htons(1234);
	ser_addr.sin_addr.s_addr=INADDR_ANY;
	//客户端发送链接请求
	if(connect(client_fd,(struct sockaddr*)&ser_addr,sizeof(ser_addr))==-1)
	{
		printf("连接服务器失败\n");
		exit(-1);
	}
	printf("已成功连接服务器\n");
	//登录
	login(client_fd);

	char buf[1024];
	while(1)
	{
		bzero(buf,sizeof(buf));
		printf("************\n1.上传文件\n2.下载文件\n3.退出\n************\n");
    	gets(buf);
    	send(client_fd,buf,strlen(buf),0);
    	if (strcmp(buf,"1")==0)
    		upload(client_fd);
    	if (strcmp(buf,"2")==0)
    		recv(client_fd,buf,sizeof(buf)-1,0);
    	if (strcmp(buf,"3")==0)
    		exit(-1);
	
    	}

}
