#include <erl_nif.h>
#include <stdint.h>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

int my_add(int a, int b) {
    return a + b;
}

static ERL_NIF_TERM pointer_to_my_add(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    return enif_make_uint64(env, (uint64_t)(uint64_t *)(&my_add));
}

static int on_load(ErlNifEnv *env, void **_sth1, ERL_NIF_TERM _sth2) {
    return 0;
}

static int on_reload(ErlNifEnv *_sth0, void **_sth1, ERL_NIF_TERM _sth2) {
    return 0;
}

static int on_upgrade(ErlNifEnv *_sth0, void **_sth1, void **_sth2, ERL_NIF_TERM _sth3) {
    return 0;
}

static ErlNifFunc nif_functions[] = {
    {"pointer_to_my_add", 0, pointer_to_my_add, 0}
};

ERL_NIF_INIT(Elixir.CFunc.Nif, nif_functions, on_load, on_reload, on_upgrade, NULL);

#if defined(__GNUC__)
#pragma GCC visibility push(default)
#endif
