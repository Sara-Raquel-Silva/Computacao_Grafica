#include <stdio.h>
#include <stdlib.h>

// Declaração de variáveis globais para os arquivos e matrizes de imagens
FILE *fpin, *f2pin, *fpoutinter; 
int **imagemR1, **imagemG1, **imagemB1, **imagemR2, **imagemG2, **imagemB2; 
int ncol1, nlin1, quantizacao1, ncol2, nlin2, quantizacao2; // Dimensões e níveis de quantização das imagens

// Declaração das funções utilizadas
void abrir_arquivos(int argc, char *argv[]);
void ler_cabecalho1(void);
void ler_cabecalho2(void);
void ler_imagem1(void);
void ler_imagem2(void);
void criararqimagensitermediarias(int num);
void gravar_imageminter(float t, int num);
void fechar_arquivos(void);

// Função para abrir os arquivos de entrada (duas imagens)
void abrir_arquivos(int argc, char *argv[]) {
    // Verifica se o número de argumentos está correto
    if (argc <= 2) {
        printf("Modo correto de uso: <prog> <imagemIn1> <imagemIn2>\n");
        exit(0);
    }
    // Abre o primeiro arquivo de imagem para leitura
    if ((fpin = fopen(argv[1], "r")) == NULL) {
        printf("Nao foi possivel abrir arquivo de imagem %s\n", argv[1]);
        exit(1);
    }
    // Abre o segundo arquivo de imagem para leitura
    if ((f2pin = fopen(argv[2], "r")) == NULL) {
        printf("Nao foi possivel abrir arquivo de imagem %s\n", argv[2]);
        exit(1);
    }
}

// Função para criar um arquivo de imagem intermediária
void criararqimagensitermediarias(int num) {
    char nomeimagem[30]; // Nome do arquivo de imagem
    sprintf(nomeimagem, "Imageminter%d.ppm", num); // Nomeia o arquivo sequencialmente
    // Abre o arquivo de saída para escrita
    if ((fpoutinter = fopen(nomeimagem, "w")) == NULL) {
        printf("Nao foi possivel abrir arquivo de saida imageminter\n");
        exit(1);
    }
}

// Função para ler os dados da primeira imagem
void ler_imagem1(void) {
    int cont, col, lin;
    // Aloca memória para as matrizes de pixels da imagem 1 (R, G, B)
    imagemR1= (int **)malloc((nlin1+1)*sizeof(int *));
    imagemG1= (int **)malloc((nlin1+1)*sizeof(int *));
    imagemB1= (int **)malloc((nlin1+1)*sizeof(int *));
    // Verifica se a memória foi alocada corretamente
    for (cont=0; cont<nlin1; cont++) {
        imagemR1[cont]=(int *)malloc(ncol1*sizeof(int));
        if (imagemR1[cont]==NULL) {
            printf("Falha na alocacao de memoria - 1\n");
            exit(1);
        }
        imagemG1[cont]=(int *)malloc(ncol1*sizeof(int));
        if (imagemG1[cont]==NULL) {
            printf("Falha na alocacao de memoria - 1\n");
            exit(1);
        }
        imagemB1[cont]=(int *)malloc(ncol1*sizeof(int));
        if (imagemB1[cont]==NULL) {
            printf("Falha na alocacao de memoria - 1\n");
            exit(1);
        }
    }
    // Lê os valores de cada pixel (R, G, B) da imagem 1
    for (lin=0; lin<nlin1; lin++) {
        for (col=0; col<ncol1; col++) {
            fscanf(fpin,"%d ",&imagemR1[lin][col]);
            fscanf(fpin,"%d ",&imagemG1[lin][col]);
            fscanf(fpin,"%d ",&imagemB1[lin][col]);
        }
    }
}

// Função para ler os dados da segunda imagem (mesmo processo que a função anterior)
void ler_imagem2(void) {
    int cont, col, lin;
    // Aloca memória para as matrizes de pixels da imagem 2 (R, G, B)
    imagemR2= (int **)malloc((nlin2+1)*sizeof(int *));
    imagemG2= (int **)malloc((nlin2+1)*sizeof(int *));
    imagemB2= (int **)malloc((nlin2+1)*sizeof(int *));
    // Verifica se a memória foi alocada corretamente
    for (cont=0; cont<nlin2; cont++) {
        imagemR2[cont]=(int *)malloc(ncol2*sizeof(int));
        if (imagemR2[cont]==NULL) {
            printf("Falha na alocacao de memoria - 1\n");
            exit(1);
        }
        imagemG2[cont]=(int *)malloc(ncol2*sizeof(int));
        if (imagemG2[cont]==NULL) {
            printf("Falha na alocacao de memoria - 1\n");
            exit(1);
        }
        imagemB2[cont]=(int *)malloc(ncol2*sizeof(int));
        if (imagemB2[cont]==NULL) {
            printf("Falha na alocacao de memoria - 1\n");
            exit(1);
        }
    }
    // Lê os valores de cada pixel (R, G, B) da imagem 2
    for (lin=0; lin<nlin2; lin++) {
        for (col=0; col<ncol2; col++) {
            fscanf(f2pin,"%d ",&imagemR2[lin][col]);
            fscanf(f2pin,"%d ",&imagemG2[lin][col]);
            fscanf(f2pin,"%d ",&imagemB2[lin][col]);
        }
    }
}

// Função para gravar uma imagem intermediária com base na interpolação entre duas imagens
void gravar_imageminter(float t, int num) {
    int lin, col;
    criararqimagensitermediarias(num); // Cria o arquivo de imagem intermediária
    // Escreve o cabeçalho da imagem (formato P3 do PPM)
    fprintf(fpoutinter, "P3\n");
    fprintf(fpoutinter, "%d %d\n", ncol1, nlin1);
    fprintf(fpoutinter, "%d\n", quantizacao1);
    
    // Interpolação dos pixels das duas imagens com o fator 't'
    for (lin = 0; lin < nlin1; lin++) {
        for (col = 0; col < ncol1; col++) {
            int r = (1 - t) * imagemR1[lin][col] + t * imagemR2[lin][col]; // Canal vermelho
            int g = (1 - t) * imagemG1[lin][col] + t * imagemG2[lin][col]; // Canal verde
            int b = (1 - t) * imagemB1[lin][col] + t * imagemB2[lin][col]; // Canal azul
            // Escreve os valores dos pixels interpolados no arquivo de saída
            fprintf(fpoutinter, "%d %d %d ", r, g, b);
        }
        fprintf(fpoutinter, "\n");
    }
    fclose(fpoutinter); // Fecha o arquivo de saída
}

// Função para ler o cabeçalho da primeira imagem
void ler_cabecalho1(void) {
    char controle[4];
    // Lê o formato do arquivo (P3), as dimensões e a quantização
    fscanf(fpin, "%s\n", controle);
    fscanf(fpin, "%d %d\n", &ncol1, &nlin1);
    fscanf(fpin, "%d\n", &quantizacao1);
}

// Função para ler o cabeçalho da segunda imagem (mesmo processo que a função anterior)
void ler_cabecalho2(void) {
    char controle[4];
    fscanf(f2pin, "%s\n", controle);
    fscanf(f2pin, "%d %d\n", &ncol2, &nlin2);
    fscanf(f2pin, "%d\n", &quantizacao2);
}

// Função para fechar os arquivos abertos
void fechar_arquivos(void) {
    fclose(fpin);  // Fecha o arquivo da primeira imagem
    fclose(f2pin); // Fecha o arquivo da segunda imagem
}

// Função principal
int main(int argc, char *argv[]) {
    float t = 0.0;
    int contador_imagens = 1; // Contador para as imagens intermediárias
    
    abrir_arquivos(argc, argv); // Abre os arquivos de entrada
    ler_cabecalho1(); // Lê o cabeçalho da primeira imagem
    ler_cabecalho2(); // Lê o cabeçalho da segunda imagem
    ler_imagem1(); // Lê a primeira imagem
    ler_imagem2(); // Lê a segunda imagem

    // Loop para gerar imagens intermediárias com diferentes valores de t (de 0.0 a 1.0)
    for (t = 0.0; t <= 1.0; t += 0.01) {
        gravar_imageminter(t, contador_imagens); // Grava a imagem interpolada
        contador_imagens++; // Incrementa o contador de imagens
    }

    fechar_arquivos(); // Fecha os arquivos abertos
    return 0;
}
