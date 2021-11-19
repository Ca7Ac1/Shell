#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

void shell() {
	while(1) {
		char **tokens = parse();
		switch tokens[0]:
		case "cd":
			break;
		case "exit:
			return 0;
		default:
			int c = fork();
			if(!c) execvp(tokens[0], tokens);
			break;
	}
}
