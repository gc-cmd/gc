#define _LARGEFILE64_SOURCE
#define _LARGEFILE_SOURCE
#define _FILE_OFFSET_BITS 64

#include "thread.h"
#include <fcntl.h>
#include<signal.h>
#define     ARGC    10
#define     READ_BUFF   4096



void recv_file(int sockfd, char* name)
{   
    if(name == NULL)
    {
        send(sockfd,"err_name",8,0);
        return;
    }
    char buf[128] = {0};

    if(recv(sockfd,buf,127,0) <= 0)
    {
        printf("recv err\n");
        return;
    }
    if(strncmp(buf,"ok#",3) != 0)
    {
        return;
    }
    printf("buf:%s\n",buf);
    char *s = buf;
    s += 3;
    printf("s：%s\n",s);
    int m_fd = open("md5.c",O_RDONLY,0600);

    char md_res_buff[1024] = {0};
    read(m_fd,md_res_buff,1024);
    char * ss = strtok(md_res_buff,"\n");
    while(ss != NULL )
    {
        if(strcmp(s,ss) == 0)
        {
            send(sockfd,"#seamfile#",10,0);
            printf("秒传\n");
            return;
        }
        ss = strtok(NULL,"\n");
       // printf("ss:%s\n",ss);
    }


/*
    int m_fd = open(name,O_RDONLY, 0600);
    printf("m_fd == -1");
    if(m_fd != -1)
    {
        //打开成功有文件；
        char md_buff[128] = {0};
        sprintf(md_buff,"./my.sh %s",name);
        system(md_buff);
        int md_fd = open("md5.c",O_RDONLY | O_LARGEFILE);
        if(md_fd == -1)
        {
            printf("err_md_fd\n");
            return;
        }
        char md_res_buff[128] = {0};
        read(md_fd,md_res_buff,127);
        char * s = strtok(md_res_buff," ");

        close(md_fd);

        char m_res_buff[128] = {0};
        sprintf(m_res_buff,"ok#size#%s",s);
        send(sockfd,m_res_buff,strlen(m_res_buff),0);

        char m_cli_status[128] = {0};
        if(recv(sockfd,m_cli_status,127,0) <= 0)
        {
            return;
        }
        if(strncmp(m_cli_status,"same#file",10) == 0)
        {
            send(sockfd,"ok#",3,0);
            close(m_fd);
            return;
        }
        close(m_fd);
        return;
    }
*/    
    send(sockfd,"ok#size#",8,0);

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

    int size = 0;
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

    int num = 0;
    int curr_size = 0;

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

    printf("\n文件完成下载!\n");
    close(fd);

    char md5[128] = {0};
    sprintf(md5,"./my.sh %s",name);
    system(md5);
    return;
}

void send_file(int c, char * name)
{
    if ( name == NULL )
    {
        send(c,"err#no name",11,0);
        return;
    }
    printf("dakaiqian\n");
    int fd = open(name,O_RDONLY |O_LARGEFILE | O_CREAT);

    if ( fd == -1 )
    {
        printf("fd err\n");
        send(c,"err",3,0);
        return;
    }
    printf("jisuansize\n");
    int size = lseek(fd,0,SEEK_END);
    lseek(fd,0,SEEK_SET);

    char res_buff[128] = {0};
    sprintf(res_buff,"ok#%d",size);
    //printf("fasong ok#size\n");
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
    if(strncmp(cli_status+3,"size#",4) == 0)
    {
        long long d_size = 0;
        sscanf(cli_status+8,"%lld",&d_size);

        if(d_size < 0)
        {
            send(c,"err_cli_size",12,0);
            return;
        }

        lseek64(fd,d_size,SEEK_SET);

        long long d_num = 0;
        char d_sendbuff[1024] = {0};
        while((d_num = read(fd,d_sendbuff,1024)) > 0)
        {
            send(c,d_sendbuff,d_num,0);
        }
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

void * work_thread(void * arg)
{
    int c = (int)arg;

    while( 1 )
    {
        char buff[256] = {0};
        
        int n = recv(c,buff,255,0);//ls, mv a.c b.c , rm a.c ,get a.c put, aa
        printf("buff = %s\n", buff);
        if ( n <= 0 )
        {
            printf("one client over\n");
            break;
        }

        int i = 0;
        char* myargv[ARGC] = {0};
        char * ptr = NULL;
        char * s = strtok_r(buff," ",&ptr);
        while( s != NULL )
        {
            myargv[i++] = s;
            s = strtok_r(NULL," ",&ptr);
        }

        char * cmd = myargv[0];//cmd 

        if ( cmd == NULL )
        {
            send(c,"err",3,0);
            continue;
        }

        if ( strcmp(cmd,"get") == 0 )
        {
            //下载
            send_file(c,myargv[1]);
        }
        else if(strcmp(cmd,"rm") == 0)
        {
            //fgets(myargv[1]);
            //remove(myargv[1]);
            if(remove(myargv[1]) == 0)
            {
                printf("%s has removed",myargv[1]);
            }
            else
            {
                perror("remove err");
            }
        }
        else if ( strcmp( cmd, "put") == 0 )
        {
      printf("myargv = %s\n", myargv[1]);
      //上传
	   recv_file(c,myargv[1]);
        }
        else
        {
            int pipefd[2];
            pipe(pipefd);

            pid_t pid = fork();
            if ( pid == -1 )
            {
                send(c,"err",3,0);
                continue;
            }

            if ( pid == 0 )
            {
                dup2(pipefd[1],1);
                dup2(pipefd[1],2);
                
                execvp(cmd,myargv);
                perror("cmd err");
                exit(0);
            }

            close(pipefd[1]);
            wait(NULL);
            char readbuff[READ_BUFF] = {"ok#"};
            read(pipefd[0],readbuff+3,READ_BUFF-4);

            send(c,readbuff,strlen(readbuff),0);
            close(pipefd[0]);
        }
    }

    close(c);
}

int thread_start(int c )
{
    pthread_t id;
    int res = pthread_create(&id,NULL,work_thread,(void*)c);
    if ( res != 0  )
    {
        return -1;
    }

    return 0;
}
