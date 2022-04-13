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

/*
*PRE:Recibe dos punteros (FILE* y preso_t*) correctamente abiertos.
*POST:Aplica la funcion fread y devuelve la cantidad de elementos leidos.
*/
size_t leer_binario(FILE* archivo,preso_t* preso){
	size_t leidos=fread(preso,sizeof(preso_t),1,archivo);
	return leidos;
}

/*
*PRE:Recibe dos punteros (FILE* y preso_t*) correctamente abiertos.
*POST:Aplica la funcion fscanf y devuelve la cantidad de elementos leidos.
*/
int leer_texto(FILE* archivo,preso_t* preso){
	int leidos=fscanf(archivo,"%[^;];%i;%c;%i;%i;%[^;];%i;\n",preso->nombre,&(preso->edad),&(preso->conducta),&(preso->pabellon),&(preso->celda),preso->fecha,&(preso->maldicion_realizada));
	return leidos;
}

/*
*PRE:Recibe dos punteros (FILE* y preso_t*) correctamente abiertos.
*POST:Aplica la funcion fwrite y devuelve la cantidad de elementos escritos.
*/
size_t escribir_binario(FILE* archivo,preso_t* preso){
	size_t escritos=fwrite(preso,sizeof(preso_t),1,archivo);
	return escritos;
}

/*
*PRE:Recibe dos punteros (FILE* y preso_t*) correctamente abiertos.
*POST:Aplica la funcion fprintf y devuelve la cantidad de elementos escritos.
*/
int escribir_texto(FILE* archivo,preso_t* preso){
	int escritos=fprintf(archivo,"%s;%i;%c;%i;%i;%s;%i;\n",preso->nombre,preso->edad,preso->conducta,preso->pabellon,preso->celda,preso->fecha,preso->maldicion_realizada);
	return escritos;
}

/*
*PRE:Recibe dos punteros (FILE* y preso_t*) correctamente abiertos.
*POST:Aplica la funcion fprintf y devuelve la cantidad de elementos escritos. Es especifica para el campo nombre del preso.
*/
int escribir_nombre(FILE* archivo, preso_t* preso){
	int escritos=fprintf(archivo,"%s\n",preso->nombre);
	return escritos;
}

/*
*PRE:Recibe dos punteros (FILE* y preso_t*) correctamente abiertos.
*POST:Aplica la funcion fscanf y devuelve la cantidad de elementos leidos. Es especifica para el campo nombre del preso.
*/
int leer_nombres(FILE* archivo, preso_t* preso){
	int leidos=fscanf(archivo,"%[^\n]\n",preso->nombre);
	return leidos;
}

/*
*PRE:Recibe 3 punteros (FILE*) correctamente abiertos.
*POST:Hace la diferencia simetrica entre los dos archivos crucio e imperius y los escribe ordenadamente en el archivo perdonables.
*/
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

//Descripcion en archivo prision.h
int generar_perdonables(char nombre_archivo[MAX_NOMBRE_ARCHIVO]){
	FILE* crucio=fopen(ARCHIVO_CRUCIO,"r");
	if(!crucio){
		printf("Error al abrir %s.\n",ARCHIVO_CRUCIO);
		return -1;
	}
	//Apertura archivos
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
	//Operacion archivos
	generar_archivo_perdonables(crucio,imperius,perdonables);
	//Cierre archivos
	fclose(perdonables);
	fclose(imperius);
	fclose(crucio);
	return 0;
}

/*
*PRE:Recibe una conducta (char).
*POST:Chequeará que el caracter ingresado corresponda a alguna de las conductas establecidas. Devuelve true en caso de que lo sea.
*/
bool es_caracter_valido(char conducta){
	return(conducta==CONDUCTA_BUENA || conducta==CONDUCTA_REGULAR || conducta==CONDUCTA_MALA);
}

/*
*PRE:Recibe la fecha ingresada (str formato aaaamm).
*POST:Chequeará que el string tenga 6 caracteres y devuelve true en caso de que sea asi.
*/
bool formato_fecha_valido(char fecha[MAX_FECHA]){
	if(strlen(fecha)==6)
		return true;
	else return false;
}

/*
*PRE:Recibe la fecha ingresada (str) y el string donde se copiará el nombre del archivo.
*POST:Formará el nombre del archivo a crear con el formato liberados_aaaamm.txt y lo copiará en el string recibido.
*/
void crear_nombre_archivo(char fecha[MAX_FECHA],char nuevo_nombre[MAX_NOMBRE_ARCHIVO]){
	char string1[MAX_NOMBRE_ARCHIVO]="liberados_";
	char string2[MAX_NOMBRE_ARCHIVO]=".txt";
	strcat(string1,fecha);
	strcat(string1,string2);
	strcpy(nuevo_nombre,string1);
}

/*
*PRE:Recibe la conducta del preso (char) y la conducta ingresada por el usuario (char).
*POST:Chequea si el preso tiene la conducta necesaria para ser liberado, en ese caso devuelve true.
*/
bool es_conducta_perdonable(char conducta_preso,char conducta_ingresada){
	char conducta[MAX_CONDUCTAS]={CONDUCTA_MALA,CONDUCTA_REGULAR,CONDUCTA_BUENA,'\0'}; //Me armé un string que ordena las conductas para otorgarles valores numericos.
	int valor_conducta_preso,valor_conducta_ingresada;
	for(int i=0;i<MAX_CONDUCTAS;i++){   
		if(conducta[i]==conducta_preso)
			valor_conducta_preso=i;
		if(conducta[i]==conducta_ingresada)
			valor_conducta_ingresada=i;
	}
	if(valor_conducta_ingresada<=valor_conducta_preso)
		return true;
	else return false;
}

/*
*PRE:Recibe 2 punteros (FILE*) a un archivo binario perdonables y a un archivo de texto liberados, ambos abiertos correctamente. Tambien recibe una 
* fecha (str formato aaaamm) y una conducta (char) minima para ser liberados ingresada por el usuario.
*POST:Escribirá en el archivo de texto liberados a los presos que cumplan las condiciones de ser liberados.
*/
void generar_archivo_liberados(FILE* perdonables,FILE* liberados, char fecha[MAX_FECHA],char conducta_ingresada){
	preso_t preso;

	size_t leidos=leer_binario(perdonables,&preso);
	while(leidos){
		if((strcmp(preso.fecha,fecha)<=0) && es_conducta_perdonable(preso.conducta,conducta_ingresada))
			escribir_nombre(liberados,&preso);
		leidos=leer_binario(perdonables,&preso);
	}
}

//Descripcion en archivo prision.h
int generar_liberados(char nombre_archivo[MAX_NOMBRE_ARCHIVO], char fecha[MAX_FECHA],char conducta){
	char nombre_liberados[MAX_NOMBRE_ARCHIVO];
	crear_nombre_archivo(fecha,nombre_liberados); 
	if(!formato_fecha_valido(fecha) || !es_caracter_valido(conducta)) //chequeo si se ingresaron bien los datos.
		return -1;
	//Apertura archivos
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
	//operacion archivos
	generar_archivo_liberados(perdonables,liberados,fecha,conducta);
	//Cierre de archivos
	fclose(perdonables);
	fclose(liberados);
	return 0;
}

/*
*PRE:Recibe 5 punteros (FILE*). 2 binarios (crucio, imperius), 1 de texto (liberados) y 2 vacios. Todos abiertos correctamente.
*POST:Escribirá en los archivos crucio_actualizado e imperius_actualizado a los presos de crucio e imperius (respectivamente) que no esten en
* el archivo liberados.
*/
void actualizar_archivos(FILE* crucio,FILE* crucio_actualizado,FILE* imperius,FILE* imperius_actualizado,FILE* liberados){
	preso_t preso1,preso2,preso3;
	int comparacion1,comparacion2;

	size_t leidos_crucio=leer_binario(crucio,&preso1);
	size_t leidos_imperius=leer_binario(imperius,&preso2);
	int leidos_liberados=leer_nombres(liberados,&preso3);
	while(leidos_crucio && leidos_imperius && leidos_liberados==1){
		comparacion1=strcmp(preso1.nombre,preso3.nombre);
		comparacion2=strcmp(preso2.nombre,preso3.nombre);
		if(comparacion1<0){
			escribir_binario(crucio_actualizado,&preso1);
			leidos_crucio=leer_binario(crucio,&preso1);
		}
		else if(comparacion1==0){
			leidos_crucio=leer_binario(crucio,&preso1);
			leidos_liberados=leer_nombres(liberados,&preso3);
		}
		else if(comparacion2<0){
			escribir_binario(imperius_actualizado,&preso2);
			leidos_imperius=leer_binario(imperius,&preso2);
		}	
		else if(comparacion2==0){
			leidos_imperius=leer_binario(imperius,&preso2);
			leidos_liberados=leer_nombres(liberados,&preso3);
		}
		else leidos_liberados=leer_nombres(liberados,&preso3);
	}
	while(leidos_crucio && leidos_liberados==1){
		comparacion1=strcmp(preso1.nombre,preso3.nombre);
		if(comparacion1<0){
			escribir_binario(crucio_actualizado,&preso1);
			leidos_crucio=leer_binario(crucio,&preso1);
		}
		else if(comparacion1==0){
			leidos_crucio=leer_binario(crucio,&preso1);
			leidos_liberados=leer_nombres(liberados,&preso3);
		}
		else leidos_liberados=leer_nombres(liberados,&preso3);
	}
	while(leidos_imperius && leidos_liberados==1){
		comparacion2=strcmp(preso2.nombre,preso3.nombre);
		if(comparacion2<0){
			escribir_binario(imperius_actualizado,&preso2);
			leidos_imperius=leer_binario(imperius,&preso2);
		}
		else if(comparacion2==0){
			leidos_imperius=leer_binario(imperius,&preso2);
			leidos_liberados=leer_nombres(liberados,&preso3);
		}
		else leidos_liberados=leer_nombres(liberados,&preso3);
	}
	while(leidos_crucio){
		escribir_binario(crucio_actualizado,&preso1);
		leidos_crucio=leer_binario(crucio,&preso1);
	}
	while(leidos_imperius){
		escribir_binario(imperius_actualizado,&preso2);
		leidos_imperius=leer_binario(imperius,&preso2);
	}
}

//Descripcion en archivo prision.h
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
	actualizar_archivos(crucio,crucio_actualizado,imperius,imperius_actualizado,liberados);
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

/*
*PRE:Recibe un puntero (FILE*) a un archivo de texto liberados, abierto correctamente.
*POST:Recorre el archivo e imprime los nombres que hay en él.
*/
void imprimir_liberados(FILE* liberados){
	preso_t preso;
	int leidos=leer_nombres(liberados,&preso);
	printf("Los presos liberados en el mes son:\n");
	while(leidos==1){
		printf("%s\n",preso.nombre);
		leidos=leer_nombres(liberados,&preso);
	}
}

//Descripcion en archivo prision.h
int mostrar_liberados(char fecha[MAX_FECHA]){
	char nombre_archivo[MAX_NOMBRE_ARCHIVO];
	crear_nombre_archivo(fecha,nombre_archivo);
	if(!formato_fecha_valido(fecha))
		return -1;
	//Apertura archivos
	FILE* liberados=fopen(nombre_archivo,"r");
	if(!liberados){
		printf("Error al abrir el archivo %s. (puede que no exista)\n",nombre_archivo);
		return -1;
	}
	//Operacion
	imprimir_liberados(liberados);
	//Cierre
	fclose(liberados);
	return 0;
}

//Descripcion en archivo prision.h
void mostrar_ayuda(){
	printf("El programa cuenta con los siguientes comandos para manejar a los presos:\n");
	printf("Comando 'perdonables':Generará un archivo binario con los presos que pueden ser perdonados. El usuario ingresa un unico argumento: el nombre del archivo binario.\n");
	printf("Comando 'liberar':Generará un archivo de texto con los presos liberados. El usuario ingresa 3 argumentos: el nombre del archivo de presos perdonables previamente creado, la fecha de liberación de los presos (en formato aaaamm), y la conducta requerida para liberar (B:buena R:regular M:mala)\n");
	printf("Comando 'actualizar':Actualizara los archivos crucio.dat e imperius.dat eliminando a los presos que hayan sido liberados. El usuario ingresa un argumento: la fecha del archivo de liberados.\n");
	printf("Comando 'mostrar_liberados':Mostrará por pantalla los presos liberados en una fecha. El usuario ingresa un argumento: la fecha (formato aaaamm).\n");
	printf("\nINGRESAR INCORRECTAMENTE EL NOMBRE DE LOS COMANDOS Y/O LA CANTIDAD DE ARGUMENTOS HARÁ QUE EL PROGRAMA FALLE.\n");
	printf("\nPara volver a visualizar esta ayuda, siempre se puede usar el comando 'ayuda'.\n");
}

//Descripcion en archivo prision.h
void mensaje_error(){
	printf("No se pudo ejecutar el comando. Por favor chequear que los argumentos son ingresados correctamente con el formato pedido.\n");
	mostrar_ayuda();
}