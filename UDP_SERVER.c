// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //unistd.h - standard symbolic constants and types
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> //The <arpa/inet.h> header makes available the type in_port_t and the type in_addr_t as defined in the description of <netinet/in.h>.
#include <netinet/in.h>
	
#define PORT	 8080
#define MAXLINE 1024
	
// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;
		
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&servaddr, 0, sizeof(servaddr)); //memset() is used to fill a block of memory with a particular value.

	memset(&cliaddr, 0, sizeof(cliaddr));  //memset() is used to fill a block of memory with a particular value.

		
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4  ADDRESS FAMILY
	servaddr.sin_addr.s_addr = INADDR_ANY;  // INET ADDRESS OF ANY N/W IN FAMILY
	servaddr.sin_port = htons(PORT); //host to network norm
		
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )      
	{
		perror("bind failed");     //The perror() function displays the description of the error that corresponds to an error code stored in the system variable errno . 
			//errno is a system variable which holds the error code that describes the error condition. This error condition is produced by a call to a library function.

		exit(EXIT_FAILURE);
	}
		
	int len, n;
	
	len = sizeof(cliaddr); //len is value/result
	
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,         //eth socket vazhi ah recieve cheyandath
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
	buffer[n] = '\0';
	printf("Client : %s\n", buffer);
	sendto(sockfd, (const char *)hello, strlen(hello),  
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len); // mssg confirm chethu
	printf("Hello message sent.\n");
		
	return 0;
}
