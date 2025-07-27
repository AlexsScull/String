#include "../include/s21_string.h"

char *s21_strerror(int errnum) {
  static char res[64];

  if (errnum >= 0 && errnum <= MAX_ERRNO - 1) {
    snprintf(res, sizeof(res), "%s", error_messages[errnum]);
  } else {
    snprintf(res, sizeof(res), "Unknown error %d", errnum);
  }

  return res;
}
