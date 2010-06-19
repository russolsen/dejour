#include <stdio.h>
#include <windows.h>

#include "args.h"
#include "paths.h"
#include "classpath.h"

#define MAX_CMD_LINE_LEN 32768

DWORD run_program( char *cmdline ) {

    STARTUPINFO si = {0};
    si.cb = sizeof (STARTUPINFO);
    PROCESS_INFORMATION pi = {0};

    DWORD rc = CreateProcess(NULL, cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
    if ( rc == 0 )
    {
        DWORD errorCode = GetLastError();
        fprintf( stderr, "Unable to run command: %s\n", cmdline );
        fprintf( stderr, "Error code: %d\n", errorCode );
        exit( errorCode );
    }

    DWORD exitCode = WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return exitCode;
}


int main(int argc, char **argv) {

    initArgs();
    initPaths();

    if (argc > 1) {
        process_args(argc - 1, argv + 1);
    }

    // Build the core classpath

    char classpath[MAX_CMD_LINE_LEN];
    strcpy( classpath, get_clojure_jar() );

    if ( get_use_contrib() ) {
        add_to_path( classpath, get_clojure_contrib_jar() );
    }

    if ( get_use_jline() ) {
        add_to_path( classpath, get_jline_jar() );
    }

    // Add in any jars found in the lib directory.

    add_to_path( classpath, get_lib_dir());

    add_to_path( classpath, path_of_all_files_in( get_lib_dir()));

    // Add in the user classpath from either the -cp
    // or -classpath arg or $CLASSPATH

    if ( strlen( get_user_classpath() ) > 0 ) {
        add_to_path( classpath, get_user_classpath() );
    }
    else if ( getenv("CLASSPATH") ) {
        add_to_path( classpath, getenv("CLASSPATH") );
    }

    // Build the command.

    char command_line[MAX_CMD_LINE_LEN];
    strcat( command_line, "" );

    // First the java command itself.

    add_list_with_quotes( command_line, get_java_cmd(), " " );

    // Then the -DCLOJURE_HOME=... paramter
    strcat( command_line, " -DCLOJURE_HOME=\"" );
    strcat( command_line, get_base_dir() );
    strcat( command_line, "\"" );

    add_list( command_line, get_vmargs(), " " );
    add_list( command_line, "-cp ", " ");
    add_list_with_quotes( command_line, classpath, " " );
    if ( get_use_jline() ) {
        add_list( command_line, get_jline_main(), " " );
    }
    add_list( command_line, get_clojure_main(), " " );
    add_list( command_line, get_clojure_args(), " " );

    // Either run the command or just print it out.
    
    DWORD status = 0;

    if ( get_debug() ) {
        printf( "%s\n", command_line );
    }
    else {
        status = run_program( command_line );
    }

    exit( status );

}
