/*este programa emula el host del servicio, se require que la IP del dispositivo host sea
estatica y avilitar el puerto 8080 para que el servidor este en escucha,ADEMAS ESTE CODIGO TRABAJA POR
PROTOCOLO TCP*/
#include <unistd.h>  

/* sockets */
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>

//cadenas y errores
#include <errno.h>
#include <stdio.h> 
#include <string.h>


//tamanio del buffer, ip, puerrto y maximo numero de clientes conectados
#define SERVER_PORT 8080
#define SERVER_HOST_IP "192.168.0.3"
#define BUFFER_SIZE 100
#define CLIE_CONECT 6

typedef struct {
      char rangeLow[8+1];
      char rangeHigh[8+1];
      unsigned char len;
      int id;
}range_t;

char buffer_tx[BUFFER_SIZE]; //buffer emisor
char buffer_rx[BUFFER_SIZE];  //buffer reseptor

//cadenas auxiliares para hacer operaciones
char cad_mont[12];
char cad_num_card[16];
char cad_seg_code[3];

typedef struct{

      char label[12+1];
      int id;
      
}card_t;

//realiza las operaciones de la transaccion
int operation1(int i){
     int cont2=0;
      //salva los datos o devuelve un error si algo no funciona bien
      if(i==0){
	    if(13>strlen(buffer_rx)){
		  strcat(cad_mont,buffer_rx);
		  return 0;
	    }else {
		  strcat(buffer_tx,"ERROR su monto exede el rango de la transaccion");
		  return 1;
	    }
	    
      }else if(i==1){

	    if((16>strlen(buffer_rx))&&(13<strlen(buffer_rx))){
		  strcat(cad_num_card,buffer_rx);
		  return 0;
	    }else {
		  strcat(buffer_tx,"ERROR su monto exede el rango de la transaccion");
		  return 1;
	    }

      }else if((i==2)){
	    if(4>strlen(buffer_rx)){
		  strcat(cad_seg_code,buffer_rx);
		  return 0;
	    }else {
		  strcat(buffer_tx,"ERROR su monto exede el rango de la transaccion");
		  return 1;
	    }

      }
      

}

//realiza las operaciones para los archivos
int operacion2(){

      range_t *range;
      card_t *cards;
      int pos=0,i,j,a,pos2=0,ret;//posicion en el arechivo
      char aux[17];
      //se habre los archivos ranges y cards
      FILE *arc_range = fopen("ranges.dat", "rb");
      FILE *arc_cards = fopen("cards.dat", "rb");

      //va almacenando los datos en los registros
     for (i = 0; i < 3; ++i) {
	   for (j=0; j <20; ++j) {
		 fseek(arc_range,pos+j,SEEK_SET);
		 if(j<9){
		       range->rangeHigh[j]=fgetc(arc_range);
		     
		 }else if ((j>9)&&(j<=17)) {
		       
		       range->rangeLow[j]=fgetc(arc_range);
		 }else if(j==19){
		       range->id=fgetc(arc_range);
		 }		 
	 
	   }
	   
	   //se unifican los registros
	   strcat(aux,range->rangeHigh);
	   strcat(aux,range->rangeLow);

	   //deteermina si la targeta pertenece al sistema
	   if(strcmp(aux,cad_num_card)==0){
		 //buscando los nombres de la targeta
		 for (i = 0; i < 3; ++i) {
		       for (j=0; j <14; ++j) {
			     fseek(arc_cards,pos2+j,SEEK_SET);
			     if(j<1){
				   cards->id=fgetc(arc_cards);
				   
			     }else if ((j>1)&&(j<14)) {
		       
				   cards->label[j]=fgetc(arc_cards);
			     }

		       }
		       pos2=pos2+14;
		       //si los id son compatibles carga los datos en el buffer de salida
		       if(cards->id==range->id){

			     //envia el nombre de la targeta
			     strcat(buffer_tx,"\nnombre de la targeta: ");
			     strcat(buffer_tx,cards->label);
			     
			     for (a = 0; a <=100; ++a) {
				   buffer_tx[a]=0;
			     }	     
			     ret=2;
			     i=3;
		       }else if(i==2){
			     strcat(buffer_tx,"TARGETA NO SOPORTADA");
			     i=3;
		       }
		 }
		 
		 
	   }else if(i==2){//debuelver error si los registros no encuentran coinsidencia
		 strcat(buffer_tx,"TARGETA NO SOPORTADA");
		 i=3;
	   }
	   pos=pos+20;
     }

           

     //cierra los archivos
     fclose(arc_range);
     fclose(arc_cards);
     return ret;
}

//aprobacion de la operacion
int operation3(){
      char cond_res[2];

      //la entidad financiera deve aprobar la operacion desde el aceso al servidor
      printf("introdusca la aprobacion de la operacion\n"); scanf("%s",cond_res);

      if(cond_res=="00"){
	    strcat(buffer_tx,"transaccion: APROBADA");
	    return 3;    

      }else {
	    strcat(buffer_tx,"transaccion: RECHAZADA");
	    return 0;
      }

          

}

//devuelve el mensaje final
void operation4(){
      char aux[100];
      int di,cond=12;
      
      di=strlen(cad_mont);

      cond=cond-di:
      while (cond!=0) {

	    
	    
	    cond--; 
      }

      strcat();
      

}

int main(int argc, char *argv[]){

      //descriptor de archivos que escucha socket y de conenccion establecida
      int socket_file_des,connec_file_des,i=0,op;
      //tamanio de ip del cliente
      unsigned int len;

      //definen el tipo ip para el servidor y el cliente
      struct sockaddr_in serv_addr,client;

      int len_rx,lex_tx=0;
      

      //se crea el  socket 
      socket_file_des=socket(AF_INET,SOCK_STREAM,0);
      if (socket_file_des==-1) {
            fprintf(stderr, "se produjo un error en el servidor: %d: %s ",errno ,strerror(errno));
            return -1;
      }else {

            printf("el socket fue cargado con exito\n");
      }

      //limpia la estructura de tipo ip del servidor de cualquier valor vasura
      memset(&serv_addr,0,sizeof(serv_addr));

      //carga las direciones ip, el tipo de coneccion y los puertos
      serv_addr.sin_family=AF_INET;
      serv_addr.sin_addr.s_addr=inet_addr(SERVER_HOST_IP);
      serv_addr.sin_port=htons(SERVER_PORT);
      
      //asignamos la direccion ip y un purto al socket
      if((bind(socket_file_des,(struct sockaddr *)&serv_addr,sizeof(serv_addr)))!=0){

            fprintf(stderr, "se produjo un error en el servidor: %d: %s ",errno ,strerror(errno));
            return -1;
            
      }else {
            printf("las asignacions al socket se hiciron correctamente\n");
      }

      //permite que el servidor entre en escucha de los clientes
      if(listen(socket_file_des,CLIE_CONECT)!=0){

            fprintf(stderr, "se produjo un error en el servidor: %d: %s ",errno ,strerror(errno));
            return -1;            
      }else {
            
            printf("el servidor se en espera de los clientes\n");
            
      }
      //se carga el tamanio de la ip del cliente en el sistema
      len=sizeof(client);

      //accepta los clientes que se van conectando al sistema
      while(1){
            connec_file_des=accept(socket_file_des,(struct sockaddr *)&client,&len);
            if (connec_file_des<0) {

                  fprintf(stderr, "se produjo un error en el servidor: %d: %s ",errno ,strerror(errno));
                  return -1;

            }else {

                  while (1) {//lee los datos que el cliente le envia al sistema

                        //leer los datos del buffer de entrada 
                        len_rx=read(connec_file_des,buffer_rx,sizeof(buffer_rx));
			printf("el cliente: %s\n",buffer_rx);
		        

			//comprueba los datos que ingreso el cliente
			op=operation1(i);

			i++;//determina la operacion que se hace segun el dato entrante
			
			if((i==3)&&(op==0)){
			     op=operacion2();
			}else if(op==2) {
			      op=operation3();
			}else {
			      operation4();
			}
			
                        if(len_rx==-1){ //si se produce un error devuelve un mensaje

                              fprintf(stderr, "se produjo un error en el servidor: %d: %s ",errno ,strerror(errno));
                              return -1;

                        }else if(len_rx==0){

                              printf("se cerro el socket del cliente");
                              close(connec_file_des);
			      break;//aniado un breack para finalizar el bucle cuando se cierra el descriptor del 
                              
                        }else {
                              write(connec_file_des,buffer_tx,strlen(buffer_tx));
                             
                        }
                  }
            }
                  
      }
}
      




