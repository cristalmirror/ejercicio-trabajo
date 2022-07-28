#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct {
      char rangeLow[8 + 1];
      char rangeHigh[8 + 1];
      unsigned char len;
      int id;
} range_t;

typedef struct {
      char label[12 + 1];
      int id;
} card_t;

//crear los registros para realizar el reconocimineto de la targeta
range_t *range_data;
card_t *card_data;

//verifiador del numero de targeta
void check_card_number(long int da,int tam){
      int i=0,j,x,dig[tam],cont[2][8],aux_i,pos=0,pos2=0;
      long int aux=da;
      char array[tam],a,array_aux[12+1];

      //separa el numero en digitos
      while(aux>0){

            dig[i]=aux%10;

            aux=aux/10;

            i++;
            
      }

      //recorre la cadena de digitos y la pasa a caracteres
      for (j = i-1; j >=0; j--) {

            a=(char)48+dig[j];

            x=tam-j;
            
            array[x]=a;
            
      }
      
      //abre los archivos ranges.dat y cards.dat
      FILE *archive_ranges = fopen("ranges.dat", "r");
      FILE *archive_cards = fopen("cards.dat", "r");


      do{
      //inicializa en 0 un array de contadores
            for (i = 0; i < 8; ++i) {
                  cont[0][i]=0;
                  cont[1][i]=0;
            }
      
      
           
            //carga los valores en los registros 
            for (i = 9; i >= 1; --i) {//el primer byte es el id por lo tanto se lo saltea

                  //lee la parte baja del registro desde el final
                  fseek(archive_ranges,pos+i,SEEK_SET);
                  range_data->rangeLow[i]=fgetc(archive_ranges);

                  //carga la parte alta del registro desde el comienzo
                  fseek(archive_ranges,pos+8-i,SEEK_SET);
                  range_data->rangeHigh[8-i]=fgetc(archive_ranges);
                  
                  //compara la parte alta y baja de los registros en busca de diferencias              
                  j=memcmp(range_data->rangeLow,array,pos+(9-i));
                  x=memcmp(range_data->rangeHigh,array,pos+(9-i));
                  //acumula los cambios por byte
                  if(j!=0) cont[0][9-i]=1;
                  if(x!=0) cont[1][9-i]=1;
      
            }
            //acumula los cabios en una variable
            for (i = 0; i < 9; ++i) {
                  j=cont[0][i]+cont[0][i+1];
                  x=cont[1][i]+cont[1][i+1];
            }
            //detrmina que almenos uno de los registros no tenga cambios
            if((j==0)||(x==0)){
                  fseek(archive_ranges,pos,SEEK_SET);
                  
                  do {//recorre el archivo archive_card
                        for (j = 0; j < 13; ++j) {//recorre la una linea
                             fseek(archive_cards,pos2+j,SEEK_SET);

                             if(j=0){//tomo el id
                                   range_data->id=fgetc(archive_ranges);
                                   card_data->id=fgetc(archive_cards);
                             }
                             if(card_data->id==range_data->id){//comparo los id
                                   fseek(archive_cards,pos2,SEEK_SET);
                                   
                                   array_aux[j]=fgetc(archive_cards);

                                   printf("el nombre de la targta es: %s\n",array_aux);
                                         
                             }else {//se pone al final de la linea 
                                   fseek(archive_cards,pos2+13,SEEK_SET);
                                   aux_i=fgetc(archive_cards);
                                   if((aux_i==0)&&(card_data->id!=range_data->id)){
                                         printf("\nTARGETA NO SOPORTADA\n");
                                         exit(0);
                                   }
                                   
                             }
                                   
                                   
                             pos2=pos2+13;
                                   
                        }
                      
                  }while (aux_i==10);//llega al final de la linea y pasa a la siguiente
                             
            }else{//se pone al final de la linea 

                  fseek(archive_ranges,pos+16,SEEK_SET);
                  aux_i=fgetc(archive_ranges);
                  if((aux_i==0)&&((j!=0)&&(x!=0))){
                         printf("\nTARGETA NO SOPORTADA\n");
                         exit(0);
                        }                  

                        
            }

            pos=pos+16;
         
                  
      }while (aux_i==10);//llega al final de la linea y pasa a la siguiente

      FILE *fp_save = fopen("save", "a");

      

       //separa el numero en digitos
      while(aux>0){

            dig[i]=aux%10;

            aux=aux/10;

            i++;
            
      }

      //recorre la cadena de digitos y la pasa a caracteres
      for (j = i-1; j >=0; j--) {

            a=(char)48+dig[j];

            x=tam-j;
            
            array[x]=a;
            
      }

      
      
      
}
