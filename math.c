#include <stdio.h>
#include <math.h>
#include <runt.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static int rproc_pi(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;

    rc = runt_ppush(vm, &s);
    RUNT_ERROR_CHECK(rc);
    s->f = M_PI;
    return RUNT_OK;
}

static int rproc_sin(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    runt_float out;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    out = sin(s->f);
    
    rc = runt_ppush(vm, &s);
    RUNT_ERROR_CHECK(rc);
    s->f = out;
    return RUNT_OK;
}

static int rproc_cos(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    runt_float out;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    out = cos(s->f);
    
    rc = runt_ppush(vm, &s);
    RUNT_ERROR_CHECK(rc);
    s->f = out;
    return RUNT_OK;
}

static int rproc_loadmath(runt_vm *vm, runt_ptr p)
{
    runt_keyword_define(vm, "pi", 2, rproc_pi, NULL);
    runt_keyword_define(vm, "sin", 3, rproc_sin, NULL);
    runt_keyword_define(vm, "cos", 3, rproc_cos, NULL);
    runt_mark_set(vm);
    return RUNT_OK;
}

runt_int runt_load_math(runt_vm *vm)
{
    runt_keyword_define(vm, "math", 4, rproc_loadmath, NULL);
    return runt_is_alive(vm);
}
