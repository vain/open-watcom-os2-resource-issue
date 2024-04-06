#include <stdio.h>

#define INCL_PM
#include <os2.h>

#include "hello.h"

void
open_dialog(HWND hwnd)
{
    int ret;
    FILE *fp;

    ret = WinDlgBox(HWND_DESKTOP, hwnd, wndproc_open, NULLHANDLE, ID_DLG, NULL);
    fp = fopen("hello.log", "a");
    fprintf(fp, "saw ret %d (DID_ERROR is %d)\n", ret, DID_ERROR);
    fclose(fp);
}

MRESULT EXPENTRY _export wndproc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    HPS hps;
    RECTL rect;

    switch (msg)
    {
        case WM_COMMAND:
            switch (COMMANDMSG(&msg)->cmd)
            {
                case IDME_OPEN:
                    open_dialog(hwnd);
                    return 0;
            }
            break;
        case WM_PAINT:
            /* Just a white window. */
            hps = WinBeginPaint(hwnd, NULLHANDLE, NULLHANDLE);
            WinQueryWindowRect(hwnd, &rect);
            WinFillRect(hps, &rect, CLR_WHITE);
            WinEndPaint(hps);
            return 0;
    }

    return WinDefWindowProc(hwnd, msg, mp1, mp2);
}

MRESULT EXPENTRY _export wndproc_open(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

int
main()
{
    HAB hab;
    HMQ hmq;
    QMSG qmsg;
    ULONG style;
    HWND win_handle;

    hab = WinInitialize(0);
    hmq = WinCreateMsgQueue(hab, 0);

    WinRegisterClass(hab, "hello", wndproc, CS_SIZEREDRAW, 0);

    style = FCF_TITLEBAR | FCF_SYSMENU | FCF_SIZEBORDER | FCF_MINMAX |
            FCF_SHELLPOSITION | FCF_TASKLIST |
            FCF_MENU;

    WinCreateStdWindow(
        HWND_DESKTOP, WS_VISIBLE, &style,
        "hello", "hello", 0, NULLHANDLE, ID_MENU, &win_handle
    );

    while (WinGetMsg(hab, &qmsg, NULLHANDLE, 0, 0))
        WinDispatchMsg(hab, &qmsg);

    return 0;
}
