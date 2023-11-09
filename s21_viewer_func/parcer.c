#include "s21_viewer.h"

int main_parcer(viewer *data, const char *file) {
  int result = SUCCESS;
  FILE *fp = fopen(file, "r");
  if (fp) {
    data->v.coord = malloc(sizeof(points) * 1);
    data->p =
        malloc(1 * sizeof(polygon));  // выделение памяти для массива полигонов
    result = parcer(data, fp);
    fclose(fp);
  } else {
    printf("No such file\n");
    result = FAILURE;
  }
  return result;
}

int parcer(viewer *data, FILE *fp) {
  int result = SUCCESS;
  char line[100];
  data->v.amount_vert = 0;
  data->amount_polygon = 0;

  while (result != FAILURE && fgets(line, sizeof(line), fp)) {
    if (!strncmp(line, "v ", 2)) {
      result = parcer_line_v(data, line);
    } else if (!strncmp(line, "f ", 2)) {
      data->p = realloc(data->p, sizeof(polygon) * (data->amount_polygon + 1));
      data->p[data->amount_polygon].value_p =
          malloc(1 * sizeof(int));  // выделение памяти для массива значений
      result = parcer_line_f(data, line);
      if (result != FAILURE) {
        data->amount_polygon++;
      }
    }
  }
  min_max_X(data);
  min_max_Y(data);
  min_max_Z(data);
  normalize(data);
  return result;
}

int parcer_line_v(viewer *data, char *line_with_v) {
  int result = SUCCESS;
  char sep[10] = " ";
  char *token = strtok(line_with_v, sep);
  token = strtok(NULL, sep);
  if (token) {
    data->v.coord =
        realloc(data->v.coord, sizeof(points) * (data->v.amount_vert + 1));
    data->v.coord[data->v.amount_vert].x = atof(token);
    token = strtok(NULL, sep);
    if (token) {
      data->v.coord[data->v.amount_vert].y = atof(token);
      token = strtok(NULL, sep);
    }
    if (token) {
      data->v.coord[data->v.amount_vert].z = atof(token);
    } else {
      result = FAILURE;
    }
  }
  data->v.amount_vert++;
  return result;
}

int parcer_line_f(viewer *data, char *line_with_f) {
  int result = SUCCESS;
  data->p[data->amount_polygon].amount_p = 0;
  char sep[10] = " ";
  char *istr;
  istr = strtok(line_with_f, sep);
  istr = strtok(NULL, sep);
  while (istr) {
    data->p[data->amount_polygon].value_p =
        realloc(data->p[data->amount_polygon].value_p,
                sizeof(int) * (data->p[data->amount_polygon].amount_p + 1));
    data->p[data->amount_polygon]
        .value_p[data->p[data->amount_polygon].amount_p] = atoi(istr);
    if (data->p[data->amount_polygon]
            .value_p[data->p[data->amount_polygon].amount_p] >
        data->v.amount_vert) {
      result = FAILURE;
      free(data->p[data->amount_polygon].value_p);
    }
    istr = strtok(NULL, sep);
    data->p[data->amount_polygon].amount_p++;
  }
  return result;
}
void min_max_X(viewer *data) {
  double min = data->v.coord[0].x;
  double max = data->v.coord[0].x;
  for (int i = 1; i < data->v.amount_vert; i++) {
    if (data->v.coord[i].x < min) {
      min = data->v.coord[i].x;
    }
    if (data->v.coord[i].x > max) {
      max = data->v.coord[i].x;
    }
  }
  data->v.MinMax_X[0] = min;
  data->v.MinMax_X[1] = max;
}

void min_max_Y(viewer *data) {
  double min = data->v.coord[0].y;
  double max = data->v.coord[0].y;
  for (int i = 1; i < data->v.amount_vert; i++) {
    if (data->v.coord[i].y < min) {
      min = data->v.coord[i].y;
    }
    if (data->v.coord[i].y > max) {
      max = data->v.coord[i].y;
    }
  }
  data->v.MinMax_Y[0] = min;
  data->v.MinMax_Y[1] = max;
}

void min_max_Z(viewer *data) {
  double min = data->v.coord[0].z;
  double max = data->v.coord[0].z;
  for (int i = 1; i < data->v.amount_vert; i++) {
    if (data->v.coord[i].z < min) {
      min = data->v.coord[i].z;
    }
    if (data->v.coord[i].z > max) {
      max = data->v.coord[i].z;
    }
  }
  data->v.MinMax_Z[0] = min;
  data->v.MinMax_Z[1] = max;
}

void normalize(viewer *data) {
  double centre_x =
      data->v.MinMax_X[0] + (data->v.MinMax_X[1] - data->v.MinMax_X[0]) / 2;
  double centre_y =
      data->v.MinMax_Y[0] + (data->v.MinMax_Y[1] - data->v.MinMax_Y[0]) / 2;
  double centre_z =
      data->v.MinMax_Z[0] + (data->v.MinMax_Z[1] - data->v.MinMax_Z[0]) / 2;

  for (int i = 0; i < data->v.amount_vert; i++) {
    data->v.coord[i].x -= centre_x;
    data->v.coord[i].y -= centre_y;
    data->v.coord[i].z -= centre_z;
  }

  // нормализация от -1 до 1
  double x = data->v.MinMax_X[1] - data->v.MinMax_X[0];
  double y = data->v.MinMax_Y[1] - data->v.MinMax_Y[0];
  double z = data->v.MinMax_Z[1] - data->v.MinMax_Z[0];
  double dmax = 0;
  if (x >= y) {
    dmax = x;
  } else {
    dmax = y;
  }
  if (dmax < z) dmax = z;
  double value = 1;
  double scale = (value - value * (-1)) / dmax;
  for (int i = 0; i < data->v.amount_vert; i++) {
    data->v.coord[i].x *= scale;
    data->v.coord[i].y *= scale;
    data->v.coord[i].z *= scale;
  }
}

// void print_coord(viewer *data) {
//   printf("amount_vert: %d\n", data->v.amount_vert);

//   for (int i = 0; i < data->v.amount_vert; i++) {
//     printf("Координата %d: x = %f, y = %f, z = %f\n", i, data->v.coord[i].x,
//            data->v.coord[i].y, data->v.coord[i].z);
//   }
// }

// void print_polygon(viewer *data) {
//   printf("amount_polygon: %d\n", data->amount_polygon);
//   for (int i = 0; i < data->amount_polygon; i++) {
//     for (int j = 0; j < data->p[i].amount_p; j++) {
//       printf("%d ", data->p[i].value_p[j]);
//     }
//     printf("\n");
//   }
// }

void free_data(viewer *data) {
  if (data->amount_polygon != 0 || data->v.amount_vert != 0) {
    if (data->v.coord) {
      free(data->v.coord);
      data->v.coord = NULL;
    }
    if (data->p) {
      for (int i = 0; i < data->amount_polygon; i++) {
        if (data->p[i].value_p) {
          free(data->p[i].value_p);
          data->p[i].value_p = NULL;
        }
      }
      free(data->p);
      data->p = NULL;
    }
  }
}
