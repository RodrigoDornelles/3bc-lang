
#include "bus_cfg_0000.h"
#include "types_null.h"
#include "driver_stack.h"

/**
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
void driver_stack(struct app_3bc_s* const self)
{
    do {
        self->rc = TBC_RET_OK;
        
        /* minimal stack */
        if (self->stack.raw.buffer == NULL) {
            self->stack.cfg.prog = &self->stack.cfgmin.prog_index;
            break;
        }

        

        /* continue configuring... */
        if (self->cache_l1.u8 < tbc_cfg_size) {
            self->rc = TBC_RET_REPEAT;
            break;
        }
    }
    while(0);
}
 