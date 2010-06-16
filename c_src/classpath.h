/* 
 * File:   classpath.h
 * Author: russ
 *
 * Created on June 10, 2010, 10:02 PM
 */

#ifndef _CLASSPATH_H
#define	_CLASSPATH_H

#ifdef	__cplusplus
extern "C" {
#endif

void add_list(char *list, char* arg, char *separator);

void add_list_with_quotes(char *list, char* arg, char *separator);

void add_to_path( char *path, char* new_element );

char *path_of_all_files_in( char *dir );


#ifdef	__cplusplus
}
#endif

#endif	/* _CLASSPATH_H */

