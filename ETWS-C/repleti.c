#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <err.h>
#include <readline/readline.h>
#include <readline/history.h>

void handle_int() { /* handle ctrl-c */
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay(); /* thanks James Taylor on Stack Overflow */
}

int repl(void) {
	

	//int size = strlen(argv[1]) + 3 + 1;
	int size = 4;
	char *prompt = malloc(size);
	if (prompt == NULL) err(1, NULL);
	snprintf(prompt, size, "> ");

	struct sigaction act = {0};
	act.sa_handler = handle_int;
	sigaction(SIGINT, &act, NULL);

	rl_clear_signals(); /* tell readline to ignore signals */

	while (true) {
		char *input = readline(prompt);

		if (input == NULL) { /* ctrl-d */
			printf("\n");
			break;
		}
		
		if (input[0] != '\0') add_history(input);


		free(input);
	}

	free(prompt);

	return 0;
}
