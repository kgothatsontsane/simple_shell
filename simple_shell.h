#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* read and write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* command chaining */
#define CMD_NORMAL 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* number_to_string() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* if using system getline() then value will be 1 */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".simple_shell_history"
#define HISTORY_MAX 4096

extern char **environ;

/**
 * struct str_list - a simple singly-linked list
 * @number: a number field
 * @str: the string field
 * @next: points to the next entry in the linked-list
 */
typedef struct str_list
{
	int number;
	char *str;
	struct str_list *next;
} list_t;

/**
 * struct passdata - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @argument: a string generated from getline containing arguments
 * @arg_vector: an array of strings generated from argument
 * @path: a string path for the current command
 * @arg_count: the argument count
 * @line_count: the line count
 * @errorCode: the error code for exit()s
 * @countLineFlag: if on count this line of input
 * @programFilename: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @historyEntries: the history entry
 * @alias: the alias entry
 * @environmentChanged: on if environ was changed
 * @returnStatus: the return returnStatus of the last exec'd command
 * @commandBuffer: address of pointer to commandBuffer, on if chaining
 * @commandBufferType: CMD_type ||, &&, ;
 * @readFileDescriptor: the f_descriptor from which to read line input
 * @historyLineCount: the history line number count
 */
typedef struct passdata
{
	char *argument;
	char **arg_vector;
	char *path;
	int arg_count;
	unsigned int line_count;
	int errorCode;
	int countLineFlag;
	char *programFilename;
	list_t *env;
	list_t *historyEntries;
	list_t *alias;
	char **environ;
	int environmentChanged;
	int returnStatus;
	char **commandBuffer;/* pointer to cmd-chain buffer, 4 mem-mangement */
	int commandBufferType;
	int readFileDescriptor;
	int historyLineCount;
} data_t;

#define DATA_INIT \
	{ \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, \
		NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0 \
	}

/**
 * struct builtin - contains the builtin string and the related function
 * @type: the system builtin command flag
 * @func: the function associated with the flag
 */
typedef struct builtin
{
	char *type;
	int (*func)(data_t *);
} builtin_table;

/* simple_shell.c */
int hsh(data_t *data, char **a_v);
int searchBuiltIn(data_t *data);
void searchCommand(data_t *data);
void exec_cmd_in_child(data_t *data);

/* command_parser.c */
int is_exec_cmd(data_t *data, char *f_path);
char *extract_substring(char *str_path, int start_idx, int stop_idx);
char *find_exec_path(data_t *data, char *search_paths, char *command);

/* LOOP? */
/* int loophsh(char **); */

/* error_handling.c */
void write_str_to_stderr(char *str);
int write_ch_to_stderr(char ch);
int write_ch_to_fd(char ch, int f_descriptor);
int write_str_to_fd(char *str, int f_descriptor);

/* error_handling1.c */
int parse_str_to_int(char *str);
void reportError(data_t *data, char *error_string);
int printDecimal(int user_input, int f_descriptor);
char *number_to_string(long int number, int b, int flgs);
void stripComments(char *buffer);

/* string_functions.C */
int _strlen(char *);
int _strcmp(char *, char *);
char *begins_with(const char *, const char *);
char *_strcat(char *, char *);

/* string_functions1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* string_functions2.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tokenize.c */
char **strTokenize(char *, char *);
char **strTokenizeIR(char *, char);

/* reallocate.c */
char *fillMemory(char *, char, unsigned int);
void freeStringArray(char **);
void *my_realloc(void *, unsigned int, unsigned int);

/* free_memory.c */
int free_ptr(void **);

/* str_to_int.c */
int isInteractiveShell(data_t *);
int isDelimiter(char, char *);
int isAlphabetic(int);
int str_to_int(char *);

/* builtin_functions.c */
int _my_exit(data_t *);
int _my_cd(data_t *);
int _my_help(data_t *);

/* builtin_functions1.c */
int _my_history(data_t *);
int _my_alias(data_t *);

/* get_line.c */
ssize_t get_user_input(data_t *);
int get_next_line(data_t *, char **, size_t *);
void handle_signal(int);

/* get_info.c */
void reset_data(data_t *);
void init_data(data_t *, char **);
void free_data(data_t *, int);

/* environment.c */
char *_get_env(data_t *, const char *);
int _my_env(data_t *);
int _my_set_env(data_t *);
int _my_unset_env(data_t *);
int init_env_list(data_t *);

/* get_environment.c */
char **get_env(data_t *);
int unset_env(data_t *, char *);
int set_env(data_t *, char *, char *);

/* history_manager.c */
char *get_history_f_path(data_t *data);
int save_cmd_history(data_t *data);
int load_cmd_history(data_t *data);
int add_history_entry(data_t *data, char *buffer, int line_count);
int sort_history(data_t *data);

/* list_manager.c */
list_t *add_entry(list_t **, const char *, int);
list_t *add_entry_end(list_t **, const char *, int);
size_t print_str_list(const list_t *);
int delete_entry_at_index(list_t **, unsigned int);
void reset_list(list_t **);

/* list_manager1.c */
size_t list_length(const list_t *);
char **list_to_arr_strings(list_t *);
size_t display_list(const list_t *);
list_t *entry_starts_with(list_t *, char *, char);
ssize_t get_entry_index(list_t *, list_t *);

/* variables.c */
int isCmdSep(data_t *, char *, size_t *);
void checkStatus(data_t *, char *, size_t *, size_t, size_t);
int replaceAlias(data_t *);
int replaceVars(data_t *);
int replaceStr(char **, char *);

#endif /* _SIMPLE_SHELL_H_*/
