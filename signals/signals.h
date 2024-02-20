#ifndef SIGNALS
#define SIGNALS

int handle_signal(void);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
#endif /* SIGNALS */
