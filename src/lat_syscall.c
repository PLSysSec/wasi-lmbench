/*
 * lat_syscall.c - time simple system calls
 *
 * Copyright (c) 1996 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 */
char	*id = "$Id: s.lat_syscall.c 1.11 97/06/15 22:38:58-07:00 lm $\n";

#include "bench.h"
#define	FNAME "/usr/include/linux/types.h"

struct _state {
	int fd;
	char* file;
};

// instead of getppid (which would be emulated in lib_dummy)
// instead use sched_yield as a null syscall
void
do_null_syscall(iter_t iterations, void *cookie)
{
	struct _state *pState = (struct _state*)cookie;
	char	c;

	while (iterations-- > 0) {
		//getppid();
		__wasi_sched_yield();
	}
}

void
do_write(iter_t iterations, void *cookie)
{
	struct _state *pState = (struct _state*)cookie;
	char	c;

	while (iterations-- > 0) {
		if (write(pState->fd, &c, 1) != 1) {
			perror("/dev/null");
			return;
		}
	}
}

void
do_read(iter_t iterations, void *cookie)
{
	struct _state *pState = (struct _state*)cookie;
	char	c;

	while (iterations-- > 0) {
		if (read(pState->fd, &c, 1) != 1) {
			perror("/dev/zero");
			return;
		}
	}
}

void
do_stat(iter_t iterations, void *cookie)
{
	struct _state *pState = (struct _state*)cookie;
	struct	stat sbuf;

	while (iterations-- > 0) {
		if (stat(pState->file, &sbuf) == -1) {
			perror(pState->file);
			return;
		}
	}
}

void
do_fstat(iter_t iterations, void *cookie)
{
	struct _state *pState = (struct _state*)cookie;
	struct	stat sbuf;

	while (iterations-- > 0) {
		if (fstat(pState->fd, &sbuf) == -1) {
			perror("fstat");
			return;
		}
	}
}

void
do_openclose(iter_t iterations, void *cookie)
{
	struct _state *pState = (struct _state*)cookie;
	int	fd;

	while (iterations-- > 0) {
		fd = open(pState->file, O_RDONLY);
		if (fd == -1) {
			perror(pState->file);
			return;
		}
		close(fd);
	}
}

int
main(int ac, char **av)
{
	int parallel = 1;
	int warmup = 0;
	int repetitions = TRIES;
	int c;
	struct _state state;
	char* usage = "[-P <parallelism>] [-W <warmup>] [-N <repetitions>] null|read|write|stat|fstat|open [file]\n";

	while (( c = getopt(ac, av, "P:W:N:")) != EOF) {
		switch(c) {
		case 'P':
			parallel = atoi(optarg);
			if (parallel <= 0) lmbench_usage(ac, av, usage);
			break;
		case 'W':
			warmup = atoi(optarg);
			break;
		case 'N':
			repetitions = atoi(optarg);
			break;
		default:
			lmbench_usage(ac, av, usage);
			break;
		}
	}
	if (optind != ac - 1 && optind != ac - 2 ) {
		lmbench_usage(ac, av, usage);
	}
	
	state.file = FNAME;
	if (optind == ac - 2) 
		state.file = av[optind + 1];

	if (!strcmp("null", av[optind])) {
		benchmp(NULL, do_null_syscall, NULL, 0, parallel, 
			warmup, repetitions, &state);
		micro("Simple syscall", get_n());
	} else if (!strcmp("write", av[optind])) {
		state.fd = open("/dev/null", O_RDWR);
		if (state.fd == -1) {
			fprintf(stderr, "Simple write: -1\n");
			return(1);
		}
		benchmp(NULL, do_write, NULL, 0, parallel, 
			warmup, repetitions, &state);
		micro("Simple write", get_n());
		close(state.fd);
	} else if (!strcmp("read", av[optind])) {
		state.fd = open("/dev/zero", O_RDONLY);
		if (state.fd == -1) {
			fprintf(stderr, "Simple read: -1\n");
			return(1);
		}
		benchmp(NULL, do_read, NULL, 0, parallel, 
			warmup, repetitions, &state);
		micro("Simple read", get_n());
		close(state.fd);
	} else if (!strcmp("stat", av[optind])) {
		benchmp(NULL, do_stat, NULL, 0, parallel, 
			warmup, repetitions, &state);
		micro("Simple stat", get_n());
	} else if (!strcmp("fstat", av[optind])) {
		state.fd = open(state.file, O_RDONLY);
		if (state.fd == -1) {
			fprintf(stderr, "fstat: -1\n");
			return(1);
		}
		benchmp(NULL, do_fstat, NULL, 0, parallel, 
			warmup, repetitions, &state);
		micro("Simple fstat", get_n());
		close(state.fd);
	} else if (!strcmp("open", av[optind])) {
		benchmp(NULL, do_openclose, NULL, 0, parallel, 
			warmup, repetitions, &state);
		micro("Simple open/close", get_n());
	} else {
		lmbench_usage(ac, av, usage);
	}
	return(0);
}
