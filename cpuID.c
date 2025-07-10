#include <intrin.h>
#include <stdio.h>

int main() {
    int info[4];
    __cpuid(info, 0x15);

    unsigned int denom       = (unsigned int) info[0];  // EAX
    unsigned int numer       = (unsigned int) info[1];  // EBX
    unsigned int core_clock  = (unsigned int) info[2];  // ECX

    printf("EAX (denominator)       : %u\n", denom);
    printf("EBX (numerator)         : %u\n", numer);
    printf("ECX (core crystal clock): %u Hz\n", core_clock);

    if (denom && numer) {
        double tsc_hz = (double)core_clock * numer / denom;
        printf("=> Computed TSC freq    : %.0f Hz\n", tsc_hz);
    } else {
        printf("Ratio or core clock not enumerated by CPUID(0x15).\n");
    }

    return 0;
}
