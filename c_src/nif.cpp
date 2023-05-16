#include <erl_nif.h>
#include <stdint.h>
#include <string>
#include <cstring>
#include <string.h>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

struct MyStruct {
    std::string mode;
    int a;
    int b;
};

extern "C" int my_add(int a, int b) {
    return a + b;
}

extern "C" int my_op(struct MyStruct * s) {
    if (s->mode == "add") {
        return s->a + s->b;
    } else if (s->mode == "subtract") {
        return s->a - s->b;
    } else if (s->mode == "multiply") {
        return s->a * s->b;
    } else if (s->mode == "divide") {
        return s->a / s->b;
    } else {
        return 0;
    }
}

ERL_NIF_TERM atom(ErlNifEnv *env, const char *msg) {
    ERL_NIF_TERM a;
    if (enif_make_existing_atom(env, msg, &a, ERL_NIF_LATIN1)) {
        return a;
    } else {
        return enif_make_atom(env, msg);
    }
}

int get_atom(ErlNifEnv *env, ERL_NIF_TERM term, std::string &var) {
    unsigned atom_length;
    if (!enif_get_atom_length(env, term, &atom_length, ERL_NIF_LATIN1)) {
        return 0;
    }

    var.resize(atom_length + 1);

    if (!enif_get_atom(env, term, &(*(var.begin())), var.size(), ERL_NIF_LATIN1)) {
        return 0;
    }

    var.resize(atom_length);
    return 1;
}

ERL_NIF_TERM error(ErlNifEnv *env, const char *msg) {
    ERL_NIF_TERM error_atom = atom(env, "error");
    ERL_NIF_TERM reason;
    unsigned char *ptr;
    size_t len = strlen(msg);
    if ((ptr = enif_make_new_binary(env, len, &reason)) != nullptr) {
        strcpy((char *) ptr, msg);
        return enif_make_tuple2(env, error_atom, reason);
    } else {
        ERL_NIF_TERM msg_term = enif_make_string(env, msg, ERL_NIF_LATIN1);
        return enif_make_tuple2(env, error_atom, msg_term);
    }
}

static ERL_NIF_TERM pointer_to_my_add(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    return enif_make_uint64(env, (uint64_t)(uint64_t *)(&my_add));
}

static ERL_NIF_TERM pointer_to_my_op(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    return enif_make_uint64(env, (uint64_t)(uint64_t *)(&my_op));
}

static ERL_NIF_TERM new_struct(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
    std::string mode;
    if (!get_atom(env, argv[0], mode)) {
        return enif_make_badarg(env);
    }

    int a, b;
    if (!enif_get_int(env, argv[1], &a)) {
        return enif_make_badarg(env);
    }
    if (!enif_get_int(env, argv[2], &b)) {
        return enif_make_badarg(env);
    }

    struct MyStruct * s = (struct MyStruct *)enif_alloc(sizeof(struct MyStruct));
    if (s == nullptr) {
        return error(env, "out of memory");
    }

    s->mode = mode;
    s->a = a;
    s->b = b;

    return enif_make_uint64(env, (uint64_t)(uint64_t *)s);
}

static ERL_NIF_TERM free_struct(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
  uint64_t ptr_u64;
  if (!enif_get_uint64(env, argv[0], reinterpret_cast<ErlNifUInt64 *>(&ptr_u64))) {
    return enif_make_badarg(env);
  }
  if (ptr_u64 == 0) return enif_make_badarg(env);

  enif_free((void *)(uint64_t *)ptr_u64);
  return atom(env, "ok");
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
    {"pointer_to_my_add", 0, pointer_to_my_add, 0},
    {"pointer_to_my_op", 0, pointer_to_my_op, 0},
    {"new_struct", 3, new_struct, 0},
    {"free_struct", 1, free_struct, 0},
};

ERL_NIF_INIT(Elixir.CFunc.Nif, nif_functions, on_load, on_reload, on_upgrade, NULL);

#if defined(__GNUC__)
#pragma GCC visibility push(default)
#endif
