# Shell
Systems project #2

Features:
- One line at a time
- exit and cdi
- Semicolons
- Redirection
- Extra whitespace
- Basic error handling

Unsuccessful features:
- Piping

Bugs:
- rm -rf fails

Headers:

command.h
- typedef struct command { char **tokens; int size; struct command *next;} command;
- command *addCommand(command *, char *);
- void printCommands(command *);
- void freeCommands(command *);

format.h
- char *lower(char *);
- char *insertSpace(char *);
- char *alterSpace(char *);
- char *deleteSpace(char *);
- char *format(char *);

parser.h
- command *parse();
- command *splitCommands(char *);

shell.h
- extern int extraIn;
- extern int extraOut;
- void shell();
- void execute(char **, int);
- void leftRedirect(char **tokens, int size);
- void rightRedirect(char **tokens, int size);
- void pipeCmd(char **tokens, int size);
- void run(char **);

strlib.h
- int count(char *, char);
