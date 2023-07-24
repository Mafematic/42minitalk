#ifndef SERVERCLIENT_H
# define SERVERCLIENT_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>

int	ft_atoi(const char *nptr);

#endif

/*
struct sigaction {
    void (*sa_handler)(int, pid_t, char*);
    sigset_t sa_mask;
    int sa_flags;
};
*/