#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <string.h>
#include <ctype.h>

static struct {
    const char* name;
    int value;
} event_types[] = {
    { "SYN", EV_SYN },
    { "KEY", EV_KEY },
    { "REL", EV_REL },
    { "ABS", EV_ABS },
    { "MSC", EV_MSC },
    { "SW",  EV_SW },
    { "LED", EV_LED },
    { "SND", EV_SND },
    { "REP", EV_REP },
    { "FF",  EV_FF },
    { "PWR", EV_PWR },
    { "FF_STATUS", EV_FF_STATUS },
    { NULL, 0 }
};

static int parse_event_type(const char* s) {
    for (int i = 0; event_types[i].name; i++) {
        if (strcasecmp(event_types[i].name, s) == 0)
            return event_types[i].value;
    }
    
    if (isdigit(*s))
        return atoi(s);

    return -1;
}

static int parse_values(const char* arg, int* values, int max_values) {
    int count = 0;
    char* copy = strdup(arg);
    char* tok = strtok(copy, ",");
    while (tok && count < max_values) {
        values[count++] = atoi(tok);
        tok = strtok(NULL, ",");
    }
    free(copy);
    return count;
}

static int value_accepted(int value, int *accepted, int n) {
    for (int i = 0; i < n; i++)
        if (value == accepted[i])
            return 1;
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 5) {
        fprintf(
            stderr,
            "Usage: %s <input-device> <event-type> <code> <accepted-values> [timeout-ms]\n"
            "Example: %s /dev/input/event4 KEY 115 1,2 500\n"
            "Event type names: SYN, KEY, REL, ABS, MSC, SW, LED, SND, REP, FF, PWR, FF_STATUS\n",
            argv[0], argv[0]
        );
        return 2;
    }

    const char* dev = argv[1];
    int type = parse_event_type(argv[2]);
    int code = atoi(argv[3]);
    int accepted[32];
    int n_accepted = parse_values(argv[4], accepted, 32);
    int timeout_ms = (argc > 5) ? atoi(argv[5]) : -1;

    if (type < 0 || code < 0 || n_accepted == 0) {
        fprintf(stderr, "Invalid arguments.\n");
        return 2;
    }

    int fd = open(dev, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 2;
    }

    struct timeval tv;
    struct timeval *ptv = NULL;
    if (timeout_ms >= 0) {
        tv.tv_sec = timeout_ms / 1000;
        tv.tv_usec = (timeout_ms % 1000) * 1000;
        ptv = &tv;
    }

    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    int ret = select(fd + 1, &rfds, NULL, NULL, ptv);
    if (ret <= 0) {
        close(fd);
        return 1;
    }

    struct input_event ev;
    while (read(fd, &ev, sizeof(ev)) == sizeof(ev)) {
        if (ev.type == type && ev.code == code && value_accepted(ev.value, accepted, n_accepted)) {
            close(fd);
            return 0;
        }

        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);
        if (select(fd + 1, &rfds, NULL, NULL, ptv) <= 0)
            break;
    }

    close(fd);
    return 1;
}