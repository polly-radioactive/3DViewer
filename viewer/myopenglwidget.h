#pragma once

#include <QColor>
#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

extern "C" {
#include "../s21_viewer_func/s21_viewer.h"
}

#define RGB_MIN 1
#define RGB_MAX 255

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 public:
  MyOpenGLWidget(QWidget *parent = nullptr);
  ~MyOpenGLWidget();
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

  viewer vr[1];
  int projection = 0;
  int sizeEdges = 1;
  int viewEdges = 0;
  int colorEdges = 0;
  int sizeVertex = 1;
  int viewVertex = 0;
  int colorVertex = 0;
  int colorBack = 0;
};
