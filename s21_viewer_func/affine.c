#include "s21_viewer.h"

void matrix_transformation(viewer *data, double transformation_matrix[][4],
                           double *vector, int i) {
  double res[4] = {0};
  for (int j = 0; j < 4; j++) {
    for (int k = 0; k < 4; k++) {
      res[j] += transformation_matrix[j][k] * vector[k];
    }
  }
  data->v.coord[i].x = res[0];
  data->v.coord[i].y = res[1];
  data->v.coord[i].z = res[2];
}

void s21_move(viewer *data, double sx, double sy, double sz) {
  for (int i = 0; i < data->v.amount_vert; i++) {
    double vector[4] = {data->v.coord[i].x, data->v.coord[i].y,
                        data->v.coord[i].z, 1};
    double transformation_matrix[4][4] = {
        {1, 0, 0, sx}, {0, 1, 0, sy}, {0, 0, 1, sz}, {0, 0, 0, 1}};
    matrix_transformation(data, transformation_matrix, vector, i);
  }
}

void s21_scale(viewer *data, double scale_cur, double scale_prev) {
  if (scale_cur > 0 && scale_prev > 0) {
    for (int i = 0; i < data->v.amount_vert; i++) {
      data->v.coord[i].x = scale_cur / scale_prev * (data->v.coord[i].x);
      data->v.coord[i].y = scale_cur / scale_prev * (data->v.coord[i].y);
      data->v.coord[i].z = scale_cur / scale_prev * (data->v.coord[i].z);
    }
  }
}

void s21_rotate(viewer *data, double angle, int x, int y, int z) {
  double radians = angle * PI / 180.0;
  double x_trans_matrix[4][4] = {{1, 0, 0, 0},
                                 {0, cos(radians), -sin(radians), 0},
                                 {0, sin(radians), cos(radians), 0},
                                 {0, 0, 0, 1}};
  double y_trans_matrix[4][4] = {{cos(radians), 0, sin(radians), 0},
                                 {0, 1, 0, 0},
                                 {-sin(radians), 0, cos(radians), 0},
                                 {0, 0, 0, 1}};
  double z_trans_matrix[4][4] = {{cos(radians), -sin(radians), 0, 0},
                                 {sin(radians), cos(radians), 0, 0},
                                 {0, 0, 1, 0},
                                 {0, 0, 0, 1}};
  for (int i = 0; i < data->v.amount_vert; i++) {
    double vector[4] = {data->v.coord[i].x, data->v.coord[i].y,
                        data->v.coord[i].z, 1};
    if (x) {
      matrix_transformation(data, x_trans_matrix, vector, i);
    } else {
      if (y) {
        matrix_transformation(data, y_trans_matrix, vector, i);
      } else {
        if (z) matrix_transformation(data, z_trans_matrix, vector, i);
      }
    }
  }
}
