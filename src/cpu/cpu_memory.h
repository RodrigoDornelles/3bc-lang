#ifndef H_CPU_MEMORY_TBC
#define H_CPU_MEMORY_TBC

void cpu_memory_free(struct app_3bc_s* const self);
void cpu_memory_aloc(struct app_3bc_s* const self);
void cpu_memory_ptr_free(struct app_3bc_s* const self);
void cpu_memory_ptr_aloc(struct app_3bc_s* const self);
void cpu_memory_ptr_pull(struct app_3bc_s* const self);
void cpu_memory_ptr_spin(struct app_3bc_s* const self);
void cpu_memory_ptr_push(struct app_3bc_s* const self);
void cpu_memory_aux_free(struct app_3bc_s* const self);
void cpu_memory_aux_aloc(struct app_3bc_s* const self);
void cpu_memory_aux_pull(struct app_3bc_s* const self);
void cpu_memory_aux_spin(struct app_3bc_s* const self);
void cpu_memory_aux_push(struct app_3bc_s* const self);

#endif

