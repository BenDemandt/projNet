#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
int packets= 0;
int main(void)
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[100], client_message[100];
    int server_struct_length = sizeof(server_addr);
    
  
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));
    
    // creert een socket
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    if(socket_desc < 0){
        printf("error bij aanmaken socket\n");
        return -1;
    }
    printf("Socket gecreerd\n");
    
    //stelt poort en ip in
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(24042);
    server_addr.sin_addr.s_addr = inet_addr("192.168.2.99");
	
	do
	{
	
		// Get input from the user:
		printf("geef een bericht in: ");
		gets(client_message);
    
		// stuurt een bericht
		if(sendto(socket_desc, client_message, strlen(client_message), 0,
			(struct sockaddr*)&server_addr, server_struct_length) < 0){
			printf("kon geen bericht verzenden\n");
			return -1;
		}
    
		// ontvangt een respons van de server
		if(recvfrom(socket_desc, server_message, sizeof(server_message), 0,
			(struct sockaddr*)&server_addr, &server_struct_length) < 0){
			printf("error bij ontvangen bericht\n");
			return -1;
		}
    
		printf("server respons: %s\n", server_message);
		packets++;
		printf("aantal packets %d\n", packets);
	
    }while(1);
	
		 // sluit de socket
    close(socket_desc);

   
    
    return 0;
}