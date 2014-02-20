/*
  Oswaldo Daniel Arroyo Vasquez rt689444
  Programación de Sockets
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "serverclient.h"

int main(int args, char *argv[]) {

	u_int port;
	int server1;
	int client1;
	int localerror;
	struct sockaddr_in *server_addr;
	struct sockaddr_in cliente_addr;
	socklen_t clienteLen;	
	int status;
	char *cadena;

	server_addr = malloc(sizeof(*server_addr));

	//Validamos los Arguemntos
	if(args < 3) {
		fprintf(stderr,"Error: Missing Arguments\n");
		fprintf(stderr,"\tUSE: %s [s/c] [PORT] [ADDR]  \n",argv[0]);
		fprintf(stderr,"\tUSE: s for Server \n");
		fprintf(stderr,"\tUSE: c for client \n");
		fprintf(stderr,"\tUSE: [ADDR] only for client \n");
		return 1;
	}

	port = atoi(argv[2]);
	if(port < 1 || port > 65535) {
		fprintf(stderr,"Port %i out of range (1-65535)\n",port);
		return 1;
	}

	//Llamamos a las funciones que crean el servidor/cliente 
	if (strcmp(argv[1],"s")==0){
		//Llamamos a la funcion que crea al servidor
		server1 = start_server(args,argv,server_addr);

		//Esperamos una Conexión
		while(1) {
		bzero(&cliente_addr,sizeof(cliente_addr));
		client1 = accept(server1,(struct sockaddr *)&cliente_addr,&clienteLen);

			if(client1 == -1) {
				localerror = errno;
				fprintf(stderr,"Error acepting conection %s\n",strerror(localerror));
				close(server1);
				return 1;
			}

			//Inicia el protocolo...
			//cadena = (char *) calloc(1,10);
			cadena = "Alo!!!\r\n";
			status=write(client1,cadena,strlen(cadena));
			//free(cadena);
			close(client1);
		}	

		return 0;
	}

	else if (strcmp(argv[1],"c")==0){
		//Llamamos a la funcion que crea al cliente
		server1 = start_client(args,argv,server_addr);
		cadena = (char *) calloc(1,30);
		status = read(server1,cadena,30);
		printf("Recived: %s\n",cadena);

		free(cadena);
		close(server1);
		return 0;
	}

	else {
		fprintf(stderr,"\tSecond argument must be: [s/c] \n");	
		return 1;
	}

	return 0;
}