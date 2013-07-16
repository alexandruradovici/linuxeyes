00001 /*
00002         mpglib: test program for libmpg123, in the style of the legacy mpglib test program
00003 
00004         copyright 2007 by the mpg123 project - free software under the terms of the LGPL 2.1
00005         see COPYING and AUTHORS files in distribution or http://mpg123.org
00006         initially written by Thomas Orgis
00007 */
00008 
00009 #include <mpg123.h>
00010 
00011 /* unistd.h is not available under MSVC, 
00012  io.h defines the read and write functions */
00013 #ifndef _MSC_VER
00014 #include <unistd.h>
00015 #else
00016 #include <io.h>
00017 #endif
00018 
00019 #ifdef _WIN32
00020 #include <fcntl.h>
00021 #endif
00022 
00023 #include <stdio.h>
00024 
00025 #define INBUFF  16384
00026 #define OUTBUFF 32768 
00027 
00028 int main(int argc, char **argv)
00029 {
00030         size_t size;
00031         unsigned char buf[INBUFF];  /* input buffer  */
00032         unsigned char out[OUTBUFF]; /* output buffer */
00033         ssize_t len;
00034         int ret;
00035         size_t in = 0, outc = 0;
00036         mpg123_handle *m;
00037 
00038 #ifdef _WIN32
00039 _setmode(_fileno(stdin),_O_BINARY);
00040 _setmode(_fileno(stdout),_O_BINARY);
00041 #endif
00042 
00043         mpg123_init();
00044         m = mpg123_new(argc > 1 ? argv[1] : NULL, &ret);
00045         if(m == NULL)
00046         {
00047                 fprintf(stderr,"Unable to create mpg123 handle: %s\n", mpg123_plain_strerror(ret));
00048                 return -1;
00049         }
00050         mpg123_param(m, MPG123_VERBOSE, 2, 0); /* Brabble a bit about the parsing/decoding. */
00051 
00052         /* Now mpg123 is being prepared for feeding. The main loop will read chunks from stdin and feed them to mpg123;
00053            then take decoded data as available to write to stdout. */
00054         mpg123_open_feed(m);
00055         if(m == NULL) return -1;
00056 
00057         fprintf(stderr, "Feed me some MPEG audio to stdin, I will decode to stdout.\n");
00058         while(1) /* Read and write until everything is through. */
00059         {
00060                 len = read(0,buf,INBUFF);
00061                 if(len <= 0)
00062                 {
00063                         fprintf(stderr, "input data end\n");
00064                         break;
00065                 }
00066                 in += len;
00067                 /* Feed input chunk and get first chunk of decoded audio. */
00068                 ret = mpg123_decode(m,buf,len,out,OUTBUFF,&size);
00069                 if(ret == MPG123_NEW_FORMAT)
00070                 {
00071                         long rate;
00072                         int channels, enc;
00073                         mpg123_getformat(m, &rate, &channels, &enc);
00074                         fprintf(stderr, "New format: %li Hz, %i channels, encoding value %i\n", rate, channels, enc);
00075                 }
00076                 write(1,out,size);
00077                 outc += size;
00078                 while(ret != MPG123_ERR && ret != MPG123_NEED_MORE)
00079                 { /* Get all decoded audio that is available now before feeding more input. */
00080                         ret = mpg123_decode(m,NULL,0,out,OUTBUFF,&size);
00081                         write(1,out,size);
00082                         outc += size;
00083                 }
00084                 if(ret == MPG123_ERR){ fprintf(stderr, "some error: %s", mpg123_strerror(m)); break; }
00085         }
00086         fprintf(stderr, "%lu bytes in, %lu bytes out\n", (unsigned long)in, (unsigned long)outc);
00087 
00088         /* Done decoding, now just clean up and leave. */
00089         mpg123_delete(m);
00090         mpg123_exit();
00091         return 0;
00092 }