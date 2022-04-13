#include <string.h>
#include "prision.h"
#define PERDONABLES "perdonables"
#define LIBERAR "liberar"
#define ACTUALIZAR "actualizar"
#define MOSTRAR_LIBERADOS "mostrar_liberados"
#define AYUDA "ayuda"

/*
* PRE:Recibirá los argumentos ingresados por consola por el usuario.
* POST:Chequea que todos los argumentos fueron ingresados correctamente, avisa en caso de que no sea asi. Si los argumentos se ingresaron
* correctamente, efectua el comando ingresado. El programa tambien cuenta con un comando 'ayuda' donde se muestran las prestaciones del programa. 
*/
int main(int argc, char* argv[]){
	int comando=0;
	if(argc==3 && strcmp(argv[1],PERDONABLES)==0)
		comando=generar_perdonables(argv[2]);
	else if(argc==5 && strcmp(argv[1],LIBERAR)==0 && strlen(argv[4])==1) //Argv[4] tiene que ser un char.
		comando=generar_liberados(argv[2],argv[3],argv[4][0]); 
	else if(argc==3 && strcmp(argv[1],ACTUALIZAR)==0)
		comando=actualizar_presos(argv[2]);
	else if(argc==3 && strcmp(argv[1],MOSTRAR_LIBERADOS)==0)
		comando=mostrar_liberados(argv[2]);
	else if(argc==2 && strcmp(argv[1],AYUDA)==0)
		mostrar_ayuda();
	else mensaje_error();
	if (comando==-1) //Las funciones devuelven -1 en caso de error.
		mensaje_error();
return 0;
}