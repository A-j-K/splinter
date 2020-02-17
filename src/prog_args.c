
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "prog_args.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _prog_args
{
	const char*	p_config_filename;
};

prog_args_pt
prog_args_new(int argc, char *argv[])
{
	prog_args_pt p = (prog_args_pt)calloc(1, sizeof(prog_args_t));
	if(p) {
		int opt;
		while((opt = getopt(argc, argv, "f:")) != -1) {
			switch(opt) {
			case 'f':
				p->p_config_filename = strdup(optarg);
				break; 
			}
		}
	}
	return p;
}

void
prog_args_free(prog_args_pt in_p)
{
	if(in_p) {
		if(in_p->p_config_filename) free((void*)in_p->p_config_filename);
		free((void*)in_p);
	}
}

const char* 
prog_args_get_config_filename(prog_args_pt in_p)
{
	const char *rval = NULL;
	if(in_p && in_p->p_config_filename) {
		rval = in_p->p_config_filename;
	}
	return rval;
}

#ifdef __cplusplus
}
#endif

