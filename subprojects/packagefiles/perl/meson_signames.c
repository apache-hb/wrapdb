#define _GNU_SOURCE

#include <signal.h>
#include <stdio.h>
#include <string.h>

int main() {
    for (int i = 0; i < NSIG; i++) {
        const char *abbrev = sigabbrev_np(i);
        if (abbrev == NULL) {
            printf("\"SIG%d\", ", i);
        } else {
            printf("\"%s\", ", abbrev);
        }
    }
    printf("0\n");
    return 0;
}