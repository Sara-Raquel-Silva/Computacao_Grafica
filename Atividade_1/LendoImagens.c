#include <stdio.h>
#include <stdlib.h>

FILE *fpin, *fpoutR, *fpoutG, *fpoutB;
int **imagemR, **imagemG, **imagemB, ncol, nlin, quantizacao;

void abrir_arquivos(int argc, char *argv[]);
void ler_cabecalho(void);
void ler_imagem(void);

void fechar_arquivos(void);

void abrir_arquivos(int argc, char *argv[]) {
     if (argc  <=1) {
	    printf("Modo correto de uso: <prog> <imagemIn> <imagemOut>\n");
	    exit(0);
     }
     if ((fpin=fopen(argv[1],"r"))==NULL) {
	    printf("Nao foi possivel abrir arquivo de imagem %s\n", argv[1]);
	    exit(1);
     }
    if ((fpoutR=fopen("ImagemR.ppm","w"))==NULL) {
        printf("Nao foi possivel abrir arquivo de saida R\n" );
        exit(1);
     }
     if ((fpoutG=fopen("ImagemG.ppm","w"))==NULL) {
        printf("Nao foi possivel abrir arquivo de saida G\n");
        exit(1);
     }
     if ((fpoutB=fopen("ImagemB.ppm","w"))==NULL) {
        printf("Nao foi possivel abrir arquivo de saida B\n");
        exit(1);
     }

}

void ler_imagem(void) {
  int cont, col, lin;
  imagemR= (int **)malloc((nlin+1)*sizeof(int *));
  imagemG= (int **)malloc((nlin+1)*sizeof(int *));
  imagemB= (int **)malloc((nlin+1)*sizeof(int *));
  for (cont=0;cont<nlin;cont++) {
    imagemR[cont]=(int *)malloc(ncol*sizeof(int));
    if (imagemR[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
    imagemG[cont]=(int *)malloc(ncol*sizeof(int));
    if (imagemG[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
    imagemB[cont]=(int *)malloc(ncol*sizeof(int));
    if (imagemR[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
  }
  for (lin=0;lin<nlin;lin++) {
    for (col=0;col<ncol;col++) {
      fscanf(fpin,"%d ",&imagemR[lin][col]);
      fscanf(fpin,"%d ",&imagemG[lin][col]);
      fscanf(fpin,"%d ",&imagemB[lin][col]);
    }
  }
} 

void ler_cabecalho(void) {
     char controle[4];
     fscanf(fpin,"%s\n",controle);
     fscanf(fpin,"%d %d\n",&ncol,&nlin);
     fscanf(fpin,"%d\n",&quantizacao);
} 

void fechar_arquivos(void) {
  fclose(fpin);
  fclose(fpoutR);
  fclose(fpoutG);
  fclose(fpoutB);
} 

int main(int argc, char *argv[]) {
  abrir_arquivos(argc,argv);
  ler_cabecalho();
  ler_imagem();
  return 0;
}
