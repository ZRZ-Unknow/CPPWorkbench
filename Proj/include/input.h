#include <termio.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#pragma once

static struct termios ori_attr, cur_attr;

static __inline int tty_reset(void){
    if (tcsetattr(STDIN_FILENO, TCSANOW, &ori_attr) != 0)
        return -1;
    return 0;
}

static __inline int tty_set(void){
    if (tcgetattr(STDIN_FILENO, &ori_attr))
        return -1;
    memcpy(&cur_attr, &ori_attr, sizeof(cur_attr) );
    cur_attr.c_lflag &= ~ICANON;
    cur_attr.c_lflag &= ~ECHO;
    cur_attr.c_cc[VMIN] = 1;
    cur_attr.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &cur_attr) != 0)
        return -1;
    return 0;
}

static __inline int kbhit(void){
    fd_set rfds;
    struct timeval tv;
    int retval;
    /* Watch stdin (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    /* Wait up to five seconds. */
    tv.tv_sec  = 0;
    tv.tv_usec = 0;
    retval = select(1, &rfds, NULL, NULL, &tv);
    /* Don't rely on the value of tv now! */
    if (retval == -1) {
        perror("select()");
        return 0;
    } else if (retval){
        return 1;
    }
    else 
        return 0;
    /* FD_ISSET(0, &rfds) will be true. */
    return 0;
}

static __inline char scan_keyboard(){
    char in;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(STDIN_FILENO,&stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(STDIN_FILENO,&stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO,TCSANOW,&new_settings);
    in = getchar();
    tcsetattr(STDIN_FILENO,TCSANOW,&stored_settings);
    return in;
}