#ifndef PRISION_H
#define PRISION_H
#define MAX_NOMBRE 200
#define MAX_FECHA 7
#define MAX_NOMBRE_ARCHIVO 50
typedef struct preso{
	char nombre[MAX_NOMBRE];
	int edad;
	char conducta;
	int pabellon;
	int celda;
	char fecha[MAX_FECHA];
	int maldicion_realizada;
	}preso_t;

/*
* PRE:Recibe el nombre (str) del archivo que se va a generar.
* POST:Genera un archivo binario a partir de los archivos crucio.dat e imperius.dat con el nombre recibido. Devuelve -1 si hubo un error.
*/
int generar_perdonables(char nombre_archivo[MAX_NOMBRE_ARCHIVO]);

/*
* PRE:Recibe el nombre (str) del archivo de perdonables, la fecha (str con formato aaaamm) a liberar y la conducta (char) minima para ser liberados.
* POST:Genera un archivo de texto con los nombres de los presos que cumplen las condiciones de ser liberados. Si el archivo ya existe, no se permite
* usar el comando. Devuelve -1 si hubo un error.
*/
int generar_liberados(char nombre_archivo[MAX_NOMBRE_ARCHIVO], char fecha[MAX_FECHA],char conducta);

/*
* PRE:Recibe la fecha (str en formato aaaamm) del archivo de liberados del cual se quiere actualizar.
* POST:Actualiza los archivos binarios crucio.dat e imperius.dat sacando los presos que fueron liberados. Devuelve -1 si hubo un error.
*/
int actualizar_presos(char fecha[MAX_FECHA]);

/*
* PRE:Recibe la fecha (str en formato aaaamm) del archivo de liberados con el que se quiere trabajar.
* POST:Mostrara por pantalla los liberados de ese mes. Devuelve -1 si hubo un error.
*/
int mostrar_liberados(char fecha[MAX_FECHA]);

/*
* PRE:El procedimiento no recibe ningun parametro.
* POST:Mostrará por pantalla las prestaciones del programa entero, información sobre qué hacen los comandos y qué datos ingresar.
*/
void mostrar_ayuda();

/*
* PRE:El procedimiento no recibe ningun parametro.
* POST:Mostrará un mensaje de error por pantalla avisandole al usuario que algun argumento fue ingresado incorrectamente o surgio un error al 
* intentar abrir alguno de los archivos.
*/
void mensaje_error();
#endif 
