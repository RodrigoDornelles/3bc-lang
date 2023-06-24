#ifndef H_CPU_JUMP_TBC
#define H_CPU_JUMP_TBC

#include "3bc_types.h"

#ifdef __cplusplus

extern "C" {

#endif

void cpu_jump_goto(struct app_3bc_s* const self);
void cpu_jump_fgto(struct app_3bc_s* const self);
void cpu_jump_zgto(struct app_3bc_s* const self);
void cpu_jump_pgto(struct app_3bc_s* const self);
void cpu_jump_ngto(struct app_3bc_s* const self);

#ifdef __cplusplus

}

#endif

#endif
