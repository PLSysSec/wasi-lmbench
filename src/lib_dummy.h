#include <unistd.h>

// emulate getpid and other simple functions not supported by my version of wasi-libc
pid_t getpid(void);

pid_t getppid(void);

int getpagesize(void);
