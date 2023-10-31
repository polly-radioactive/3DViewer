#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  free_data(ui->widget->vr);
  delete ui;
}

void MainWindow::on_actionQuit_triggered() { close(); }

void MainWindow::on_spinBoxMoveX_valueChanged(int arg1) {
  ui->horizontalSliderMoveX->setValue(ui->spinBoxMoveX->value());
}

void MainWindow::on_spinBoxMoveY_valueChanged(int arg1) {
  ui->horizontalSliderMoveY->setValue(ui->spinBoxMoveY->value());
}

void MainWindow::on_spinBoxMoveZ_valueChanged(int arg1) {
  ui->horizontalSliderMoveZ->setValue(ui->spinBoxMoveZ->value());
}

void MainWindow::on_spinBoxRotateX_valueChanged(int arg1) {
  ui->horizontalSliderRotateX->setValue(ui->spinBoxRotateX->value());
}

void MainWindow::on_spinBoxRotateY_valueChanged(int arg1) {
  ui->horizontalSliderRotateY->setValue(ui->spinBoxRotateY->value());
}

void MainWindow::on_spinBoxRotateZ_valueChanged(int arg1) {
  ui->horizontalSliderRotateZ->setValue(ui->spinBoxRotateZ->value());
}

void MainWindow::on_spinBoxScale_valueChanged(int arg1) {
  ui->horizontalSliderScale->setValue(ui->spinBoxScale->value());
}

void MainWindow::on_horizontalSliderMoveX_valueChanged(int value) {
  int deltaX = ui->spinBoxMoveX->value();
  ui->spinBoxMoveX->setValue(ui->horizontalSliderMoveX->value());
  deltaX = ui->spinBoxMoveX->value() - deltaX;
  s21_move(ui->widget->vr, (double)deltaX / 100.0f, 0, 0);
  ui->widget->update();
}

void MainWindow::on_horizontalSliderMoveY_valueChanged(int value) {
  int deltaY = ui->spinBoxMoveY->value();
  ui->spinBoxMoveY->setValue(ui->horizontalSliderMoveY->value());
  deltaY = ui->spinBoxMoveY->value() - deltaY;
  s21_move(ui->widget->vr, 0, (double)deltaY / 100.0f, 0);
  ui->widget->update();
}

void MainWindow::on_horizontalSliderMoveZ_valueChanged(int value) {
  int deltaZ = ui->spinBoxMoveZ->value();
  ui->spinBoxMoveZ->setValue(ui->horizontalSliderMoveZ->value());
  deltaZ = ui->spinBoxMoveZ->value() - deltaZ;
  s21_move(ui->widget->vr, 0, 0, (double)deltaZ / 100.0f);
  ui->widget->update();
}

void MainWindow::on_horizontalSliderRotateX_valueChanged(int value) {
  int deltaR = ui->spinBoxRotateX->value();
  ui->spinBoxRotateX->setValue(ui->horizontalSliderRotateX->value());
  deltaR = ui->spinBoxRotateX->value() - deltaR;
  s21_rotate(ui->widget->vr, deltaR, 1, 0, 0);
  ui->widget->update();
}

void MainWindow::on_horizontalSliderRotateY_valueChanged(int value) {
  int deltaR = ui->spinBoxRotateY->value();
  ui->spinBoxRotateY->setValue(ui->horizontalSliderRotateY->value());
  deltaR = ui->spinBoxRotateY->value() - deltaR;
  s21_rotate(ui->widget->vr, deltaR, 0, 1, 0);
  ui->widget->update();
}

void MainWindow::on_horizontalSliderRotateZ_valueChanged(int value) {
  int deltaR = ui->spinBoxRotateZ->value();
  ui->spinBoxRotateZ->setValue(ui->horizontalSliderRotateZ->value());
  deltaR = ui->spinBoxRotateZ->value() - deltaR;
  s21_rotate(ui->widget->vr, deltaR, 0, 0, 1);
  ui->widget->update();
}

void MainWindow::on_horizontalSliderScale_valueChanged(int value) {
  int deltaS = ui->spinBoxScale->value();
  ui->spinBoxScale->setValue(ui->horizontalSliderScale->value());
  deltaS = ui->spinBoxScale->value() - deltaS;
  if (deltaS > 0) {
    s21_scale(ui->widget->vr, 1 + (double)deltaS / 100.0f, 1);
  } else {
    s21_scale(ui->widget->vr, 1, 1 - (double)deltaS / 100.0f);
  }
  ui->widget->update();
}

void MainWindow::on_openFileButton_clicked() {
  QString filename = QFileDialog::getOpenFileName(
      this, "Choose file", QDir::currentPath(), ".obj (*.obj)");
  if (!filename.isEmpty()) {
    if (main_parcer(ui->widget->vr, filename.toStdString().c_str()) !=
        FAILURE) {
      QFileInfo fname(filename);
      ui->filenameLabel->setText(fname.fileName());
      ui->verticesLabel->setText(
          QString::number(ui->widget->vr[0].v.amount_vert));
      ui->edgesLabel->setText(
          QString::number(ui->widget->vr[0].amount_polygon));
      ui->spinBoxMoveX->setValue(0);
      ui->spinBoxMoveY->setValue(0);
      ui->spinBoxMoveZ->setValue(0);
      ui->spinBoxRotateX->setValue(0);
      ui->spinBoxRotateY->setValue(0);
      ui->spinBoxRotateZ->setValue(0);
      ui->spinBoxScale->setValue(0);
    } else {
      QMessageBox::information(nullptr, "File error",
                               "Model file has been read with an error.");
    }
  }
}
