/* 
 * File:   paths.h
 * Author: russ
 *
 * Created on June 10, 2010, 10:07 PM
 */

#ifndef _PATHS_H
#define	_PATHS_H

#ifdef	__cplusplus
extern "C" {
#endif

extern char *get_base_dir();
extern char *get_lib_dir();
extern char *get_jline_jar();
extern char *get_clojure_jar();
extern char *get_clojure_contrib_jar();
extern char *get_java_cmd();


extern void initPaths();


#ifdef	__cplusplus
}
#endif

#endif	/* _PATHS_H */

