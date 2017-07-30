#include "define_head_file.h"
int main(int argc, char const *argv[])
{
	int listen_fd=socket(AF_INET,SOCK_STREAM,0);
	if(listen_fd==-1)
	{
		perror("socket init fail\n");
		exit(-1);
	}
	//初始化地址结构
	struct  sockaddr_in  listen_addr;
    bzero(&listen_addr,sizeof(listen_addr));
    listen_addr.sin_family=AF_INET;
    listen_addr.sin_port=htons(1234);
    listen_addr.sin_addr.s_addr=INADDR_ANY;
    //绑定
    if(bind(listen_fd,(struct sockaddr*)&listen_addr,sizeof(listen_addr))==-1)
    {
        perror("bind fail\n");
        exit(-1);
    }
    //监听
    if(listen(listen_fd,10)==-1)
    {
        perror("listen fail\n");
        exit(-1);
    }
    //接收客户请求
    while(1)
    {
    	struct  sockaddr_in  client_addr;
        socklen_t  client_len=sizeof(client_addr);
        int client_fd=accept(listen_fd,(struct sockaddr*)&client_addr,&client_len);
        if(client_fd>0)
        {            
            printf("ip=%s\tport=%d已连接\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
        }
        //获取ID
        char buf[1024];
        char ID[1024];
        char password[1024];
        bzero(ID,sizeof(ID));
        bzero(password,sizeof(password));
        bzero(buf,sizeof(buf));
        recv(client_fd,ID,sizeof(ID)-1,0);
        recv(client_fd,password,sizeof(password)-1,0);
        if (strcmp(ID,"123456")==0 && strcmp(password,"666666")==0)
        {
        	strcpy(buf,"登录成功");
            send(client_fd,buf,strlen(buf),0);
            while(1)
            {
            bzero(buf,sizeof(buf));
            recv(client_fd,buf,sizeof(buf)-1,0);
            if(strcmp(buf,"1")==0)
            {
                char filename[100] = {"get.txt"};  //文件名
                FILE *fp = fopen(filename, "wb");  //以二进制方式打开（创建）文件
                if(fp == NULL)
                {
                    printf("Cannot open file, press any key to exit!\n");
                    system("pause");
                    exit(0);
                }
                char buffer[BUF_SIZE] = {0};  //文件缓冲区
                int nCount;
                while( (nCount = recv(client_fd, buffer, BUF_SIZE, 0)) > 0 )
                {
                     fwrite(buffer, nCount, 1, fp);
                }
                puts("File transfer success!");
                fclose(fp);
                break;
         	}
        	if(strcmp(buf,"2")==0)
        	{
           		strcpy(buf,"文件列表为空");
           		send(client_fd,buf,strlen(buf),0);
           		bzero(buf,sizeof(buf));
        	}
        	if(strcmp(buf,"3")==0)
        	{
            printf("ID=%s已下线\n",&ID);
            break;
        	}
            }
            
        }
        else
        {
        	strcpy(buf,"登录失败");
            send(client_fd,buf,strlen(buf),0);
            bzero(ID,sizeof(ID));
            bzero(password,sizeof(password));
            bzero(buf,sizeof(buf));
            recv(client_fd,ID,sizeof(ID)-1,0);
        	recv(client_fd,password,sizeof(password)-1,0);
        }
    	
    }

}
