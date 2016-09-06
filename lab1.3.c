# include <stdio.h>
# include <stdlib.h>

int ***generarMatriz(int *cursor, int *final ,int *numF,int *numC,char nombre[]);
int comparar(int *m,int *m2);

int main(){
	

	int cursor;
	int final;
	int nf,nc,np;
	int numFp;
	int numCp;
	
	int ***imagen;
	int ***imagenB;
	
	int numF,numC;	
	char nombre[]="ejemplo.txt";
	char nombre2[]="ejempl2.txt";
	
	cursor=0;
	final=0;
	
	imagen = generarMatriz(&cursor,&final,&numF,&numC,nombre);
	numFp=numF;
	numCp=numC;
	cursor =0;
	final=0;
	printf("\n-------------------------\n");
	while(final!=1){
		imagenB=generarMatriz(&cursor,&final,&numF,&numC,nombre2);
	
		if(imagenB==0){
			free(imagen);
			free(imagenB);
			break;
		}
		
		for(nf=0;nf<numF;nf++){
			for(nc=0;nc<numC;nc++){
				for(np=0;np<3;np++){
					printf("%i,",imagenB[nf][nc][np]);
				}
				printf(" ");
		
			}
			printf("\n");
		}
		printf("\n-------------------------\n");
		
		comparar(imagen[0][0],imagenB[0][0]); 
		
		
		free(imagenB);
		
	}
	return 0;
}

int comparar(int m[3],int m2[3]){
	int i;
	for(i=0;i<3;i++){
		printf("%i y %i \n",m[i],m2[i]);
	}
	return 0;
}

int ***generarMatriz(int *cursor,int *final, int *numF, int *numC,char nombre[]){
	

	int numFilas;
	int numColumnas;
	int ***m;
	
	char t[3];
	char cadena[4];
	char caracter;
	
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
	
	i=0;
	
	while(i<3){
		
		caracter=fgetc(archivo);
		t[i]=caracter;
	
		*cursor=*cursor+1;
		i++;
	}

	
	numFilas=(int)(t[0]-48);
	numColumnas=(int)(t[2]-48);

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
	
	/*while(nf<numFilas){
		if(nc=numColumnas){
			nc=0;
			nf++;
		}
		
		m[nf][nc]=(int*)malloc(3*sizeof(int));
		if(m[nf][nc]==NULL){
			printf("No se pudo reservar espacio en la memoria");
			exit(1);
		}
		nc++;
	}*/
	
	fgetc(archivo);
	

	*cursor=*cursor+1;
	
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
	
	for(nf=0;nf<numFilas;nf++){
		for(nc=0;nc<numColumnas;nc++){
			for(np=0;np<3;np++){
				printf("%i,",m[nf][nc][np]);
			}
			printf(" ");
		
		}
		printf("\n");
	}
	
	
	*numF=numFilas;
	*numC=numColumnas;
	
	return m;
	
}
