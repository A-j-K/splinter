

#include <stdio.h>

#include "app.h"

#ifdef __cplusplus
extern "C" {
#endif

static prog_config_pt gp_config;

prog_config_pt
get_app_config()
{
	return gp_config;
}

int 
run_app(int argc, char *argv[])
{
	int rval = 0;

	gp_config = prog_config_new(
		"/etc/splinter.conf", 
		prog_args_new(argc, argv)
	);

	printf("Hello World\n");

	prog_config_free(gp_config);
	return rval;
}

#ifdef __cplusplus
}
#endif

