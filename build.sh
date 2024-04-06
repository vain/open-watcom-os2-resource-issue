#!/bin/sh

set -xe

owcc -Wall -Wextra -bos2v2_pm -o hello.exe hello.c
wrc -bt=os2 -zku8 hello.rc
