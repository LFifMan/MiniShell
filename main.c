#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    while (1) {
        printf("Prompt> ");
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "exit\n") == 0) {
            break;
        }
    }
    return 0;
}
