#include<sys/socket.h>

#include<stdio.h>

#include <unistd.h>

#include <errno.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>


#include<string.h>

#include<netdb.h>

#include<stdlib.h>
void checkHostName(int hostname)

{

    if (hostname == -1)

    {

        perror("gethostname");

        exit(1);

    }

}

void checkHostEntry(struct hostent * hostentry)

{

    if (hostentry == NULL)

    {

        perror("gethostbyname");

        exit(1);

    }

}

 

void checkIPbuffer(char *IPbuffer)

{

    if (NULL == IPbuffer)

    {

        perror("inet_ntoa");

        exit(1);

    }

}



int main()

{

    char buf[100];
	 int k;
    socklen_t len;

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

    server.sin_port=6272;



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

char hostbuffer[256];

    char *IPbuffer;

    struct hostent *host_entry;

    int hostname;

    while(1)

    {
	k=send(temp_sock_desc,hostbuffer,100,0);
	k=send(temp_sock_desc,IPbuffer,100,0);

        k=recv(temp_sock_desc,buf,100,0);

        if(k==-1)

        {

            printf("Error in receiving");

            exit(1);

        }
	printf("\nMessage from client is : %s",buf);
	
	if(strncmp(buf,"ipaddress",9)==0)
	{
	hostname = gethostname(hostbuffer, sizeof(hostbuffer));
	checkHostName(hostname);
	host_entry = gethostbyname(hostbuffer);
	checkHostEntry(host_entry);
	IPbuffer = inet_ntoa(*((struct in_addr*) 
	host_entry->h_addr_list[0]));
	k=send(temp_sock_desc,hostbuffer,100,0);
	k=send(temp_sock_desc,IPbuffer,100,0);
	}

	else if (strncmp(buf,"ipaddress",9)!=0)
	{
	printf("\nMessage from client : %s ",buf);
	printf("\nEnter data to be send to client: ");
        fgets(buf,100,stdin);
	}

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

 

