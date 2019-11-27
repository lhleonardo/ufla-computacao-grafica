// basicoDesenho.cpp
// baseado em basico.cpp

// Este programa e' o basico.cpp mais algum codigo para desenhar um triangulo

// Historico de alteracoes:
//    FEV/02 - Carla Freitas
// 26/MAR/08 - Bruno Schneider - adicionado glutInit

#include <GL/glut.h> // a glut inclui a gl.h

// estrutura que descreve um ponto (x,y)
typedef struct XY {
        GLfloat x;
        GLfloat y;
} PontoXY;

PontoXY P1, P2, P3;

// Funcao de callback de desenho
// Executada sempre que e' necessario re-exibir a imagem
void RenderScene()
{
    // Limpa a janela com a cor especificada como cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);

    // Indica para a maquina de estados da OpenGL que todas as primitivas geométricas que
    // forem chamadas deste ponto em diante devem ter a cor vermelha
    glColor3f(1.0f, 0.0f, 0.0f);

    // Chamadas de funcoes OpenGL para desenho
    glBegin(GL_TRIANGLES);
      glVertex2f(P1.x,P1.y);
      glVertex2f(P2.x,P2.y);
      glVertex2f(P3.x,P3.y);
    glEnd();

    // Flush dos comandos de desenho que estejam no "pipeline" da OpenGL
    // para conclusao da geracao da imagem
    glFlush();
}

// Inicializa aspectos do rendering
void SetupRC()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  // cor de fundo da janela
}

// Inicializa os tres pontos com valores default
void SetupObjeto()
{
    P1.x = 0;
    P1.y = 1;
    P2.x = -1;
    P2.y = 0;
    P3.x = 1;
    P3.y = 0;
}

// Parte principal - ponto de inicio de execucao
// Cria janela
// Inicializa aspectos relacionados a janela e a geracao da imagem
// Especifica a funcao de callback de desenho
int main(int argc, char* argv[])
{
    // Procedimento de inicializacao da GLUT
    glutInit(&argc, argv);

    // Indica que deve ser usado um unico frame buffer e representacao de cores RGB
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Cria uma janela com o titulo especificado
    glutCreateWindow("Primeiro desenho com OpenGL e GLUT");

    // Especifica para a OpenGL que funcao deve ser chamada para geracao da imagem
    glutDisplayFunc(RenderScene);

    // Executa a inicializacao de parametros de exibicao
    SetupRC();

    // Inicializa as informacoes geometricas do objeto
    SetupObjeto();

    // Entra no loop de tratamento de eventos da GLUT
    glutMainLoop();
    return 0;
}
