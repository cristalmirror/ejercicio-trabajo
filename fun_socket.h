/*
la coneccion y comunicacion del socket con el host fue simulada con archivos
*/

#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>

//crea el socket
int socketCreate(){
      /*toma los datos del archivo del sistema que contiene la informacion de la red local
        y la guarda en un registro*/
      struct hostent *helden=gethostbyname("/etc/hosts");
      /*en windows se usa:
        struct host *helden=gethostbyname("C:\WINNT\system32\drivers\etc\hosts");*/

      //realiza el retorno 
      if(helden->h_name!=NULL){
            
            return helden->h_name;
      }else{
            return -1;
      }
}
//conecta el socket
int socketConnect(int handle, const char *ip,unsigned char *data, unsigned short port){

      
      
      return 0;
            
}
//lee el socket
int socketRead(int handle, unsigned char *data,int maxTimeout){


}
//escribe el socket
int socketWrite(int handle,const unsigned char *data){

      

}
//cierra el socket
int socketClose(int handle){


}
