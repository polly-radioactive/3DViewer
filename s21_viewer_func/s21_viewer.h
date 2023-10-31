#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE 2

#define eps 1e-7
#define PI 3.14159265358979323846

typedef struct {
  double x, y, z;
} points;

typedef struct {
  int amount_vert;  // количество вершин
  points *coord;    // массив координат
  double MinMax_X[2];  // мин и мах значение для отцентрировки
  double MinMax_Y[2];
  double MinMax_Z[2];
} vertex;

typedef struct {
  int amount_p;  // количество значений
  int *value_p;  // тут хранятся значения
} polygon;

typedef struct {
  vertex v;            // массив точек
  int amount_polygon;  // количество полигонов
  polygon *p;          // массив полигонов
} viewer;

int main_parcer(viewer *data, const char *file);
int parcer(viewer *data, FILE *fp);
int parcer_line_v(viewer *data, char *line_with_v);
int parcer_line_f(viewer *data, char *line_with_f);

void min_max_X(viewer *data);
void min_max_Y(viewer *data);
void min_max_Z(viewer *data);

// void print_coord(viewer *data);
// void print_polygon(viewer *data);

void normalize(viewer *data);
void free_data(viewer *data);

void matrix_transformation(viewer *data, double transformation_matrix[][4],
                           double *vector, int i);
void s21_move(viewer *data, double sx, double sy, double sz);
void s21_scale(viewer *data, double scale_cur, double scale_prev);
void s21_rotate(viewer *data, double angle, int x, int y, int z);
