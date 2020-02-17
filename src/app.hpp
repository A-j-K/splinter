#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include <libconfig.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _appcontext
{
	const char *_p_config_filename;
	config_t _config;
};
typedef struct _appcontext  appcontext_t;
typedef struct _appcontext *appcontext_pt;

/**
 * Used to run the application, essentially, main()
 * @param int argc
 * @param char *argv[]
 * @return int
 */
int run_app(int argc, char *argv[]);

/**
 * Used to get a pointer to the application context.
 * @return appconf_pt
 */
appcontext_pt get_app_context();

/**
 * Used to get a pointer to the application configuration.
 */
config_t* get_app_config();

#ifdef __cplusplus
}
#endif


#endif /* APP_H_INCLUDED */

