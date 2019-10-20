#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "strings.h"
#include "../../baik.h"

char **baik_type_completion(const char *, int, int);
char *baik_type_generator(const char *, int);
char *baik_types[] = {
    "tulis",
    "jika",
    "lainnya",
    "untuk",
    "ulang",
    "benar",
    "salah",
    "isi",
    "panjang",
    NULL
};

char **
baik_type_completion(const char *text, int start, int end)
{
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, baik_type_generator);
}

char *
baik_type_generator(const char *text, int state)
{
    static int list_index, len;
    char *name;

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }

    while ((name = baik_types[list_index++])) {
        if (strncmp(name, text, len) == 0) {
            return strdup(name);
        }
    }

    return NULL;
}

int repl()
{
    rl_bind_key('\t', rl_complete);
    rl_attempted_completion_function = baik_type_completion;
    struct baik *baik = baik_create();

    while (1) {
        char* baik_input = readline("baik >> ");

        if (!baik_input)
            break;

        if( 0 == strcmp(&baik_input[(strlen(baik_input)-1)], "{"))
        {
            while (1) {
                char* baik_input_next = readline("... ");
                strcat(baik_input,baik_input_next);
                if( 0 == strcmp(&baik_input[(strlen(baik_input)-1)], "}")){
                    break;
                }
                free(baik_input_next);
            }
        }

        add_history(baik_input);
        baik_exec(baik, baik_input, NULL);
        free(baik_input);
    }
    return 0;
}
  
int main(int argc,char* argv[]) 
{ 
    struct baik *baik = baik_create();
    baik_err_t err = BAIK_OK;
    baik_val_t res = 0;
    int i;

    for (i = 1; i < argc && argv[i][0] == '-' && err == BAIK_OK; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            err = baik_exec(baik, argv[++i], &res);
        } else if  (strcmp(argv[i], "-c") == 0){
            baik_set_generate_jsc(baik, 1);
        } else if (strcmp(argv[i], "-l") == 0 && i + 1 < argc) {
            //cs_log_set_level(atoi(argv[++i]));
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            err = baik_exec_file(baik, argv[++i], &res);
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Baik, built: " __DATE__ "\n");
            printf("Usage:\n");
            printf("%s [OPTIONS] [baik_file ...]\n", argv[0]);
            printf("OPTIONS:\n");
            printf("  -e string    - Execute Baik expression\n");
            printf("  -c           - Enable code precompiling to .inac files\n");
            printf("  -f baik_file - Execute code from .ina Baik file\n");
            return EXIT_SUCCESS;
        } else {
            fprintf(stderr, "Unknown flag: [%s]\n", argv[i]);
            return EXIT_FAILURE;
        }
    }
    for (; i < argc && err == BAIK_OK; i++) {
        err = baik_exec_file(baik, argv[i], &res);
    }

    if (err == BAIK_OK) {
        if(res == 0)
            repl();
    } else {
        baik_print_error(baik, stdout, NULL, 1);
    }

    baik_destroy(baik);
    return EXIT_SUCCESS;
} 