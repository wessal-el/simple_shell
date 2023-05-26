#ifndef SHELL_H
#define SHELL_H

#define FILE_HIS ".simple_shell_history"
#define MAX_HIS 5000
#define _LOWERCASE 1
#define _UNSIGNED 2
#define _GETLINE 0
#define _STRTOK 0
#define FLUSH_BUFF -1
#define WBUFF_SIZE 1030
#define RBUFF_SIZE 1030
#define _NORM 0
#define _OR 1
#define _AND 2
#define _CHAIN 3

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/**
 * struct strlist - linked list
 * @n: num field
 * @s: string
 * @nxt: point to next node
 */
typedef struct strlist
{
	int n;
	char *s;
	struct strlist *nxt;
} list;

/**
 * struct data - contains data to pass into function
 * @str: string generated from getline containing arg
 * @av: array of strings generated from str
 * @p: string path for current command
 * @ac: argument count
 * @lcount: error count
 * @ernum: the error code for exit
 * @lflag: if on count this line
 * @name: program filename
 * @envt: linked list local copy of envir
 * @envir: modified copy of environ from LL env
 * @hist: history
 * @als: alias
 * @chenv: on if environ change
 * @stts: return status of last exec'd command
 * @cmdbuf: address of pointer to cmdbuf
 * @buftype: CMD type || && ;
 * @rfd: fd from which to read line input
 * @counthist: history line number count
 */
typedef struct data
{
	char *str;
	char **av;
	char *p;
	int ac;
	unsigned int lcount;
	int ernum;
	int lflag;
	char *name;
	list *envt;
	list *hist;
	list *als;
	char **envir;
	int chenv;
	int stts;
	char **cmdbuf;
	int buftype;
	int rfd;
	int counthist;
} info;

/**
 *struct built - contains builtin str and related function
 *@tp: builtin command flag
 *@funct: function
 */
typedef struct built
{
	char *tp;
	int (*funct)(info *);
} built_table;

char *swith(const char *, const char *);
char *str_cat(char *, char *);
int str_cmp(char *, char *);
int str_len(char *);

char *str_cpy(char *, char *);
char *str_dup(const char *);
void _put(char *);
int put_char(char);

char *str_ncpy(char *, char *, int);
char *str_ncat(char *, char *, int);
char *str_chr(char *, char);

char **str_tow(char *, char *);
char **str__tow(char *, char);

int h(info *, char **);
int _builtin(info *);
void findcmd(info *);
void forkcmd(info *);

int iscmd(info *, char *);
char *dupchar(char *, int, int);
char *_path(info *, char *, char *);

int puts_fd(char *s, int FD);
int put_fd(char s, int FD);
int eput_char(char);
void _eput(char *);

char *mem_set(char *, char, unsigned int);
void f_free(char **);
void *__realloc(void *, unsigned int, unsigned int);

int _free(void **);

int loop(char **);

int interac(info *);
int is_del(char, char *);
int is_alpha(int);
int __atoi(char *);

int erratoi(char *);
void printerr(info *, char *);
int printd(int, int);
char *conv_num(long int, int, int);
void rmcomnt(char *);

int mexit(info *);
int mcd(info *);
int mhelp(info *);
int mhist(info *);
int malias(info *);

ssize_t get_inpt(info *);
int mgetline(info *, char **, size_t *);
void Handler(int);

void clr_inf(info *);
void set_inf(info *, char **);
void freeinf(info *, int);

char *mgetenv(info *, const char *);
int menv(info *);
int msetenv(info *);
int munsetenv(info *);
int pop_env(info *);
char **get_envir(info *);
int unset_env(info *, char *);
int set_env(info *, char *, char *);

char *gethist(info *inf);
int whist(info *inf);
int rhist(info *inf);
int buildhist(info *inf, char *buff, int lcount);
int renumhist(info *inf);

list *addnode(list **, const char *, int);
list *addnodeend(list **, const char *, int);
size_t printl_str(const list *);
int del_node(list **, unsigned int);
void freel(list **);
size_t listlen(const list *);
char **liststr(list *);
size_t printl(const list *);
list *node_start(list *, char *, char);
ssize_t get_index(list *, list *);

int ischain(info *, char *, size_t *);
void check(info *, char *, size_t *, size_t, size_t);
int rep_als(info *);
int rep_var(info *);
int rep_str(char **, char *);

#endif
