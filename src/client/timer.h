typedef struct timer {
    double start;
    double lifetime;
} Timer;

bool is_timer_done(Timer *t);
double get_elapsed(Timer *t);
void start_timer(Timer *t, double lifetime);

/* vim: set et sw=4 ts=4 tw=72: */
