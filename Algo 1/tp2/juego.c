#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "copa.h"
const int PARTIDA_EN_CURSO=0;
const int VICTORIA=1;
const int DERROTA=-1;


/*
* PRE:El usuario ingresara un caracter.
* POST:El procedimiento, guardará el caracter ingresado en una variable.
*/
void pedir_movimiento(char* direccion)
{
	printf("Ingrese una direccion: w (arriba), a (izquierda), s (abajo), d (derecha).\n");
	scanf(" %c", direccion);
}

/*
* PRE:El jugador ingresara los caracteres solicitados.
* POST:El programa validará la entrada de datos, los pedirá de nuevo en caso de ser
* invalidos, y en caso de ser validos efectuara la jugada. Se le avisará al jugador si gana o pierde.
*/
int main()
{
	srand((unsigned int)time(NULL)); 
	char laberinto_mostrado[TAMANIO][TAMANIO];
	juego_t juego;
	char direccion;
	

	inicializar_laberinto(&juego);
	actualizar_laberinto(juego,laberinto_mostrado);
	mostrar_laberinto(laberinto_mostrado);
	printf("vida:%i\n",juego.jugador.vida);
	while(estado_juego(juego)==PARTIDA_EN_CURSO)
	{
		pedir_movimiento(&direccion);
		while(!es_movimiento_valido(&juego,direccion))
		{
			printf("\nNo se puede mover en esa direcion o el caracter ingresado no es valido.\n");
			pedir_movimiento(&direccion);
		}
		mover_jugador(&(juego.jugador),direccion);
		mover_rival(&juego);
		actualizar_juego(&juego);
		actualizar_laberinto(juego,laberinto_mostrado);
		mostrar_laberinto(laberinto_mostrado);
		printf("vida:%i\n",juego.jugador.vida);
	}
	if(estado_juego(juego)==DERROTA)
		printf("\n¡PERDISTE!\n");
	else printf("\n¡GANASTE!\n");

return 0;
}