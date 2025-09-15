#include "s21_string.h"

// ==================== МАКРОСЫ ОШИБОК ====================
#if defined __APPLE__ || defined __MACH__
#define MAX_ERRNO 106
#define MIN_ERRNO 0
static const char *error_messages[] = {
    "Undefined error: 0",                         // 0
    "Operation not permitted",                    // 1
    "No such file or directory",                  // 2
    "No such process",                            // 3
    "Interrupted system call",                    // 4
    "Input/output error",                         // 5
    "Device not configured",                      // 6
    "Argument list too long",                     // 7
    "Exec format error",                          // 8
    "Bad file descriptor",                        // 9
    "No child processes",                         // 10
    "Resource deadlock avoided",                  // 11
    "Cannot allocate memory",                     // 12
    "Permission denied",                          // 13
    "Bad address",                                // 14
    "Block device required",                      // 15
    "Resource busy",                              // 16
    "File exists",                                // 17
    "Cross-device link",                          // 18
    "Operation not supported by device",          // 19
    "Not a directory",                            // 20
    "Is a directory",                             // 21
    "Invalid argument",                           // 22
    "Too many open files in system",              // 23
    "Too many open files",                        // 24
    "Inappropriate ioctl for device",             // 25
    "Text file busy",                             // 26
    "File too large",                             // 27
    "No space left on device",                    // 28
    "Illegal seek",                               // 29
    "Read-only file system",                      // 30
    "Too many links",                             // 31
    "Broken pipe",                                // 32
    "Numerical argument out of domain",           // 33
    "Result too large",                           // 34
    "Resource temporarily unavailable",           // 35
    "Operation now in progress",                  // 36
    "Operation already in progress",              // 37
    "Socket operation on non-socket",             // 38
    "Destination address required",               // 39
    "Message too long",                           // 40
    "Protocol wrong type for socket",             // 41
    "Protocol not available",                     // 42
    "Protocol not supported",                     // 43
    "Socket type not supported",                  // 44
    "Operation not supported",                    // 45
    "Protocol family not supported",              // 46
    "Address family not supported by protocol",   // 47
    "Address already in use",                     // 48
    "Can't assign requested address",             // 49
    "Network is down",                            // 50
    "Network is unreachable",                     // 51
    "Network dropped connection on reset",        // 52
    "Software caused connection abort",           // 53
    "Connection reset by peer",                   // 54
    "No buffer space available",                  // 55
    "Socket is already connected",                // 56
    "Socket is not connected",                    // 57
    "Can't send after socket shutdown",           // 58
    "Too many references: can't splice",          // 59
    "Operation timed out",                        // 60
    "Connection refused",                         // 61
    "Too many levels of symbolic links",          // 62
    "File name too long",                         // 63
    "Host is down",                               // 64
    "No route to host",                           // 65
    "Directory not empty",                        // 66
    "Too many processes",                         // 67
    "Too many users",                             // 68
    "Disc quota exceeded",                        // 69
    "Stale NFS file handle",                      // 70
    "Too many levels of remote in path",          // 71
    "RPC struct is bad",                          // 72
    "RPC version wrong",                          // 73
    "RPC prog. not avail",                        // 74
    "Program version wrong",                      // 75
    "Bad procedure for program",                  // 76
    "No locks available",                         // 77
    "Function not implemented",                   // 78
    "Inappropriate file type or format",          // 79
    "Authentication error",                       // 80
    "Need authenticator",                         // 81
    "Device power is off",                        // 82
    "Device error",                               // 83
    "Value too large to be stored in data type",  // 84
    "Bad executable (or shared library)",         // 85
    "Bad CPU type in executable",                 // 86
    "Shared library version mismatch",            // 87
    "Malformed Mach-o file",                      // 88
    "Operation canceled",                         // 89
    "Identifier removed",                         // 90
    "No message of desired type",                 // 91
    "Illegal byte sequence",                      // 92
    "Attribute not found",                        // 93
    "Bad message",                                // 94
    "Reserved",                                   // 95 (EMULTIHOP)
    "No message available on STREAM",             // 96
    "Reserved",                                   // 97 (ENOLINK)
    "No STREAM resources",                        // 98
    "Not a STREAM",                               // 99
    "Protocol error",                             // 100
    "STREAM ioctl timeout",                       // 101
    "Operation not supported on socket",          // 102
    "Policy not found",                           // 103
    "State not recoverable",                      // 104
    "Previous owner died",                        // 105
    "Interface output queue is full"              // 106
};
#elif __linux__
#define MAX_ERRNO 134
#define MIN_ERRNO 0
static const char *error_messages[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};
#else
#define MAX_ERRMSG 0
#define MAX_ERRSTR "Unknown error"
#endif

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