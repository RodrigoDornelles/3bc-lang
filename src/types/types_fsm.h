#ifndef H_TYPES_FSM_TBC
#define H_TYPES_FSM_TBC

/** FSM INTERRUPTS **/
enum ___tbc_app_fsm_e {
    FSM_3BC_DEFAULT = 0,
    FSM_3BC_STARTING = 1,
    FSM_3BC_EXPAND = 2,
    FSM_3BC_READING = 3,
    FSM_3BC_RUNNING = 4,
    FSM_3BC_COUNTING = 5,
    FSM_3BC_EXITING = 6,
    FSM_3BC_STOPED = 7,
    FSM_3BC_VACUUM = 8,
    FSM_3BC_LOADING = 9,
    FSM_3BC_ERROR = 10
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
