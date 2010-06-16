/* 
 * File:   args.h
 * Author: russ
 *
 * Created on May 28, 2010, 7:47 AM
 */

#ifndef _ARGS_H
#define	_ARGS_H

#ifdef	__cplusplus
extern "C" {
#endif

extern int get_debug();

extern char *get_vmargs();

extern char *get_classpath();

extern char *get_clojure_main() ;

extern char *get_clojure_args();

extern char *get_user_classpath();

extern char *get_jline_main();

extern int get_use_jline();

extern int get_use_contrib();

extern char *get_vmargs();

extern void process_args( int argc, char** argv );

extern void initArgs();

#ifdef	__cplusplus
}
#endif

#endif	/* _ARGS_H */

