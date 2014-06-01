#include <stdio.h>
#include <stdlib.h>

/* If compiling on Windows */
#ifdef _WIN32

#include <string.h>
#define BUFFER_SIZE 256

char *readline(char *prompt) {
    /* Implements the readline function for Windows
     *
     * |prompt| is a null-terminated character array which will be displayed
     * before taking input
     *
     * Allocates BUFFER_SIZE bytes of memory on the heap and returns
     * a pointer to the first byte
     *
     * It is the responsibility of the caller to deallocate this to prevent
     * memory leaks
     */

    printf("%s", prompt);

    char *line = (char *) malloc(BUFFER_SIZE * sizeof(char));
    char *status = fgets(line, BUFFER_SIZE, stdin);

    /* Check for EOF */
    if (feof(stdin) || !status) {
        free(line);
        
        return NULL;
    }

    int length = strlen(line);
    
    /* If buffer overflow */
    if (line[length-1] != '\n') {
        /* Purge stdin */
        char *tmp_buffer[16];
        while (1) {
            char *status = fgets(tmp_buffer, 16, stdin);

            if (feof(stdin) || !status)
                break;

            if (tmp_buffer[strlen(tmp_buffer) - 1] == '\n')
                break;
        }
    }
    else {
        /* Truncate */
        line[length-1] = '\0';
    }

    return line;
}

void add_history(char *unused) {}

#elif __APPLE__
#include <editline/readline.h>

#else
#include <editline/readline.h>
#include <editline/history.h>

#endif


int main() {
    printf("Welcome to KLisp v0.0.1\n");
    printf("Press Ctrl+c to exit ...\n");

    while (1) {
        char *input = readline("klisp > ");

        if (!input) {
            printf("\n");
            exit(0);
        }

        add_history(input);

        printf("%s\n", input);

        free(input);
    }

    return 0;
}

