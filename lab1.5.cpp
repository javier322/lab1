

# include <stdio.h>
# include <stdlib.h>

int ***generarMatriz(int *cursor, int *final ,int *numF,int *numC,char nombre[]);
int buscarImagen(int ***m1,int ***m2,int numF,int numF2,int numC,int numC2);
int encontrarImagen(int ***m1, int ***m2,int numF,int numF2,int numC,int numC2);
int comparar(int m[3],int m2[3]);
int ***voltearImagen(int ***m,int *fila,int *columnas);

int main(){
	

	int cursor;
	int final;
	int nf,nc,np;
	int numFp;
	int numCp;
	
	int ***imagen;
	int ***imagenB;
	
	int busqueda;
	int numImagen;
	FILE *archivo;

	
	int numF,numC;	
	char nombre[]="ejemplo.txt";
	char nombre2[]="ejempl2.txt";
	
	archivo=fopen("resultado.txt","w");
	numImagen=1;
	busqueda=0;
	cursor=0;
	final=0;
	
	imagen = generarMatriz(&cursor,&final,&numF,&numC,nombre);
	numFp=numF;
	numCp=numC;
	cursor =0;
	final=0;
	while(final!=1){
		imagenB=generarMatriz(&cursor,&final,&numF,&numC,nombre2);
	
		if(imagenB==0){
			free(imagen);
			free(imagenB);
			break;
		}


		busqueda=buscarImagen(imagen,imagenB,numFp,numF,numCp,numC);
		if(busqueda==1){
			fprintf(archivo,"imagen %i",numImagen);
			fprintf(archivo,"%s"," :encontrada\n");
			numImagen++;

		}
		else{
			fprintf(archivo,"imagen %i",numImagen);
			fprintf(archivo,"%s"," :No encontrada\n");
			numImagen++;
			
		}
		
		free(imagenB);
		
	}
	fclose(archivo);
	printf("El programa se ejecuto correctamente");
	return 0;
}




int ***generarMatriz(int *cursor,int *final, int *numF, int *numC,char nombre[]){
	

	int numFilas;
	int numColumnas;
	int ***m;
	
	char cadena[4];
	char caracter;
	char numMatrizf[100];
	char numMatrizc[100];
	int nf,nc,np,i;
	int numero;
	
	FILE *archivo;
	archivo=fopen(nombre,"r");
	if(archivo==NULL){
		printf("El archivo no existe");
		exit(1);
	}
	
	i=0;

	while(i<*cursor){
		
	
		if(feof(archivo)!=0){
			*final=1;
			return 0;
		}
		fgetc(archivo);
		i=1+i;
	}
	
	
	caracter=fgetc(archivo);
	numMatrizf[0]=caracter;
	++*cursor;
	i=1;
	while(caracter!=32){
		
		caracter=fgetc(archivo);
		if(caracter==32){
			break;
		}
		numMatrizf[i]=caracter;
	
		++*cursor;
		i++;
	}
	++*cursor;
	numFilas=atoi(numMatrizf);
	
	
	caracter=fgetc(archivo);
	numMatrizc[0]=caracter;
	i=1;
	++*cursor;
	while(caracter!=10){
		
		
		caracter=fgetc(archivo);
		if(caracter==10){
			break;
		}
		numMatrizc[i]=caracter;

	
		++*cursor;
		i++;
	}
	++*cursor;
	numColumnas=atoi(numMatrizc);
	

	i=0;
	
	m=(int***)malloc(numFilas*sizeof(int**));
	if(m==NULL){
		printf("No se pudo reservar espacion en la memoria");
		exit(1);
	}
	
	for(nf=0;nf<numFilas;nf++){
		m[nf]=(int**)malloc(numColumnas*sizeof(int*));
		if(m[nf]==NULL){
			printf("No se pudo reservar espacio en la memoria");
			exit(1);	
		
		}
	}

	
	for(nf=0;nf<numFilas;nf++){
		for(nc=0;nc<numColumnas;nc++){
			m[nf][nc]=(int*)malloc(3*sizeof(int));
			if(m[nf][nc]==NULL){
				printf("No se pudo reservar espacio en la memoria");
				exit(1);
			}	
		}
	}
	

	
	
	nf=0;
	nc=0;
	np=0;
	i=0;
	
	while(feof(archivo)==0 && caracter!=45){
		caracter=fgetc(archivo);
		
		*cursor=*cursor+1;
	
		if(nf>=numFilas){
			break;
		}
		else if(caracter==44){
			cadena[3]='\0';
			numero=atoi(cadena);
			m[nf][nc][np]=numero;
			
			i=0;
			np++;
			
			cadena[0]=34;
			cadena[1]=34;
			cadena[2]=34;
			
		}
		else if(caracter==32){
			
			numero=atoi(cadena);
			m[nf][nc][np]=numero;
			
			i=0;
			np=0;
			nc++;
			cadena[0]=34;
			cadena[1]=34;
			cadena[2]=34;
			
		}
		else if(caracter==10){
			numero=atoi(cadena);
			m[nf][nc][np]=numero;
			
			nf++;
			nc=0;
			i=0;
			np=0;
			cadena[0]=34;
			cadena[1]=34;
			cadena[2]=34;
		}
		else{
			cadena[i]=caracter;
			i++;
		}
		
		
	}
	
	if(nf<numFilas){
		numero=atoi(cadena);
		m[nf][nc][np]=numero;
	}
	
	fclose(archivo);
	
	
	
	
	i=0;
	while(i<5){
		*cursor=*cursor+1;
		i++;
	}
	
	*numF=numFilas;
	*numC=numColumnas;
	
	return m;
	
}

int buscarImagen(int ***m1,int ***m2,int numF,int numF2,int numC,int numC2){
	
	int busqueda;
	int i;
	
	i=0;
	busqueda=encontrarImagen(m1,m2,numF,numF2,numC,numC2);
		if(busqueda==1){
		return 1;
			
		}

	while(i<3){
		if(busqueda==1){
			return 1;
			
		}
		m2=voltearImagen(m2,&numF2,&numC2);
		busqueda=encontrarImagen(m1,m2,numF,numF2,numC,numC2);
		i++;
		if(busqueda==1){
			return 1;
			
		}
		
	}
	return 0;
}









int encontrarImagen(int ***m1, int ***m2,int numF,int numF2,int numC,int numC2){

	int cursor[2];
	int nf,nc;
	int nf2,nc2;
	int comparacion;
	
	nf=0;
	nc=0;
	nf2=0;
	nc2=0;
	cursor[0]=0;
	cursor[1]=0;
	comparacion=0;

	while(nf<numF){
		
		comparacion=comparar(m1[nf][nc],m2[nf2][nc2]);
	
		if( comparacion==1){
			
			cursor[0]=nf;
			cursor[1]=nc;
			nc++;
			
			while(comparacion==1){
			
				nc2++;
				
				if(nc2>=numC2){
					nf++;
					nc=cursor[1];
					nf2++;
					nc2=0;
					
				}
				if(nf2>=numF2){
					return 1;
				}
				
				if(nc>=numC){
					nf++;
					nc=cursor[1];
				}
				if(nf>=numF){
					break;
				}
				comparacion=comparar(m1[nf][nc],m2[nf2][nc2]);
				nc++;
			}
			
			nf=cursor[0];
			nc=cursor[1]+1;
			nc2=0;
			nf2=0;
			if(nc>=numC){
				nf++;
				nc=0;
			}
		}
		
		else{
			nc++;
			if(nc>=numC){
				nf++;
				nc=0;
			}	
		}
	}
		
		return 0;
}
	
	
	
	
	
	
int comparar(int m[3],int m2[3]){

	int i;
	for(i=0;i<3;i++){
	
		if(m[i]!=m2[i]){
			return 0;
		}
	}
	return 1;
}

int ***voltearImagen(int ***imagen,int *filas,int *columnas){
	int ***m;
	int nf,nc,np;
	int nf2,nc2;
	int aux;
	
	
	
	m=(int***)malloc(*columnas*sizeof(int**));
	if(m==NULL){
		printf("No se pudo reservar espacion en la memoria");
		exit(1);
	}
	
	for(nf=0;nf<*columnas;nf++){
		m[nf]=(int**)malloc(*filas*sizeof(int*));
		if(m[nf]==NULL){
			printf("No se pudo reservar espacio en la memoria");
			exit(1);	
		
		}
	}

	
	for(nf=0;nf<*columnas;nf++){
		for(nc=0;nc<*filas;nc++){
			m[nf][nc]=(int*)malloc(3*sizeof(int));
			if(m[nf][nc]==NULL){
				printf("No se pudo reservar espacio en la memoria");
				exit(1);
			}	
		}
	}

	
	nf=0;
	nc=0;
	nf2=0;
	nc2=*columnas;	
	
	while (nc2!=0){
		if(nf2>=*filas){
			nc2--;
			nf++;
			nf2=0;
			nc=0;
		}
		if(nc2==0){
			break;
		}
		m[nf][nc]=imagen[nf2][nc2-1];
		nc++;
		nf2++;
	}
	
	aux=*columnas;
	*columnas=*filas;
	*filas=aux;
	return m;
}
