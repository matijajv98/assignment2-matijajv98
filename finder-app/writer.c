#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{

    openlog("file_writer", LOG_PID | LOG_CONS | LOG_PERROR, LOG_USER);

    if(argc != 3)
    {
        syslog(LOG_ERR, "Invalid number of arguments: expected 2, got %d", argc - 1);
        closelog();
        return -1;
    }

    const char *filename = argv[1];
    const char *content = argv[2];

    syslog(LOG_DEBUG, "Starting writing into file: filename='%s', contenct='%s'\n", filename, content);

    int fd;
    fd = open(filename,  O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if(fd == -1)
    {
        syslog(LOG_ERR, "Failed to open/create file %s: %s\n", filename, strerror(errno));
        closelog();
        return -1;
    }

    syslog(LOG_DEBUG, "File opened successfully: fd=%d", fd);

    size_t len = strlen(content);
    ssize_t bytes_written = write(fd, content, len);

    if(bytes_written == -1)
    {
        syslog(LOG_ERR, "Failed to write to file %s: %s", filename, strerror(errno));
        close(fd);
        closelog();
        return 1;
    }

    if((size_t)bytes_written != len)
    {
        syslog(LOG_WARNING, "Partial write to file %s!", filename);
    }
    else
    {
        syslog(LOG_INFO, "Successfully wrote to file %s", filename);
    }

    if(close(fd) == -1)
    {
        syslog(LOG_ERR, "Error closing file %s: %s\n", filename, strerror(errno));
        closelog();
        return 1;
    }

    syslog(LOG_INFO, "Write operation completed successfully: filename=%s", filename);
    closelog();

    return 0;
}