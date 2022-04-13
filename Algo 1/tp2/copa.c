#include "copa.h"
#include "laberinto.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define IZQUIERDA 'a'
#define ABAJO 's'
#define DERECHA 'd'
#define ARRIBA 'w'
const char JUGADOR='J';
const char RIVAL='G';
const char COPA='C';
const char POCIONES='P';
const char IMPEDIMENTA='I';
const char RIDDIKULUS='R';
const char ESCREGUTO='E';
const char ACROMANTULA='A';
const char BOGGART='B';
const char ESFINGE='F';
const int DISTANCIA_MANHATTAN=10;
const int GANO=1;
const int PERDIO=-1;
const int SIGUE_EN_CURSO=0;
const int DANIO_ESCREGUTO=20;
const int DANIO_ACROMANTULA=10;
const int DANIO_BOGGART=15;
const int DANIO_POR_TURNO=3;
const int VIDA_POCION=15;
const int VIDA_IMPEDIMENTA=0;
const int VIDA_RIDDIKULUS=0;
const int VIDA_ESFINGE=0;
const int VIDA_INICIAL_JUGADOR=50;
const int CANTIDAD_INICIAL_PASOS=0;

//Tiene la descripción en el copa.h provisto por la cátedra.
void mostrar_laberinto(char laberinto[TAMANIO][TAMANIO])
{
	for (int fila=0;fila<TAMANIO;fila++)
	{
	for(int columna=0;columna<TAMANIO;columna++)
	if(laberinto[fila][columna]==PARED)
		printf("|");
	else
		printf("%c",laberinto[fila][columna]);
	printf("\n");
	}
}

/*
* PRE:Recibira dos matrices, el laberinto original y el laberinto que sera mostrado.
* POST:Copiara los caracteres del laberinto original al laberinto que sera mostrado.
*/
void copiar_laberinto(char laberinto_original[TAMANIO][TAMANIO],char laberinto_mostrado[TAMANIO][TAMANIO])
{
	for (int i=0;i<TAMANIO;i++)
		for(int j=0;j<TAMANIO;j++)
			laberinto_mostrado[i][j]=laberinto_original[i][j];
}

//Tiene la descripcion en el copa.h provisto por la cátedra.
coordenada_t posicion_aleatoria()
{
	coordenada_t coordenada_aleatoria;
	coordenada_aleatoria.fil=(rand()%TAMANIO);
	coordenada_aleatoria.col=(rand()%TAMANIO);
	return coordenada_aleatoria;
}

/*
* PRE:Recibira una posición inicial y un laberinto sobre el cual comparar.
* POST:Devolverá verdadera si la posición es válida(si no hay nada en esa posición)
*/
bool es_posicion_inicial_valida(coordenada_t posicion, char laberinto[TAMANIO][TAMANIO])
{
	bool es_valida=false;
	if(laberinto[posicion.fil][posicion.col]==VACIO)
		es_valida=true;
	return es_valida;
}

/*
* PRE:Recibira un puntero a una posicion y un laberinto sobre el cual comparar.
* POST:Devolvera una posicion aleatoria constantemente hasta que sea válida.
*/
void asignar_posicion_valida(coordenada_t* posicion,char laberinto[TAMANIO][TAMANIO])
{
	do
	*posicion=posicion_aleatoria();
	while(!es_posicion_inicial_valida(*posicion,laberinto));
}

/*
* PRE:Recibira dos posiciones.
* POST:Devolvera la distancia manhattan entre las dos posiciones.
*/
int distancia_manhattan(coordenada_t posicion1, coordenada_t posicion2)
{
	int distancia;
	distancia=abs((posicion1.col)-(posicion2.col))+abs((posicion1.fil)-(posicion2.fil));
	return distancia;
}

/*
* PRE:Recibira punteros a las posiciones del rival y jugador y la posicion de la copa 
* asi como el laberinto sobre el que comparará.
* POST:Devolverá una posicion para los jugadores que se encuentra a la distancia pedida de la copa
*/
void asignar_posicion_jugadores(coordenada_t* posicion,char laberinto[TAMANIO][TAMANIO], coordenada_t posicion_copa)
{
	do
	*posicion=posicion_aleatoria();
	while(!es_posicion_inicial_valida(*posicion,laberinto)||(distancia_manhattan(*posicion,posicion_copa)<=DISTANCIA_MANHATTAN));
}

/*
* PRE:Recibira un puntero a la copa y el laberinto sobre el cual inicializar.
* POST:Inicializará todos los campos de la copa.
*/
void inicializar_copa(copa_t* copa, char laberinto[TAMANIO][TAMANIO])
{
	copa->codigo=COPA;
	asignar_posicion_valida(&(copa->posicion),laberinto);
	laberinto[copa->posicion.fil][copa->posicion.col]=copa->codigo;
}

/*
* PRE:Recibira un puntero a una estructura obstaculo_t (en este caso el escreguto) y el laberinto sobre el cual inicializar.
* POST:Inicializará todos los campos de la estructura.
*/
void inicializar_escreguto(obstaculo_t* escreguto,int* tope_obstaculos, char laberinto[TAMANIO][TAMANIO])
{
	escreguto->codigo=ESCREGUTO;
	escreguto->danio=DANIO_ESCREGUTO;
	asignar_posicion_valida(&(escreguto->posicion),laberinto);
	laberinto[escreguto->posicion.fil][escreguto->posicion.col]=escreguto->codigo;
	(*tope_obstaculos)++;
}

/*
* PRE:Recibira un puntero a una estructura obstaculo_t (en este caso la acromantula) y el laberinto sobre el cual inicializar.
* POST:Inicializará todos los campos de la estructura.
*/
void inicializar_acromantula(obstaculo_t* acromantula,int* tope_obstaculos,char laberinto[TAMANIO][TAMANIO])
{
	acromantula->codigo=ACROMANTULA;
	acromantula->danio=DANIO_ACROMANTULA;
	asignar_posicion_valida(&(acromantula->posicion),laberinto);
	laberinto[acromantula->posicion.fil][acromantula->posicion.col]=acromantula->codigo;
	(*tope_obstaculos)++;
}

/*
* PRE:Recibira un puntero a una estructura obstaculo_t (en este caso el boggart) y el laberinto sobre el cual inicializar.
* POST:Inicializará todos los campos de la estructura.
*/
void inicializar_boggart(obstaculo_t* boggart, int* tope_obstaculos,char laberinto[TAMANIO][TAMANIO])
{
	boggart->codigo=BOGGART;
 	boggart->danio=DANIO_BOGGART;
 	asignar_posicion_valida(&(boggart->posicion),laberinto);
 	laberinto[boggart->posicion.fil][boggart->posicion.col]=boggart->codigo;
 	(*tope_obstaculos)++;
}
/*
* PRE:Recibira un vector de estructuras obstaculo_t asi como un puntero al tope del vector y el laberinto sobre el cual inicializar.
* POST:Inicializará todas las estructuras en el laberinto.
*/
void inicializar_obstaculos(obstaculo_t obstaculos [TOTAL_OBSTACULOS],int* tope_obstaculos,char laberinto[TAMANIO][TAMANIO])
{
	(*tope_obstaculos)=0;
	inicializar_escreguto(&obstaculos[*tope_obstaculos],tope_obstaculos,laberinto);
	inicializar_acromantula(&obstaculos[*tope_obstaculos],tope_obstaculos,laberinto);
	inicializar_boggart(&obstaculos[*tope_obstaculos],tope_obstaculos,laberinto);
}

/*
* PRE:Recibira un puntero a una estructura ayuda_t (en este caso impedimenta) y el laberinto sobre el cual inicializar.
* POST:Inicializará todos los campos de la estructura.
*/
void inicializar_impedimenta(ayuda_t* impedimenta,int* tope_ayudas,char laberinto[TAMANIO][TAMANIO])
{
	impedimenta->codigo=IMPEDIMENTA;
	impedimenta->vida_a_recuperar=VIDA_IMPEDIMENTA;
	asignar_posicion_valida(&(impedimenta->posicion),laberinto);
	laberinto[impedimenta->posicion.fil][impedimenta->posicion.col]=impedimenta->codigo;
	(*tope_ayudas)++;
}

/*
* PRE:Recibira un puntero a una estructura ayuda_t (en este caso riddikulus) y el laberinto sobre el cual inicializar.
* POST:Inicializará todos los campos de la estructura.
*/
void inicializar_riddikulus(ayuda_t* riddikulus,int* tope_ayudas,char laberinto[TAMANIO][TAMANIO])
{
	riddikulus->codigo=RIDDIKULUS;
	riddikulus->vida_a_recuperar=VIDA_RIDDIKULUS;
	asignar_posicion_valida(&(riddikulus->posicion),laberinto);
	laberinto[riddikulus->posicion.fil][riddikulus->posicion.col]=riddikulus->codigo;
	(*tope_ayudas)++;
}

/*
* PRE:Recibira un puntero a una estructura ayuda_t (en este casopocion) y el laberinto sobre el cual inicializar.
* POST:Inicializará todos los campos de la estructura.
*/
void inicializar_pociones(ayuda_t* pocion,int* tope_ayudas,char laberinto[TAMANIO][TAMANIO])
{
	pocion->codigo=POCIONES;
	pocion->vida_a_recuperar=VIDA_POCION;
	asignar_posicion_valida(&(pocion->posicion),laberinto);
	laberinto[pocion->posicion.fil][pocion->posicion.col]=pocion->codigo;
	(*tope_ayudas)++;
}

/*
* PRE:Recibira un puntero a una estructura ayuda_t (en este caso esfinge) y el laberinto sobre el cual inicializar.
* POST:Inicializará todos los campos de la estructura.
*/
void inicializar_esfinge(ayuda_t* esfinge,int* tope_ayudas,char laberinto[TAMANIO][TAMANIO])
{
	esfinge->codigo=ESFINGE;
	esfinge->vida_a_recuperar=VIDA_ESFINGE;
	asignar_posicion_valida(&(esfinge->posicion),laberinto);
	laberinto[esfinge->posicion.fil][esfinge->posicion.col]=esfinge->codigo;
	(*tope_ayudas)++;
}

/*
* PRE:Recibira un vector de estructuras ayuda_t asi como un puntero al tope del vector y el laberinto sobre el cual inicializar.
* POST:Inicializará todas las estructuras en el laberinto.
*/
void inicializar_ayudas(ayuda_t ayudas[TOTAL_AYUDAS],int* tope_ayudas,char laberinto[TAMANIO][TAMANIO])
{
	(*tope_ayudas)=0;
	inicializar_impedimenta(&ayudas[*tope_ayudas],tope_ayudas,laberinto);
	inicializar_riddikulus(&ayudas[*tope_ayudas],tope_ayudas,laberinto);
	for(int contador=0;contador<3;contador++)
		inicializar_pociones(&ayudas[*tope_ayudas],tope_ayudas,laberinto);
	inicializar_esfinge(&ayudas[*tope_ayudas],tope_ayudas,laberinto);
}

/*
* PRE:Recibira un puntero al rival, la posicion de la copa y el laberinto sobre el cual inicializar.
* POST:Inicializará todos los campos de la estructura.
*/
void inicializar_rival(rival_t* rival, char laberinto[TAMANIO][TAMANIO],coordenada_t posicion_copa)//se manda la posicion de la copa porque se llama a funciones que dan la distancia manhattan
{
	rival->codigo=RIVAL;
	rival->direccion=DERECHA;
	rival->cantidad_pasos=CANTIDAD_INICIAL_PASOS;
	asignar_posicion_jugadores(&(rival->posicion),laberinto,posicion_copa);
	laberinto[rival->posicion.fil][rival->posicion.col]=rival->codigo;
}

/*
* PRE:Recibira un puntero al jugador, la posicion de la copa y el laberinto sobre el cual inicializar.
* POST:Inicializará todos los campos de la estructura.
*/
void inicializar_jugador(jugador_t* jugador, char laberinto[TAMANIO][TAMANIO],coordenada_t posicion_copa)
{
	jugador->vida=VIDA_INICIAL_JUGADOR;
	jugador->codigo=JUGADOR;
	jugador->tope_ayudas=0;
	asignar_posicion_jugadores(&(jugador->posicion),laberinto,posicion_copa);
	laberinto[jugador->posicion.fil][jugador->posicion.col]=jugador->codigo;

}

//Tiene la descripcion en el copa.h provisto por la cátedra.
void inicializar_laberinto(juego_t* juego)
{
	char laberinto_aux[TAMANIO][TAMANIO]; //Este laberinto auxiliar lo uso para dejar el laberinto original solo con las paredes.
	inicializar_paredes_laberinto(juego->laberinto_original);
	copiar_laberinto(juego->laberinto_original,laberinto_aux);
	inicializar_copa(&(juego->copa),juego->laberinto_original);
	inicializar_obstaculos(juego->obstaculos,&(juego->tope_obstaculos),juego->laberinto_original);
	inicializar_ayudas(juego->ayudas,&(juego->tope_ayudas),juego->laberinto_original);
	inicializar_rival(&(juego->rival),juego->laberinto_original,juego->copa.posicion);
	inicializar_jugador(&(juego->jugador),juego->laberinto_original,juego->copa.posicion);
	copiar_laberinto(laberinto_aux,juego->laberinto_original);
}

/*
* PRE:Recibe el codigo y posicion de un elemento y el laberinto sobre el cual lo va a asignar.
* POST:Asigna el codigo en la posicion del laberinto.
*/
void asignar_elemento(char codigo, coordenada_t posicion, char laberinto[TAMANIO][TAMANIO])
{
	laberinto[posicion.fil][posicion.col]=codigo;
}

/*
* PRE:Recibe el vector ayudas del jugador asi como su tope.
* POST:Recorre el vector y devuelve verdadera si está la esfinge, es decir si el jugador tiene la esfinge.
*/
bool tiene_esfinge(ayuda_t ayudas[TOTAL_AYUDAS],int tope_ayudas_jugador)
{
	bool hay_esfinge=false;
	int i=0;
	while((i<tope_ayudas_jugador)&&(!hay_esfinge))
	{
		if(ayudas[i].codigo==ESFINGE)
			hay_esfinge=true;
		i++;
	}
	return hay_esfinge;
}

//Tiene la descripcion en el copa.h provisto por la cátedra.
void actualizar_laberinto(juego_t juego,char laberinto[TAMANIO][TAMANIO])
{
	copiar_laberinto(juego.laberinto_original,laberinto);
	if(juego.jugador.vida<=15||tiene_esfinge(juego.jugador.ayudas,juego.jugador.tope_ayudas))
		asignar_elemento(juego.copa.codigo,juego.copa.posicion,laberinto);
	for(int i=0;i<juego.tope_obstaculos;i++)
		asignar_elemento(juego.obstaculos[i].codigo,juego.obstaculos[i].posicion,laberinto);
	for(int j=0;j<juego.tope_ayudas;j++)
		asignar_elemento(juego.ayudas[j].codigo,juego.ayudas[j].posicion,laberinto);
	asignar_elemento(juego.rival.codigo,juego.rival.posicion,laberinto);
	asignar_elemento(juego.jugador.codigo,juego.jugador.posicion,laberinto);
}

/*
* PRE:Recibe un puntero a la posicion y una tecla(direccion) que tiene que haber sido validada anteriormente.
* POST:Cambiara la coordenada de la posicion en funcion de la direccion dada.
*/
void mover(coordenada_t* posicion, char tecla)
{
	switch(tecla)
	{
		case IZQUIERDA:
			(posicion->col)--;
			break;
		case DERECHA:
			(posicion->col)++;
			break;
		case ARRIBA:
			(posicion->fil)--;
			break;
		case ABAJO:
			(posicion->fil)++;
			break;
	}
}

/*
* PRE:Recibe el juego, la posicion actual y la direccion a la cual se quiere ir.
* POST:Devolverá verdadero si hay pasillo y esta dentro del rango de la matriz.
*/
bool hay_pasillo(juego_t juego, coordenada_t posicion_actual, char tecla)
{
	bool disponible=true;
	switch (tecla)
	{
		case IZQUIERDA:
			if((juego.laberinto_original[posicion_actual.fil][(posicion_actual.col)-1]==PARED)||(((posicion_actual.col)-1)<0)||(((posicion_actual.col)-1)>=TAMANIO))
				disponible=false;
			break;
		case DERECHA:
			if((juego.laberinto_original[posicion_actual.fil][(posicion_actual.col)+1]==PARED)||(((posicion_actual.col)+1)<0)||(((posicion_actual.col)+1)>=TAMANIO))
				disponible=false;
			break;
		case ARRIBA:
			if((juego.laberinto_original[(posicion_actual.fil)-1][posicion_actual.col]==PARED)||(((posicion_actual.fil)-1)<0)||(((posicion_actual.fil)-1)>=TAMANIO))
				disponible=false;
			break;
		case ABAJO:
			if((juego.laberinto_original[(posicion_actual.fil)+1][posicion_actual.col]==PARED)||(((posicion_actual.fil)+1)<0)||(((posicion_actual.fil)+1)>=TAMANIO))
				disponible=false;
			break;
	}
	return disponible;
}

//Tiene la descripcion en el copa.h provisto por la cátedra.
bool es_movimiento_valido(juego_t* juego, char tecla)
{	
	if((tecla!=IZQUIERDA)&&(tecla!=DERECHA)&&(tecla!=ABAJO)&&(tecla!=ARRIBA))
		return false;
	else return hay_pasillo(*juego,juego->jugador.posicion,tecla);
} 

//Tiene la descripcion en el copa.h provisto por la cátedra.
void mover_jugador(jugador_t* jugador, char direccion)
{
	mover(&(jugador->posicion),direccion);
}

/*
*PRE:Recibe un puntero a la direccion del rival para cambiarla.
*POST:Cambia la direccion del rival en funcion de su direccion previa.
*/
void cambiar_direccion_rival(char* direccion)
{
	switch (*direccion)
	{
		case DERECHA:
			*direccion=ABAJO;
			break;
		case ABAJO:
			*direccion=IZQUIERDA;
			break;
		case IZQUIERDA:
			*direccion=ARRIBA;
			break;
		case ARRIBA:
			*direccion=DERECHA;
			break;
	}
}

//Tiene la descripcion en el copa.h provisto por la cátedra.
void mover_rival(juego_t* juego)
{
	bool se_movio=false;
	while(!se_movio)
	{
		if(juego->rival.cantidad_pasos==4)
		{
			cambiar_direccion_rival(&(juego->rival.direccion));
			juego->rival.cantidad_pasos=CANTIDAD_INICIAL_PASOS;
		}
		if (hay_pasillo(*juego,juego->rival.posicion,juego->rival.direccion))
		{
			mover(&(juego->rival.posicion),juego->rival.direccion);
			se_movio=true;
		}
		(juego->rival.cantidad_pasos)++;
	}
}

/*
*PRE:Recibe dos posicion validadas.
*POST:Compara si esas dos posiciones son iguales.
*/
bool tienen_misma_posicion(coordenada_t posicion1, coordenada_t posicion2) 
{
	return((posicion1.fil==posicion2.fil)&&(posicion1.col==posicion2.col));
}

//Tiene la descripcion en el copa.h provisto por la cátedra.
int estado_juego(juego_t juego)
{
	if(tienen_misma_posicion(juego.copa.posicion,juego.jugador.posicion)&&(juego.jugador.vida>0))
		return GANO;
	else if(tienen_misma_posicion(juego.copa.posicion,juego.rival.posicion)||(juego.jugador.vida<=0))
		return PERDIO;
	else return SIGUE_EN_CURSO;
}

/*
*PRE:Recibe un puntero al jugador luego de un turno.
*POST:Resta la vida al jugador luego de moverse.
*/
void restar_vida(jugador_t* jugador)
{
	jugador->vida-=DANIO_POR_TURNO;
}

/*
*PRE:Recibe el codigo de un obstaculo y de una ayuda en el vector ayudas del jugador.
*POST:Devuelve verdadero si la ayuda contrarresta al obstaculo.
*/
bool estoy_protegido(char codigo_ayudas, char codigo_obstaculos)
{
	if(((codigo_obstaculos==ESCREGUTO)&&(codigo_ayudas==IMPEDIMENTA))||((codigo_obstaculos==BOGGART)&&(codigo_ayudas==RIDDIKULUS)))
		return true;
	else return false;
}

/*
*PRE:Recibe el vector ayudas del jugador asi como un puntero al tope del vector y la posicion del elemento a eliminar.
*POST:Remueve la ayuda del vector ayudas del jugador, luego achica el tope.
*/
void remover_ayuda_jugador(ayuda_t ayudas[TOTAL_AYUDAS],int* tope_ayudas,int posicion)
{
	for(int i=posicion;i<(*tope_ayudas);i++)
	{
		ayudas[i]=ayudas[i+1];
	}
	(*tope_ayudas)--;
}

/*
*PRE:Recibe el vector obstaculos del juego asi como un puntero al tope del vector y la posicion del elemento a eliminar.
*POST:Remueve el obstaculo del vector obstaculos, luego achica el tope.
*/
void remover_obstaculo_juego(obstaculo_t obstaculos[TOTAL_OBSTACULOS],int* tope_obstaculos,int posicion)
{
	for(int i=posicion;i<(*tope_obstaculos);i++)
	{
		obstaculos[i]=obstaculos[i+1];
	}
	(*tope_obstaculos)--;
}

/*
*PRE:Recibe un puntero al juego.
*POST:Chequea si la posicion donde esta el jugador coincide con la posicion de un obstaculo, en caso de coincidir se fijara si tiene una ayuda para contrarrestar,
* en caso de tenerla, no se resta vida. En caso contrario se resta la vida. Por ultimo se elimina el obstaculo del juego.
*/
void revisar_obstaculos(juego_t* juego)
{
	int pos_obstaculo,i=0,j=0;
	bool hay_obstaculo=false,tengo_ayuda=false;
	while(i<(juego->tope_obstaculos)&&(!hay_obstaculo))
	{
		if(tienen_misma_posicion(juego->obstaculos[i].posicion,juego->jugador.posicion))
		{
			hay_obstaculo=true;
			pos_obstaculo=i;
		}
		i++;
	}
	if(hay_obstaculo)
	{
		while(j<(juego->jugador.tope_ayudas)&&(!tengo_ayuda))
		{
			if(estoy_protegido((juego->jugador.ayudas[j].codigo),(juego->obstaculos[pos_obstaculo].codigo)))
			{
				tengo_ayuda=true;
				remover_ayuda_jugador(juego->jugador.ayudas,&(juego->jugador.tope_ayudas),j);
			}
			j++;
		}
		if(!tengo_ayuda)
			juego->jugador.vida-=juego->obstaculos[pos_obstaculo].danio;
		remover_obstaculo_juego(juego->obstaculos,&(juego->tope_obstaculos),pos_obstaculo);
	}
}

/*
*PRE:Recibe una ayuda y un puntero al jugador.
*POST:Suma la vida de la ayuda al jugador.
*/
void sumar_vida(ayuda_t ayuda,jugador_t* jugador)
{
	if((jugador->vida+ayuda.vida_a_recuperar)>VIDA_INICIAL_JUGADOR)
		jugador->vida=VIDA_INICIAL_JUGADOR;
	else ((jugador->vida)+=(ayuda.vida_a_recuperar));
}

/*
*PRE:Recibe el vector ayudas del jugador asi como un puntero al tope del vector y la ayuda que se agregara.
*POST:Agrega la ayuda al vector ayudas del jugador.
*/
void agregar_ayuda_jugador(ayuda_t ayudas[TOTAL_AYUDAS],ayuda_t ayuda_agregada, int* tope_ayudas)
{
	ayudas[(*tope_ayudas)]=ayuda_agregada;
	(*tope_ayudas)++;
}

/*
*PRE:Recibe el vector ayudas del juego asi como un puntero al tope del vector y la posicion del elemento a eliminar.
*POST:Remueve la ayuda del vector ayudas del juego, luego achica el tope.
*/
void remover_ayuda_juego(ayuda_t ayudas[TOTAL_AYUDAS],int* tope_ayudas_juego,int posicion)
{
	for(int i=posicion;i<(*tope_ayudas_juego);i++)
	{
		ayudas[i]=ayudas[i+1];
	}
	(*tope_ayudas_juego)--;
}

/*
*PRE:Recibe un puntero al juego
*POST:Chequea si hay ayudas en la posicion del jugador. En caso de haber, las consume si son pociones y las almacena en su vector si son otras ayudas.
*/
void revisar_ayudas(juego_t* juego)
{
	bool hay_ayuda=false;
	int pos_ayuda,i=0;
	while(i<(juego->tope_ayudas)&&(!hay_ayuda))
	{
		if(tienen_misma_posicion(juego->ayudas[i].posicion,juego->jugador.posicion))
		{
			hay_ayuda=true;
			pos_ayuda=i;
		}
		i++;
	}
	if(hay_ayuda)
	{
		sumar_vida(juego->ayudas[pos_ayuda],&(juego->jugador));
		if((juego->ayudas[pos_ayuda].codigo)!=POCIONES)
			agregar_ayuda_jugador(juego->jugador.ayudas,juego->ayudas[pos_ayuda],&(juego->jugador.tope_ayudas));
		remover_ayuda_juego(juego->ayudas,&(juego->tope_ayudas),pos_ayuda);
	}

}

//Tiene la descripcion en el copa.h provisto por la cátedra.
void actualizar_juego(juego_t* juego)
{
	restar_vida(&(juego->jugador));
	revisar_obstaculos(juego);
	revisar_ayudas(juego);

}



