#include "s21_test_viewer.h"

START_TEST(parser_1) {
  viewer data[2048];
  char *name = "./test_file/test.obj";
  int res = main_parcer(data, name);
  free_data(data);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(parser_2) {
  viewer data[2048];
  char *name = "./test_file/tes.obj";
  int res = main_parcer(data, name);
  free_data(data);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(parser_3) {
  viewer data[2048];
  char *name = "./test_file/test_not_z.obj";
  int res = main_parcer(data, name);
  free_data(data);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(parser_4) {
  viewer data[2048];
  char *name = "./test_file/test_polygon.obj";
  int res = main_parcer(data, name);
  free_data(data);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(parser_5) {
  viewer data[2048];
  char *name = "./test_file/cessna.obj";
  int res = main_parcer(data, name);
  free_data(data);
  ck_assert_int_eq(res, 0);
}
END_TEST

// Тестирование функции перемещения
START_TEST(test_move) {
  viewer data;
  data.v.amount_vert = 1;
  data.v.coord = (points *)malloc(sizeof(points));
  data.v.coord[0].x = 1.0;
  data.v.coord[0].y = 1.0;
  data.v.coord[0].z = 1.0;

  s21_move(&data, 1.0, 1.0, 1.0);

  ck_assert_double_eq(data.v.coord[0].x, 2.0);
  ck_assert_double_eq(data.v.coord[0].y, 2.0);
  ck_assert_double_eq(data.v.coord[0].z, 2.0);

  free(data.v.coord);
}
END_TEST

// Тестирование функции масштабирования
START_TEST(test_scale) {
  viewer data;
  data.v.amount_vert = 1;
  data.v.coord = (points *)malloc(sizeof(points));
  data.v.coord[0].x = 2.0;
  data.v.coord[0].y = 2.0;
  data.v.coord[0].z = 2.0;

  s21_scale(&data, 2.0, 1.0);

  ck_assert_double_eq(data.v.coord[0].x, 4.0);
  ck_assert_double_eq(data.v.coord[0].y, 4.0);
  ck_assert_double_eq(data.v.coord[0].z, 4.0);

  free(data.v.coord);
}
END_TEST

// Тестирование функции вращения вокруг оси X
START_TEST(test_rotate_x) {
  viewer data;
  data.v.amount_vert = 1;
  data.v.coord = (points *)malloc(sizeof(points));
  data.v.coord[0].x = 0.0;
  data.v.coord[0].y = 1.0;
  data.v.coord[0].z = 0.0;

  s21_rotate(&data, 90.0, 1, 0, 0);

  ck_assert_double_le(fabs(data.v.coord[0].y),
                    1e-6);  // y должен приблизиться к 0 после вращения
  ck_assert_double_le(fabs(data.v.coord[0].z - 1.0),
                    1e-6);  // z должен стать 1 после вращения

  free(data.v.coord);
}
END_TEST

Suite *suite_parser(void) {
  Suite *s = suite_create("Checking s21_check_parser...");
  TCase *tcase = tcase_create("parser");
  tcase_add_test(tcase, parser_1);
  tcase_add_test(tcase, parser_2);
  tcase_add_test(tcase, parser_3);
  tcase_add_test(tcase, parser_4);
  tcase_add_test(tcase, parser_5);

  suite_add_tcase(s, tcase);
  return s;
}

Suite *suite_affine(void) {
  Suite *s = suite_create("Checking s21_check_affine...");
  TCase *tcase = tcase_create("parser");
  tcase_add_test(tcase, test_move);
  tcase_add_test(tcase, test_scale);
  tcase_add_test(tcase, test_rotate_x);

  suite_add_tcase(s, tcase);
  return s;
}

int main(void) {
  const int total = 2;
  Suite *test_cases[total];
  test_cases[0] = suite_parser();
  test_cases[1] = suite_affine();

  for (int i = 0; i < total; i++) {
    SRunner *runner = srunner_create(test_cases[i]);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    srunner_free(runner);
  }
}
