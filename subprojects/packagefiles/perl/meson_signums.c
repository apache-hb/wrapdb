#include <signal.h>
#include <stdio.h>

int main() {
    for (int i = 0; i < NSIG; i++) {
        printf("%d, ", i);
    }
    printf("0\n");
    return 0;
}