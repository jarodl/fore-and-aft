/*
 * =====================================================================================
 *
 *       Filename:  GLBoard.h
 *
 *    Description:  Draws a board using OpenGL.
 *
 *        Version:  1.0
 *        Created:  02/01/2011 08:55:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jarod Luebbert (), jarodluebbert@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef GLBOARD_H
#define GLBOARD_H

#include <stdlib.h>
#include <GL/glew.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

class GLBoard;

static GLBoard *instance;

class GLBoard
{
  public:
    GLBoard(int argc, char* argv[])
    {
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
      glutInitWindowSize(400, 300);
      glutCreateWindow("Fore and Aft Solver");
      glutDisplayFunc(renderWrapper);

      glewInit();
      if (!GLEW_VERSION_2_0)
      {
        fprintf(stderr, "OpenGL 2.0 not available.");
      }

      glutMainLoop();
    }

    ~GLBoard()
    {
    }

    static void setInstance(GLBoard *b)
    {
      instance = b;
    }

    static void renderWrapper()
    {
      instance->render();
    }

    void render()
    {
      glClear(GL_COLOR_BUFFER_BIT);
      glLoadIdentity();
      /* Draw here a plain surface */
      glBegin(GL_QUADS);
      for (int i = -50; i < 50; i++)
          for (int j = -50; j < 50; j++)
          {
              glVertex2f(i, j);
              glVertex2f(i + 1, j);
              glVertex2f(i + 1, j + 1);
              glVertex2f(i, j + 1);
          }
      glEnd();
    }
};


#endif
