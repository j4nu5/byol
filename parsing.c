#include "mpc.h"
#include <stdio.h>
#include <string.h>
#include <editline/readline.h>

int main() {
    /* Parsers */
    mpc_parser_t* Number        = mpc_new("number");
    mpc_parser_t* Operator      = mpc_new("operator");
    mpc_parser_t* Expression    = mpc_new("expression");
    mpc_parser_t* KLisp         = mpc_new("klisp");

    /* Language Definition */
    mpca_lang(MPCA_LANG_DEFAULT,
    "                                                               \
        number      : /-?[0-9]+(\\.[0-9]+)?/;                       \
        operator    : '+' | '-' | '*' | '/';                        \
        expression  : <number> | '(' <operator> <expression>+ ')';  \
        klisp       : /^/ <operator> <expression>+ /$/;             \
    ",
    Number, Operator, Expression, KLisp);

    printf("Welcome to KLisp v0.0.1\n");
    printf("To exit press Ctrl+c\n");

    while (1) {
        char *input = readline("klisp> ");

        if (!input) {
            printf("\n");
            break;
        }

        if (!strlen(input))
            continue;

        add_history(input);

        /* Process the input */
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, KLisp, &r)) {
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        }
        else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }

    /* Cleanup */
    mpc_cleanup(4, Number, Operator, Expression, KLisp);
    return 0;
}

