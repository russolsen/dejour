#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

/**
 * Return true if this argument needs quoting.
 */
static int needs_quotes( char* arg ) {
    if ( arg == NULL || strlen(arg) == 0 ) {
        return FALSE;
    }
    if ( *arg == '"' ) {
        return FALSE;
    }

    return strchr( arg, ' ' ) != NULL;
}

/**
 * Append arg to list, using separator as appropriate.
 * Quotes the argument if a) it isn't already surrounded by quotes,
 * b) it's non-empty and c) it contains a space.
 */
void add_list_with_quotes(char *list, char* arg, char *separator) {
    if (strlen(list) > 0 && strlen(arg) > 0) {
        strcat(list, separator);
    }

    if ( ! needs_quotes( arg ) ) {
        strcat(list, arg);
    }
    else {
        strcat( list, "\"" );
        strcat( list, arg );
        strcat( list, "\"" );
    }
}

/**
 * Append arg to list, using separator as appropriate.
 * Modifies list.
 */
void add_list(char *list, char* arg, char *separator) {
    if (strlen(list) > 0 && strlen(arg) > 0) {
        strcat(list, separator);
    }
    strcat(list, arg);
}

/**
 * Append new_element to path. Assumes that we are dealing
 * with a ; separated Windows classpath.
 * Modifies path.
 */
void add_to_path( char *path, char* new_element ) {
    add_list( path, new_element, ";");
}

/**
 * Count the number of files in dir.
 */
static int number_of_files_in( char *dir ){

    struct dirent * dp;
    DIR * dir_p = opendir (dir);

    int n=0;
    while ((dp = readdir (dir_p)) != NULL) {
        n++;
    }
    closedir (dir_p);
    return n;

}

/**
 * Return true if path ends with .jar
 */
static int is_jar_name( char* path ) {
    char *p_dot = strrchr(path, '.');
    return strcmp( p_dot, ".jar");
}

/**
 * Return a windows ; separated path of
 * all of the jar files in dir.
 */
char *path_of_all_files_in( char *dir ){

    int n = number_of_files_in( dir );

    char *path = calloc( n, MAX_PATH + 1);
    strcpy( path, "");

    struct dirent * dp;

    DIR * dir_p = opendir (dir);

    while ((dp = readdir (dir_p)) != NULL) {
        if ( is_jar_name(dp->d_name) ) {
            continue;
        }
        char full_file_path[MAX_PATH];
        strcpy( full_file_path, dir );
        strcat( full_file_path, "\\");
        strcat( full_file_path, dp->d_name);
        add_to_path(path, full_file_path);
    }
    closedir (dir_p);

    return path;
}
