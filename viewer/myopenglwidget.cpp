#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent} {}

MyOpenGLWidget::~MyOpenGLWidget() {}

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
}

void MyOpenGLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void MyOpenGLWidget::paintGL() {
  if (!colorBack) {
    glClearColor(0, 0, 0, 0);
  } else if (colorBack == 1) {
    glClearColor(1, 0, 0, 0);
  } else if (colorBack == 2) {
    glClearColor(0, 1, 0, 0);
  } else if (colorBack == 3) {
    glClearColor(0, 0, 1, 0);
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (projection) {
    glFrustum(-1, 1, -1, 1, 7, 12);
    glTranslatef(0, 0, -8);
  } else {
    glOrtho(-1, 1, -1, 1, -1, 1);
  }

  // вывод полигонов
  glLineWidth(sizeEdges);
  if (!viewEdges) {
    glDisable(GL_LINE_STIPPLE);
  } else if (viewEdges == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x00FF);
  }
  if (!colorEdges) {
    glColor3d(1, 1, 1);
  } else if (colorEdges == 1) {
    glColor3d(1, 0, 0);
  } else if (colorEdges == 2) {
    glColor3d(0, 1, 0);
  } else if (colorEdges == 3) {
    glColor3d(0, 0, 1);
  }
  for (int i = 0; i < vr->amount_polygon; ++i) {
    glBegin(GL_LINE_LOOP);
    for (int j = 0; j < vr->p[i].amount_p; ++j) {
      int vertice = vr->p[i].value_p[j];
      glVertex3d(vr->v.coord[vertice - 1].x, vr->v.coord[vertice - 1].y,
                 vr->v.coord[vertice - 1].z);
    }
    glEnd();
  }

  // Вывод вершин
  if (vr[0].amount_polygon != 0) {
    if (viewVertex == 1) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }
    if (viewVertex) {
      glPointSize(sizeVertex);
      if (!colorVertex) {
        glColor3d(1, 1, 1);
      } else if (colorVertex == 1) {
        glColor3d(1, 0, 0);
      } else if (colorVertex == 2) {
        glColor3d(0, 1, 0);
      } else if (colorVertex == 3) {
        glColor3d(0, 0, 1);
      }
      for (int i = 0; i < vr->v.amount_vert; ++i) {
        glBegin(GL_POINTS);
        glVertex3d(vr->v.coord[i].x, vr->v.coord[i].y, vr->v.coord[i].z);
        glEnd();
      }
    }
  }
}
