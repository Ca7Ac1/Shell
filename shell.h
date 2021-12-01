#ifndef SHELL_H
#define SHELL_H

extern int extraIn;
extern int extraOut;

void shell();
void execute(char **, int);
void leftRedirect(char **tokens, int size);
void rightRedirect(char **tokens, int size);
void run(char **);

#endif
