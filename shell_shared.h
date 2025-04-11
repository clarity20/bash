// New header file created to break off function main() from shell.c and provide
// the new main.c and the remaining shell.c with all necessary header material

// (1) Defines/includes from the original shell.c
#define INSTALL_DEBUG_MODE

#include "config.h"

#include "bashtypes.h"
#if !defined (_MINIX) && defined (HAVE_SYS_FILE_H)
#  include <sys/file.h>
#endif
#include "posixstat.h"
#include "posixtime.h"
#include "bashansi.h"
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include "filecntl.h"
#if defined (HAVE_PWD_H)
#  include <pwd.h>
#endif

#if defined (HAVE_UNISTD_H)
#  include <unistd.h>
#endif

#include "bashintl.h"

#define NEED_SH_SETLINEBUF_DECL		/* used in externs.h */

#include "shell.h"
#include "parser.h"
#include "flags.h"
#include "trap.h"
#include "mailcheck.h"
#include "builtins.h"
#include "builtins/common.h"

#if defined (JOB_CONTROL)
#include "jobs.h"
#else
extern int running_in_background;
extern int initialize_job_control PARAMS((int));
extern int get_tty_state PARAMS((void));
#endif /* JOB_CONTROL */

#include "input.h"
#include "execute_cmd.h"
#include "findcmd.h"

#if defined (USING_BASH_MALLOC) && defined (DEBUG) && !defined (DISABLE_MALLOC_WRAPPERS)
#  include <malloc/shmalloc.h>
#elif defined (MALLOC_DEBUG) && defined (USING_BASH_MALLOC)
#  include <malloc/shmalloc.h>
#endif

#if defined (HISTORY)
#  include "bashhist.h"
#  include <readline/history.h>
#endif

#if defined (READLINE)
#  include <readline/readline.h>
#  include "bashline.h"
#endif

#include <tilde/tilde.h>
#include <glob/strmatch.h>

#if defined (__OPENNT)
#  include <opennt/opennt.h>
#endif

// (2) Make every function & variable previously hidden in shell.c visible to main.c, too.
// This requires declarations, externs, and conversion from static to automatic.

// (2a) functions
extern void exit_shell (int s);
extern void sh_exit (int s);
extern void subshell_exit (int s);
extern void set_exit_status (int s);
#if defined (RESTRICTED_SHELL)
extern int shell_is_restricted (char *name);
#endif
extern int maybe_make_restricted (char *name);
extern void disable_priv_mode ();
extern void unbind_args ();
extern void unset_bash_input (int check_zero);
extern void get_current_user_info ();

#ifdef __CYGWIN__
extern void _cygwin32_check_tmp ();
#endif

extern int parse_long_options PARAMS((char **, int, int));
extern int parse_shell_options PARAMS((char **, int, int));
extern int bind_args PARAMS((char **, int, int, int));

extern void start_debugger PARAMS((void));

extern void add_shopt_to_alist PARAMS((char *, int));
extern void run_shopt_alist PARAMS((void));

extern void execute_env_file PARAMS((char *));
extern void run_startup_files PARAMS((void));
extern int open_shell_script PARAMS((char *));
extern void set_bash_input PARAMS((void));
extern int run_one_command PARAMS((char *));
#if defined (WORDEXP_OPTION)
extern int run_wordexp PARAMS((char *));
#endif


extern int uidget();

void set_option_defaults PARAMS((void));
void reset_option_defaults PARAMS((void));

void init_interactive PARAMS((void));
void init_noninteractive PARAMS((void));
void init_interactive_script PARAMS((void));

void set_shell_name PARAMS((char *));
void shell_initialize PARAMS((void));
void shell_reinitialize PARAMS((void));

void show_shell_usage PARAMS((FILE *, int));


// (2b) Variables
extern int gnu_error_format;
extern int shell_initialized;
extern int bash_argv_initialized;
extern COMMAND *global_command;
extern struct user_info current_user;
extern char *current_host_name;
extern int login_shell;
extern int interactive;
extern int interactive_shell;
extern int hup_on_exit;
extern int check_jobs_at_exit;
extern int autocd;
extern int startup_state;
extern int reading_shell_script;
extern int debugging_login_shell;
extern char **shell_environment;
extern int executing;
extern int current_command_number;
extern int indirection_level;
extern char *shell_name;
extern time_t shell_start_time;
extern struct timeval shellstart;
extern int running_under_emacs;
extern int have_devfd;

// (2c) Initially-static variables
extern char *bashrc_file;
extern int act_like_sh;
extern int su_shell;
extern int sourced_env;
extern int running_setuid;
extern int debugging;
extern int no_rc;
extern int no_profile;
extern int do_version;
extern int make_login_shell;
extern int want_initial_help;
extern int debugging_mode;
extern int no_line_editing;
#if defined (TRANSLATABLE_STRINGS)
extern int dump_translatable_strings;
extern int dump_po_strings;
#endif
extern int wordexp_only;
extern int protected_mode;
extern int pretty_print_mode;

extern procenv_t subshell_top_level;
extern int subshell_argc;
extern char **subshell_argv;
extern char **subshell_envp;
extern char *exec_argv0;
#if defined(BUFFERED_INPUT)
extern int default_buffered_input;
#endif
extern int read_from_stdin;
extern int want_pending_command;
extern char *command_execution_string;
extern char *shell_script_filename;
extern int malloc_trace_at_exit;
extern int shell_reinitialized;
extern FILE *default_input;
extern STRING_INT_ALIST *shopt_alist;
extern int shopt_ind, shopt_len;

