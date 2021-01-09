#include "SC.h"

int main() {
  int ret1, nbytes;
  mqd_t mq_id;
  struct mq_attr attr;
  struct stat s_b;
  attr.mq_msgsize = 256;
  attr.mq_maxmsg = 10;
  
  mq_id = mq_open("/mque", O_CREAT | O_RDWR, 0666, &attr);
  if (mq_id < 0) {
    perror("mq_open");
    exit(1);
  }

  char str1[20] = "hello.c";
  
  ret1 = mq_send(mq_id, str1, 20, 5);
  if (ret1 < 0) {
    perror("mq_send");
    exit(2);
  }

  int max_len= 256, prior;


  nbytes = mq_receive(mq_id, (char *)&s_b, 1024, &prior);
  if (nbytes < 0) {
    perror("mq_recv");
    exit(2);
  }


  printf("-------File Attributes--------\n");
  printf("ID of device                    : %ld\n", (long)s_b.st_dev);
  printf("Inode number of the file        : %ld\n", (long)s_b.st_ino);
  printf("File type                       : ");
  switch (s_b.st_mode & S_IFMT) {
  case S_IFBLK:
    printf("block the device\n");
    break;
  case S_IFCHR:
    printf("character\n");
    break;
  case S_IFDIR:
    printf("directory\n");
    break;
  case S_IFIFO:
    printf("FIFO pipe\n");
    break;
  case S_IFLNK:
    printf("symlink\n");
    break;
  case S_IFREG:
    printf("regular file\n");
    break;
  case S_IFSOCK:
    printf("socket \n");
    break;
  default:
    printf("unknown \n");
    break;
  }
  printf("Mode                            : %lo (octal)\n", (unsigned long)s_b.st_mode);
  printf("Link count                      : %ld\n", (long)s_b.st_nlink);
  printf("User ID                         : %ld\n" , (long)s_b.st_uid);
  printf("Group ID                        : %ld\n", (long)s_b.st_gid);
  printf("Blocksize for file system I/O   : %ld bytes\n", (long)s_b.st_blksize);
  printf("File size                       : %lld bytes\n", (long long)s_b.st_size);
  printf("Number of Blocks allocated : %lld\n", (long long)s_b.st_blocks);
  printf("Last status change              : %s", ctime(&s_b.st_ctime));
  printf("Last file access                : %s", ctime(&s_b.st_atime));
  printf("Last file modification          : %s", ctime(&s_b.st_mtime));

  /* Close the Queue */
  mq_close(mq_id);

  return 0;
}
