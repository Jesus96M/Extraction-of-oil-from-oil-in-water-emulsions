#include "parametros.h"
void configuracion2(int porcent){
	// Funcion que genera el archivo con la configuracion para hacer un restart
	snprintf(nombre,sizeof(nombre),"Configuracion_%d_%lld.dat",porcent,sem);
	FILE *datos1=fopen(nombre,"w");
	for(i=0;i<N;i++){
		// Pinta las capas
		fprintf(datos1,"%d\n",*(C+i));
	}
	fclose(datos1);
}

void configuracionConectados2(int porcent){
	// Funcion que genera el archivo con la configuracion para hacer un restart
	snprintf(nombre,sizeof(nombre),"ConfiConectados_%d_%lld.dat",porcent,sem);
	FILE *datos1=fopen(nombre,"w");
	for(i=0;i<N;i++){
		// Pinta las capas
		fprintf(datos1,"%d\n",*(conectado+i));
	}
	fclose(datos1);
}

void descripcion(){
	// Funcion que genera un archivo txt donde se escriben las caracteristicas de la simulacion
	FILE *datos1=fopen("descripcion.txt","w");
	fprintf(datos1,"Simulación de la seperacion de fases agua/aceite/aire con MC\n");
	fprintf(datos1,"Hay interaccion entre las particulas (Jij)\n");
	fprintf(datos1,"Hay gravedad (rho_i) y fuerza externa de ultrasonido (ki)\n");
	fprintf(datos1,"Se supone que la densidad del agua es 1 (rho_1=1) y la del aceite se da relativa a esta (rho_2=rho_r)\n");
	fprintf(datos1,"Los parámetros utilizados son:\n");
	fprintf(datos1,"Lx=%d,Ly=%d,T=%lf\n",Lx,Ly,T);
	//fprintf(datos1,"A1=%lf,A2=%lf,J1=%lf,J2=%lf,J12=%lf\n",A1,A2,J1,J2,J12);
	fprintf(datos1,"J1=%lf,J2=%lf,J12=%lf\n",J1,J2,J12);
	//fprintf(datos1,"k1=%lf, k2=%lf, alpha=%lf, lambda=%lf\n",k1,k2,alpha,lambda);
	fprintf(datos1,"k1=%lf, k2=%lf, alpha=%lf\n",k1,k2,alpha);
	fprintf(datos1,"La intensidad del exceso de presión es, por=%lf\n",por);
	fprintf(datos1,"gravity=%lf, rho_r=%lf,\n",gravity,rho_r);
	fprintf(datos1,"Nsteps=%ld, Nmed=%ld\n",Nsteps,Nmed);
	fprintf(datos1,"El porcentaje de aceite en liquido incial es per=%lf\n",per);
	fprintf(datos1,"En la condicion inicial el aceite aparece distribuido aleatoriamente dentro de una gota semicircular de agua.\n");
	fprintf(datos1,"El resto del sistema inicialmente es aire.\n");
	fclose(datos1);
}

void midePosicionesDistancias(){
	int ind;
	double x_prom_aceite, z_prom_aceite;
	double x_prom_agua, z_prom_agua;
	x_prom_aceite=0.0;
	z_prom_aceite=0.0;
	x_prom_agua=0.0;
	z_prom_agua=0.0;
	for(ind=0;ind<N;ind++){
		if(C[ind]==2){
			x_prom_aceite=x_prom_aceite+getX(ind)*1.0;
			z_prom_aceite=z_prom_aceite+getZ(ind)*1.0;
		}
		if(C[ind]==1){
			x_prom_agua=x_prom_agua+getX(ind)*1.0;
			z_prom_agua=z_prom_agua+getZ(ind)*1.0;
		}
	}
	x_prom_aceite=x_prom_aceite/(numeroCeldasAceite*1.0);
	z_prom_aceite=z_prom_aceite/(numeroCeldasAceite*1.0);
	fprintf(fp2,"%ld\t%lf\t%lf\n",k,x_prom_aceite,z_prom_aceite);
	x_prom_agua=x_prom_agua/(numeroCeldasAgua*1.0);
	z_prom_agua=z_prom_agua/(numeroCeldasAgua*1.0);
	fprintf(fp3,"%ld\t%lf\t%lf\n",k,x_prom_agua,z_prom_agua);
	fprintf(fp5,"%ld\t%lf\t%lf\n",k,sqrt(pow(x_prom_aceite-x_prom_agua,2.0)+pow(z_prom_aceite-z_prom_agua,2.0)),x_prom_aceite-x_prom_agua);
}

void mideBordeGota(){
	fprintf(fp4,"%d\n",x_droplet);
}

void mideSuperficie(){
	int ind_x,ind_y,ind;
	int numAire, numAgua, numAceite;
	numAire=0;
	numAgua=0;
	numAceite=0;
	for(ind_x=0;ind_x<Lx;ind_x++){
		for(ind_y=(Ly-1);ind_y>(-1);ind_y--){
			ind=ind_x+Lx*ind_y;
			//printf("%d\t%d\t%d\n",ind_x,ind_y,ind);
			//printf("%d\n",C[ind]);
			if(C[ind]==1){
				numAgua++;
				break;
			}
			if(C[ind]==2){
				numAceite++;
				break;
			}
		}
		//Si recorremos toda la columna y no hay ni agua ni aceite
	}
	numAire=Lx-numAgua-numAceite;
	fprintf(fp6,"%ld\t%d\t%d\t%d\n",k,numAire,numAgua,numAceite);
}

void mideExtraccionAceite(){
	int acum,indd,ind_x,ind_y;
	double p;
	// Mide cuando un porcentaje p del aceite está a la izq de la linea xB
	// Primero medimos cuantas celdas de acite hay a la izq de la xB
	acum=0;
	for(ind_x=0;ind_x<x_droplet;ind_x++){
		for(ind_y=0;ind_y<Ly;ind_y++){
			indd=ind_x+ind_y*Lx;
			if(C[indd]==2){
				acum++;
			}
		}
	}
	p=(acum*1.0)/numeroCeldasAceite;
	if(!aceite5medidoQ){
		if(p>0.05){
			fprintf(fp7,"%d\t%ld\n",5,k);
			aceite5medidoQ=true;
		}
	}
	if(!aceite10medidoQ){
		if(p>0.1){
			fprintf(fp7,"%d\t%ld\n",10,k);
			aceite10medidoQ=true;
		}
	}
	if(!aceite15medidoQ){
		if(p>0.15){
			fprintf(fp7,"%d\t%ld\n",15,k);
			aceite15medidoQ=true;
		}
	}
	if(!aceite20medidoQ){
		if(p>0.2){
			fprintf(fp7,"%d\t%ld\n",20,k);
			aceite20medidoQ=true;
		}
	}
	if(!aceite25medidoQ){
		if(p>0.25){
			fprintf(fp7,"%d\t%ld\n",25,k);
			aceite25medidoQ=true;
		}
	}
	if(!aceite30medidoQ){
		if(p>0.3){
			fprintf(fp7,"%d\t%ld\n",30,k);
			aceite30medidoQ=true;
		}
	}
	if(!aceite35medidoQ){
		if(p>0.35){
			fprintf(fp7,"%d\t%ld\n",35,k);
			aceite35medidoQ=true;
		}
	}
	if(!aceite40medidoQ){
		if(p>0.4){
			fprintf(fp7,"%d\t%ld\n",40,k);
			aceite40medidoQ=true;
		}
	}
	if(!aceite45medidoQ){
		if(p>0.45){
			fprintf(fp7,"%d\t%ld\n",45,k);
			aceite45medidoQ=true;
		}
	}
	if(!aceite50medidoQ){
		if(p>0.5){
			fprintf(fp7,"%d\t%ld\n",50,k);
			aceite50medidoQ=true;
		}
	}
}

void mideExtraccionAceite2(){
	int indd;
	int contador;
	double thre, frac;
	/*
	// medida antigua que busca un film de aceite
	if(!aceiteExtracionmedidoQ){
		for(indd=0;indd<x_droplet;indd++){			
			if(C[indd]!=2){
				//Si no es aceite para y vete
				break;
			}
			if(indd==(x_droplet-1)){//Si llega aquí sin salirse es que la capa de aceite se ha formado entre 0 y xB
				aceiteExtracionmedidoQ=true;
				fprintf(fp8,"%ld\n",k);
			}
		}
	}
	*/
	contador=x_droplet;
	thre=0.8;// 80%
	if(!aceiteExtracionmedidoQ){
		// si no hemos medido ya
		// buscamos un porcentaje de 80% de aceite a la izq de xB
		for(indd=0;indd<x_droplet;indd++){			
			if(C[indd]!=2){
				//Si no es aceite resta
				contador--;
			}
		}
		frac=(contador*1.0)/x_droplet;//fraccion de celdas de aceite
		if(frac>thre){
			aceiteExtracionmedidoQ=true;
			fprintf(fp8,"%ld\n",k);
		}
	}
}

void midePorcentajeAceiteEnGota(){
	int ind;
	int celdasAceite;
	int celdasAgua;
	double ratio;
	celdasAceite=0;
	celdasAgua=0;
	for(ind=0;ind<N;ind++){
		//Recorremos todas las celdas
		if(getX(ind)>x_droplet){
			//Si esta a la derecha del borde xB es que pertenece a la gota macroscopica
			if(C[ind]==1){
				celdasAgua++;
			} else if(C[ind]==2){
				celdasAceite++;
			}
		}
	}
	ratio=celdasAceite*1.0/(celdasAceite+celdasAgua);
	fprintf(fp9,"%ld\t%lf\n",k,ratio);
}


void abreArchivos(){
	snprintf(nombre,sizeof(nombre),"Salida_Aceite_%lld.dat",sem);
	fp2=fopen(nombre,"a");
	snprintf(nombre,sizeof(nombre),"Salida_Agua_%lld.dat",sem);
	fp3=fopen(nombre,"a");
	snprintf(nombre,sizeof(nombre),"Salida_Borde_%lld.dat",sem);
	fp4=fopen(nombre,"a");
	snprintf(nombre,sizeof(nombre),"Salida_Distancia_%lld.dat",sem);
	fp5=fopen(nombre,"a");
	snprintf(nombre,sizeof(nombre),"Salida_Superficie_%lld.dat",sem);
	fp6=fopen(nombre,"a");
	snprintf(nombre,sizeof(nombre),"Salida_ExtraccionAceitePorcentaje_%lld.dat",sem);
	fp7=fopen(nombre,"a");
	snprintf(nombre,sizeof(nombre),"Salida_ExtraccionAceiteFilm_%lld.dat",sem);
	fp8=fopen(nombre,"a");
	snprintf(nombre,sizeof(nombre),"Salida_PorcentajeAceiteEnGota_%lld.dat",sem);
	fp9=fopen(nombre,"a");
}

void cierraArchivos(){
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	fclose(fp6);
	fclose(fp7);
	fclose(fp8);
	fclose(fp9);
}
