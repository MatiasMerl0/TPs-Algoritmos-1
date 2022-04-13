#include "prision.h"
#include <stdio.h>
#include <stdbool.h>
#define MAX_CONDUCTAS 4
#define CONDUCTA_BUENA 'B'
#define CONDUCTA_REGULAR 'R'
#define CONDUCTA_MALA 'M'

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
int main(){

	if(es_conducta_perdonable('s','j'))
		printf("si\n");
	else printf("no\n");

	return 0;
}