#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main() {
    const char *dirname = ".";  // Current directory

    // Open the directory for reading
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    // Read and print directory entries
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        char filename[512];
        snprintf(filename, sizeof(filename), "%s/%s", dirname, entry->d_name);

        struct stat file_stat;
        if (stat(filename, &file_stat) == -1) {
            perror("Error getting file status");
            continue;
        }

        struct passwd *user_info = getpwuid(file_stat.st_uid);
        struct group *group_info = getgrgid(file_stat.st_gid);
        char date[50];
        strftime(date, sizeof(date), "%b %d %H:%M", localtime(&file_stat.st_mtime));

        printf("%ld\t%s\t%s\t%s\t%ld\t%s\t%s\n",
               file_stat.st_blocks / 2,
               (S_ISDIR(file_stat.st_mode)) ? "d" : "-",
               (file_stat.st_mode & S_IRUSR) ? "r" : "-",
               (file_stat.st_mode & S_IWUSR) ? "w" : "-",
               file_stat.st_size,
               user_info->pw_name,
               entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return 0;
}

