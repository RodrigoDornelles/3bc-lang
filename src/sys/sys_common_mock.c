void sys_common_mock_none(tbc_app_st *const self)
{

}

void sys_common_mock_exit(tbc_app_st *const self)
{
    self->rc = TBC_RET_EXIT;
}

void sys_common_mock_exit_force(tbc_app_st *const self)
{
    self->rc = TBC_RET_EXIT_FORCE;
}
