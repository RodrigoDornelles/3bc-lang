
#include "ds_extern_program.h"

extern tbc_uint8_t ds_ext_program_array[100][3];
extern tbc_line_t ds_ext_program_count;

static void ds_extern_program_next(tbc_app_st app);
static void ds_extern_program_load(tbc_app_st app);
static void ds_extern_program_insert(tbc_app_st app);
static void ds_extern_program_cleanup(tbc_app_st app);

void ds_extern_program_install(tbc_app_st app)
{
    /** install pacakge **/
    app->nametable.program.next = (void*) &ds_extern_program_next;
    app->nametable.program.load = (void*) &ds_extern_program_load;
    app->nametable.program.insert = (void*) &ds_extern_program_insert;
    app->nametable.program.cleanup = (void*) &ds_extern_program_cleanup;
}

void ds_extern_program_next(tbc_app_st app)
{
    /** enqueue **/
    ++ds_ext_program_count;
}

static void ds_extern_program_load(tbc_app_st app)
{
    /** cpu <- program memory **/
    app->cache_l0.reg = ds_extern_program_array[ds_ext_program_count][0];
    app->cache_l0.mem = ds_extern_program_array[ds_ext_program_count][1];
    app->cache_l0.dta = ds_extern_program_array[ds_ext_program_count][2];
}

static void ds_extern_program_insert(tbc_app_st app)
{
    /** interpreter -> program memory **/
    ds_extern_program_array[ds_ext_program_count][0] = app->cache_l0.reg;
    ds_extern_program_array[ds_ext_program_count][1] = app->cache_l0.mem;
    ds_extern_program_array[ds_ext_program_count][2] = app->cache_l0.dta;
}

static void ds_extern_program_cleanup(tbc_app_st app)
{
    while (ds_ext_program_count) {
        /** clear all columns **/
        ds_extern_program_array[ds_ext_program_count][0] = 0;
        ds_extern_program_array[ds_ext_program_count][1] = 0;
        ds_extern_program_array[ds_ext_program_count][2] = 0;
        /** dequeue **/
        --ds_ext_program_count;
    }
}
