#include <check.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

// =========================================================================
// МАКРОСЫ
// =========================================================================

#define TEST_SPRINTF(test_name, format_str, value, type) \
  START_TEST(test_name) {                                \
    char str_sp[200] = {0};                              \
    type val = (value);                                  \
    int res_sp = s21_sprintf(str_sp, format_str, val);   \
    ck_assert_str_eq(" ", str_sp);                       \
  }                                                      \
  END_TEST

TEST_SPRINTF(Le_mins_inf, "%-Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_plus_inf, "%+Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_spac_inf, "% Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_hash_inf, "%#Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_fzer_inf, "%0Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_mins_ng_inf, "%-Le", (long double)(-INFINITY), long double)
TEST_SPRINTF(Le_plus_ng_inf, "%+Le", (long double)(-INFINITY), long double)
TEST_SPRINTF(Le_spac_ng_inf, "% Le", (long double)(-INFINITY), long double)
TEST_SPRINTF(Le_hash_ng_inf, "%#Le", (long double)(-INFINITY), long double)
TEST_SPRINTF(Le_fzer_ng_inf, "%0Le", (long double)(-INFINITY), long double)

// =========================================================================

TEST_SPRINTF(LE_mins_inf, "%-LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_plus_inf, "%+LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_spac_inf, "% LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_hash_inf, "%#LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_fzer_inf, "%0LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_mins_ng_inf, "%-LE", (long double)(-INFINITY), long double)
TEST_SPRINTF(LE_plus_ng_inf, "%+LE", (long double)(-INFINITY), long double)
TEST_SPRINTF(LE_spac_ng_inf, "% LE", (long double)(-INFINITY), long double)
TEST_SPRINTF(LE_hash_ng_inf, "%#LE", (long double)(-INFINITY), long double)
TEST_SPRINTF(LE_fzer_ng_inf, "%0LE", (long double)(-INFINITY), long double)

// =========================================================================

TEST_SPRINTF(Lf_mins_inf, "%-Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_plus_inf, "%+Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_spac_inf, "% Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_hash_inf, "%#Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_fzer_inf, "%0Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_mins_ng_inf, "%-Lf", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lf_plus_ng_inf, "%+Lf", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lf_spac_ng_inf, "% Lf", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lf_hash_ng_inf, "%#Lf", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lf_fzer_ng_inf, "%0Lf", (long double)(-INFINITY), long double)

// =========================================================================

TEST_SPRINTF(Lg_mins_inf, "%-Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_plus_inf, "%+Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_spac_inf, "% Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_hash_inf, "%#Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_fzer_inf, "%0Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_mins_ng_inf, "%-Lg", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lg_plus_ng_inf, "%+Lg", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lg_spac_ng_inf, "% Lg", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lg_hash_ng_inf, "%#Lg", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lg_fzer_ng_inf, "%0Lg", (long double)(-INFINITY), long double)

// =========================================================================

TEST_SPRINTF(LG_mins_inf, "%-LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_plus_inf, "%+LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_spac_inf, "% LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_hash_inf, "%#LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_fzer_inf, "%0LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_mins_ng_inf, "%-LG", (long double)(-INFINITY), long double)
TEST_SPRINTF(LG_plus_ng_inf, "%+LG", (long double)(-INFINITY), long double)
TEST_SPRINTF(LG_spac_ng_inf, "% LG", (long double)(-INFINITY), long double)
TEST_SPRINTF(LG_hash_ng_inf, "%#LG", (long double)(-INFINITY), long double)
TEST_SPRINTF(LG_fzer_ng_inf, "%0LG", (long double)(-INFINITY), long double)

// ================================================================================================================================
//                                                        ~~  TEST SUITE  ~~
// ================================================================================================================================
// ================================================================================================================================

Suite *sprintf_suite(void) {
  Suite *suite = suite_create("test_s21_sprintf");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, Le_mins_inf);
  tcase_add_test(tc, Le_plus_inf);
  tcase_add_test(tc, Le_spac_inf);
  tcase_add_test(tc, Le_hash_inf);
  tcase_add_test(tc, Le_fzer_inf);
  tcase_add_test(tc, Le_mins_ng_inf);
  tcase_add_test(tc, Le_plus_ng_inf);
  tcase_add_test(tc, Le_spac_ng_inf);
  tcase_add_test(tc, Le_hash_ng_inf);
  tcase_add_test(tc, Le_fzer_ng_inf);

  tcase_add_test(tc, LE_mins_inf);
  tcase_add_test(tc, LE_plus_inf);
  tcase_add_test(tc, LE_spac_inf);
  tcase_add_test(tc, LE_hash_inf);
  tcase_add_test(tc, LE_fzer_inf);
  tcase_add_test(tc, LE_mins_ng_inf);
  tcase_add_test(tc, LE_plus_ng_inf);
  tcase_add_test(tc, LE_spac_ng_inf);
  tcase_add_test(tc, LE_hash_ng_inf);
  tcase_add_test(tc, LE_fzer_ng_inf);

  tcase_add_test(tc, Lf_mins_inf);
  tcase_add_test(tc, Lf_plus_inf);
  tcase_add_test(tc, Lf_spac_inf);
  tcase_add_test(tc, Lf_hash_inf);
  tcase_add_test(tc, Lf_fzer_inf);
  tcase_add_test(tc, Lf_mins_ng_inf);
  tcase_add_test(tc, Lf_plus_ng_inf);
  tcase_add_test(tc, Lf_spac_ng_inf);
  tcase_add_test(tc, Lf_hash_ng_inf);
  tcase_add_test(tc, Lf_fzer_ng_inf);

  tcase_add_test(tc, Lg_mins_inf);
  tcase_add_test(tc, Lg_plus_inf);
  tcase_add_test(tc, Lg_spac_inf);
  tcase_add_test(tc, Lg_hash_inf);
  tcase_add_test(tc, Lg_fzer_inf);
  tcase_add_test(tc, Lg_mins_ng_inf);
  tcase_add_test(tc, Lg_plus_ng_inf);
  tcase_add_test(tc, Lg_spac_ng_inf);
  tcase_add_test(tc, Lg_hash_ng_inf);
  tcase_add_test(tc, Lg_fzer_ng_inf);

  tcase_add_test(tc, LG_mins_inf);
  tcase_add_test(tc, LG_plus_inf);
  tcase_add_test(tc, LG_spac_inf);
  tcase_add_test(tc, LG_hash_inf);
  tcase_add_test(tc, LG_fzer_inf);
  tcase_add_test(tc, LG_mins_ng_inf);
  tcase_add_test(tc, LG_plus_ng_inf);
  tcase_add_test(tc, LG_spac_ng_inf);
  tcase_add_test(tc, LG_hash_ng_inf);
  tcase_add_test(tc, LG_fzer_ng_inf);

  suite_add_tcase(suite, tc);
  return suite;
}

// ================================================================================================================================
//                                                           ~~  MAIN  ~~
// ================================================================================================================================
// ================================================================================================================================

int main(int argc, char **argv) {
  Suite *s1 = sprintf_suite();

  SRunner *runner = srunner_create(s1);

  srunner_run_all(runner, CK_NORMAL);

  int failed = srunner_ntests_failed(runner);

  srunner_free(runner);

  return 0;
}