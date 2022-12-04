#ifndef H_TYPES_FSM_TBC
#define H_TYPES_FSM_TBC

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

/** IDLE INTERRUPTS **/
enum ___tbc_sleep_e {
    SLEEP_3BC_NONE = 0,
    SLEEP_3BC_REAL_TICK,
    SLEEP_3BC_FAKE_TICK,
    SLEEP_3BC_MICROSECONDS,
    SLEEP_3BC_MILLISECONDS,
    SLEEP_3BC_SECONDS
};

typedef enum ___tbc_app_fsm_e tbc_app_fsm_et;
typedef enum ___tbc_sleep_e tbc_sleep_et;

#endif
