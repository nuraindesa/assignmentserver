#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>
#include<sys/types.h>
#include<time.h>
#include<netinet/in.h>

int main()
{
    	char buf[100];
    	char dt[100];
	int k;
	char s[100];
   	socklen_t len;
	pid_t pid;
	time_t ticks;

    int sock_desc,temp_sock_desc;
    struct sockaddr_in server,client;
    memset(&server,0,sizeof(server));
    memset(&client,0,sizeof(client));

    sock_desc=socket(AF_INET,SOCK_STREAM,0);
    if(sock_desc==-1)
    {
        printf("Error in socket creation");
        exit(1);
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=7778;

    k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
    if(k==-1)
    {
        printf("Error in binding");
        exit(1);
    }
    k=listen(sock_desc,20);
    if(k==-1)
    {
        printf("Error in listening");
        exit(1);
    }
    len=sizeof(client);
    temp_sock_desc=accept(sock_desc,(struct sockaddr*)&client,&len);
    if(temp_sock_desc==-1)
    {
        printf("Error in temporary socket creation");
        exit(1);
    }
    
	time_t mytime = time(NULL);
	char * time_str = ctime(&mytime);
    	time_str[strlen(time_str)-1] = '\0';
	printf("Current Time : %s\n", time_str);
	k=send(temp_sock_desc,time_str,100,0);
	if (mytime >=0 && mytime <12)
	{
		strncpy(s,"good morning from server !\n",100);
		printf(s);
	}
	else if (mytime>=12 && mytime<18)
	{	
		
		strncpy(s,"Good Afternoon from server !\n",100);
		printf(s);
	}
	else if(mytime>=18)
	{
		strncpy(s,"Good Evening from server !\n",100);
		printf(s);
	}
	k=send(temp_sock_desc,s,100,0);
	k=recv(temp_sock_desc,dt,100,0);
	printf("Client Time : %s\n", dt);
	


	while (1)
	{
        k=recv(temp_sock_desc,buf,100,0);
        
	if(k==-1)
        {
            printf("Error in receiving");
            exit(1);
        }

	printf("\nMessage from client is : %s",buf);
	printf("\nEnter data to be send to client: ");



        fgets(buf,100,stdin);



        if(strncmp(buf,"end",3)==0)



            break;







        k=send(temp_sock_desc,buf,100,0);



        if(k==-1)



        {



            printf("Error in sending");



            exit(1);



        }

}



    close(temp_sock_desc);







    exit(0);



    return 0;



}

