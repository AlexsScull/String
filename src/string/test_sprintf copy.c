
// TEST_SPRINTF(test_s21_sprintf_d_min_pl, "int: %d", INT_MIN - 1, int)
// TEST_SPRINTF(test_s21_sprintf_d_max_pl, "int: %d", INT_MAX + 1, int)
// TEST_SPRINTF(test_s21_sprintf_d_null, "int: %d", NULL, int)

// %i - int
// TEST_SPRINTF(test_s21_sprintf_i_min_pl, "int: %i", INT_MIN - 1, int)
// TEST_SPRINTF(test_s21_sprintf_i_max_pl, "int: %i", INT_MAX + 1, int)
// TEST_SPRINTF(test_s21_sprintf_i_null, "int: %i", NULL, int)

// %o - unsigned int
// TEST_SPRINTF(test_s21_sprintf_o_min_pl, "unsigned int: %o", 0 - 1, unsigned int)
// TEST_SPRINTF(test_s21_sprintf_o_max_pl, "unsigned int: %o", UINT_MAX + 1, unsigned int)
// TEST_SPRINTF(test_s21_sprintf_o_null, "unsigned int: %o", NULL, unsigned int)

// %u - unsigned int
// TEST_SPRINTF(test_s21_sprintf_u_min_pl, "unsigned int: %u", 0 - 1, unsigned int)
// TEST_SPRINTF(test_s21_sprintf_u_max_pl, "unsigned int: %u", UINT_MAX + 1, unsigned int)
// TEST_SPRINTF(test_s21_sprintf_u_null, "unsigned int: %u", NULL, unsigned int)

// %x - unsigned int
// TEST_SPRINTF(test_s21_sprintf_x_min_pl, "unsigned int: %x", 0 - 1, unsigned int)
// TEST_SPRINTF(test_s21_sprintf_x_max_pl, "unsigned int: %x", UINT_MAX + 1, unsigned int)
// TEST_SPRINTF(test_s21_sprintf_x_null, "unsigned int: %x", NULL, unsigned int)

// %X - unsigned int
// TEST_SPRINTF(test_s21_sprintf_X_min_pl, "unsigned int: %X", 0 - 1, unsigned int)
// TEST_SPRINTF(test_s21_sprintf_X_max_pl, "unsigned int: %X", USHRT_MAX + 1, unsigned int)
// TEST_SPRINTF(test_s21_sprintf_X_null, "unsigned int: %X", NULL, unsigned int)

// ================================================================
// Модификатор h (short)
// ================================================================

// %hd - short
// TEST_SPRINTF(test_s21_sprintf_hd_min_pl, "short: %hd", SHRT_MIN - 1, short)
// TEST_SPRINTF(test_s21_sprintf_hd_max_pl, "short: %hd", SHRT_MAX + 1, short)
// TEST_SPRINTF(test_s21_sprintf_hd_null, "short: %hd", NULL, short)

// %hi - short
// TEST_SPRINTF(test_s21_sprintf_hi_min_pl, "short: %hi", SHRT_MIN - 1, short)
// TEST_SPRINTF(test_s21_sprintf_hi_max_pl, "short: %hi", SHRT_MAX + 1, short)
// TEST_SPRINTF(test_s21_sprintf_hi_null, "short: %hi", NULL, short)

// %ho - unsigned short
// TEST_SPRINTF(test_s21_sprintf_ho_min_pl, "unsigned short : %ho", 0 - 1, unsigned short)
// TEST_SPRINTF(test_s21_sprintf_ho_max_pl, "unsigned short : %ho", USHRT_MAX + 1, unsigned short)
// TEST_SPRINTF(test_s21_sprintf_ho_null, "unsigned short : %ho", NULL, unsigned short)

// TEST_SPRINTF(test_s21_sprintf_hu_min_pl, "unsigned short : %hu", 0 - 1, unsigned short)
// TEST_SPRINTF(test_s21_sprintf_hu_max_pl, "unsigned short : %hu", USHRT_MAX + 1, unsigned short)
// TEST_SPRINTF(test_s21_sprintf_hu_null, "unsigned short : %hu", NULL, unsigned short)

// %hx - unsigned short
// TEST_SPRINTF(test_s21_sprintf_hx_min_pl, "unsigned short : %hx", 0 - 1, unsigned short)
// TEST_SPRINTF(test_s21_sprintf_hx_max_pl, "unsigned short : %hx", USHRT_MAX + 1, unsigned short)
// TEST_SPRINTF(test_s21_sprintf_hx_null, "unsigned short : %hx", NULL, unsigned short)

// %hX - unsigned short
// TEST_SPRINTF(test_s21_sprintf_hX_min_pl, "unsigned short : %hX", 0 - 1, unsigned short)
// TEST_SPRINTF(test_s21_sprintf_hX_max_pl, "unsigned short : %hX", USHRT_MAX + 1, unsigned short)
// TEST_SPRINTF(test_s21_sprintf_hX_null, "unsigned short : %hX", NULL, unsigned short)

// ================================================================
// Модификатор hh (char)
// ================================================================

// %hhd - signed char
// TEST_SPRINTF(test_s21_sprintf_hhd_min_pl, "signed char: %hhd", SCHAR_MIN - 1, signed char)
// TEST_SPRINTF(test_s21_sprintf_hhd_max_pl, "signed char: %hhd", SCHAR_MAX + 1, signed char)
// TEST_SPRINTF(test_s21_sprintf_hhd_null, "signed char: %hhd", NULL, signed char)

// %hhi - signed char
// TEST_SPRINTF(test_s21_sprintf_hhi_min_pl, "signed char: %hhi", SCHAR_MIN - 1, signed char)
// TEST_SPRINTF(test_s21_sprintf_hhi_max_pl, "signed char: %hhi", SCHAR_MAX + 1, signed char)
// TEST_SPRINTF(test_s21_sprintf_hhi_null, "signed char: %hhi", NULL, signed char)

// %hho - unsigned char
// TEST_SPRINTF(test_s21_sprintf_hho_min_pl, "unsigned char : %hho", 0 - 1, unsigned char)
// TEST_SPRINTF(test_s21_sprintf_hho_max_pl, "unsigned char : %hho", UCHAR_MAX + 1, unsigned char)
// TEST_SPRINTF(test_s21_sprintf_hho_null, "unsigned char : %hho", NULL, unsigned char)

// %hhu - unsigned char
// TEST_SPRINTF(test_s21_sprintf_hhu_min_pl, "unsigned char : %hhu", 0 - 1, unsigned char)
// TEST_SPRINTF(test_s21_sprintf_hhu_max_pl, "unsigned char : %hhu", UCHAR_MAX + 1, unsigned char)
// TEST_SPRINTF(test_s21_sprintf_hhu_null, "unsigned char : %hhu", NULL, unsigned char)

// %hhx - unsigned char
// TEST_SPRINTF(test_s21_sprintf_hhx_min_pl, "unsigned char : %hhx", 0 - 1, unsigned char)
// TEST_SPRINTF(test_s21_sprintf_hhx_max_pl, "unsigned char : %hhx", UCHAR_MAX + 1, unsigned char)
// TEST_SPRINTF(test_s21_sprintf_hhx_null, "unsigned char : %hhx", NULL, unsigned char)

// %hhX - unsigned char
// TEST_SPRINTF(test_s21_sprintf_hhX_min_pl, "unsigned char : %hhX", 0 - 1, unsigned char)
// TEST_SPRINTF(test_s21_sprintf_hhX_max_pl, "unsigned char : %hhX", UCHAR_MAX + 1, unsigned char)
// TEST_SPRINTF(test_s21_sprintf_hhX_null, "unsigned char : %hhX", NULL, unsigned char)

// ================================================================
// Модификатор l (long)
// ================================================================

// %ld - long
// TEST_SPRINTF(test_s21_sprintf_ld_min_pl, "long: %ld", LONG_MIN - 1, long)
// TEST_SPRINTF(test_s21_sprintf_ld_max_pl, "long: %ld", LONG_MAX + 1, long)
// TEST_SPRINTF(test_s21_sprintf_ld_null, "long: %ld", NULL, long)

// %li - long
// TEST_SPRINTF(test_s21_sprintf_li_min_pl, "long: %li", LONG_MIN - 1, long)
// TEST_SPRINTF(test_s21_sprintf_li_max_pl, "long: %li", LONG_MAX + 1, long)
// TEST_SPRINTF(test_s21_sprintf_li_null, "long: %li", NULL, long)

// %lo - unsigned long
// TEST_SPRINTF(test_s21_sprintf_lo_min_pl, "unsigned long : %lo", 0 - 1, unsigned long)
// TEST_SPRINTF(test_s21_sprintf_lo_max_pl, "unsigned long : %lo", ULONG_MAX + 1, unsigned long)
// TEST_SPRINTF(test_s21_sprintf_lo_null, "unsigned long : %lo", NULL, unsigned long)

// %lu - unsigned long
// TEST_SPRINTF(test_s21_sprintf_lu_min_pl, "unsigned long : %lu", 0 - 1, unsigned long)
// TEST_SPRINTF(test_s21_sprintf_lu_max_pl, "unsigned long : %lu", ULONG_MAX + 1, unsigned long)
// TEST_SPRINTF(test_s21_sprintf_lu_null, "unsigned long : %lu", NULL, unsigned long)

// %lx - unsigned long
// TEST_SPRINTF(test_s21_sprintf_lx_min_pl, "unsigned long : %lx", 0 - 1, unsigned long)
// TEST_SPRINTF(test_s21_sprintf_lx_max_pl, "unsigned long : %lx", ULONG_MAX + 1, unsigned long)
// TEST_SPRINTF(test_s21_sprintf_lx_null, "unsigned long : %lx", NULL, unsigned long)

// %lX - unsigned long
// TEST_SPRINTF(test_s21_sprintf_lX_min_pl, "unsigned long : %lX", 0 - 1, unsigned long)
// TEST_SPRINTF(test_s21_sprintf_lX_max_pl, "unsigned long : %lX", USHRT_MAX + 1, unsigned long)
// TEST_SPRINTF(test_s21_sprintf_lX_null, "unsigned long : %lX", NULL, unsigned long)

// ================================================================
// Модификатор ll (long long)
// ================================================================

// TEST_SPRINTF(test_s21_sprintf_lld_min_pl, "long long: %lld", LLONG_MIN - 1, long long)
// TEST_SPRINTF(test_s21_sprintf_lld_max_pl, "long long: %lld", LLONG_MAX + 1, long long)
// TEST_SPRINTF(test_s21_sprintf_lld_null, "long long: %lld", NULL, long long)
// TEST_SPRINTF(test_s21_sprintf_lli_min_pl, "long long: %lli", LLONG_MIN - 1, long long)
// TEST_SPRINTF(test_s21_sprintf_lli_max_pl, "long long: %lli", LLONG_MAX + 1, long long)
// TEST_SPRINTF(test_s21_sprintf_lli_null, "long long: %lli", NULL, long long)
// TEST_SPRINTF(test_s21_sprintf_llo_min_pl, "unsigned long long: %llo", 0 - 1, unsigned long long)
// TEST_SPRINTF(test_s21_sprintf_llo_max_pl, "unsigned long long: %llo", ULLONG_MAX + 1, unsigned long long)
// TEST_SPRINTF(test_s21_sprintf_llo_null, "unsigned long long: %llo", NULL, unsigned long long)
// TEST_SPRINTF(test_s21_sprintf_llu_min_pl, "unsigned long long: %llu", 0 - 1, unsigned long long)
// TEST_SPRINTF(test_s21_sprintf_llu_max_pl, "unsigned long long: %llu", ULLONG_MAX + 1, unsigned long long)
// TEST_SPRINTF(test_s21_sprintf_llu_null, "unsigned long long: %llu", NULL, unsigned long long)
// TEST_SPRINTF(test_s21_sprintf_llx_min_pl, "unsigned long long: %llx", 0 - 1, unsigned long long)
// TEST_SPRINTF(test_s21_sprintf_llx_max_pl, "unsigned long long: %llx", ULLONG_MAX + 1, unsigned long long)
// TEST_SPRINTF(test_s21_sprintf_llx_null, "unsigned long long: %llx", NULL, unsigned long long)
// TEST_SPRINTF(test_s21_sprintf_llX_min_pl, "unsigned long long: %llX", 0 - 1, unsigned long long)
// TEST_SPRINTF(test_s21_sprintf_llX_max_pl, "unsigned long long: %llX", ULLONG_MAX + 1, unsigned long long)
// TEST_SPRINTF(test_s21_sprintf_llX_null, "unsigned long long: %llX", NULL, unsigned long long)
// TEST_SPRINTF(test_s21_sprintf_c_min_pl, "Char: %c", -128 - 1, char)
// TEST_SPRINTF(test_s21_sprintf_c_max_pl, "Char: %c", 127 + 1, char)
// TEST_SPRINTF(test_s21_sprintf_c_null, "Char: %c", NULL, char)
// TEST_SPRINTF(test_s21_sprintf_d_minus_zero_form, "%-05d", 123, int)
// TEST_SPRINTF(test_s21_sprintf_i_minus_zero_form, "%-05i", 123, int)
// TEST_SPRINTF(test_s21_sprintf_u_plus, "%+u", 123, int)
// TEST_SPRINTF(test_s21_sprintf_u_space, "% u", 123, int)
// TEST_SPRINTF(test_s21_sprintf_u_minus_zero_form, "%-05u", 123, int)
// TEST_SPRINTF(test_s21_sprintf_u_neg_plus, "%+u", -123, int)
// TEST_SPRINTF(test_s21_sprintf_u_neg_space, "% u", -123, int)
// TEST_SPRINTF(test_s21_sprintf_o_plus, "%+o", 123, int)
// TEST_SPRINTF(test_s21_sprintf_o_space, "% o", 123, int)
// TEST_SPRINTF(test_s21_sprintf_o_minus_zero_form, "%-05o", 123, int)
// TEST_SPRINTF(test_s21_sprintf_o_neg_plus, "%+o", -123, int)
// TEST_SPRINTF(test_s21_sprintf_o_neg_space, "% o", -123, int)
// TEST_SPRINTF(test_s21_sprintf_x_plus, "%+x", 123, int)
// TEST_SPRINTF(test_s21_sprintf_x_space, "% x", 123, int)
// TEST_SPRINTF(test_s21_sprintf_x_minus_zero_form, "%-05x", 123, int)
// TEST_SPRINTF(test_s21_sprintf_x_neg_plus, "%+x", -123, int)
// TEST_SPRINTF(test_s21_sprintf_x_neg_space, "% x", -123, int)
// TEST_SPRINTF(test_s21_sprintf_X_plus, "%+X", 123, int)
// TEST_SPRINTF(test_s21_sprintf_X_space, "% X", 123, int)
// TEST_SPRINTF(test_s21_sprintf_X_minus_zero_form, "%-05X", 123, int)
// TEST_SPRINTF(test_s21_sprintf_X_neg_plus, "%+X", -123, int)
// TEST_SPRINTF(test_s21_sprintf_X_neg_space, "% X", -123, int)
// TEST_SPRINTF(test_s21_sprintf_f_hash, "%#.0f", 123.0, double) // Проблемный тест
// TEST_SPRINTF(test_s21_sprintf_e_hash, "%#.0e", 123.0, double) // Проблемный тест
// TEST_SPRINTF(test_s21_sprintf_E_hash, "%#.0E", 123.0, double) // Проблемный тест
// TEST_SPRINTF(test_s21_sprintf_g_hash, "%#.0g", 123.0, double) // Проблемный тест
// TEST_SPRINTF(test_s21_sprintf_G_hash, "%#.0G", 123.0, double) // Проблемный тест





// static void setup_wide(void) {
//     if (!setlocale(LC_ALL, "en_US.UTF-8")) {
//         setlocale(LC_ALL, "C.UTF-8");
//     }
// }

// START_TEST(test_lc_zero_pad) {
//     wchar_t wc = L'字';
//     char buf1[32], buf2[32];
//     int res1 = s21_sprintf(buf1, "%05lc", wc);
//     int res2 = sprintf(buf2, "%05lc", wc);
//     ck_assert_str_eq(buf1, buf2);
//     ck_assert_int_eq(res1, res2);
// }
// END_TEST

// START_TEST(test_lc_combined_flags) {
//     wchar_t wc = L'@';
//     char buf1[32], buf2[32];
//     int res1 = s21_sprintf(buf1, "% -5lc", wc);
//     int res2 = sprintf(buf2, "% -5lc", wc);
//     ck_assert_str_eq(buf1, buf2);
//     ck_assert_int_eq(res1, res2);
// }
// END_TEST

// START_TEST(test_lc_invalid_flag) {
//     wchar_t wc = L'X';
//     char buf1[32], buf2[32];
//     int res1 = s21_sprintf(buf1, "%#lc", wc);
//     int res2 = sprintf(buf2, "%#lc", wc);
//     ck_assert_str_eq(buf1, buf2);
//     ck_assert_int_eq(res1, res2);
// }
// END_TEST

// START_TEST(test_ls_with_null_char) {
//     wchar_t ws[] = L"AB\0CD";
//     char buf1[32], buf2[32];
//     int res1 = s21_sprintf(buf1, "%ls", ws);
//     int res2 = sprintf(buf2, "%ls", ws);
//     ck_assert_str_eq(buf1, buf2);
//     ck_assert_int_eq(res1, res2);
// }
// END_TEST


// START_TEST(test_ls_zero_pad) {
//     wchar_t *ws = L"zero";
//     char buf1[32], buf2[32];
//     int res1 = s21_sprintf(buf1, "%010ls", ws);
//     int res2 = sprintf(buf2, "%010ls", ws);
//     ck_assert_str_eq(buf1, buf2);
//     ck_assert_int_eq(res1, res2);
// }
// END_TEST

// START_TEST(test_ls_large_string) {
//     wchar_t large_ws[1025];
//     for (int i = 0; i < 1024; i++) {
//         large_ws[i] = L'あ' + (i % 10);
//     }
//     large_ws[1024] = L'\0';
    
//     char *buf1 = malloc(5000);
//     char *buf2 = malloc(5000);
//     ck_assert_ptr_nonnull(buf1);
//     ck_assert_ptr_nonnull(buf2);
    
//     int res1 = s21_sprintf(buf1, "%ls", large_ws);
//     int res2 = sprintf(buf2, "%ls", large_ws);
//     ck_assert_str_eq(buf1, buf2);
//     ck_assert_int_eq(res1, res2);
    
//     free(buf1);
//     free(buf2);
// }
// END_TEST

// START_TEST(test_s21_sprintf_ls_null_wish_form) {
//     char buf1[32], buf2[32];
//     int res1 = s21_sprintf(buf1, "%.5ls", (wchar_t*)NULL);
//     int res2 = sprintf(buf2, "%.5ls", (wchar_t*)NULL);
//     ck_assert_str_eq(buf1, buf2);
//     ck_assert_int_eq(res1, res2);
// }
// END_TEST

// START_TEST(test_s21_sprintf_ls_null) {
//     char buf1[64], buf2[64];
//     int res1 = s21_sprintf(buf1, "wchar_t: %ls", (wchar_t*)NULL);
//     int res2 = sprintf(buf2, "wchar_t: %ls", (wchar_t*)NULL);
//     ck_assert_str_eq(buf1, buf2);
//     ck_assert_int_eq(res1, res2);
// }
// END_TEST
