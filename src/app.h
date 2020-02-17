#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include "prog_config.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Get application configuration pointer.
 */
prog_config_pt get_app_config();


/**
 * Used to run the application, essentially, main()
 * @param int argc
 * @param char *argv[]
 * @return int
 */
int run_app(int argc, char *argv[]);


#ifdef __cplusplus
}
#endif


#endif /* APP_H_INCLUDED */

