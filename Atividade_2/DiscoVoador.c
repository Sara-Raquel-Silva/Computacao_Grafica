#include <GL/glut.h>
#include <math.h> 

// Função para desenhar uma elipse (usada para o disco voador e outros elementos)
void dEllipse(float cx, float cy, float rx, float ry) {
    int num_segments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);  // Centro da elipse
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * M_PI * (float)i / (float)num_segments;  // Ângulo atual
        float x = rx * cosf(theta);  // Componente x
        float y = ry * sinf(theta);  // Componente y
        glVertex2f(x + cx, y + cy);  // Posição do vértice
    }
    glEnd();
}

// Função para desenhar o sol
void dSol() {
    float x = 0.8f;  // Posição do sol no eixo x
    float y = 0.8f;  // Posição do sol no eixo y
    float radius = 0.1f;

    glBegin(GL_TRIANGLE_FAN);  // Desenhar o sol com triângulos
    glColor3f(1.0f, 1.0f, 0.0f);  // Cor amarela
    glVertex2f(x, y);  // Centro do círculo
    for (int i = 0; i <= 36; i++) {
        float angle = i * 2.0f * M_PI / 36;
        float dx = radius * cos(angle);
        float dy = radius * sin(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

// Função para desenhar nuvens
void dNuvem(float x, float y) {
    float radius = 0.1f;

    // Círculo central
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f);  // Cor branca
    glVertex2f(x, y);
    for (int i = 0; i <= 36; i++) {
        float angle = i * 2.0f * M_PI / 36;
        float dx = radius * cos(angle);
        float dy = radius * sin(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();

    // Dois círculos laterais
    dEllipse(x + 0.12f, y, radius, radius);
    dEllipse(x - 0.12f, y, radius, radius);
}

// Função para desenhar o horizonte
void dHorizonte() {
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.8f, 0.5f);  // Cor verde claro
    glVertex2f(-1.0f, -0.2f);  // Canto inferior esquerdo
    glVertex2f(1.0f, -0.2f);   // Canto inferior direito
    glVertex2f(1.0f, -1.0f);   // Canto superior direito
    glVertex2f(-1.0f, -1.0f);  // Canto superior esquerdo
    glEnd();
}

// Função para desenhar uma árvore
void dArovre(float x, float y) {
    // Desenhar tronco
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f);  // Cor marrom
    glVertex2f(x - 0.02f, y - 0.2f);
    glVertex2f(x + 0.02f, y - 0.2f);
    glVertex2f(x + 0.02f, y);
    glVertex2f(x - 0.02f, y);
    glEnd();

    // Desenhar a copa usando três elipses sobrepostas
    glColor3f(0.0f, 0.5f, 0.0f);  // Cor verde para a copa

    // Elipse superior
    dEllipse(x, y + 0.05f, 0.08f, 0.12f);

    // Elipse lateral direita
    dEllipse(x + 0.05f, y, 0.08f, 0.1f);

    // Elipse lateral esquerda
    dEllipse(x - 0.05f, y, 0.08f, 0.1f);

}
void dCoqueiro(float x, float y) {
    // Desenhar tronco
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f);  // Cor marrom
    glVertex2f(x - 0.02f, y - 0.2f);
    glVertex2f(x + 0.02f, y - 0.2f);
    glVertex2f(x + 0.02f, y);
    glVertex2f(x - 0.02f, y);
    glEnd();

    // Desenhar a copa (usando um triângulo)
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.5f, 0.0f);  // Cor verde
    glVertex2f(x, y + 0.1f);  // Topo do triângulo
    glVertex2f(x - 0.1f, y);
    glVertex2f(x + 0.1f, y);
    glEnd();
}


// Função para desenhar um arbusto com frutos
void drawBush(float x, float y) {
    glColor3f(0.0f, 0.6f, 0.0f);  // Cor verde para o arbusto

    // Desenhar várias elipses sobrepostas para simular o arbusto
    dEllipse(x, y, 0.1f, 0.05f); // Parte central
    dEllipse(x + 0.05f, y, 0.08f, 0.04f); // Parte direita
    dEllipse(x - 0.05f, y, 0.08f, 0.04f); // Parte esquerda
    dEllipse(x, y + 0.05f, 0.08f, 0.03f); // Parte superior

    // Adicionar frutos
    glColor3f(0.0f, 0.0f, 1.0f); 
    dEllipse(x + 0.02f, y + 0.02f, 0.02f, 0.02f);  
    dEllipse(x - 0.03f, y + 0.03f, 0.02f, 0.02f);  
    dEllipse(x - 0.02f, y - 0.03f, 0.02f, 0.02f);  
    
}



// Função para desenhar o disco voador
void dDisco(float x, float y) {
    // Base do disco voador (elipse horizontal)
    glColor3f(0.7f, 0.7f, 0.7f);  // Cor cinza clara para a base
    dEllipse(x, y, 0.2f, 0.05f);  // Base maior (elipse)

    // Cúpula superior (elipse menor)
    glColor3f(0.5f, 0.5f, 0.5f);  // Cor cinza escura para a cúpula
    dEllipse(x, y + 0.05f, 0.1f, 0.05f);  // Cúpula do disco voador

    // Desenhar luzes na parte inferior do disco
    glColor3f(1.0f, 0.0f, 0.0f);  // Cor vermelha para as luzes
    dEllipse(x - 0.1f, y - 0.02f, 0.02f, 0.01f);  // Luz esquerda
    glColor3f(0.0f, 1.0f, 0.0f);  // Cor verde para a luz do meio
    dEllipse(x, y - 0.02f, 0.02f, 0.01f);  // Luz central
    glColor3f(0.0f, 0.0f, 1.0f);  // Cor azul para a luz direita
    dEllipse(x + 0.1f, y - 0.02f, 0.02f, 0.01f);  // Luz direita
}

// objeto que servira de algo para o disco voador
void dbaseCasa(){
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);  // Cor cinza
    glVertex2f(0.5f, -0.8f);  // Canto inferior esquerdo
    glVertex2f(1.0f, -0.8f);   // Canto inferior direito
    glVertex2f(1.0f, -0.5f);   // Canto superior direito
    glVertex2f(0.5f, -0.5f);  // Canto superior esquerdo
    glEnd();
}
void dtelhado(){
    glBegin(GL_TRIANGLES);
    glColor3f(0.55f, 0.27f, 0.07f);  // Cor marrom
    glVertex2f(0.5f, -0.5f);  // Canto inferior esquerdo
    glVertex2f(1.0f, -0.5f);   // Canto inferior direito
    glVertex2f(0.75f, -0.3f);   // Canto superior
    glEnd();
}
void dJanela(){
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);  // Cor preta
    glVertex2f(0.6f, -0.7f);  // Canto inferior esquerdo
    glVertex2f(0.7f, -0.7f);   // Canto inferior direito
    glVertex2f(0.7f, -0.6f);   // Canto superior direito
    glVertex2f(0.6f, -0.6f);  // Canto superior esquerdo
    glEnd();
}
void dPorta(){
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);  // Cor preta
    glVertex2f(0.8f, -0.8f);  // Canto inferior esquerdo
    glVertex2f(0.9f, -0.8f);   // Canto inferior direito
    glVertex2f(0.9f, -0.6f);   // Canto superior direito
    glVertex2f(0.8f, -0.6f);  // Canto superior esquerdo
    glEnd();

}

// Função de exibição que desenha todos os elementos
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    dSol();  // Desenha o sol
    dNuvem(-0.5f, 0.6f);  // Desenha nuvem 
    dNuvem(-0.2f, 0.4f);
    dNuvem(0.2f, 0.7f);   // Desenha nuvem 
    dHorizonte();  // Desenha o horizonte
    
    // Desenha árvores
    dArovre(-0.8f, -0.5f);
    dArovre(-0.5f, -0.2f);
    dArovre(-0.2f, -0.4f);
    dArovre(0.3f, -0.5f);
    dArovre(0.7f, -0.0f);
    
    dbaseCasa();
    dtelhado();
    dJanela();
    dPorta();
    // Desenha coqueiros
    dCoqueiro(-0.9f, -0.0f);
    dCoqueiro(-0.6f, -0.7f);
    dCoqueiro(-0.0f, -0.2f);
    dCoqueiro(0.2f, -0.7f);

     // Desenha arbustos
    drawBush(-0.9f, -0.95f); // Arbusto à esquerda
    drawBush(-0.6f, -0.95f); // Arbusto à esquerda 
    drawBush(-0.2f, -0.95f); // Arbusto à esquerda 
    drawBush(0.0f, -0.95f);  // Arbusto centro
    drawBush(0.2f, -0.95f);  // Arbusto à direita 
    drawBush(0.6f, -0.95f);  // Arbusto à direita
    drawBush(0.9f, -0.95f);  // Arbusto à direita
    
    // Desenha o disco voador no céu
    dDisco(0.0f, 0.7f);  
    
    glFlush();  // Garantir que tudo seja desenhado
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Disco Voador");
    
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);  // Cor de fundo 
    
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Definir coordenadas 2D
    
    glutDisplayFunc(display);  // Função de exibição
    glutMainLoop();  // Iniciar o loop do GLUT
    
    return 0;
}

