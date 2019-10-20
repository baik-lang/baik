#include "strings.h"
#include "baik.h"
#include <emscripten.h>

void EMSCRIPTEN_KEEPALIVE baik(char str[])
{
    struct baik *baik = baik_create();
    baik_err_t err = BAIK_OK;
    baik_val_t res = 0;

    if (err == BAIK_OK)
    {
        if (res == 0)
            baik_exec(baik, str, NULL);
    }
    else
    {
        baik_print_error(baik, stdout, NULL, 1);
    }

    baik_destroy(baik);
}
