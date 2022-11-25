
#include "ds_extern_program.h"

extern tbc_uint8_t ds_ext_prog_mem[100];
extern tbc_line_t ds_ext_pc;

static void ds_extern_program_next(tbc_app_st app);
static void ds_extern_program_load(tbc_app_st app);
static void ds_extern_program_insert(tbc_app_st app);
static void ds_extern_program_cleanup(tbc_app_st app);

void ds_extern_program_install(tbc_app_st app)
{
    /** install package **/
    app->nametable.program.next = (void*) &ds_extern_program_next;
    app->nametable.program.load = (void*) &ds_extern_program_load;
    app->nametable.program.insert = (void*) &ds_extern_program_insert;
    app->nametable.program.cleanup = (void*) &ds_extern_program_cleanup;
    /** clear program **/
    ds_extern_program_cleanup(app);
}

void ds_extern_program_next(tbc_app_st app)
{
    /** enqueue **/
    ++ds_ext_pc;
}

static void ds_extern_program_load(tbc_app_st app)
{
    /** cpu <- program memory **/
    tbc_line_t program_counter = (ds_ext_pc << 1) + ds_ext_pc;/**< pc * 3 **/
    app->cache_l0.reg = ds_ext_prog_mem[program_counter + 0];/**< [pc][0] **/
    app->cache_l0.mem = ds_ext_prog_mem[program_counter + 1];/**< [pc][2] **/
    app->cache_l0.dta = ds_ext_prog_mem[program_counter + 2];/**< [pc][2] **/
}

static void ds_extern_program_insert(tbc_app_st app)
{
    /** interpreter -> program memory **/
    tbc_line_t program_counter = (ds_ext_pc << 1) + ds_ext_pc;/**< pc * 3 **/
    ds_ext_prog_mem[program_counter + 0] = app->cache_l0.reg;/**< [pc][0] **/
    ds_ext_prog_mem[program_counter + 1] = app->cache_l0.mem;/**< [pc][1] **/
    ds_ext_prog_mem[program_counter + 2] = app->cache_l0.dta;/**< [pc][2] **/
}

static void ds_extern_program_cleanup(tbc_app_st app)
{
    /** all buffer **/;
    while (ds_ext_pc) {
        /** clear all columns **/
        ds_ext_prog_mem[ds_ext_pc][0] = 0;
        /** dequeue **/
        --ds_ext_pc;
    }
}
