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

int generar_perdonables(char nombre_archivo[MAX_NOMBRE_ARCHIVO]);
int generar_liberados(char nombre_archivo[MAX_NOMBRE_ARCHIVO], char fecha[MAX_FECHA],char conducta);
int actualizar_presos(char fecha[MAX_FECHA]);
int mostrar_liberados(char fecha[MAX_FECHA]);
void mostrar_ayuda();
void mensaje_error();
#endif 
