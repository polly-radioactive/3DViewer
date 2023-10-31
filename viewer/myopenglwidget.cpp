#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent} {}

void MyOpenGLWidget::initializeGL() {
  float r, g, b, a = normalize_0_1(255.0f, RGB_MIN, RGB_MAX);
  initializeOpenGLFunctions();
  qColorToRGB(Qt::black, r, g, b);
  glClearColor(r, g, b, a);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
}

void MyOpenGLWidget::paintGL() {
  float r, g, b;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (vr[0].amount_polygon != 0) {
    // Вывод вершин
    //        //        glEnable(GL_POINT_SMOOTH);
    //        glPointSize(5.0f);
    //        qColorToRGB(Qt::red, r, g, b);
    ////        qDebug() << "вершины:";
    //        for (int i = 0; i < vr->v.amount_vert; ++i) {
    //            glBegin(GL_POINTS);
    //            glColor3f(r, g, b);
    ////            qDebug() << vr->v.coord[i].x << " " << vr->v.coord[i].y << "
    ///" /                     << vr->v.coord[i].z;
    //            glVertex3f(vr->v.coord[i].x, vr->v.coord[i].y,
    //            vr->v.coord[i].z); glEnd();
    //        }

    // вывод полигонов
    qColorToRGB(Qt::white, r, g, b);
    glColor3f(r, g, b);
    glLineWidth(1.0f);

    for (int i = 0; i < vr->amount_polygon; ++i) {
      glBegin(GL_LINE_LOOP);
      for (int j = 0; j < vr->p[i].amount_p; ++j) {
        int vertice = vr->p[i].value_p[j];
        glVertex3f(vr->v.coord[vertice - 1].x, vr->v.coord[vertice - 1].y,
                   vr->v.coord[vertice - 1].z);
      }
      glEnd();
    }
  }
}

void MyOpenGLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void MyOpenGLWidget::qColorToRGB(const QColor &C, float &r, float &g,
                                 float &b) const {
  r = normalize_0_1(C.red(), RGB_MIN, RGB_MAX);
  g = normalize_0_1(C.green(), RGB_MIN, RGB_MAX);
  b = normalize_0_1(C.blue(), RGB_MIN, RGB_MAX);
}

float MyOpenGLWidget::normalize_0_1(float val, float min, float max) const {
  return (val - min) / (max - min);
}
