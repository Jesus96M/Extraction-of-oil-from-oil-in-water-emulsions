#include "parametros.h"
int main(int argc, char *argv[]) {	
	switch(argc){
		case 2:
			fp=fopen(argv[1],"r");
			if(fgets(texto,200,fp)==NULL){
				printf("Error en el programa: Revisa condiciones.dat");
			};
			if(fscanf(fp,"%d\t%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%ld\t%ld", &Lx, &Ly, &per, &T, &J1, &J2, &J12, &gravity, &rho_r, &k1, &alpha, &por, &Nsteps, &Nmed));
			fclose(fp);
			k2=k1*rho_r;
			// Las interacciones diagonales se ponen a la mitad
			J1_diag=J1/2.0;
			J2_diag=J2/2.0;
			J12_diag=J12/2.0;
			break;
		default:
			printf("Error en el programa: %s numero de argumentos incorrecto\n",argv[0]);
			exit(0);
	}
	reservaMemoria();
	vecinos();

	// Fijamos la condicion iniciales
	semilla();
	condicionesIniciales();
	k=1;// MC Step
	porce=0;
	configuracion2(porce);
	configuracionConectados2(porce);
	porce++;

	abreArchivos();
	k=0;
	calculaInicioDroplet();
	mideBordeGota();
	
	midePosicionesDistancias();
	mideSuperficie();
	midePorcentajeAceiteEnGota();
	// Core del ALGORITMO MC
	descripcion();
	printf("MC LOOP\n");
	
	while(k<Nsteps){//Npasos=Ncambios que realiza el Monte Carlo
		// MC en tiempo discreto

		//Seleccionamos una celda al azar y elegimos un vecino valido al azar
		//La propuesta es intercambiarlo (Kawasaki dynamics)
		aleatorio=FRANDOM*N;
		ind1=(int) aleatorio;
		ind2=eligeVecino(ind1);
		//Ya tenemos las 2 celdas elegidas. Ahora hay que calcular cual es la diferencia de energia en realizar este movimiento
		if(C[ind1]==C[ind2]){
			// No hacemos nada ya que se trata de un cambio trivial
			// agua <---> agua  //  aceite <---> aceite //  aire <---> aire
		} else{
			// Tenemos un cambio no trivial
			// Calculamos primero cuantos vecinos de cada celda son agua y cuantos aceite
			calculaVecinos(ind1,ind2);
			calculaVecinosDiag(ind1, ind2);
			// Ya sabemos cuantos vecinos de ind1 e ind2 son agua y aceite
			// Calculamos ahora la probabilidad de aceptar ese cambio, basado en la diferencia de energia en el cambio
			probabilidad=calculaProbabilidad(ind1,ind2);
			aleatorio=FRANDOM;
			if(aleatorio<probabilidad){
				// Se acepta el cambio
				cambio(ind1,ind2);
			} else{
				// El cambio se rechaza y no hacemos nada
			}
		}
		// Aumentamos el paso del MC
		k++;

		// Medimos
		if((k % 1000)==0){
			calculaInicioDroplet();
			mideExtraccionAceite();
			mideExtraccionAceite2();
			revisaConectados();
		}

		if((k % Nmed)==0){
			printf("\rMidiendo %d/%ld",porce,(Nsteps/Nmed));
			fflush(stdout);
			
			configuracion2(porce);
			configuracionConectados2(porce);
			porce++;
			midePosicionesDistancias();
			mideBordeGota();
			mideSuperficie();
			midePorcentajeAceiteEnGota();
		}
	}
	printf("\r\n");
	cierraArchivos();

	return 1;
}
