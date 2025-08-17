#include "../include/s21_string.h"

char *s21_strerror(int errnum) {
  static char res[64];
  const int num_errors = sizeof(error_messages) / sizeof(error_messages[0]);

  if (errnum >= 0 && errnum < num_errors) {
    snprintf(res, sizeof(res), "%s", error_messages[errnum]);
  } else {
    snprintf(res, sizeof(res), "Unknown error %d", errnum);
  }
  return res;
}