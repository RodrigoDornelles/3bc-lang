#ifndef H_FSM_TYPES_TBC
#define H_FSM_TYPES_TBC

/** FSM INTERRUPTS **/
enum ___tbc_app_fsm_e {
    FSM_3BC_DEFAULT = 0,
    FSM_3BC_READING,
    FSM_3BC_RUNNING,
    FSM_3BC_WAITING,
    FSM_3BC_IO_READ,
    FSM_3BC_IO_SEND,
    FSM_3BC_EXITING,
    FSM_3BC_STOPED
};

typedef enum ___tbc_app_fsm_e tbc_app_fsm_et;

#endif