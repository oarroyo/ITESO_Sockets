//Client.c
//File Transfer

#include <stdio.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <sys/time.h>


long currentTimeMillis() ;
int main(int argc, char* argv[]) { 	//Main
	int udpSocket;
struct sockaddr_in udpServer, udpClient;	//Creamos la estructura para el cliente
socklen_t addrlen = sizeof(udpClient),len;
	int status;
	char buffer[255] = "";
	int i;
	int option;
	int fd;
	int contador=0;
	long start, end;
	char ip[17];
	u_short clientPort;
	char *tok;
	int fileSize;
	int totalReadBytes, readBytes;
	char fileBuffer[10240];
	int writeBytes;

//Se crea el socket para UDP, en caso de que no se pueda crear nos 
//imprime un mensaje de error.
	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(udpSocket == -1) {
		fprintf(stderr,"Can't create UDP Socket");
	return 1;
	}

	udpServer.sin_family = AF_INET;
	inet_pton(AF_INET,"127.0.0.1",&udpServer.sin_addr.s_addr); //Direccion local host
	udpServer.sin_port = htons(5000);			//Puerto :5000

	status = sendto(udpSocket,argv[1],strlen(argv[1]),0,(struct sockaddr*)&udpServer, sizeof(udpServer));
	bzero(buffer,255);
	status = recvfrom(udpSocket, buffer, 255, 0, (struct sockaddr*)&udpClient, &addrlen );

	inet_ntop(AF_INET,&(udpClient.sin_addr),ip,INET_ADDRSTRLEN);
	clientPort = ntohs(udpClient.sin_port);

	printf("Archivo: %s de [%s:%i]\n\r",buffer,ip,clientPort); //Se reciben los parametros para conectarnos con el server
	
	status = sendto(udpSocket,"OK",strlen("OK"),0,(struct sockaddr*)&udpServer, sizeof(udpServer)); //Manda un ok de que se recibio 													// el archivo completo
    printf("OK\n\r"); 
	totalReadBytes = 0;
	while(totalReadBytes < fileSize) {
		readBytes = recvfrom(udpSocket,fileBuffer,10240,0,(struct sockaddr*)&udpClient, &addrlen );
		
	while(writeBytes < readBytes) {
		writeBytes += write(fd,fileBuffer+writeBytes,readBytes-writeBytes);
	}
	
	totalReadBytes += writeBytes;
	}
	close(fd); 

	bzero(buffer,255);
	status = recvfrom(udpSocket, buffer, 255, 0, (struct sockaddr*)&udpClient, &addrlen );
	printf("Archivo recibido de [%s:%i] con el contenido %s",ip,clientPort,buffer); 
	printf("BYE\n\r");
	close(udpSocket); //Cerramos el socket de UDP

	return 0;
	} //Fin del main

   
