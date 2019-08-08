#define _LARGEFILE64_SOURCE
#define _LARGEFILE_SOURCE
#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>

#define     PORT    6000
#define     IPSTR   "127.0.0.1"

int connect_to_ser();
void recv_file(int sockfd, char* name);
void send_file(int c, char * name);
int main()
{
    int sockfd = connect_to_ser();
    if ( sockfd == -1 )
    {
        printf("connect to ser failed!\n");
        return 0;
    }

    while( 1 )
    {
        char buff[128] = {0};

        printf("Connect>>");
        fflush(stdout);

        fgets(buff,128,stdin);//  ls, rm a.c , get a.c ,sdfg , exit
        buff[strlen(buff)-1] = 0;

        if ( buff[0] == 0 )
        {
            continue;
        }

        char sendbuff[128] = {0};
        strcpy(sendbuff,buff);

        int i = 0;
        char * myargv[10] = {0};
        char * s = strtok(buff," ");
        while( s != NULL )
        {
            myargv[i++] = s;
            s = strtok(NULL," ");
        }

        if ( myargv[0] == NULL )
        {
            continue;
        }

        if ( strcmp(myargv[0],"exit") == 0 )
        {
            break;
        }
        else if ( strcmp(myargv[0],"get") == 0 )
        {
            if ( myargv[1] == NULL )
            {
                continue;
            }
            send(sockfd,sendbuff,strlen(sendbuff),0);//get a.c
            recv_file(sockfd,myargv[1]);
        }
        else if(strcmp(myargv[0],"rm") == 0)
        {
            if(myargv[1] == NULL)
            {
                continue;
            }
            send(sockfd,sendbuff,strlen(sendbuff),0);
        }
        else if ( strcmp(myargv[0],"put") == 0 )
        {
		if ( myargv[1] == NULL )
		    {
		        continue;
		    }
		    send(sockfd,sendbuff,strlen(sendbuff),0);//get a.c
		    send_file(sockfd,myargv[1]);
        }
        else
        {
            send(sockfd,sendbuff,strlen(sendbuff),0);

            char readbuff[4096] = {0};
            recv(sockfd, readbuff,4095,0);
            if ( strncmp(readbuff,"ok#",3) != 0 )
            {
                printf("err");
                continue;
            }

            printf("%s\n",readbuff+3);

        }
    }

    close(sockfd);
}

void recv_file(int sockfd, char* name)
{


    int d_fd = open(name,O_WRONLY | O_LARGEFILE);
    if(d_fd != -1)
    {
        char d_buff[128] = {0};
        if(recv(sockfd,d_buff,127,0) <= 0)
        {
            return;
        }
        if(strncmp(d_buff,"ok#",3) != 0)
        {
            printf("Error:%s\n",d_buff+3);
            return;
        }
        long long d_size = 0;

        printf("d_file size :%s\n",d_buff+3);
        sscanf(d_buff+3,"%lld",&d_size);
        if(d_size == 0)
        {
            send(sockfd,"err_size",8,0);
            return;
        }
        printf("aaaaaaaaaaaaa、\n");
        long long fd_size = lseek64(d_fd,0,SEEK_END);
        if(d_size != fd_size)
        {
            printf("local file size:%lld\n",fd_size);
            char d_res_buff[128] = {0};
            sprintf(d_res_buff,"ok#size#%lld",fd_size);

            send(sockfd,d_res_buff,strlen(d_res_buff),0);
            char d_recvbuff[1024] = {0};

            long long d_num = 0;
            long long d_curr_size = fd_size;
            while((d_num = recv(sockfd,d_recvbuff,1024,0)) > 0)
            {
                write(d_fd,d_recvbuff,d_num);
                d_curr_size += d_num;
                float d_f = d_curr_size * 100.0 / d_size;
                printf("继续下载下载进度*:%.2f%%\r",d_f);
                fflush(stdout);
                if(d_curr_size >= d_size)
                {
                    break;
                }
            }
            printf("文件下载完成\n");
        }
        close(d_fd);
        return;
    }
    
    send(sockfd,"ok#",3,0);

    char buff[128] = {0};
    if ( recv(sockfd,buff,127,0) <= 0 )
    {
        return;
    }
    if ( strncmp(buff,"ok#",3) != 0 )//ok#345
    {
        printf("Error:%s\n",buff+3);
        return;
    }

    long long size = 0;
    printf("file size:%s\n",buff+3);
    sscanf(buff+3,"%d",&size);

    if( size == 0 )
    {
        send(sockfd,"err",3,0);
        return;
    }

    int fd = open(name,O_WRONLY|O_CREAT,0600);
    if ( fd == -1 )
    {
        send(sockfd,"err",3,0);
        return;
    }

    send(sockfd,"ok",2,0);

    char recvbuff[1024] = {0};

    long  num = 0;
    long curr_size = 0;

    while( ( num = recv(sockfd,recvbuff,1024,0)) > 0 )
    {
        write(fd,recvbuff,num);
        curr_size += num;

        float f = curr_size * 100.0 / size ;
        printf("下载:%.2f%%\r",f);
        fflush(stdout);

        if ( curr_size >= size )
        {
            break;
        }
    }

    printf("\n文件下载完成!\n");
    close(fd);
    return;
}
void send_file(int c, char * name)
{
    if ( name == NULL )
    {
        send(c,"err#no name",11,0);
        return;
    }
    char m_buff[128] = {0};
    sprintf(m_buff,"./my.sh %s",name);
    system(m_buff);
    int md_fd = open("md5.c",O_RDONLY | O_CREAT);
    if(md_fd == -1)
    {
        printf("md_fd err\n");
        return;
    }
    char md_res_buff[128] = {0};
    read(md_fd,md_res_buff,128);
    char * s = strtok(md_res_buff,"\n");
    char buff[128] = {0};
    printf("s:%s\n",s);

    close(md_fd);
    system("rm md5.c");

    sprintf(buff,"ok#%s",s);
    send(c,buff,strlen(buff),0);
    char p[128] = {0};
    if(recv(c,p,127,0) <= 0)
    {
        return;
    }
    if(strncmp(p,"#seamfile#",10) == 0)
    {
        printf("miaochuan\n");
        return;
    }

    int fd = open(name,O_RDONLY);
    if ( fd == -1 )
    {
        send(c,"err",3,0);
        return;
    }

    int size = lseek(fd,0,SEEK_END);
    lseek(fd,0,SEEK_SET);

    char res_buff[128] = {0};
    sprintf(res_buff,"ok#%d",size);

    send(c,res_buff,strlen(res_buff),0);

    char cli_status[64] = {0};
    if ( recv(c,cli_status,63,0) <= 0 )
    {
        close(fd);
        return;
    }

    if ( strncmp(cli_status,"ok",2) != 0 )
    {
        close(fd);
        return;
    }

    int num = 0;
    char sendbuff[1024] = {0};
    while( (num = read(fd,sendbuff,1024)) > 0 )
    {
        send(c,sendbuff,num,0);
    }

    close(fd);

    return;
}
int connect_to_ser()
{
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if ( sockfd == -1 )
    {
        return -1;
    }

    struct sockaddr_in saddr;
    memset(&saddr,0,sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);
    saddr.sin_addr.s_addr = inet_addr(IPSTR);

    int res = connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
    if ( res == -1 )
    {
        return -1;
    }

    return sockfd;
}
