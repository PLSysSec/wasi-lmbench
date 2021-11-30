#include "lib_dummy.h"

//taken from wasi-libc source code
pid_t getpid(void) {
    // Return an arbitrary value, greater than 1 which is special.
    return 42;
}

pid_t getppid(void) {
    // Return an arbitrary value, greater than 1 which is special.
    return 43;
}

// TODO: I should check how the benchmarks use this
// probably shoudln't matter though
pid_t getpagesize(void) {
    // Return an arbitrary value, greater than 1 which is special.
    return 4096;
}