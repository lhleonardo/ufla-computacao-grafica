// duasViewports.cpp
// baseado em basicoDesenho.cpp

// Este programa e' o basico.cpp mais codigo para criar duas viewports na mesma janela

// Historico de alteracoes:
//    FEV/02 - Carla Freitas
// 05/JUN/08 - Bruno Schneider - adicionado glutInit

#include <cstdlib>
#include <GL/glut.h> // a glut inclui a gl.h

// estrutura que descreve um ponto (x,y)
typedef struct XY {
        GLfloat x;
        GLfloat y;
} PontoXY;

PontoXY  P0, P1, P2, P3;

// parâmetros de transformações

float xDesloc=0.5, yDesloc=-0.5;

// Inicializa os pontos com valores default, cor azul
void SetupObjeto (void)
    {
      P0.x = 0;   // P0 é a origem do triangulo
      P0.y = 0;
      P1.x = 0;  // P1 = (0,0.3)
      P1.y = 0.3;
      P2.x = -0.2; // P2 = (-0.2,0)
      P2.y = 0;
      P3.x = 0.2;  // P3 = (0.2,0)
      P3.y = 0;
      glColor3f(0.0f, 0.0f, 1.0f);  // azul
    }


// Inicializa cor de fundo e regiao visivel default
//
void SetupRC(void)
    {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // cor branca de fundo da janela
    }

//  Desenha triangulo
void DesenhaTriangulo (void)
    {
     glBegin (GL_TRIANGLES);
        glVertex2f (P0.x+P1.x,P0.y+P1.y);
        glVertex2f (P0.x+P2.x,P0.y+P2.y);
        glVertex2f (P0.x+P3.x,P0.y+P3.y);
     glEnd();
    }

// desenha diferentes triângulos
void DesenhaCena (void)
    {
      //  Desenha triangulos diferentes alterando P0


     SetupObjeto();
     glColor3f(1.0, 0.0, 0.0);
     DesenhaTriangulo();                // triangulo original

     P0.x = P0.x+xDesloc;
     glColor3f(0.0, 1.0, 0.0);
     DesenhaTriangulo();               // triangulo deslocado em X

     P0.y = P0.y+yDesloc;
     glColor3f(1.0, 1.0, 0.0);
     DesenhaTriangulo();              // triangulo deslocado em X e Y

     P0.x = 0;
     glColor3f(0.0, 0.0, 0.0);
     DesenhaTriangulo();                   // deslocamento somente em Y
    }

// Função que desenha
// Executada sempre que ocorre qualquer evento de janela
void RenderScene()
{
    // Limpa a janela com a cor especificada como cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);

    glViewport(0,0,300,300); // 1a. viewport a esquerda da janela


    // Chamadas de funções OpenGL para desenho


     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();           //  window default

     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     // Desenha eixos
     glColor3f(1.0f, 0.0f, 0.0f); // eixos vermelhos
     glBegin(GL_LINES);
       glVertex2f (0.0, -0.8);
       glVertex2f (0.0, 0.8);
       glVertex2f (-0.8, 0.0);
       glVertex2f (0.8, 0.0);
     glEnd();

     DesenhaCena();

    // altera a área do SRU a ser exibida na 2a. viewport

     /*glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluOrtho2D (-4,4,-4,4)
     */

     // define a 2a. viewport
     glViewport(305,0,300,300); // 2a. viewport a direita da janela



     // Recomeça a exibir o SRU
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     // Desenha eixos
     glColor3f(1.0f, 0.0f, 0.0f); // eixos vermelhos
     glBegin(GL_LINES);
       glVertex2f (0.0, -0.8);
       glVertex2f (0.0, 0.8);
       glVertex2f (-0.8, 0.0);
       glVertex2f (0.8, 0.0);
     glEnd();


     DesenhaCena();

     glutSwapBuffers();
    }
// Callback comum de teclado
void KeyboardFunc ( unsigned char key, int x, int y )
{
     if(key == 'q') // encerra o programa
       {
         exit(0);
       }

}

// Parte principal - ponto de inicio de execucao
// Cria janela
// Inicializa aspectos relacionados a janela e a geracao da imagem
// Especifica a função callback de desenho

int main(int argc, char* argv[])
{
    // Procedimento de inicializacao da GLUT
    glutInit(&argc, argv);

    // Indica que devem ser usados dois buffers para armazenamento da imagem e representacao de cores RGB
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Cria uma janela com o titulo especificado
    glutInitWindowSize(610,300);
    glutCreateWindow("Exemplo com duas viewports");

    // Especifica a função de desenho
    glutDisplayFunc(RenderScene);

    // Callback de teclado
    glutKeyboardFunc(KeyboardFunc);

     // Executa a inicializacao de parametros de exibicao para a janela corrente
    SetupRC();

    // Inicializa as informacoes geometricas do objeto
    // cores valem para a janela corrente
    SetupObjeto();

    // Entra no loop de tratamento de eventos da GLUT
    glutMainLoop();
    return 0;
}
