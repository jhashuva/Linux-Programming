#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc,char *argv[]) {
    const char *dirname = argv[1];
    mode_t mode = 0777; // Set permissions for the new directory

    // Create a new directory
    if (mkdir(dirname, mode) == -1) {
        perror("Error creating directory");
        return 1;
    }

    printf("Directory '%s' created successfully.\n", dirname);

    return 0;
}


