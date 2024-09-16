#include <stdio.h>
#include <stdlib.h>

FILE *fpin, *f2pin, *fpoutinter;
int **imagemR1, **imagemG1, **imagemB1, **imagemR2, **imagemG2, **imagemB2;
int ncol1, nlin1, quantizacao1, ncol2, nlin2, quantizacao2;

void abrir_arquivos(int argc, char *argv[]);
void ler_cabecalho1(void);
void ler_cabecalho2(void);
void ler_imagem1(void);
void ler_imagem2(void);
void criararqimagensitermediarias(int num);
void gravar_imageminter(float t, int num);
void fechar_arquivos(void);

void abrir_arquivos(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("Modo correto de uso: <prog> <imagemIn1> <imagemIn2>\n");
        exit(0);
    }
    if ((fpin = fopen(argv[1], "r")) == NULL) {
        printf("Nao foi possivel abrir arquivo de imagem %s\n", argv[1]);
        exit(1);
    }
    if ((f2pin = fopen(argv[2], "r")) == NULL) {
        printf("Nao foi possivel abrir arquivo de imagem %s\n", argv[2]);
        exit(1);
    }
}

void criararqimagensitermediarias(int num) {
    char nomeimagem[30];
    sprintf(nomeimagem, "Imageminter%d.ppm", num);
    if ((fpoutinter = fopen(nomeimagem, "w")) == NULL) {
        printf("Nao foi possivel abrir arquivo de saida imageminter\n");
        exit(1);
    }
}

void ler_imagem1(void) {
    int cont, col, lin;
    imagemR1= (int **)malloc((nlin1+1)*sizeof(int *));
    imagemG1= (int **)malloc((nlin1+1)*sizeof(int *));
    imagemB1= (int **)malloc((nlin1+1)*sizeof(int *));
    for (cont=0;cont<nlin1;cont++) {
      imagemR1[cont]=(int *)malloc(ncol1*sizeof(int));
      if (imagemR1[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
        printf("Falha na alocacao de memoria - 1\n");
        exit(1);
      }
      imagemG1[cont]=(int *)malloc(ncol1*sizeof(int));
      if (imagemG1[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
        printf("Falha na alocacao de memoria - 1\n");
        exit(1);
      }
      imagemB1[cont]=(int *)malloc(ncol1*sizeof(int));
      if (imagemB1[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
        printf("Falha na alocacao de memoria - 1\n");
        exit(1);
      }
    }
    for (lin=0;lin<nlin1;lin++) {
      for (col=0;col<ncol1;col++) {
        fscanf(fpin,"%d ",&imagemR1[lin][col]);
        fscanf(fpin,"%d ",&imagemG1[lin][col]);
        fscanf(fpin,"%d ",&imagemB1[lin][col]);
      }
    }
  } 

void ler_imagem2(void) {
    int cont, col, lin;
    imagemR2= (int **)malloc((nlin2+1)*sizeof(int *));
    imagemG2= (int **)malloc((nlin2+1)*sizeof(int *));
    imagemB2= (int **)malloc((nlin2+1)*sizeof(int *));
    for (cont=0;cont<nlin2;cont++) {
      imagemR2[cont]=(int *)malloc(ncol2*sizeof(int));
      if (imagemR2[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
        printf("Falha na alocacao de memoria - 1\n");
        exit(1);
      }
      imagemG2[cont]=(int *)malloc(ncol2*sizeof(int));
      if (imagemG2[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
        printf("Falha na alocacao de memoria - 1\n");
        exit(1);
      }
      imagemB2[cont]=(int *)malloc(ncol2*sizeof(int));
      if (imagemB2[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
        printf("Falha na alocacao de memoria - 1\n");
        exit(1);
      }
    }
    for (lin=0;lin<nlin2;lin++) {
      for (col=0;col<ncol2;col++) {
        fscanf(f2pin,"%d ",&imagemR2[lin][col]);
        fscanf(f2pin,"%d ",&imagemG2[lin][col]);
        fscanf(f2pin,"%d ",&imagemB2[lin][col]);
      }
    }
  }

void gravar_imageminter(float t, int num) {
    int lin, col;
    criararqimagensitermediarias(num);
    fprintf(fpoutinter, "P3\n");
    fprintf(fpoutinter, "%d %d\n", ncol1, nlin1);
    fprintf(fpoutinter, "%d\n", quantizacao1);

    for (lin = 0; lin < nlin1; lin++) {
        for (col = 0; col < ncol1; col++) {
            int r = (1 - t) * imagemR1[lin][col] + t * imagemR2[lin][col];
            int g = (1 - t) * imagemG1[lin][col] + t * imagemG2[lin][col];
            int b = (1 - t) * imagemB1[lin][col] + t * imagemB2[lin][col];
            fprintf(fpoutinter, "%d %d %d ", r, g, b);
        }
        fprintf(fpoutinter, "\n");
    }
    fclose(fpoutinter);
}

void ler_cabecalho1(void) {
    char controle[4];
    fscanf(fpin, "%s\n", controle);
    fscanf(fpin, "%d %d\n", &ncol1, &nlin1);
    fscanf(fpin, "%d\n", &quantizacao1);
}

void ler_cabecalho2(void) {
    char controle[4];
    fscanf(f2pin, "%s\n", controle);
    fscanf(f2pin, "%d %d\n", &ncol2, &nlin2);
    fscanf(f2pin, "%d\n", &quantizacao2);
}

void fechar_arquivos(void) {
    fclose(fpin);
    fclose(f2pin);
}

int main(int argc, char *argv[]) {
    float t = 0.0;
    int contador_imagens = 1;
    
    abrir_arquivos(argc, argv);
    ler_cabecalho1();
    ler_cabecalho2();
    ler_imagem1();
    ler_imagem2();

    for (t = 0.0; t <= 1.0; t += 0.05) {
        gravar_imageminter(t, contador_imagens);
        contador_imagens++;
    }

    fechar_arquivos();
    return 0;
}
