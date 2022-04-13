#include <stdio.h>
#include <stdbool.h>
/* PRECONDICIONES:
	-La edad, fuerza e inteligencia ingresadas seran números enteros, lo que quiere
	decir que el usuario no ingresará números negativos ni con coma.
	-Al introducir los valores de capacidad mágica, el usuario introducira 
	los caracteres indicados.
	-En consecuencia las funciones deben recibir los tipos de datos que se especifican.

   POSCONDICIONES:
	-El programa validará los datos ingresados y en caso de no estar en el rango
	pedido, volvera a pedirlos hasta que el usuario los ingrese correctamente.
	-Se informará qué alumno ingresado es el campeon, y en caso de que ningún
	alumno haya sido elegido entonces también se informará.
	-Luego de cada ingreso el programa preguntará si se quiere volver a ingresar
	un alumno.	
*/

const int EDAD_MINIMA=17;
const int ATRIBUTO_MAXIMO=10;
const int ATRIBUTO_MINIMO=1;

void pedir_edad(int *edad)
{
	printf("Ingrese la edad del alumno.\n");
	scanf("%i", edad);
}

bool es_mayor(int edad_ingresante) //procedimiento que valida si el alumno es mayor de 17
{
	if (edad_ingresante>=EDAD_MINIMA)
		return true;
	else return false;
}

void pedir_inteligencia(int *inteligencia)
{
	printf("Ingrese el valor de la inteligencia (número entero entre 1 y 10)\n");
	scanf("%i", inteligencia);
}
void pedir_fuerza(int *fuerza)
{
	printf("Ingrese el valor de la fuerza (número entero entre 1 y 10)\n");
	scanf("%i", fuerza);
}
void pedir_capacidad_magica(char *capacidad_magica)
{
	printf("Ingrese el valor de la capacidad mágica ('B' buena, 'R' regular, 'M' mala)\n");
	scanf(" %c", capacidad_magica);
}

void pedir_atributos_correctos(int *inteligencia_ingresante, int *fuerza_ingresante, char *capacidad_magica_ingresante )
{
	do 
	pedir_inteligencia(inteligencia_ingresante);
	while ( !((*inteligencia_ingresante<=ATRIBUTO_MAXIMO)&&(*inteligencia_ingresante>=ATRIBUTO_MINIMO)) );
	do
	pedir_fuerza(fuerza_ingresante);
	while ( !((*fuerza_ingresante<=ATRIBUTO_MAXIMO)&&(*fuerza_ingresante>=ATRIBUTO_MINIMO)) );
	do
	pedir_capacidad_magica(capacidad_magica_ingresante);
	while ( !((*capacidad_magica_ingresante=='B')||(*capacidad_magica_ingresante=='M')||(*capacidad_magica_ingresante=='R')) );
}

bool es_mejor_inteligencia(int inteligencia, int inteligencia_ingresante)
{
	bool es_peor;
	if(inteligencia<inteligencia_ingresante)
		es_peor=false;
	else if(inteligencia>inteligencia_ingresante)
		es_peor=true;
	return !es_peor;
}

bool es_mejor_fuerza(int fuerza, int fuerza_ingresante)
{
	bool es_peor;
	if(fuerza<fuerza_ingresante)
		es_peor=false; 
	else if(fuerza>fuerza_ingresante)
		es_peor=true;
	return !es_peor;
}

bool es_mejor_capacidad_magica(char capacidad_magica, char capacidad_magica_ingresante)
{
	bool es_peor;
	switch(capacidad_magica_ingresante)
			{
				case 'M':
					es_peor=true;
					break;
				case 'R':
					if(capacidad_magica=='M')
						es_peor=false;
					else es_peor=true;
					break;
				case 'B':
					if (capacidad_magica=='B')
						es_peor=true;
					else es_peor=false;
					break;
			}
	return !es_peor;			
}
/*Funcion que compara los atributos actuales con los que se estan ingresando
 para ver cual de los dos alumnos es mas apto para ser campeón*/
bool es_mejor(int inteligencia,int fuerza,char capacidad_magica,int inteligencia_ingresante,int fuerza_ingresante,char capacidad_magica_ingresante)
{                                               
	if(inteligencia!=inteligencia_ingresante)
	return (es_mejor_inteligencia(inteligencia, inteligencia_ingresante));
	else if (fuerza!=fuerza_ingresante)
	return (es_mejor_fuerza(fuerza, fuerza_ingresante));
	else return (es_mejor_capacidad_magica(capacidad_magica, capacidad_magica_ingresante));
			
}

void preguntar_seguir(char *ingresar_alumnos)
{
	printf("Desea ingresar otro alumno? (N para NO, cualquier otra letra para sí)\n");
	scanf(" %c", ingresar_alumnos);
}

//Procedimiento que asigna el numero del contador al alumno
void asignar_campeon_actual(int contador_alumnos, int *numero_campeon)
{
	(*numero_campeon)=contador_alumnos;
}

//procedimiento que asigna los nuevos valores de los atributos 
void actualizar_atributos(int *inteligencia, int *fuerza, char *capacidad_magica, int inteligencia_ingresante, int fuerza_ingresante, char capacidad_magica_ingresante)
{
	(*inteligencia)=inteligencia_ingresante;
	(*fuerza)=fuerza_ingresante;
	(*capacidad_magica)=capacidad_magica_ingresante;
}

int main()
{
	int contador_alumnos,numero_campeon;
	int edad, inteligencia, fuerza;
	int inteligencia_ingresante, fuerza_ingresante;
	char ingresar_alumnos;
	char capacidad_magica;
	char capacidad_magica_ingresante;

	inteligencia=0;
	fuerza=0;
	capacidad_magica=' ';
	contador_alumnos=0;
	numero_campeon=0; /*inicializo la variable numero_campeon en 0, si a lo largo del
                       codigo no se modifica es porque no hay campeón*/

	printf("Desea ingresar un alumno? (N para NO, cualquier otra tecla para sí)");
	scanf(" %c", &ingresar_alumnos);
	if (ingresar_alumnos=='N')
		numero_campeon=0;
	else
	{
		contador_alumnos = (contador_alumnos+1);
		pedir_edad(&edad);
		if (es_mayor(edad))
		{
			pedir_atributos_correctos(&inteligencia_ingresante,&fuerza_ingresante,&capacidad_magica_ingresante);
			actualizar_atributos(&inteligencia,&fuerza,&capacidad_magica,inteligencia_ingresante,fuerza_ingresante,capacidad_magica_ingresante);
			asignar_campeon_actual(contador_alumnos, &numero_campeon);
		}	
		preguntar_seguir(&ingresar_alumnos);
		while (ingresar_alumnos!='N')
		{
			contador_alumnos = (contador_alumnos+1);
			pedir_edad(&edad);
			if(es_mayor(edad))
			{
				pedir_atributos_correctos(&inteligencia_ingresante,&fuerza_ingresante,&capacidad_magica_ingresante);
				if(es_mejor(inteligencia,fuerza,capacidad_magica,inteligencia_ingresante,fuerza_ingresante,capacidad_magica_ingresante))
				{
					actualizar_atributos(&inteligencia,&fuerza,&capacidad_magica,inteligencia_ingresante,fuerza_ingresante,capacidad_magica_ingresante);
					asignar_campeon_actual(contador_alumnos, &numero_campeon);
				}	
			}
			preguntar_seguir(&ingresar_alumnos);
		}

	}
	if (numero_campeon==0)
		printf("No hay campeón :(\n");
	else printf("El campeón es el número %i :) \n", numero_campeon);
	return 0;
}