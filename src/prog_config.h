
#ifndef PROG_CONFIG_H_INCLUDED
#define PROG_CONFIG_H_INCLUDED

#include "prog_args.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _prog_config;
typedef struct _prog_config  prog_config_t;
typedef struct _prog_config *prog_config_pt;

prog_config_pt
prog_config_new(const char*, prog_args_pt);

void
prog_config_free(prog_config_pt);

int
prog_config_set_prog_args(prog_config_pt inp_self, prog_args_pt in_p);


#ifdef __cplusplus
}
#endif

#endif /* PROG_CONFIG_H_INCLUDED */

