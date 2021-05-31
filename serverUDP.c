#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)

 {
    int socket_desc;
    struct sockaddr_in server_addr, client_addr;
    char server_message[100], client_message[100];
    int client_struct_length = sizeof(client_addr);
    
    
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));
    
    // creeert socket
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    if(socket_desc < 0){
        printf("error met aanmaken socket\n");
        return -1;
    }
    
  
    // stelt poort en ip in:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // bindt de poort en ip
    if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("poort niet gevonden\n");
        return -1;
    }
    
		do
		{
			
			printf("wachten op bericht\n\n");
			// ontvangt bericht
			if (recvfrom(socket_desc, client_message, sizeof(client_message), 0,
			(struct sockaddr*)&client_addr, &client_struct_length) < 0){
			printf("niks ontvangen\n");
			return -1;
			}
			printf("bericht ontvangen van ip: %s en poort: %i\n",
			inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			printf("bericht van client: %s\n", client_message);
    
    
			// geeft een respons
			strcpy(server_message, client_message);
	
    
			if (sendto(socket_desc, server_message, strlen(server_message), 0,
			(struct sockaddr*)&client_addr, client_struct_length) < 0)
			{	 
			printf("kan niet verzenden\n");
			return -1;
			}
		}while(1);
    
	
	
    // sluit het socket
    close(socket_desc);
   
 }

