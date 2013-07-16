#include <sys/types.h>
#include <sys/stat.h>
#include <ftw.h>
#include <unistd.h>

int files=0;
int nr=0;
int nrd=0;
int nrd_changed=0;
int show=0;
char cd_path[1000];
FILE *save_to_f;
mpeg_id3 s_my_id3;
WINDOW *win;
list_type mp3s; //list of mp3s
int mp3snr=-1; //nr of mp3s - 1

//__ftw_func_t fisier()//(const char *s, const struct stat *fis, int x)
int fisier(const char *s, const struct stat *fis, int x, struct FTW *x_ftw)
{
  wsetcolor (win,12,0);
  if (show==1) mvwprintw (win,1,2,"Found %d files",nr);
  wrefresh(win);  
  if ((x==FTW_D) && (files==0))
  {
//    printf ("%d ",x_ftw->level);
//    puts (s);
      files=1;
      nrd_changed=0;
      nftw (s,fisier,0,0);
      files=0;
  }
  if ((x_ftw->level==1) && (files==1) && (x!=FTW_D)) 
  {
    char *ext;
    if (rindex(s,'.') != NULL) 
    { 
      ext=strdup (rindex(s,'.'));
      if ((strcasecmp(ext,".mpg")==0) || (strcasecmp(ext,".mp2")==0) || (strcasecmp(ext,".mp3")==0))
      {
        nr++;
	if (nrd_changed==0)
	{
	  nrd++;
	  mp3snr++;
	  sprintf (mp3s[mp3snr],"------- DIR %.3d -------",nrd);
	  nrd_changed=1;
	}
	id3 ((char*)s,&s_my_id3);
	mp3snr++;
        sprintf (mp3s[mp3snr],"%.3d   %s",nr,text);
      }
    }
  }
  return 0;
}

void getdir (char *dir)
{
  int scr2=4;
  mp3snr=-1;
  win=newwin (scr2-1,36,7+((nrscr-scr2)/2),(nrcols-36)/2);
  wsetcolor (win,13,0);
  mvwprintw (win,2,0,"Please wait...");
  for (int h=0;h<=scr2-1;h++) mvwprintw (win,h,0,"                                                            ");
  wsetcolor (win,12,0);
  le_border (win,36,scr2-1);
  wrefresh(win);
  nr=0;
  nrd=0;
  nrd_changed=0;
/*  show=0;
  files=1;
  nftw (dir,fisier,0,0); */
  show=1;
  files=0;
  nftw (dir,fisier,0,0);
  reread=1;
  werase (win);
}

void jazzpiper()
{
  /*int scr2=4;
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
  readstring (w,1,11,46,"/",'\0');*/
  strcpy (memstring,"");
  readstring_window ("Make Playlist for JazzPIPER MCD650S", "CD-ROM Path", 0, '\0', 0);
  if (strcmp(memstring,"")!=0)
  {
      //for (i=0;i<=n;i++)  fprintf (f,"%.3d    %s\n\r",i+1,filelist[n-i].text);
      strcpy (cd_path,memstring);
      getdir (cd_path);
      if (showlist (nrscr-4,"JazzPIPER MCD650S Playlist", 0, mp3s, mp3snr)==1)
      {
        strcpy (memstring,getcwd(NULL,0));
        strcat (memstring,"/");
        readstring_window ("Make Playlist for JazzPIPER MCD650S", "Save to file", 0, '\0', 0);
	if (strcmp(memstring,"")!=0)
        {
          save_to_f=fopen (memstring,"w");
          fprintf (save_to_f,"JazzPIPER MCD650S Playlist - LinuxEyes %s\n",version);
	  for (int i=0;i<=mp3snr;i++) fprintf (save_to_f,"%s\n",mp3s[i]);
	  fclose (save_to_f);
	}
      }
  }
}
