#define TBC_SOURCE_ENTRY
#include "bus/bus_cfg_0000.h"
#include "driver/driver_stack.h"
#include "types/types_null.h"

/**
 * @throw ERROR_MEM_STACK_CFG_MIS
 * @throw ERROR_MEM_STACK_CFG_MIN
 * @throw ERROR_MEM_STACK_CFG_OUT
 *
 * @dot
 * digraph stack_g {
 *     graph [
 *         rankdir = "LR",
 *         ranksep = 1.5
 *     ];
 *     "app" [
 *         label = "Stack Memory | <SM> 0xf7fc4380",
 *         shape = "record"
 *     ];
 *     "stack" [
 *         label = "Stack Buffer | <ST> ST 16 | <SP> SP 12 | <CFG1> | <CFG2> | <CFG3> | <SS1> SS 5 | PC | <SS2> SS 1 | PC | <DATA1> | <DATA2> | <SS3> SS 3 | <FREE1> | <FREE2> | <FREE3> | <FREE4>",
 *         shape = "record"
 *     ];
 *     "comment1" [
 *         label = "program memory config",
 *         shape = "note"
 *     ];
 *     "comment2" [
 *         label = "heap memory config",
 *         shape = "note"
 *     ];
 *     "comment3" [
 *         label = "interpreter config",
 *         shape = "note"
 *     ];
 *     "comment4" [
 *         label = "data",
 *         shape = "note"
 *     ];
 *     "comment5" [
 *         label = "free",
 *         shape = "note"
 *     ];
 *     "comment6" [
 *         label = "stack head",
 *         shape = "note"
 *     ];
 *     "comment7" [
 *         label = "stack tail",
 *         shape = "note"
 *     ];
 *     "app":SM -> "stack":ST [];
 *     "stack":SP:e -> "stack":SS3:e [];
 *     "stack":SS1 -> "stack":ST:n [];
 *     "stack":SS2 -> "stack":SS1 [];
 *     "stack":SS3 -> "stack":SS2 [];
 *     "stack":ST:e -> "stack":FREE4:e [];
 *     "comment1" -> "stack":CFG1 [style="dotted", weight=0, arrowhead="none"];
 *     "comment2" -> "stack":CFG2 [style="dotted", weight=0, arrowhead="none"];
 *     "comment3" -> "stack":CFG3 [style="dotted", weight=0, arrowhead="none"];
 *     "comment4" -> "stack":DATA1 [style="dotted", weight=0, arrowhead="none"];
 *     "comment4" -> "stack":DATA2 [style="dotted", weight=0, arrowhead="none"];
 *     "comment5" -> "stack":FREE1 [style="dotted", weight=0, arrowhead="none"];
 *     "comment5" -> "stack":FREE2 [style="dotted", weight=0, arrowhead="none"];
 *     "comment5" -> "stack":FREE3 [style="dotted", weight=0, arrowhead="none"];
 *     "comment5" -> "stack":FREE4 [style="dotted", weight=0, arrowhead="none"];
 *     "stack":ST ->"comment6" [style="dotted", weight=0, arrowhead="none"];
 *     "stack":FREE4 ->"comment7" [style="dotted", weight=0, arrowhead="none"];
 *     "stack":FREE4 -> "legend" [style="invis"];
 *     "legend" [
 *         label = <<table cellspacing="0" cellpadding="4" border="0" cellborder="1" style="rounded">
 *                         <tr><td colspan="2" bgcolor="lightgray"><b>Legend</b></td></tr>
 *                         <tr><td>PC</td><td>program counter</td></tr>
 *                         <tr><td>SS</td><td>Stack Size</td></tr>
 *                         <tr><td>SP</td><td>Stack Pointer</td></tr>
 *                         <tr><td>ST</td><td>Stack Tail</td></tr>
 *                     </table>>,
 *         shape = "plaintext",
 *         style = "filled",
 *         fillcolor = "white",
 *         fontname = "Arial",
 *         fontsize = "10"
 *     ];
 * }
 * @enddot
 */
void driver_stack_init(struct app_3bc_s* const self, tbc_u8_t* buf, tbc_u8_t len)
{
    tbc_u8_t cfg = 0;

    do {
        /* minimal stack */
        if (buf == NULL) {
            self->stack.cfg.prog = &self->stack.cfgmin.prog_index;
            self->rc = TBC_RET_OK;
            break;
        }

        /* attach the stack mem */
        self->stack.raw.buffer = buf;
        self->stack.raw.buffer[0] = len;

        /* first step advanced stack */
        if (self->stack.mem->sp == 0) {
            /* missing the size of stack */
            if (self->stack.mem->st == 0) {
                self->rc = TBC_RET_THROW_ERROR;
                self->cache_l1.error = ERROR_MEM_STACK_CFG_MIS;
                break;
            }
            /* stack size is not enough */
            if (self->stack.mem->st < 8) {
                self->rc = TBC_RET_THROW_ERROR;
                self->cache_l1.error = ERROR_MEM_STACK_CFG_MIN;
                break;
            }
            /* skip @c st and @c sp */
            self->stack.mem->sp += 2;
        }
    
        /** add configuration **/
        while (cfg < tbc_cfg_size) {
            /* insuficient memory to configure all */
            if ((self->stack.mem->sp + tbc_cfg_standard[cfg].size) > self->stack.mem->st) {
                self->rc = TBC_RET_THROW_ERROR;
                self->cache_l1.error = ERROR_MEM_STACK_CFG_OUT;
                break;
            }
            /** @todo document this */
            if (cfg < sizeof(struct ___tbc_stack_cfg_s)/sizeof(void*)) {
                /* Calculate the address of cfg based on cfg */
                tbc_stack_basic_prog_st** conf = ((tbc_stack_basic_prog_st**) &self->stack.cfg.___pad0) 
                    + cfg + 1;
                /* Calculate the address of buf based on self->stack.mem->sp */
                tbc_u8_t* buf = self->stack.raw.buffer;
                buf += self->stack.mem->sp;
                /* Assign buf to the calculated cfg address */
                *conf = (tbc_stack_basic_prog_st*) buf; 
            }

            /* expand stack */
            self->stack.mem->sp += tbc_cfg_standard[cfg].size;
            ++cfg;
        }

        /* first stack size */
        if (self->rc != TBC_RET_THROW_ERROR) {
            self->stack.mem->data[self->stack.mem->sp - 2] = self->stack.mem->sp;
        }
    }
    while(0);
}
