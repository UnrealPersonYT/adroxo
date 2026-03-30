// Utilize in a PRNG tester
#include <adroxo.h>
#include <stdio.h>

int main(void){
    uint64_t buffer[4] = {1,2,3,4};
    FILE* _stdout = stdout;
    setvbuf(_stdout, NULL, _IONBF, 0);
    while(1){
        uint64_t v = adroxo64_q(buffer);
        fwrite(&v, sizeof(v), 1, _stdout);
    }
    return 0;
}