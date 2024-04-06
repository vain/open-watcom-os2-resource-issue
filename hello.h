#ifndef HELLO_H
#define HELLO_H

#define ID_MENU 1
#define IDME_OPEN 102

#define ID_DLG 1

MRESULT EXPENTRY _export wndproc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY _export wndproc_open(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

#endif /* HELLO_H */
