#!/bin/bash

# ------------------------------------------------------------------------------------------------
a=-27
echo "START_TEST(test_s21_strerror_negative) { ck_assert_str_eq(s21_strerror($a), strerror($a)); }"
for (( i=0; i <= 135; i++ ))
do
echo "START_TEST(test_s21_strerror_$i) { ck_assert_str_eq(s21_strerror($i), strerror($i)); }"
done
j=66666
echo "START_TEST(test_s21_strerror_$j) { ck_assert_str_eq(s21_strerror($j), strerror($j)); }"

# ------------------------------------------------------------------------------------------------
echo "Suite *sscanf_suite(void) {"
echo "Suite *s = suite_create(\"s21_sscanf\");"
echo "TCase *tc_strerror = tcase_create(\"Core\");"


echo "  tcase_add_test(tc_strerror, test_s21_strerror_negative);"
for (( i=1; i <= 135; i++ ))
do
echo "  tcase_add_test(tc_strerror, test_s21_strerror_$i);"
done
echo "  tcase_add_test(tc_strerror, test_s21_strerror_$j);"


echo "  suite_add_tcase(s, tc_strerror);"
echo "  return s;"
echo "}"
# ------------------------------------------------------------------------------------------------

















