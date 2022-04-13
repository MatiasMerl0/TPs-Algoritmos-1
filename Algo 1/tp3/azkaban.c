#include <string.h>
#include "prision.h"
#define PERDONABLES "perdonables"
#define LIBERAR "liberar"
#define ACTUALIZAR "actualizar"
#define MOSTRAR_LIBERADOS "mostrar_liberados"
#define AYUDA "ayuda"

int main(int argc, char* argv[]){
	int comando=0;
	if(argc==3 && strcmp(argv[1],PERDONABLES)==0)
		comando=generar_perdonables(argv[2]);
	else if(argc==5 && strcmp(argv[1],LIBERAR)==0 && strlen(argv[4])==1)
		comando=generar_liberados(argv[2],argv[3],argv[4][0]); 
	else if(argc==3 && strcmp(argv[1],ACTUALIZAR)==0)
		comando=actualizar_presos(argv[2]);
	else if(argc==3 && strcmp(argv[1],MOSTRAR_LIBERADOS)==0)
		comando=mostrar_liberados(argv[2]);
	else if(argc==2 && strcmp(argv[1],AYUDA)==0)
		mostrar_ayuda();
	else mensaje_error();
	if (comando==-1)
		mensaje_error();
return 0;
}