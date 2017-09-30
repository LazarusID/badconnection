#include "brokenpipe.h"

#include <unistd.h>

void broken_pipe(int fd) {
    close(fd);
}
