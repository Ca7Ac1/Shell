# Shell
Systems project #2

Features:
- exit and cd
- Semicolons
- Redirection ("<", ">" and ">>")
- Allow extra whitespace between tokens (' ' and '\t')
- Basic error handling and reporting
- Multi-piping with redirection allowed on either end

Bugs:
- rm -rf fails
- No way to use ~ to go to home directory

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
- void run(char **);

strlib.h
- int count(char *, char);
