#include "parametros.h"
void semilla(void){
	// Copiado del generador que me dio Juanjo
	FILE* Frandfile;
	zseed=0;
	Frandfile = fopen("/dev/urandom","r");
	if(0==fread(&zseed,8,1,Frandfile)){
		printf("Error en la semilla\n");
		exit(0);
	};
	zseed=(unsigned long long) abs(zseed);
	fclose(Frandfile);
	sem=zseed;
}
