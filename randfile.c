#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int rand_num() {
    int fd = open("/dev/random", O_RDONLY);
    unsigned int* rand = (unsigned int*) malloc(sizeof(int));
    read(fd, rand, sizeof(int));
    close(fd);
    unsigned int num = *rand;
    free(rand);
    return num;
}

int main() {
    printf("random: %u\n", rand_num());
    int nums[10];
    int i = 0;
    for (; i < 10; i++) {
        nums[i] = rand_num();
    }

    for(i = 0; i < 10; i++) {
        printf("rand num #%d: %u\n", i, nums[i]);
    }

    int fd = open("numbers", O_CREAT | O_WRONLY, 0644);
    write(fd, nums, sizeof(nums));
    close(fd);

    int fd2 = open("numbers", O_RDONLY);
    int nums2[10];

    read(fd2, nums2, sizeof(nums));
    close(fd2);
    printf("\n\n\n");
    for(i = 0; i < 10; i++) {
        printf("rand num2 #%d: %u\n", i, nums2[i]);
    }

}
