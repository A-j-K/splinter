
#include <string.h>
#include <stdlib.h>

#include "prog_args.h"
#include "prog_config.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _prog_config
{
	const char*	p_filename;
	prog_args_pt	p_args;
};

prog_config_pt
prog_config_new(const char* in_pfilename, prog_args_pt in_p)
{
	prog_config_pt p = (prog_config_pt)calloc(1, sizeof(prog_config_t));
	if(p) {
		const char* s = prog_args_get_config_filename(in_p);
		p->p_filename = s ? strdup(s) : strdup(in_pfilename);
		p->p_args = in_p;
	}
	return p;
}

void
prog_config_free(prog_config_pt in_p)
{
	if(in_p) {
		if(in_p->p_filename) free((void*)in_p->p_filename);
		if(in_p->p_args) prog_args_free(in_p->p_args);
		free((void*)in_p);
	}
}

int
prog_config_set_prog_args(prog_config_pt inp_self, prog_args_pt in_p)
{
	if(inp_self && in_p) {
		inp_self->p_args = in_p;
		return 0;
	}
	return -1;
}

#ifdef __cplusplus
}
#endif

