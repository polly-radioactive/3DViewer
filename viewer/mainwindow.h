#pragma once
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_actionQuit_triggered();
  void on_spinBoxMoveX_valueChanged(int arg1);
  void on_spinBoxMoveY_valueChanged(int arg1);
  void on_spinBoxMoveZ_valueChanged(int arg1);
  void on_spinBoxRotateX_valueChanged(int arg1);
  void on_spinBoxRotateY_valueChanged(int arg1);
  void on_spinBoxRotateZ_valueChanged(int arg1);
  void on_spinBoxScale_valueChanged(int arg1);
  void on_horizontalSliderMoveX_valueChanged(int value);
  void on_horizontalSliderMoveY_valueChanged(int value);
  void on_horizontalSliderMoveZ_valueChanged(int value);
  void on_horizontalSliderRotateX_valueChanged(int value);
  void on_horizontalSliderRotateY_valueChanged(int value);
  void on_horizontalSliderRotateZ_valueChanged(int value);
  void on_horizontalSliderScale_valueChanged(int value);

  void on_openFileButton_clicked();

 private:
  Ui::MainWindow *ui;
};
