// basicoTransformacaoDB.cpp
// baseado em basicoTransformacao.cpp

// Este programa demonstra o uso de double buffer

// Historico de alteracoes:
//    FEV/02 - Carla Freitas
// 26/MAR/08 - Bruno Schneider - adicionado glutInit
// 05/JUN/08 - Bruno Schneider
//             Adicionei o termino ao teclar ESC. Reduzi a variacao da posicao de P1.
//             Adicionei o procedimento MostrarMenu().

#include <cstdlib> // para usar a funcao exit
#include <iostream> // para usar os operadores de E/S
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

    // Rotacao de 5 graus em Z. Essa rotacao e' cumulativa. Para entender os motivos, leia 
    // a secao 2.10 (pag 44) da especificacao de OpenGL 1.4. Como o programa nao determina
    // qual matriz sera afetada pela transformacao, matriz padrao (MODELVIEW) e' usada.
    glRotatef(5,0,0,1);
    // Chamadas de funcoes OpenGL para desenho
    glBegin(GL_TRIANGLES);
      glVertex2f(P1.x,P1.y);
      glVertex2f(P2.x,P2.y);
      glVertex2f(P3.x,P3.y);
    glEnd();

    // Flush dos comandos de desenho que estejam no "pipeline" da OpenGL
    // para conclusao da geracao da imagem
    glutSwapBuffers();
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

void MostrarMenu()
{
    using std::cout;
    cout << "\nDurante a execucao, voce pode usar as seguintes teclas:\n"
         << "    r) rotaciona o triangulo\n"
         << "  ESC) para sair do programa\n";
}

void SpecialKeys(int key, int x, int y)
{
}

// Especifica callback comum de teclado
void KeyboardFunc ( unsigned char key, int x, int y )
{
    if (key == 27) // se for a tecla ESC...
        exit(0);  // ...termina o programa

    if (key == 'r')
        glutPostRedisplay();

}

// Parte principal - ponto de inicio de execucao
// Cria janela
// Inicializa aspectos relacionados a janela e a geracao da imagem
// Especifica a funcao de callback de desenho
int main(int argc, char* argv[])
{
    // Procedimento de inicializacao da GLUT
    glutInit(&argc, argv);

    MostrarMenu();

    // Indica que deve ser usado um unico frame buffer e representacao de cores RGB
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Cria uma janela com o titulo especificado
    glutCreateWindow("Usando double buffer");

    // Especifica a funcao que vai tratar teclas comuns (letras, numeros)
    glutKeyboardFunc(KeyboardFunc);

    // Especifica a funcao que vai tratar teclas especiais (setas, Fn, ESC, etc.)
    glutSpecialFunc(SpecialKeys);

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
