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
    if (fd != -1) {
        int wr_stat = write(fd, nums, sizeof(nums));
        if (wr_stat == -1) {
            printf("WRITING FAILED!!");
        }
        close(fd);
    } else {
        printf("Couldn't open file");
    }

    int failure = 0;
    int fd2 = open("numbers", O_RDONLY);
    int nums2[10];
    if (fd2 != -1) {
        int rd_stat = read(fd2, nums2, sizeof(nums));
        if (rd_stat == -1) {
            printf("Reading failed, setting all vals to 0");
            failure = 1;
        }
        close(fd2);
    } else {
        printf("open failed, setting all vals to 0");
        failure = 0;
    }
    for(;failure && i < 10; i++) {
        nums2[i] = 0;
    }
    printf("\n\n\n");
    for(i = 0; i < 10; i++) {
        printf("rand num2 #%d: %u\n", i, nums2[i]);
    }

}
