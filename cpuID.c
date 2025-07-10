#include <intrin.h>
#include <stdio.h>

int main() {
    int info[4];
    __cpuid(info, 0x15);
    printf("Core crystal freq from CPUID.15: %llu Hz\n", (unsigned long long)info[2]);
    return 0;
}
