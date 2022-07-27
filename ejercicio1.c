#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//se crean los registros que almacenan los datos en memoria
typedef struct data{

     int num;
      
}data_type;

//se crean los nodos con los registros
typedef struct list{
      
      data_type elemnt;
      struct list *sig;
}list_type;

//inicializa los nodos en valores nulos o 0
void init_data_list(list_type **node){

      *node=NULL;
      
}

//carga los dataos a la lista
void load_data_list(data_type *number){

      printf("introdusca un numero: "); scanf("%i",&number->num);

}

//devuelve un valor booleano si la condicion es verdadera


//carga los datos de la lista
void insert_data_list(list_type **node,data_type number){

      list_type *aux;
      //se crea el espacion en memoria para el nuevo nodo que contiene los datos
      list_type *nue=(list_type *) malloc(sizeof(list_type));

      //se cargan los datos 
      nue->elemnt=number;
      nue->sig=NULL;

      //se introduce los nodos al final de la lista
      if (*node==NULL) {

            *node=nue;
            
      }else {

            aux=*node;
            while (aux->sig!=NULL) {

                  aux=aux->sig;
            }
            aux->sig=nue;
      }     
      
}

//esta funcion carga los numeros de la lista en un archivo
void output_string_archive(list_type *node){
      int i=0,n_dig=0,x;
      list_type *aux;
      aux=node;
      char _archive[15];//nombre del archivo

      
      //se introduce el nombre del archivo
      printf("introdusca el nombre del archivo: "); scanf("%s", &_archive);

      //se crea el archivo
      FILE *archive= fopen(_archive, "a");

      

      //recorre la lista con los datos y los carga en el archivo
      while (aux->sig!=NULL) {

            //determina la cantidad de digitos del numero que se introduce 
            x=aux->elemnt.num;
            n_dig=0;
            while (x>0) {
                  n_dig++;
                  x/=10;
            }
           
            //inserta los ceros que faltan para que el formato sea correcto
            for (i = n_dig; i <10; ++i) {
                  fprintf(archive,"0");

                  
            }
           //inserta los numros al final de la cadena y realiza el salto de linea
            fprintf(archive,"%i",aux->elemnt.num);

            fprintf(archive,"\r\n");
                         
            aux=aux->sig;
            
      }
      //reporta si hubo un error al en el archivo
      if(ferror(archive)){
            printf("ocurrio un error al guardar el archivo\n");

      }else {
            printf("el archivo se guardo con exito\n"); 
      }
      
      fclose(archive);

      
      
}




int main(int argc, char *argv[]){
      
      list_type *l;
      data_type num;
      bool cond=0;

      //inicializador de la lista en valor nulo
      init_data_list(&l);

      //proceso de introducion de nuemros en la lista
      do{

            load_data_list(&num);
            insert_data_list(&l,num);
           
            if (num.num==0){
                  
                  cond=1;
                  
            }
            
      } while (cond==0);
      
      //introduce los datos de la lista en un archivo
      output_string_archive(l);

      
      return 0;
}
