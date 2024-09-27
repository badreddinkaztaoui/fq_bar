#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <X11/Xlib.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <unistd.h>

#define TIME_FORMAT "%H:%M (%d-%m-%Y)"
#define MAXSTR 1024

static const char *get_date(void);
static const char *get_available_ram(void);
static const char *get_cpu_usage(void);
static const char *get_uname(void);

static void set_root_name(const char *name);

static const char *get_date(void) {
    static char date[MAXSTR];
    time_t now = time(0);
    strftime(date, MAXSTR, TIME_FORMAT, localtime(&now));
    return date;
}

static const char *get_available_ram(void) {
    static char ram_info[MAXSTR];
    struct sysinfo s;
    sysinfo(&s);
    snprintf(ram_info, sizeof(ram_info), "RAM: %.1f/%.1f GB",
             ((double)(s.totalram - s.freeram)) / (1024 * 1024 * 1024),
             ((double)s.totalram) / (1024 * 1024 * 1024));
    return ram_info;
}

static const char *get_uname(void) {
    static char uname_str[MAXSTR];
    struct utsname u;
    if (uname(&u) == 0) {
        snprintf(uname_str, sizeof(uname_str), "%s %s", u.nodename, u.release);
    } else {
        strncpy(uname_str, "Unknown", sizeof(uname_str));
    }
    return uname_str;
}

static const char* get_cpu_usage() {
    FILE *fp;
    char buf[1024];
    double user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    char *cpu_usage_str;

    fp = fopen("/proc/stat", "r");
    if (!fp) {
        perror("fopen");
        return NULL;
    }

    if (fgets(buf, sizeof(buf), fp)) {
        sscanf(buf, "cpu %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
               &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice);
    }

    fclose(fp);

    double total_time = user + nice + system + idle + iowait + irq + softirq + steal;
    double cpu_usage = ((total_time - idle) / total_time) * 100;

    cpu_usage_str = malloc(sizeof(char) * 10);

    snprintf(cpu_usage_str, 10, "%.2f%%", cpu_usage);

    return cpu_usage_str;
}

static void set_root_name(const char *name) {
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "[ft_bar] cannot open display!\n");
        exit(1);
    }
    XStoreName(display, DefaultRootWindow(display), name);
    XSync(display, 0);
    XCloseDisplay(display);
}

int main(void) {
    char status[MAXSTR];

    while (1) {
        snprintf(status, sizeof(status), "%s | %s | %s | %s",
                 get_available_ram(), get_cpu_usage(), get_date(), get_uname());

        set_root_name(status);
        sleep(1);
    }

    return 0;
}
