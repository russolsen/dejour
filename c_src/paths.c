#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


static char *base_dir;
static char *lib_dir;
static char *sys_lib_dir;
static char *jline_jar;
static char *clojure_jar;
static char *java_cmd;

char *get_base_dir() { return base_dir; }
char *get_sys_lib_dir() { return sys_lib_dir; }
char *get_lib_dir() { return lib_dir; }
char *get_jline_jar() { return jline_jar; }
char *get_clojure_jar() { return clojure_jar; }
char *get_java_cmd() { return java_cmd; }

/**
 * Allocate enough space for a path.
 */
static char* new_pathname() {
    calloc( 1, MAX_PATH );
}
/*
 * Modify the path by lobbing off the final bit.
 * So '/aaa/bbb/ccc => /aaa/bbb
 * Changes the string in place.
 */
static char* dirname( char *path ) {
    char *p = strrchr(path, '\\');
    if ( p ) {
        *p = (char)0;
    }
}

/**
 * Return the path to the base directory
 * of this application.
 */
static char *compute_base_dir() {
    char* path = new_pathname();
    GetModuleFileName(NULL, path, MAX_PATH );
    dirname( path );
    dirname( path );
    return path;
}

/**
 * Return the path to the lib directory.
 */
static char *compute_lib_dir() {
    char* path = compute_base_dir();
    strcat( path, "\\lib");
    return path;
}

/**
 * Return the path to the system lib directory.
 */
static char *compute_sys_lib_dir() {
    char* path = compute_base_dir();
    strcat( path, "\\syslib");
    return path;
}

/**
 * Get the path to the clojure.jar file.
 */
static char *compute_clojure_jar( ) {
    char* path = compute_lib_dir();
    strcat( path, "\\clojure.jar");
    return path;
}

/**
 * Get the path to the jline.jar file.
 */
static char *compute_jline_jar( ) {
    char* path = compute_sys_lib_dir();
    strcat( path, "\\jline.jar");
    return path;
}


#ifdef NO_CONSOLE
#    define JAVA_CMD "javaw" 
#else
#    define JAVA_CMD "java" 
#endif

/**
 * Get the java command.
 */
static char *compute_java_cmd( ) {
    char* cmd = new_pathname();
    if ( getenv( "JAVA_HOME" ) ) {
        strcpy( cmd, getenv( "JAVA_HOME" ) );
        strcat( cmd, "\\bin\\" );
        strcat( cmd, JAVA_CMD );
    }
    else {
        strcat( cmd, JAVA_CMD );
    }
    return cmd;
}

void initPaths() {
    base_dir = compute_base_dir();
    lib_dir = compute_lib_dir();
    sys_lib_dir = compute_sys_lib_dir();
    jline_jar = compute_jline_jar();
    clojure_jar = compute_clojure_jar();
    java_cmd = compute_java_cmd();
}

