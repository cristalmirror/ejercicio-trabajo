#include<stdio.h>
#include<stdlib.h>
#include"recon_cards.h"
#include"fun_socket.h"

//se define la informacion del servidor
#define _IP "192.162.1.55"
#define _PORT 8080

//condicion que determina la cantidad de digitos del numero de targeta
int condition(long int num){

      int cont=0;
      while (num>0) {

            num/=10;

            cont++;
            
      }
      
      return cont;
}

//funcion  que corrobora e introuce los datos
void data_int(float *mon,long int *num_ca,int *cod_card){

      printf("\nintrodusca el monto: ");
      scanf("%f", &*mon);

      //introduccion del numero de targeta
      const int tam=13,tam2=3;
      int x;
      
      do {//repite la introduccion del numero si fue erroneo 
             
            printf("\nintrodusca el numero de targta: ");
            scanf("%ld", &*num_ca);

            x=condition(*num_ca);

            check_card_number(*num_ca,x);
            
            if (tam>x){//condicion del digito
                  printf("numero de targeta invalidado, intente insrtarlo nuevamente\n");
            }
           
      } while (tam>x);

      
      do {//repite la introduccion del numero si fue erroneo 
             
            printf("\nintrodusca el codigo de targta: ");
            scanf("%i", &*cod_card);
            
            x=condition(*cod_card);
            if (tam2!=x){//condicion del digito
                  printf("numero de targeta invalidado, intente insrtarlo nuevamente\n");
            }
            
      } while (tam2!=x);

      
}

int main(int argc, char *argv[]){

      float m;
      long int n_c;
      int cod_c,_handle,sc_byte,t;
            
      //introducion de los datos
      data_int(&m,&n_c,&cod_c);

      //crea el socket
      _handle=socketCreate();

      //simula el tiempo de coneccion 
      t=rand()%6; 
      
      //conecta el sockt
      sc_byte=socketConnect(_handle,_IP,"data_save",t);
      
      
      return 0;
}


