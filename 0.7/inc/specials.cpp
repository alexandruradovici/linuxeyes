#include <unistd.h>

void jazzpiper()
{
  int scr2=4;
  WINDOW *w1;
  w1=newwin (scr2+1,62,(6+(scr-scr2)/2),9);
  wrefresh (w1);
  werase (w1);
  WINDOW *w;
  w=newwin (scr2-1,60,7+((scr-scr2)/2),10);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  box (w,ACS_VLINE,ACS_HLINE);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Save Playlist for JazzPIPER MCD650S");
  wsetcolor (w,12,0);
  mvwprintw (w,scr2-3,2,"Playlist");
  wrefresh(w);
  readstring (w,1,11,46,"/",'\0');
  if (strcmp(memstring,"")!=0)
  {
    int i;
    FILE *f;
    f=fopen (memstring,"w");
    for (i=0;i<=n;i++)  fprintf (f,"%.3d    %s\n\r",i+1,filelist[n-i].text);
    fclose (f);
  }
}
