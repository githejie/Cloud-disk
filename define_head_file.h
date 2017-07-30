#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include  <errno.h>
#include  <stdlib.h>
#include  <linux/input.h> 
#include  <pwd.h>
#include  <grp.h>
#include  <time.h>
#include  <sys/file.h>
#include  <dirent.h>
#include  <sys/mman.h>
#include  <sys/uio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/sem.h>
#include <sys/socket.h>
#include <rpc/rpc.h>


#define  FILE_CRW_FLAG  O_CREAT|O_EXCL|O_RDWR
#define  FILE_CW_FLAG   O_CREAT|O_EXCL|O_WRONLY
#define  FILE_W_FLAG    O_WRONLY|O_TRUNC
#define  FILE_RW_FLAG   O_RDWR
#define  FILE_INIT_MODE S_IRWXU|S_IRWXG|S_IRWXO
#define  FILE_RWB_FLAG  O_RDWR|O_NONBLOCK
#define  BUF_SIZE  1024
