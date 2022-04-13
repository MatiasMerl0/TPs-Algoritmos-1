#include<stdlib.h>
#include<stdio.h>
#define MAX_NOMBRE 200
#define MAX_FECHA 7


int main(){
	typedef struct preso{
	char nombre[MAX_NOMBRE];
	int edad;
	char conducta;
	int pabellon;
	int celda;
	char fecha[MAX_FECHA];
	int maldicion_realizada;
	}preso_t;

	preso_t preso;
	FILE* crucio_txt=fopen("crucio.txt","r");
	if(!crucio_txt){
		printf("hubo error.\n");
		return -1;
	}
	FILE* imperio_txt=fopen("imperio.txt","r");
	if(!imperio_txt){
		printf("hubo error.\n");
		fclose(crucio_txt);
		return -1;
	}
	FILE* crucio_dat=fopen("crucio.dat","w");
	if(!crucio_dat){
		printf("hubo error.\n");
		fclose(imperio_txt);
		fclose(crucio_txt);
		return -1;
	}
	FILE* imperius_dat=fopen("imperius.dat","w");
	if(!imperius_dat){
		printf("hubo error.\n");
		fclose(imperio_txt);
		fclose(crucio_txt);
		fclose(crucio_dat);
		return -1;
	}

	int leidos=fscanf(crucio_txt, "%[^;];%i;%c;%i;%i;%[^;];%i;\n",preso.nombre,&(preso.edad),&(preso.conducta),&(preso.pabellon),&(preso.celda),preso.fecha,&(preso.maldicion_realizada));
	while(leidos==7){
		fwrite(&preso,sizeof(preso_t),1,crucio_dat);
		leidos=fscanf(crucio_txt, "%[^;];%i;%c;%i;%i;%[^;];%i;\n",preso.nombre,&(preso.edad),&(preso.conducta),&(preso.pabellon),&(preso.celda),preso.fecha,&(preso.maldicion_realizada));
	}

	leidos=fscanf(imperio_txt, "%[^;];%i;%c;%i;%i;%[^;];%i;\n",preso.nombre,&(preso.edad),&(preso.conducta),&(preso.pabellon),&(preso.celda),preso.fecha,&(preso.maldicion_realizada));
	while(leidos==7){
		fwrite(&preso,sizeof(preso_t),1,imperius_dat);
		leidos=fscanf(imperio_txt, "%[^;];%i;%c;%i;%i;%[^;];%i;\n",preso.nombre,&(preso.edad),&(preso.conducta),&(preso.pabellon),&(preso.celda),preso.fecha,&(preso.maldicion_realizada));
	}
	fclose(imperius_dat);
	fclose(imperio_txt);
	fclose(crucio_txt);
	fclose(crucio_dat);
	return 0;
}