#include<stdlib.h>
#include<stdio.h>
#define MAX_NOMBRE 200
#define MAX_FECHA 7

	typedef struct preso{
	char nombre[MAX_NOMBRE];
	int edad;
	char conducta;
	int pabellon;
	int celda;
	char fecha[MAX_FECHA];
	int maldicion_realizada;
	}preso_t;

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

int main(){

/*preso_t preso;
	FILE* crucio_dat=fopen("crucio.dat","r");
	if(!crucio_dat){
		printf("hubo error1.\n");
		return -1;
	}
	FILE* imperius_dat=fopen("imperius.dat","r");
	if(!imperius_dat){
		printf("hubo error2.\n");
		fclose(crucio_dat);
		return -1;
	}

	FILE* crucio_txt=fopen("crucio2.txt","w");
	if(!crucio_txt){
		printf("hubo error3.\n");
		fclose(imperius_dat);
		fclose(crucio_dat);
		return -1;
	}
	FILE* imperius_txt=fopen("imperius2.txt","w");
	if(!imperius_txt){
		printf("hubo error4.\n");
		fclose(imperius_dat);
		fclose(crucio_dat);
		fclose(crucio_txt);
		return -1;
	}

	int leidos=leer_binario(crucio_dat,&preso);
	while(leidos){
		escribir_texto(crucio_txt,&preso);
		leidos=leer_binario(crucio_dat,&preso);
	}
*/
	preso_t preso;
	FILE* perdonables=fopen("perdonables","r");
	if(!perdonables){
		printf("error\n");
		return -1;
	}	
	FILE* perdonables_txt=fopen("perdonables.txt","w");
	if(!perdonables_txt){
		printf("error\n");
		return -1;
	}

	int leidos=leer_binario(perdonables,&preso);
	while(leidos){
		escribir_texto(perdonables_txt,&preso);
		leidos=leer_binario(perdonables,&preso);
	}

	/*fclose(imperius_dat);
	fclose(imperius_txt);
	fclose(crucio_txt);
	fclose(crucio_dat);
	*/
	fclose(perdonables_txt);
	fclose(perdonables);
	return 0;
}