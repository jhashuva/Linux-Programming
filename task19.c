#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc,char *argv[]) {

    const char *dirname;

    if(argc==1){
    dirname = "."; // Current directory
    }else{
    dirname = argv[1];
    }
    // Open the directory for reading
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    printf("Contents of directory '%s':\n", dirname);

    // Read and print the directory entries
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    if (closedir(dir) == -1) {
        perror("Error closing directory");
        return 1;
    }

    return 0;
}
