/* DuasJanelas.cpp
*
*  fevereiro,2002 por Carla Freitas
*
*
*   usa duas janelas e entrada de teclado nas duas janelas
*/

/* include de definicoes das funcoes da glut
   glut.h inclui gl.h, que contem os headers de funcoes da OpenGL propriamente dita
   glut.h inclui tambem definicoes necessarias para o uso de OpenGl nos diversos ambientes Windows
*/
#include <GL/glut.h>
#include <stdio.h>

// estrutura que descreve um ponto (x,y)
typedef struct XY {
        GLfloat x;
        GLfloat y;
} PontoXY;

// Tamanho das bordas das janelas na horizontal
const int TAM_BORDAS_H=10;
const int TAM_JANELAS_H=390;

PontoXY P1, P2, P3;

// variaveis para armazenar identificadores de janelas
int janelaUm, janelaDois;

// callback de teclado: resultados diferentes dependendo da janela

void KeyboardFunc1 ( unsigned char key, int x, int y )
{
     printf("janela corrente = %d\n",glutGetWindow());
     if ( key == 'v') // muda a cor do objeto para verde
         glColor3f(0.0f,1.0f,0.0f);
     if (key == 'r') // muda a cor do objeto para vermelho default
         glColor3f(1.0f,0.0f,0.0f);
     glutPostRedisplay();
}

void KeyboardFunc2 ( unsigned char key, int x, int y )
{
     printf("janela corrente = %d\n",glutGetWindow());
     if ( key == 'b') // muda a cor do objeto para azul
         glColor3f(0.0f,0.0f,1.0f);
     if (key == 'r') // muda a cor do objeto para vermelho
         glColor3f(1.0f,0.0f,0.0f);
     glutPostRedisplay();
}

/*
void KeyboardFunc ( unsigned char key, int x, int y )
{
     printf("janela corrente = %d\n",glutGetWindow());
     if ( key == 'b') // muda a cor do objeto para azul
       {
         glColor3f(0.0f,0.0f,1.0f);
        }
     if ( key == 'v') // muda a cor do objeto para verde
       {
         glColor3f(0.0f,1.0f,0.0f);
        }
     if (key == 'r') // muda a cor do objeto para vermelho
       {
         glColor3f(1.0f,0.0f,0.0f);
       }
     glutPostRedisplay();
}
*/

void RenderScene1(void)
{
    // Limpa a janela com a cor especificada como cor de fundo
    // especificada  para a janela esta janela (ou com a default)
    glClear(GL_COLOR_BUFFER_BIT);

    // Chamadas de funções OpenGL para desenho
    glBegin (GL_LINE_LOOP);
        glVertex2f (P1.x,P1.y);
        glVertex2f (P2.x,P2.y);
        glVertex2f (P3.x,P3.y);
    glEnd();

    // Flush dos comandos de desenho que estejam no "pipeline" da OpenGL
    // para conclusao da geracao da imagem
    glFlush();

}


// Função de callback de desenho na janela 2
// Executada sempre que é necessario re-exibir a imagem
void RenderScene2(void)
{
    // Limpa a janela com a cor especificada como cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);

    // Chamadas de funções OpenGL para desenho
    glBegin (GL_TRIANGLES);
        glVertex2f (P1.x,P1.y);
        glVertex2f (P2.x,P2.y);
        glVertex2f (P3.x,P3.y);
    glEnd();

    // Flush dos comandos de desenho que estejam no "pipeline" da OpenGL
    // para conclusao da geracao da imagem
    glFlush();
}

// Inicializa aspectos do rendering da janela corrente
void SetupRC(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // cor de fundo da janela branco
}

// Inicializa os tres pontos com valores default e cor vermelha
void SetupObjeto (void)
{
    glColor3f(1.0f,0.0f,0.0f); // vermelho
    P1.x = 0;
    P1.y = 1;
    P2.x = -1;
    P2.y = 0;
    P3.x = 1;
    P3.y = 0;
}

// Parte principal - ponto de início de execução
// Cria duas janelas
// Inicializa aspectos relacionados as janela e a geração da imagem
// Especifica a função de callback de desenho de cada janela
// Especifica callback de entrada de teclado para cada janela

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    // Indica que deve ser usado um unico buffer para armazenamento da imagem e representacao de cores RGB
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Cria uma janela com o titulo especificado e indica a sua callback
    // Usa valores default: janela em 0,0 400x400
    glutInitWindowPosition (0,0);
    glutInitWindowSize (TAM_JANELAS_H,TAM_JANELAS_H);
    janelaUm = glutCreateWindow("Janela 1");
    glutDisplayFunc(RenderScene1);
    glutKeyboardFunc(KeyboardFunc1);

    // Executa a inicializacao de parametros de exibicao para a janela corrente
    // ATENÇÃO: Só vale para a janela corrente = janela 1
    SetupRC();

    // Inicializa as informacoes do objeto
    // cor é válida para a janela corrente = janela 1
    SetupObjeto();

    // Cria a segunda janela em outra posição
    // Vai utilizar cor de fundo (preto) e de desenho (branco) default

    glutInitWindowPosition (TAM_JANELAS_H+TAM_BORDAS_H,0);
    glutInitWindowSize (TAM_JANELAS_H,TAM_JANELAS_H);
    janelaDois =  glutCreateWindow("Janela 2");
    glutDisplayFunc(RenderScene2); // Especifica callback da janela 2
    glutKeyboardFunc(KeyboardFunc2);

    // Dispara a "maquina de estados" de OpenGL
    glutMainLoop();
    return 0;
}
