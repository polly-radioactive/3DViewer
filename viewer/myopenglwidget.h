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
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void qColorToRGB(const QColor &C, float &r, float &g, float &b) const;
  float normalize_0_1(float val, float min, float max) const;

  viewer vr[1];
};
