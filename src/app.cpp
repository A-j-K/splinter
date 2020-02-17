

#include <stdio.h>
#include <unistd.h>

#include "app.hpp"

#ifdef __cplusplus
extern "C" {
#endif

static appcontext_t app_context;

// Forward declarations
static void process_args(int, char**);

int run_app(int argc, char *argv[])
{
	config_t *p_config = NULL;
	appcontext_pt p_context = get_app_context();

	// Provide some defaults before commandline args processing.
	p_context->_p_config_filename = "/etc/splinter.conf";

	// Now process commandline args, if any.
	process_args(argc, argv);


	// Load the application configuration.
	p_config_file = (char*)p_context->_p_config_filename;
	config_init(p_config);
	if(config_read_file(p_config, p_config_file) != CONFIG_TRUE) {
		printf("Failed to read conf file at line %d: %s\n",
			config_error_line(p_config),
			config_error_text(p_config)
		);
		config_destroy(p_config);
		return -1;
	}

	printf("Hello World\n");
	return 0;
}


appcontext_pt get_app_context()
{
	return &app_context;
}

config_t* get_app_config()
{
	return &(get_app_context()->_config);
}

static void process_args(int argc, char** argv)
{
	int opt;
	while((opt = getopt(argc, argv, "f:")) != -1) {
		switch(opt) {
		case 'f':
			printf("option: %s:\n", optarg);
			break; 
		}
	}
}

#ifdef __cplusplus
}
#endif

