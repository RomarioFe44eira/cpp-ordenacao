#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Randomico1000000.txt
//Randomico750000.txt
//Randomico500000.txt

//Invertido1000000.txt
//Invertido750000.txt
//Invertido500000.txt

//Ordenado1000000.txt
//Ordenado750000.txt
//Ordenado500000.txt

#define CASO "Invertido"
#define BASE_DIR "c:\\test\\Randomico750000.txt"
#define DIR_LOG "c:\\test\\LogPerformace.txt"

int bubbleSort(int *vetor, int tamanho);
int insertSort_test(int *vetor, int tamanho)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                0;
int selectSort(int *vetor, int tamanho);
int shellSort(int *vetor, int tamanho);
int performLog(char *algoritmo, int tamanho, double tempo);

double calculaTempo(int tempoInicial, int tempoFinal){
	return ((double)(tempoFinal - tempoInicial)*1000)/CLOCKS_PER_SEC;
}
int performLog(char *algoritmo, int tamanho, double tempo){
	
	
	FILE *arquivo;	
	arquivo = fopen(DIR_LOG, "a");
	fprintf(arquivo, "Algoritmo: %s Sort | Tamanho:%d rows | Tempo: %.2f Milisegundos | %s \n", algoritmo, tamanho, tempo, CASO);	
	printf("Arquivo de log foi atualizado!.\n");
	return 0;
}
int existeArquivo(char *nome){
	FILE *arquivo;
	arquivo = fopen(nome, "r" );
	if(arquivo){
		fclose(arquivo);
		return 1;
	}
	return 0;
}
int menuPrincipal(){
    int escolha = 0;
    do{        
        printf("Ordenar por: \n");
        printf("1 - Bubble Sort\n");
        printf("2 - Insertion Sort\n");
        printf("3 - Selection Sort\n");
		printf("4 - Shell Sort\n");
        printf("5 - Cancelar\n\n");
        printf("Informe sua escolha: ");
        scanf("%d", &escolha);
    }while(escolha <0 && escolha > 5);
    return escolha;      
}

//ALGORITMOS DE ORDENAÇÃO.
int bubbleSort(int *vetor, int tamanho){    
	int i, continua, aux, rows = tamanho;
	clock_t tempoInicial, tempoFinal;   
    double tempo_gasto;		
	
    tempoInicial = clock();
    do{
        continua = 0;
        for(i = 0; i < tamanho-1; i++){
            if(vetor[i] > vetor[i+1]){
                aux = vetor[i];
                vetor[i] = vetor[i+1];
                vetor[i+1] = aux;                
                continua = i;
            }
        }
        tamanho--;
    }while(continua != 0);
    tempoFinal = clock();
	
    tempo_gasto = calculaTempo(tempoInicial, tempoFinal);	
	performLog("Bubble", rows, tempo_gasto);
    
	for(i = 0; i < tamanho; i++){       
        printf("%d\n", vetor[i]);
    }     
    printf("Rows: %d | Tempo Decorrido: %.2f ms", rows, tempo_gasto);         
    return 0;
}
int insertSort_test(int *vetor, int tamanho){
	
	int i, j, aux, rows = tamanho;
	
	clock_t tempoInicial, tempoFinal; 
	double tempo_gasto;
    
	tempoInicial = clock();    
	for(i = 1; i < tamanho; i++){
        aux = vetor[i];		
        for(j = i; (j > 0) && (aux < vetor[j-1]); j--)
            vetor[j] = vetor[j-1];        
        vetor[j] = aux;
    }
	tempoFinal = clock();
	tempo_gasto = calculaTempo(tempoInicial, tempoFinal);
	performLog("Insertion", rows, tempo_gasto);
	for(i=0; i < tamanho; i++){
		printf("%d\n", vetor[i]); 
	}   	
    
	printf("Rows: %d\t| Tempo Decorrido: %.2f Milisegundos", rows, tempo_gasto);
	return 0;
}
int selectionSort(int *vetor, int tamanho){
	int i, j, menor, troca, rows = tamanho;
	
	clock_t tempoInicial, tempoFinal;   
    double tempo_gasto;	
    tempoInicial = clock();
	
	for(i==0; i < tamanho-1;i++){
		menor = i;
		for(j = i+1; j<tamanho; j++){
			if(vetor[j] < vetor[menor])
				menor = j;
		}
		if(i != menor){
			troca = vetor[i];
			vetor[i] = vetor[menor];
			vetor[menor] = troca;
		}
	}
	tempoFinal = clock();
	tempo_gasto = calculaTempo(tempoInicial, tempoFinal);	
	performLog("Selection", rows, tempo_gasto);
	printf("O processo de ordenacao por selection Sort foi concluido com sucesso.");
	return 0;
}
int shellSort(int *vetor, int tamanho){
    
    int i , j , gap, valor, rows = tamanho; 
	
	clock_t tempoInicial, tempoFinal;   
    double tempo_gasto;	
    tempoInicial = clock();
	
    for (gap = tamanho/2; gap > 0; gap /= 2){
        for (i = gap; i < tamanho; i++){
            for (j = i-gap; j >= 0 && vetor[j] > vetor[j+gap]; j-=gap){
                valor = vetor[j+gap];
                vetor[j+gap] = vetor[j];
                vetor[j] = valor;
            }
		}	
	}
	tempoFinal = clock();
	tempo_gasto = calculaTempo(tempoInicial, tempoFinal);	
	performLog("Shell", rows, tempo_gasto);	
    return 0;
}

int main(){
	char dir[255];			
    do{
        printf("Informe o diretorio do arquivo a ser Ordenado: ");
        gets(dir);
        if(strlen(dir) == 0){            
            strcpy(dir, BASE_DIR);
        }       
        existeArquivo(dir) != 1 ?printf("Diretorio do arquivo invalido!\n"): printf("Arquivo localizado..\n");            
    }while(existeArquivo(dir) != 1);
	
	FILE *ptr_arquivo = NULL;
	ptr_arquivo = fopen(dir, "r");
	(!ptr_arquivo)?printf("Erro ao abrir o arquivo!\n"):printf("Arquivo Aberto com sucesso para leitura.\n");
	
	
	int fileSizeRows = 0, *vetor, i;
    char aux[25];

    while(fgets(aux, sizeof(aux), ptr_arquivo) != NULL){ 
		fileSizeRows++;
	}

	vetor = (int *) calloc(fileSizeRows, sizeof(int));
	rewind(ptr_arquivo);
	
    for(i = 0; i < fileSizeRows; i++){
		fgets(aux, sizeof(aux), ptr_arquivo);
		vetor[i] = atoi(aux);
	}	
	
	switch(menuPrincipal()){
        case 1:		
			bubbleSort(vetor, fileSizeRows);		
		break;
        
		case 2:			
			insertSort_test(vetor,fileSizeRows);		
		break;       
		
		case 3:
		selectionSort(vetor,fileSizeRows);
		break;
		case 4:
		shellSort(vetor,fileSizeRows);
		break;
		case 5:
			printf("Cancelamento solicitado.\n");
			exit(1);
		break;
		
    }   
	fclose(ptr_arquivo);
    return 0;
}