
#ifndef PROG_ARGS_H_INCLUDED
#define PROG_ARGS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

struct _prog_args;
typedef struct _prog_args  prog_args_t;
typedef struct _prog_args *prog_args_pt;

prog_args_pt
prog_args_new(int argc, char *argv[]);

void
prog_args_free(prog_args_pt);

const char* 
prog_args_get_config_filename(prog_args_pt);

#ifdef __cplusplus
}
#endif

#endif /* PROG_ARGS_H_INCLUDED */

