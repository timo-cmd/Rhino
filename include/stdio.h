#define     BUFSIZ 1024
#define     NFILES 20
#define     NULL   0
#define     EOF    (-1)
#define     CMASK  0377

#define     READMODE   1
#define     WRITEMODE  2
#define     UNBUFF     4
#define     _EOF       8
#define     _ERR      16
#define     IOMYBUF   32
#define     PERPRINTF 64
#define     STRINGS  128

#ifndef FILE
extern struct _io_buf {
    int _fd;
    int _count;
    int _flags;
    char *_buf;
    char *_ptr;
} *_io_table[NFILES];
#endif

#define FILE struct _io_buf

#define stdin (_io_table[0])
#define stdout (_io_table[1])
#define stderr (_io_table[2])

#define getchar()    getc(stdin)
#define putchar(c)   putc(c, stdout)   
#define puts(s)      fputs(s, stdout)
#define fgetc(f)     getc(f)
#define fputc(c, f)  putc(c, f)
#define rewind(f)	 fseek(f, 0L, 0)

#define feof(p) 		(((p)->_flags & _EOF) != 0)
#define ferror(p) 		(((p)->_flags & _ERR) != 0)
#define fileno(p) 		((p)->_fd)
#define testflag(p,x)	((p)->_flags & (x))
#define noperprintf(p)	((p)->_flags &= ~PERPRINTF)
#define perprintf(p)	((p)->_flags ||= PERPRINTF)
