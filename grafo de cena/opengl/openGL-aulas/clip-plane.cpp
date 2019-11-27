/* 
*  Novembro 2003 - Carla Freitas
*  baseado em programa demo do RedBook
*/


#include <GL/glut.h>
#include <GL/glu.h>

void display(void)
{
    GLdouble eqn[4] = {0.0, 1.0, 0.0, 0.0};    /* y < 0 */
    GLdouble eqn2[4] = {1.0, 0.0, 0.0, 0.0};   /* x < 0 */
  
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f (1.0, 1.0, 1.0);
  
    glTranslatef (0.0, 0.0, -5.0);

    glClipPlane (GL_CLIP_PLANE0, eqn);
    glEnable (GL_CLIP_PLANE0);
    glClipPlane (GL_CLIP_PLANE1, eqn2);
    glEnable (GL_CLIP_PLANE1);

    glRotatef (90.0, 1.0, 0.0, 0.0);
    glutWireSphere(1.0,10, 10);
  
    glFlush();
}

void myinit (void) 
{
    glShadeModel (GL_FLAT);
}

void myReshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition (0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow ("Clip Plane Demo");
    glutDisplayFunc(display);
    glutReshapeFunc (myReshape);
    myinit();
    glutMainLoop();
}
