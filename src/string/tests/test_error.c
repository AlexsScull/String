#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../include/s21_string.h"

START_TEST(test_s21_strerror_negative) {
  ck_assert_str_eq(s21_strerror(-27), strerror(-27));
}
START_TEST(test_s21_strerror_0) {
  ck_assert_str_eq(s21_strerror(0), strerror(0));
}
START_TEST(test_s21_strerror_1) {
  ck_assert_str_eq(s21_strerror(1), strerror(1));
}
START_TEST(test_s21_strerror_2) {
  ck_assert_str_eq(s21_strerror(2), strerror(2));
}
START_TEST(test_s21_strerror_3) {
  ck_assert_str_eq(s21_strerror(3), strerror(3));
}
START_TEST(test_s21_strerror_4) {
  ck_assert_str_eq(s21_strerror(4), strerror(4));
}
START_TEST(test_s21_strerror_5) {
  ck_assert_str_eq(s21_strerror(5), strerror(5));
}
START_TEST(test_s21_strerror_6) {
  ck_assert_str_eq(s21_strerror(6), strerror(6));
}
START_TEST(test_s21_strerror_7) {
  ck_assert_str_eq(s21_strerror(7), strerror(7));
}
START_TEST(test_s21_strerror_8) {
  ck_assert_str_eq(s21_strerror(8), strerror(8));
}
START_TEST(test_s21_strerror_9) {
  ck_assert_str_eq(s21_strerror(9), strerror(9));
}
START_TEST(test_s21_strerror_10) {
  ck_assert_str_eq(s21_strerror(10), strerror(10));
}
START_TEST(test_s21_strerror_11) {
  ck_assert_str_eq(s21_strerror(11), strerror(11));
}
START_TEST(test_s21_strerror_12) {
  ck_assert_str_eq(s21_strerror(12), strerror(12));
}
START_TEST(test_s21_strerror_13) {
  ck_assert_str_eq(s21_strerror(13), strerror(13));
}
START_TEST(test_s21_strerror_14) {
  ck_assert_str_eq(s21_strerror(14), strerror(14));
}
START_TEST(test_s21_strerror_15) {
  ck_assert_str_eq(s21_strerror(15), strerror(15));
}
START_TEST(test_s21_strerror_16) {
  ck_assert_str_eq(s21_strerror(16), strerror(16));
}
START_TEST(test_s21_strerror_17) {
  ck_assert_str_eq(s21_strerror(17), strerror(17));
}
START_TEST(test_s21_strerror_18) {
  ck_assert_str_eq(s21_strerror(18), strerror(18));
}
START_TEST(test_s21_strerror_19) {
  ck_assert_str_eq(s21_strerror(19), strerror(19));
}
START_TEST(test_s21_strerror_20) {
  ck_assert_str_eq(s21_strerror(20), strerror(20));
}
START_TEST(test_s21_strerror_21) {
  ck_assert_str_eq(s21_strerror(21), strerror(21));
}
START_TEST(test_s21_strerror_22) {
  ck_assert_str_eq(s21_strerror(22), strerror(22));
}
START_TEST(test_s21_strerror_23) {
  ck_assert_str_eq(s21_strerror(23), strerror(23));
}
START_TEST(test_s21_strerror_24) {
  ck_assert_str_eq(s21_strerror(24), strerror(24));
}
START_TEST(test_s21_strerror_25) {
  ck_assert_str_eq(s21_strerror(25), strerror(25));
}
START_TEST(test_s21_strerror_26) {
  ck_assert_str_eq(s21_strerror(26), strerror(26));
}
START_TEST(test_s21_strerror_27) {
  ck_assert_str_eq(s21_strerror(27), strerror(27));
}
START_TEST(test_s21_strerror_28) {
  ck_assert_str_eq(s21_strerror(28), strerror(28));
}
START_TEST(test_s21_strerror_29) {
  ck_assert_str_eq(s21_strerror(29), strerror(29));
}
START_TEST(test_s21_strerror_30) {
  ck_assert_str_eq(s21_strerror(30), strerror(30));
}
START_TEST(test_s21_strerror_31) {
  ck_assert_str_eq(s21_strerror(31), strerror(31));
}
START_TEST(test_s21_strerror_32) {
  ck_assert_str_eq(s21_strerror(32), strerror(32));
}
START_TEST(test_s21_strerror_33) {
  ck_assert_str_eq(s21_strerror(33), strerror(33));
}
START_TEST(test_s21_strerror_34) {
  ck_assert_str_eq(s21_strerror(34), strerror(34));
}
START_TEST(test_s21_strerror_35) {
  ck_assert_str_eq(s21_strerror(35), strerror(35));
}
START_TEST(test_s21_strerror_36) {
  ck_assert_str_eq(s21_strerror(36), strerror(36));
}
START_TEST(test_s21_strerror_37) {
  ck_assert_str_eq(s21_strerror(37), strerror(37));
}
START_TEST(test_s21_strerror_38) {
  ck_assert_str_eq(s21_strerror(38), strerror(38));
}
START_TEST(test_s21_strerror_39) {
  ck_assert_str_eq(s21_strerror(39), strerror(39));
}
START_TEST(test_s21_strerror_40) {
  ck_assert_str_eq(s21_strerror(40), strerror(40));
}
START_TEST(test_s21_strerror_41) {
  ck_assert_str_eq(s21_strerror(41), strerror(41));
}
START_TEST(test_s21_strerror_42) {
  ck_assert_str_eq(s21_strerror(42), strerror(42));
}
START_TEST(test_s21_strerror_43) {
  ck_assert_str_eq(s21_strerror(43), strerror(43));
}
START_TEST(test_s21_strerror_44) {
  ck_assert_str_eq(s21_strerror(44), strerror(44));
}
START_TEST(test_s21_strerror_45) {
  ck_assert_str_eq(s21_strerror(45), strerror(45));
}
START_TEST(test_s21_strerror_46) {
  ck_assert_str_eq(s21_strerror(46), strerror(46));
}
START_TEST(test_s21_strerror_47) {
  ck_assert_str_eq(s21_strerror(47), strerror(47));
}
START_TEST(test_s21_strerror_48) {
  ck_assert_str_eq(s21_strerror(48), strerror(48));
}
START_TEST(test_s21_strerror_49) {
  ck_assert_str_eq(s21_strerror(49), strerror(49));
}
START_TEST(test_s21_strerror_50) {
  ck_assert_str_eq(s21_strerror(50), strerror(50));
}
START_TEST(test_s21_strerror_51) {
  ck_assert_str_eq(s21_strerror(51), strerror(51));
}
START_TEST(test_s21_strerror_52) {
  ck_assert_str_eq(s21_strerror(52), strerror(52));
}
START_TEST(test_s21_strerror_53) {
  ck_assert_str_eq(s21_strerror(53), strerror(53));
}
START_TEST(test_s21_strerror_54) {
  ck_assert_str_eq(s21_strerror(54), strerror(54));
}
START_TEST(test_s21_strerror_55) {
  ck_assert_str_eq(s21_strerror(55), strerror(55));
}
START_TEST(test_s21_strerror_56) {
  ck_assert_str_eq(s21_strerror(56), strerror(56));
}
START_TEST(test_s21_strerror_57) {
  ck_assert_str_eq(s21_strerror(57), strerror(57));
}
START_TEST(test_s21_strerror_58) {
  ck_assert_str_eq(s21_strerror(58), strerror(58));
}
START_TEST(test_s21_strerror_59) {
  ck_assert_str_eq(s21_strerror(59), strerror(59));
}
START_TEST(test_s21_strerror_60) {
  ck_assert_str_eq(s21_strerror(60), strerror(60));
}
START_TEST(test_s21_strerror_61) {
  ck_assert_str_eq(s21_strerror(61), strerror(61));
}
START_TEST(test_s21_strerror_62) {
  ck_assert_str_eq(s21_strerror(62), strerror(62));
}
START_TEST(test_s21_strerror_63) {
  ck_assert_str_eq(s21_strerror(63), strerror(63));
}
START_TEST(test_s21_strerror_64) {
  ck_assert_str_eq(s21_strerror(64), strerror(64));
}
START_TEST(test_s21_strerror_65) {
  ck_assert_str_eq(s21_strerror(65), strerror(65));
}
START_TEST(test_s21_strerror_66) {
  ck_assert_str_eq(s21_strerror(66), strerror(66));
}
START_TEST(test_s21_strerror_67) {
  ck_assert_str_eq(s21_strerror(67), strerror(67));
}
START_TEST(test_s21_strerror_68) {
  ck_assert_str_eq(s21_strerror(68), strerror(68));
}
START_TEST(test_s21_strerror_69) {
  ck_assert_str_eq(s21_strerror(69), strerror(69));
}
START_TEST(test_s21_strerror_70) {
  ck_assert_str_eq(s21_strerror(70), strerror(70));
}
START_TEST(test_s21_strerror_71) {
  ck_assert_str_eq(s21_strerror(71), strerror(71));
}
START_TEST(test_s21_strerror_72) {
  ck_assert_str_eq(s21_strerror(72), strerror(72));
}
START_TEST(test_s21_strerror_73) {
  ck_assert_str_eq(s21_strerror(73), strerror(73));
}
START_TEST(test_s21_strerror_74) {
  ck_assert_str_eq(s21_strerror(74), strerror(74));
}
START_TEST(test_s21_strerror_75) {
  ck_assert_str_eq(s21_strerror(75), strerror(75));
}
START_TEST(test_s21_strerror_76) {
  ck_assert_str_eq(s21_strerror(76), strerror(76));
}
START_TEST(test_s21_strerror_77) {
  ck_assert_str_eq(s21_strerror(77), strerror(77));
}
START_TEST(test_s21_strerror_78) {
  ck_assert_str_eq(s21_strerror(78), strerror(78));
}
START_TEST(test_s21_strerror_79) {
  ck_assert_str_eq(s21_strerror(79), strerror(79));
}
START_TEST(test_s21_strerror_80) {
  ck_assert_str_eq(s21_strerror(80), strerror(80));
}
START_TEST(test_s21_strerror_81) {
  ck_assert_str_eq(s21_strerror(81), strerror(81));
}
START_TEST(test_s21_strerror_82) {
  ck_assert_str_eq(s21_strerror(82), strerror(82));
}
START_TEST(test_s21_strerror_83) {
  ck_assert_str_eq(s21_strerror(83), strerror(83));
}
START_TEST(test_s21_strerror_84) {
  ck_assert_str_eq(s21_strerror(84), strerror(84));
}
START_TEST(test_s21_strerror_85) {
  ck_assert_str_eq(s21_strerror(85), strerror(85));
}
START_TEST(test_s21_strerror_86) {
  ck_assert_str_eq(s21_strerror(86), strerror(86));
}
START_TEST(test_s21_strerror_87) {
  ck_assert_str_eq(s21_strerror(87), strerror(87));
}
START_TEST(test_s21_strerror_88) {
  ck_assert_str_eq(s21_strerror(88), strerror(88));
}
START_TEST(test_s21_strerror_89) {
  ck_assert_str_eq(s21_strerror(89), strerror(89));
}
START_TEST(test_s21_strerror_90) {
  ck_assert_str_eq(s21_strerror(90), strerror(90));
}
START_TEST(test_s21_strerror_91) {
  ck_assert_str_eq(s21_strerror(91), strerror(91));
}
START_TEST(test_s21_strerror_92) {
  ck_assert_str_eq(s21_strerror(92), strerror(92));
}
START_TEST(test_s21_strerror_93) {
  ck_assert_str_eq(s21_strerror(93), strerror(93));
}
START_TEST(test_s21_strerror_94) {
  ck_assert_str_eq(s21_strerror(94), strerror(94));
}
START_TEST(test_s21_strerror_95) {
  ck_assert_str_eq(s21_strerror(95), strerror(95));
}
START_TEST(test_s21_strerror_96) {
  ck_assert_str_eq(s21_strerror(96), strerror(96));
}
START_TEST(test_s21_strerror_97) {
  ck_assert_str_eq(s21_strerror(97), strerror(97));
}
START_TEST(test_s21_strerror_98) {
  ck_assert_str_eq(s21_strerror(98), strerror(98));
}
START_TEST(test_s21_strerror_99) {
  ck_assert_str_eq(s21_strerror(99), strerror(99));
}
START_TEST(test_s21_strerror_100) {
  ck_assert_str_eq(s21_strerror(100), strerror(100));
}
START_TEST(test_s21_strerror_101) {
  ck_assert_str_eq(s21_strerror(101), strerror(101));
}
START_TEST(test_s21_strerror_102) {
  ck_assert_str_eq(s21_strerror(102), strerror(102));
}
START_TEST(test_s21_strerror_103) {
  ck_assert_str_eq(s21_strerror(103), strerror(103));
}
START_TEST(test_s21_strerror_104) {
  ck_assert_str_eq(s21_strerror(104), strerror(104));
}
START_TEST(test_s21_strerror_105) {
  ck_assert_str_eq(s21_strerror(105), strerror(105));
}
START_TEST(test_s21_strerror_106) {
  ck_assert_str_eq(s21_strerror(106), strerror(106));
}
START_TEST(test_s21_strerror_107) {
  ck_assert_str_eq(s21_strerror(107), strerror(107));
}
START_TEST(test_s21_strerror_108) {
  ck_assert_str_eq(s21_strerror(108), strerror(108));
}
START_TEST(test_s21_strerror_109) {
  ck_assert_str_eq(s21_strerror(109), strerror(109));
}
START_TEST(test_s21_strerror_110) {
  ck_assert_str_eq(s21_strerror(110), strerror(110));
}
START_TEST(test_s21_strerror_111) {
  ck_assert_str_eq(s21_strerror(111), strerror(111));
}
START_TEST(test_s21_strerror_112) {
  ck_assert_str_eq(s21_strerror(112), strerror(112));
}
START_TEST(test_s21_strerror_113) {
  ck_assert_str_eq(s21_strerror(113), strerror(113));
}
START_TEST(test_s21_strerror_114) {
  ck_assert_str_eq(s21_strerror(114), strerror(114));
}
START_TEST(test_s21_strerror_115) {
  ck_assert_str_eq(s21_strerror(115), strerror(115));
}
START_TEST(test_s21_strerror_116) {
  ck_assert_str_eq(s21_strerror(116), strerror(116));
}
START_TEST(test_s21_strerror_117) {
  ck_assert_str_eq(s21_strerror(117), strerror(117));
}
START_TEST(test_s21_strerror_118) {
  ck_assert_str_eq(s21_strerror(118), strerror(118));
}
START_TEST(test_s21_strerror_119) {
  ck_assert_str_eq(s21_strerror(119), strerror(119));
}
START_TEST(test_s21_strerror_120) {
  ck_assert_str_eq(s21_strerror(120), strerror(120));
}
START_TEST(test_s21_strerror_121) {
  ck_assert_str_eq(s21_strerror(121), strerror(121));
}
START_TEST(test_s21_strerror_122) {
  ck_assert_str_eq(s21_strerror(122), strerror(122));
}
START_TEST(test_s21_strerror_123) {
  ck_assert_str_eq(s21_strerror(123), strerror(123));
}
START_TEST(test_s21_strerror_124) {
  ck_assert_str_eq(s21_strerror(124), strerror(124));
}
START_TEST(test_s21_strerror_125) {
  ck_assert_str_eq(s21_strerror(125), strerror(125));
}
START_TEST(test_s21_strerror_126) {
  ck_assert_str_eq(s21_strerror(126), strerror(126));
}
START_TEST(test_s21_strerror_127) {
  ck_assert_str_eq(s21_strerror(127), strerror(127));
}
START_TEST(test_s21_strerror_128) {
  ck_assert_str_eq(s21_strerror(128), strerror(128));
}
START_TEST(test_s21_strerror_129) {
  ck_assert_str_eq(s21_strerror(129), strerror(129));
}
START_TEST(test_s21_strerror_130) {
  ck_assert_str_eq(s21_strerror(130), strerror(130));
}
START_TEST(test_s21_strerror_131) {
  ck_assert_str_eq(s21_strerror(131), strerror(131));
}
START_TEST(test_s21_strerror_132) {
  ck_assert_str_eq(s21_strerror(132), strerror(132));
}
START_TEST(test_s21_strerror_133) {
  ck_assert_str_eq(s21_strerror(133), strerror(133));
}
START_TEST(test_s21_strerror_134) {
  ck_assert_str_eq(s21_strerror(134), strerror(134));
}
START_TEST(test_s21_strerror_135) {
  ck_assert_str_eq(s21_strerror(135), strerror(135));
}
START_TEST(test_s21_strerror_66666) {
  ck_assert_str_eq(s21_strerror(66666), strerror(66666));
}

Suite *error_suite(void) {
  Suite *s = suite_create("test_error");
  TCase *tc_strerror = tcase_create("Core");
  tcase_add_test(tc_strerror, test_s21_strerror_negative);
  tcase_add_test(tc_strerror, test_s21_strerror_0);
  tcase_add_test(tc_strerror, test_s21_strerror_1);
  tcase_add_test(tc_strerror, test_s21_strerror_2);
  tcase_add_test(tc_strerror, test_s21_strerror_3);
  tcase_add_test(tc_strerror, test_s21_strerror_4);
  tcase_add_test(tc_strerror, test_s21_strerror_5);
  tcase_add_test(tc_strerror, test_s21_strerror_6);
  tcase_add_test(tc_strerror, test_s21_strerror_7);
  tcase_add_test(tc_strerror, test_s21_strerror_8);
  tcase_add_test(tc_strerror, test_s21_strerror_9);
  tcase_add_test(tc_strerror, test_s21_strerror_10);
  tcase_add_test(tc_strerror, test_s21_strerror_11);
  tcase_add_test(tc_strerror, test_s21_strerror_12);
  tcase_add_test(tc_strerror, test_s21_strerror_13);
  tcase_add_test(tc_strerror, test_s21_strerror_14);
  tcase_add_test(tc_strerror, test_s21_strerror_15);
  tcase_add_test(tc_strerror, test_s21_strerror_16);
  tcase_add_test(tc_strerror, test_s21_strerror_17);
  tcase_add_test(tc_strerror, test_s21_strerror_18);
  tcase_add_test(tc_strerror, test_s21_strerror_19);
  tcase_add_test(tc_strerror, test_s21_strerror_20);
  tcase_add_test(tc_strerror, test_s21_strerror_21);
  tcase_add_test(tc_strerror, test_s21_strerror_22);
  tcase_add_test(tc_strerror, test_s21_strerror_23);
  tcase_add_test(tc_strerror, test_s21_strerror_24);
  tcase_add_test(tc_strerror, test_s21_strerror_25);
  tcase_add_test(tc_strerror, test_s21_strerror_26);
  tcase_add_test(tc_strerror, test_s21_strerror_27);
  tcase_add_test(tc_strerror, test_s21_strerror_28);
  tcase_add_test(tc_strerror, test_s21_strerror_29);
  tcase_add_test(tc_strerror, test_s21_strerror_30);
  tcase_add_test(tc_strerror, test_s21_strerror_31);
  tcase_add_test(tc_strerror, test_s21_strerror_32);
  tcase_add_test(tc_strerror, test_s21_strerror_33);
  tcase_add_test(tc_strerror, test_s21_strerror_34);
  tcase_add_test(tc_strerror, test_s21_strerror_35);
  tcase_add_test(tc_strerror, test_s21_strerror_36);
  tcase_add_test(tc_strerror, test_s21_strerror_37);
  tcase_add_test(tc_strerror, test_s21_strerror_38);
  tcase_add_test(tc_strerror, test_s21_strerror_39);
  tcase_add_test(tc_strerror, test_s21_strerror_40);
  tcase_add_test(tc_strerror, test_s21_strerror_41);
  tcase_add_test(tc_strerror, test_s21_strerror_42);
  tcase_add_test(tc_strerror, test_s21_strerror_43);
  tcase_add_test(tc_strerror, test_s21_strerror_44);
  tcase_add_test(tc_strerror, test_s21_strerror_45);
  tcase_add_test(tc_strerror, test_s21_strerror_46);
  tcase_add_test(tc_strerror, test_s21_strerror_47);
  tcase_add_test(tc_strerror, test_s21_strerror_48);
  tcase_add_test(tc_strerror, test_s21_strerror_49);
  tcase_add_test(tc_strerror, test_s21_strerror_50);
  tcase_add_test(tc_strerror, test_s21_strerror_51);
  tcase_add_test(tc_strerror, test_s21_strerror_52);
  tcase_add_test(tc_strerror, test_s21_strerror_53);
  tcase_add_test(tc_strerror, test_s21_strerror_54);
  tcase_add_test(tc_strerror, test_s21_strerror_55);
  tcase_add_test(tc_strerror, test_s21_strerror_56);
  tcase_add_test(tc_strerror, test_s21_strerror_57);
  tcase_add_test(tc_strerror, test_s21_strerror_58);
  tcase_add_test(tc_strerror, test_s21_strerror_59);
  tcase_add_test(tc_strerror, test_s21_strerror_60);
  tcase_add_test(tc_strerror, test_s21_strerror_61);
  tcase_add_test(tc_strerror, test_s21_strerror_62);
  tcase_add_test(tc_strerror, test_s21_strerror_63);
  tcase_add_test(tc_strerror, test_s21_strerror_64);
  tcase_add_test(tc_strerror, test_s21_strerror_65);
  tcase_add_test(tc_strerror, test_s21_strerror_66);
  tcase_add_test(tc_strerror, test_s21_strerror_67);
  tcase_add_test(tc_strerror, test_s21_strerror_68);
  tcase_add_test(tc_strerror, test_s21_strerror_69);
  tcase_add_test(tc_strerror, test_s21_strerror_70);
  tcase_add_test(tc_strerror, test_s21_strerror_71);
  tcase_add_test(tc_strerror, test_s21_strerror_72);
  tcase_add_test(tc_strerror, test_s21_strerror_73);
  tcase_add_test(tc_strerror, test_s21_strerror_74);
  tcase_add_test(tc_strerror, test_s21_strerror_75);
  tcase_add_test(tc_strerror, test_s21_strerror_76);
  tcase_add_test(tc_strerror, test_s21_strerror_77);
  tcase_add_test(tc_strerror, test_s21_strerror_78);
  tcase_add_test(tc_strerror, test_s21_strerror_79);
  tcase_add_test(tc_strerror, test_s21_strerror_80);
  tcase_add_test(tc_strerror, test_s21_strerror_81);
  tcase_add_test(tc_strerror, test_s21_strerror_82);
  tcase_add_test(tc_strerror, test_s21_strerror_83);
  tcase_add_test(tc_strerror, test_s21_strerror_84);
  tcase_add_test(tc_strerror, test_s21_strerror_85);
  tcase_add_test(tc_strerror, test_s21_strerror_86);
  tcase_add_test(tc_strerror, test_s21_strerror_87);
  tcase_add_test(tc_strerror, test_s21_strerror_88);
  tcase_add_test(tc_strerror, test_s21_strerror_89);
  tcase_add_test(tc_strerror, test_s21_strerror_90);
  tcase_add_test(tc_strerror, test_s21_strerror_91);
  tcase_add_test(tc_strerror, test_s21_strerror_92);
  tcase_add_test(tc_strerror, test_s21_strerror_93);
  tcase_add_test(tc_strerror, test_s21_strerror_94);
  tcase_add_test(tc_strerror, test_s21_strerror_95);
  tcase_add_test(tc_strerror, test_s21_strerror_96);
  tcase_add_test(tc_strerror, test_s21_strerror_97);
  tcase_add_test(tc_strerror, test_s21_strerror_98);
  tcase_add_test(tc_strerror, test_s21_strerror_99);
  tcase_add_test(tc_strerror, test_s21_strerror_100);
  tcase_add_test(tc_strerror, test_s21_strerror_101);
  tcase_add_test(tc_strerror, test_s21_strerror_102);
  tcase_add_test(tc_strerror, test_s21_strerror_103);
  tcase_add_test(tc_strerror, test_s21_strerror_104);
  tcase_add_test(tc_strerror, test_s21_strerror_105);
  tcase_add_test(tc_strerror, test_s21_strerror_106);
  tcase_add_test(tc_strerror, test_s21_strerror_107);
  tcase_add_test(tc_strerror, test_s21_strerror_108);
  tcase_add_test(tc_strerror, test_s21_strerror_109);
  tcase_add_test(tc_strerror, test_s21_strerror_110);
  tcase_add_test(tc_strerror, test_s21_strerror_111);
  tcase_add_test(tc_strerror, test_s21_strerror_112);
  tcase_add_test(tc_strerror, test_s21_strerror_113);
  tcase_add_test(tc_strerror, test_s21_strerror_114);
  tcase_add_test(tc_strerror, test_s21_strerror_115);
  tcase_add_test(tc_strerror, test_s21_strerror_116);
  tcase_add_test(tc_strerror, test_s21_strerror_117);
  tcase_add_test(tc_strerror, test_s21_strerror_118);
  tcase_add_test(tc_strerror, test_s21_strerror_119);
  tcase_add_test(tc_strerror, test_s21_strerror_120);
  tcase_add_test(tc_strerror, test_s21_strerror_121);
  tcase_add_test(tc_strerror, test_s21_strerror_122);
  tcase_add_test(tc_strerror, test_s21_strerror_123);
  tcase_add_test(tc_strerror, test_s21_strerror_124);
  tcase_add_test(tc_strerror, test_s21_strerror_125);
  tcase_add_test(tc_strerror, test_s21_strerror_126);
  tcase_add_test(tc_strerror, test_s21_strerror_127);
  tcase_add_test(tc_strerror, test_s21_strerror_128);
  tcase_add_test(tc_strerror, test_s21_strerror_129);
  tcase_add_test(tc_strerror, test_s21_strerror_130);
  tcase_add_test(tc_strerror, test_s21_strerror_131);
  tcase_add_test(tc_strerror, test_s21_strerror_132);
  tcase_add_test(tc_strerror, test_s21_strerror_133);
  tcase_add_test(tc_strerror, test_s21_strerror_134);
  tcase_add_test(tc_strerror, test_s21_strerror_135);
  tcase_add_test(tc_strerror, test_s21_strerror_66666);
  suite_add_tcase(s, tc_strerror);
  return s;
}

/**
 * Точка входа в программу
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 *
 * Использование:
 *   ./test      - обычный режим (вывод только ошибок)
 *   ./test +    - подробный режим (вывод всех тестов)
 */
int main(int argc, char **argv) {
  int failed = 0;
  Suite *s = error_suite();
  SRunner *runner = srunner_create(s);

  // Устанавливаем режим вывода в зависимости от аргументов
  if (argc > 1 && strcmp(argv[1], "+") == 0) {
    srunner_run_all(runner, CK_VERBOSE);  // Подробный вывод
  } else {
    srunner_run_all(runner, CK_NORMAL);  // Только ошибки
  }

  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}