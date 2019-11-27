// basico.cpp
// baseado em Simple.c (OpenGL SuperBible)

// Este programa serve de "esqueleto" para desenvolver programas usando GLUT e OpenGL

// Historico de alteracoes:
//    FEV/02 - Carla Freitas
// 26/MAR/08 - Bruno Schneider - adicionado glutInit

#include <iostream>
#include <GL/glut.h> // a glut inclui a gl.h

// Funcao de callback de desenho
// Executada sempre que e' necessario re-exibir a imagem
void RenderScene()
{
    // Limpa a janela com a cor especificada como cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);

    // Aqui devem ser inseridas chamadas de funções OpenGL para desenho


    // Flush dos comandos de desenho que estejam no "pipeline" da OpenGL
    // para conclusao da geracao da imagem
    glFlush();
}


// Inicializa aspectos do rendering
void SetupRC()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  // cor de fundo da janela
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
    glutCreateWindow("Programa Basico com OpenGL e GLUT");

    // Especifica para a OpenGL que funcao deve ser chamada para geracao da imagem
    glutDisplayFunc(RenderScene);

    // Executa a inicializacao de parametros de exibicao
    SetupRC();

    // Escrever informacoes sobre a versao de OpenGL em uso porque pode ser util saber.
    std::cout << "Usando OpenGL '" << glGetString(GL_VERSION) << "' implementado por '"
              << glGetString(GL_VENDOR) << "' em arquitetura '" << glGetString(GL_RENDERER)
              << "'.\nExtensoes disponiveis: " << glGetString(GL_EXTENSIONS) << std::endl;

    // Entra no loop de tratamento de eventos da GLUT
    glutMainLoop();
    return 0;
}
