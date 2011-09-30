#include <stdio.h>
#include <windows.h>

static char vm_args[3000];
static char user_classpath[3000];
static char clojureArgs[3000];
static char clojureMain[1000];
static char jlineMain[1000];
static int debug = FALSE;

static int use_jline = TRUE;

static void add_vm_arg(char* arg) {
    add_list_with_quotes(vm_args, arg, " ");
}

static void add_user_classpath(char* file) {
    add_list(user_classpath, file, ";");
}

static void add_clojure_arg(char* arg) {
    add_list_with_quotes(clojureArgs, arg, " ");
}

static void arg_check(char *argument_name, int i, int argc) {
    if (i >= argc) {
        fprintf(stderr, "Option %s requires an argument\n", argument_name);
    }
}

/**
 * Return true if we are debugging.
 */
int get_debug() {
    return debug;
}

/**
 * Return true if we should use jline.
 */
int get_use_jline() {
    return use_jline;
}

/**
 * Return all the vm args in a single string.
 */
char *get_vmargs() {
    return vm_args;
}

/**
 * Return the jline main class.
 */
char *get_jline_main() {
    return jlineMain;
}

/**
 * Return the user specified classpath.
 */
char *get_user_classpath() {
    return user_classpath;
}

/**
 * Return the user specified clojure main class.
 */
char *get_clojure_main() {
    return clojureMain;
}

/**
 * Return the user specified clojure arguments.
 */
char *get_clojure_args() {
    return clojureArgs;
}

/**
 * Process all the program arguments, setting
 * the various flags and options as we go.
 */
void process_args(int argc, char** argv) {

    int i;

    for (i = 0; i < argc; i++) {
        char *arg = argv[i];

        if (strcmp(arg, "-debug") == 0) {
            debug = TRUE;
        }
        else if (strncmp(arg, "-J", 2) == 0) {
            add_vm_arg(arg + 2);
        }
        else if (strncmp(arg, "-D", 2) == 0) {
            add_vm_arg(arg);
        }
        else if (strncmp(arg, "-X", 2) == 0) {
            add_vm_arg(arg);
        }
        else if ((strcmp(arg, "-client") == 0) ||
                (strcmp(arg, "-hotspot") == 0) ||
                (strcmp(arg, "-server") == 0)) {
            add_vm_arg(arg);
        }
        else if ((strcmp(arg, "-classpath") == 0) ||
                (strcmp(arg, "-cp") == 0)) {
            arg_check(arg, ++i, argc);
            add_user_classpath(argv[i]);
        }

        else if (strcmp(arg, "-no-jline") == 0) {
            use_jline = FALSE;
            strcpy(jlineMain, "");
        }

        else if (strcmp(arg, "-jline-main") == 0) {
            arg_check(arg, ++i, argc);
            strcpy(jlineMain, argv[i]);
        }

        else if (strcmp(arg, "-main") == 0) {
            arg_check(arg, ++i, argc);
            strcpy(clojureMain, argv[i]);
        }

        else if (strcmp(arg, "--") == 0) {
            i++;
            break;
        }

        else {
            break;
        }

    }

    for (; i < argc; i++) {
        add_clojure_arg(argv[i]);
    }

}

void initArgs() {
    strcpy( vm_args, "" );
    strcpy( clojureArgs, "" );
    strcpy( user_classpath, "" );
    strcpy(jlineMain, "jline.ConsoleRunner");
    strcpy(clojureMain, "clojure.main");
}

