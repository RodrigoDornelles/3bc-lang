#ifdef __MINGW32__
#include <windows.h>
#else
#include <Windows.h>
#endif
#include "sys_windows_output.h"

void sys_windows_output(tbc_app_st *const self)
{
    static HANDLE fileptr = NULL;

    // Initialize the fileptr if it hasn't been initialized before
    if (fileptr == NULL) {
        fileptr = GetStdHandle(STD_OUTPUT_HANDLE);
        if (fileptr == INVALID_HANDLE_VALUE) {
            // Handle error if GetStdHandle fails
            // (you might want to handle the error accordingly)
            return;
        }
    }

    if (self->cache_l3.fixbuf.size > 0) {
        DWORD bytesWritten;
        WriteFile(
            fileptr,
            self->cache_l3.fixbuf.storage,
            self->cache_l3.fixbuf.size,
            &bytesWritten,
            NULL
        );
    } else {
        DWORD bytesWritten;
        WriteFile(
            fileptr,
            self->cache_l3.fixbuf.storage,
            -self->cache_l3.fixbuf.size,
            &bytesWritten,
            NULL
        );
    }
}
