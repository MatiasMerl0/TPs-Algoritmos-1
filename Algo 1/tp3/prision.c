#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "prision.h"
#define MAX_NOMBRE 200
#define MAX_FECHA 7
#define MAX_NOMBRE_ARCHIVO 50
#define MAX_CONDUCTAS 4
#define ARCHIVO_IMPERIUS "imperius.dat"
#define ARCHIVO_CRUCIO "crucio.dat"
#define CONDUCTA_BUENA 'B'
#define CONDUCTA_REGULAR 'R'
#define CONDUCTA_MALA 'M'

size_t leer_binario(FILE* archivo,preso_t* preso){
	size_t leidos=fread(preso,sizeof(preso_t),1,archivo);
	return leidos;
}
int leer_texto(FILE* archivo,preso_t* preso){
	int leidos=fscanf(archivo,"%[^;];%i;%c;%i;%i;%[^;];%i;\n",preso->nombre,&(preso->edad),&(preso->conducta),&(preso->pabellon),&(preso->celda),preso->fecha,&(preso->maldicion_realizada));
	return leidos;
}
size_t escribir_binario(FILE* archivo,preso_t* preso){
	size_t escritos=fwrite(preso,sizeof(preso_t),1,archivo);
	return escritos;
}
int escribir_texto(FILE* archivo,preso_t* preso){
	int escritos=fprintf(archivo,"%s;%i;%c;%i;%i;%s;%i;\n",preso->nombre,preso->edad,preso->conducta,preso->pabellon,preso->celda,preso->fecha,preso->maldicion_realizada);
	return escritos;
}
int escribir_nombre(FILE* archivo, preso_t* preso){
	int escritos=fprintf(archivo,"%s\n",preso->nombre);
	return escritos;
}

void generar_archivo_perdonables(FILE* crucio, FILE* imperius, FILE* perdonables){
	preso_t preso1,preso2;

	size_t leidos_crucio=leer_binario(crucio,&preso1);
	size_t leidos_imperius=leer_binario(imperius,&preso2);
	while(leidos_crucio && leidos_imperius){
		int comparacion=strcmp(preso1.nombre,preso2.nombre);
		if(comparacion>0){
			escribir_binario(perdonables,&preso2);
			leidos_imperius=leer_binario(imperius,&preso2);
		}
		else if(comparacion<0){
			escribir_binario(perdonables,&preso1);
			leidos_crucio=leer_binario(crucio,&preso1);
		}
		else{
			leidos_crucio=leer_binario(crucio,&preso1);
			leidos_imperius=leer_binario(imperius,&preso2);
		}
	}
	while(leidos_imperius){
		escribir_binario(perdonables,&preso2);
		leidos_imperius=leer_binario(imperius,&preso2);
	}
	while(leidos_crucio){
		escribir_binario(perdonables,&preso1);
		leidos_crucio=leer_binario(crucio,&preso1);
	}
}

int generar_perdonables(char nombre_archivo[MAX_NOMBRE_ARCHIVO]){
	FILE* crucio=fopen(ARCHIVO_CRUCIO,"r");
	if(!crucio){
		printf("Error al abrir %s.\n",ARCHIVO_CRUCIO);
		return -1;
	}

	FILE* imperius=fopen(ARCHIVO_IMPERIUS,"r");
	if(!imperius){
		printf("Error al abrir %s.\n",ARCHIVO_IMPERIUS);
		fclose(crucio);
		return -1;
	}

	FILE* perdonables=fopen(nombre_archivo,"w");
	if(!perdonables){
		printf("Error al abrir %s.\n",nombre_archivo);
		fclose(imperius);
		fclose(crucio);
		return -1;
	}

	generar_archivo_perdonables(crucio,imperius,perdonables);

	fclose(perdonables);
	fclose(imperius);
	fclose(crucio);
	return 0;
}

bool formato_fecha_valido(char fecha[MAX_FECHA]){
	if(strlen(fecha)==6)
		return true;
	else return false;
}
void crear_nombre_archivo(char fecha[MAX_FECHA],char nuevo_nombre[MAX_NOMBRE_ARCHIVO]){
	char string1[MAX_NOMBRE_ARCHIVO]="liberados_";
	char string2[MAX_NOMBRE_ARCHIVO]=".txt";
	strcat(string1,fecha);
	strcat(string1,string2);
	strcpy(nuevo_nombre,string1);
}

bool es_conducta_perdonable(char conducta_preso,char conducta_ingresada){
	char conducta[MAX_CONDUCTAS]={CONDUCTA_MALA,CONDUCTA_REGULAR,CONDUCTA_BUENA,'\0'};
	int valor_conducta_preso,valor_conducta_ingresada;
	for(int i=0;i<MAX_CONDUCTAS;i++){   //Me armé un string que ordena las conductas para otorgarles valores numericos.
		if(conducta[i]==conducta_preso)
			valor_conducta_preso=i;
		if(conducta[i]==conducta_ingresada)
			valor_conducta_ingresada=i;
	}
	if(valor_conducta_ingresada<=valor_conducta_preso)
		return true;
	else return false;
}

void generar_archivo_liberados(FILE* perdonables,FILE* liberados, char fecha[MAX_FECHA],char conducta_ingresada){
	preso_t preso;

	size_t leidos=leer_binario(perdonables,&preso);
	while(leidos){
		if((strcmp(preso.fecha,fecha)==0) && es_conducta_perdonable(preso.conducta,conducta_ingresadaar))
			escribir_nombre(liberados,&preso);
		leidos=leer_binario(perdonables,&preso);
	}
}

int generar_liberados(char nombre_archivo[MAX_NOMBRE_ARCHIVO], char fecha[MAX_FECHA],char conducta){
	char nombre_liberados[MAX_NOMBRE_ARCHIVO];
	crear_nombre_archivo(fecha,nombre_liberados); 
	if(!formato_fecha_valido(fecha))
		return -1;

	FILE* perdonables=fopen(nombre_archivo,"r");
	if(!perdonables){
		printf("Error al abrir %s.\n",nombre_archivo);
		return -1;
	}

	FILE* liberados=fopen(nombre_liberados,"r");
	if(!liberados){
		liberados=fopen(nombre_liberados,"w"); //chequeo si existe el archivo intentando leer, si devuelve NULL creo el archivo.
		if(!liberados){
			printf("Error al abrir %s.\n",nombre_liberados);
			fclose(perdonables);
			return -1;
		}
	}
	else{
		fclose(liberados); //Si ya existe el archivo no lo puedo reescribir asi que lo cierro sin hacer nada.
		printf("El archivo ya existe.\n");
		return -1;
	}
		
	generar_archivo_liberados(perdonables,liberados,fecha,conducta);
	
	fclose(perdonables);
	fclose(liberados);
	return 0;
}

void actualizar_archivo(FILE* archivo,FILE* archivo_actualizado,FILE* liberados){
	preso_t preso1,preso2;

	size_t leidos_archivo=leer_binario(archivo,&preso1);
	int leidos_liberados=leer_texto(liberados,&preso2);
	while(leidos_archivo && leidos_liberados==7){
		int comparacion=strcmp(preso1.nombre,preso2.nombre);
		if(comparacion>0){
			escribir_binario(archivo_actualizado,&preso1);
			leidos_archivo=leer_binario(archivo,&preso1);
		}
		else if(comparacion<0)
			leidos_liberados=leer_texto(liberados,&preso2);
		else{
			leidos_liberados=leer_texto(liberados,&preso2);
			leidos_archivo=leer_binario(archivo,&preso1);
		}
	}
	while(leidos_archivo){
		escribir_binario(archivo_actualizado,&preso1);
		leidos_archivo=leer_binario(archivo,&preso1);
	}
}

int actualizar_presos(char fecha[MAX_FECHA]){
	char nombre_archivo[MAX_NOMBRE_ARCHIVO];
	crear_nombre_archivo(fecha,nombre_archivo);
	if(!formato_fecha_valido(fecha))
		return -1;

	//Apertura de los archivos
	FILE* crucio=fopen(ARCHIVO_CRUCIO,"r");
	if(!crucio){
		printf("Error al abrir %s.\n",ARCHIVO_CRUCIO);
		return -1;
	}

	FILE* imperius=fopen(ARCHIVO_IMPERIUS,"r");
	if(!imperius){
		printf("Error al abrir %s.\n",ARCHIVO_IMPERIUS);
		fclose(crucio);
		return -1;
	}

	FILE* liberados=fopen(nombre_archivo,"r");
	if(!liberados){
		printf("Error al abrir %s.(puede que no exista)\n",nombre_archivo);
		fclose(crucio);
		fclose(imperius);
		return -1;
	}

	FILE* imperius_actualizado=fopen("imperius2.dat","w");
	if(!imperius_actualizado){
		printf("Error al intentar actualizar los archivos.\n");
		fclose(crucio);
		fclose(imperius);
		fclose(liberados);
		return -1;
	}

	FILE* crucio_actualizado=fopen("crucio2.dat","w");
	if(!crucio_actualizado){
		printf("Error al intentar actualizar los archivos.\n");
		fclose(crucio);
		fclose(imperius);
		fclose(liberados);
		fclose(imperius_actualizado);
		return -1;
	}
	//operaciones con los archivos
	actualizar_archivo(crucio,crucio_actualizado,liberados);
	actualizar_archivo(imperius,imperius_actualizado,liberados);
	//cierre de archivos
	fclose(crucio); 
	fclose(imperius);
	fclose(liberados);
	fclose(crucio_actualizado);
	fclose(imperius_actualizado);
	//Operaciones post-cierre
	remove(ARCHIVO_CRUCIO);  
	remove(ARCHIVO_IMPERIUS);
	rename("imperius2.dat",ARCHIVO_IMPERIUS);
	rename("crucio2.dat",ARCHIVO_CRUCIO);
	return 0;
}

void imprimir_liberados(FILE* liberados){
	preso_t preso;
	int leidos=leer_texto(liberados,&preso);
	printf("Los presos liberados en el mes son:\n");
	while(leidos==7){
		printf("%s\n",preso.nombre);
		leidos=leer_texto(liberados,&preso);
	}
}
int mostrar_liberados(char fecha[MAX_FECHA]){
	char nombre_archivo[MAX_NOMBRE_ARCHIVO];
	crear_nombre_archivo(fecha,nombre_archivo);
	if(!formato_fecha_valido(fecha))
		return -1;

	FILE* liberados=fopen(nombre_archivo,"r");
	if(!liberados){
		printf("Error al abrir el archivo %s. (puede que no exista)\n",nombre_archivo);
		return -1;
	}

	imprimir_liberados(liberados);

	fclose(liberados);
	return 0;
}

void mostrar_ayuda(){
	printf("El programa cuenta con los siguientes comandos para manejar a los presos:\n");
	printf("\nComando 'perdonables':Generará un archivo binario con los presos que pueden ser perdonados. El usuario ingresa un unico argumento: el nombre del archivo binario.\n");
	printf("\nComando 'liberar':Generará un archivo de texto con los presos liberados. El usuario ingresa 3 argumentos: el nombre del archivo de presos perdonables previamente creado, la fecha de liberación de los presos (en formato aaaamm), y la conducta requerida para liberar (B:buena R:regular M:mala)\n");
	printf("\nComando 'actualizar':Actualizara los archivos crucio.dat e imperius.dat eliminando a los presos que hayan sido liberados. El usuario ingresa un argumento: la fecha del archivo de liberados.\n");
	printf("\nComando 'mostrar_liberados':Mostrará por pantalla los presos liberados en una fecha. El usuario ingresa un argumento: la fecha (formato aaaamm).\n");
	printf("\nINGRESAR INCORRECTAMENTE EL NOMBRE DE LOS COMANDOS Y/O LA CANTIDAD DE ARGUMENTOS HARÁ QUE EL PROGRAMA FALLE.\n");
	printf("\nPara volver a visualizar esta ayuda, siempre se puede usar el comando 'ayuda'.\n");
}

void mensaje_error(){
	printf("No se pudo ejecutar el comando. Por favor chequear que los argumentos son ingresados correctamente con el formato pedido.\n");
	mostrar_ayuda();
}