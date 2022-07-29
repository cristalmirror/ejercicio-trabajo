#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>

//defino la ip del server con la que busco conectarme
#define SERVER_ADDRESS "192.168.0.3"
#define PORT 8080

//defino los buffers de comunicacion
char buffer_tx[100];
char buffer_rx[100];

int main(int argc, char *argv[]){

      //creo un descritpor del archivo del cliente
      int socket_file_des,i=0,j;
      struct sockaddr_in serv_addr;
      char aux[3];
      
      //tiempo maximo de espera de la coneciion
      clock_t t=5;
      
      //creo un descritpor del archivo del cliente
      socket_file_des=socket(AF_INET,SOCK_STREAM,0);
      if(socket_file_des==-1){
            printf("error al realizar el socket\n");
            return-1;
      }

      //inicializamos el registro con los datos del servidor en 0
      memset(&serv_addr,0,sizeof(serv_addr));


      //cargamos los datos del servidor en el registro
      serv_addr.sin_family=AF_INET;
      serv_addr.sin_addr.s_addr=inet_addr(SERVER_ADDRESS);
      serv_addr.sin_port=htons(PORT);
      
      //establese la connecion entre el servidor y el clinte
      if(connect(socket_file_des,(struct sockaddr *)&serv_addr,sizeof(serv_addr))!=0){

            printf("ERROR DE COMUNICACION\n");
            return-1;
      }
     
      //envia los datos al host
      while (i<=3) {
           

            if(i==0){
                  printf("introdusca el monto (con dos decimales para los centabos):\n");
                  scanf("%s",buffer_tx);

            }else if(i==1){

                   printf("introdusca el numero de su targeta():\n");
                   scanf("%s",buffer_tx);
                   
            }else if(i==2){
                  
                  printf("introdusca el monto (no mas de 3 digitos):\n");
                  scanf("%s",buffer_tx);
                  
            }else {
                 close(socket_file_des); 
            }
            i++;
            //envia un mensaje al servidor
            write(socket_file_des,buffer_tx,sizeof(buffer_tx));
      }
      //resive mensajes desde el servidor
      read(socket_file_des,buffer_rx,sizeof(buffer_rx));
      printf("%s\n",buffer_rx );
      //se cierra el socket
      close(socket_file_des);
      
      
      
      return 0;
}


