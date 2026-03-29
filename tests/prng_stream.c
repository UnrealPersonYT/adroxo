// Utilize in a PRNG tester
#include <adroxo.h>
#include <stdint.h>
#include <stdio.h>

int main(void){
    FILE* _stdout = stdout;
    uint64_t ctr = 1;
    setvbuf(_stdout, NULL, _IONBF, 0);
    while(1){
        uint64_t buffer[8] = {ctr++};
        adroxo512(buffer);
        fwrite(buffer, sizeof(uint64_t), sizeof(buffer) / sizeof(uint64_t), _stdout);
    }
    return 0;
}