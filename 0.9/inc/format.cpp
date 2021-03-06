#include <fstream.h>

struct
{
   char name[500];
   char artist[30];
   char song[30];
   char text[80];
   int min;
   int sec;
   int tag;    
   int curent;
   int mark;
}le05[5000];

void readname (char *text, char *caption)
{
  int scr2=4;
  WINDOW *w1;
  w1=newwin (scr2+1,62,(6+(nrscr-scr2)/2),(nrcols-62)/2);
  wrefresh (w1);
  werase (w1);
  WINDOW *w;
  w=newwin (scr2-1,60,7+((nrscr-scr2)/2),(nrcols-60)/2);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,60,scr2-1);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," %s ",caption);
  wsetcolor (w,12,0);
  mvwprintw (w,scr2-3,2,"Filename");
  wrefresh(w);
  readstring (w,1,11,46,text,'\0');
}

int formatselect()
{
  int format=0;
  int scr2=9;
  int t=0;
  WINDOW *w;
  w=newwin (scr2-1,29,7+((nrscr-scr2)/2),(nrcols-29)/2);
  wsetcolor (w,13,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,29,scr2-1);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Select Format ");
  wsetcolor (w,12,0);
  mvwprintw (w,2,2,"x : XMMS (files list)");
  mvwprintw (w,3,2,"l : LP03 (LinuxEyes v0.3)");
  mvwprintw (w,4,2,"L : LP05 (LinuxEyes v0.5)");
  mvwprintw (w,5,2,"m : M3U (>= XMMS 1.2.7)");
  mvwprintw (w,7,14," ESC - quit ");
  wrefresh(w);
  timeout (1);
  format=0;
  do
  {
    do
    {
      messages();
      t=getch();
    } while (t==ERR);
    if (t=='x')
    {
      format=1;
      t='q';
    }
    if (t=='l')
    {
      format=2;
      t='q';
    }
    if (t=='L')
    {
      format=3;
      t='q';
    }
    if (t=='m')
    {
      format=4;
      t='q';
    }
    if (t==27)
    {
      t=getch();
      if (t==ERR) t='q';
    }
  } while (t!='q');
  werase (w);
  wrefresh (w);
  return format;
}

int importxmms (char *file)
{
  int i=-1;
  char s[1000];
  ifstream f(file);
  if (!f.fail())
  while (!f.eof())
  { 
    i++;
      f.getline (s,sizeof(s));
      filelist[i].tag=id3(s,&my_id3);
      strcpy (filelist[i].name,s);
      strcpy(filelist[i].artist,my_id3.artist);
      strcpy(filelist[i].song,my_id3.song);
      strcpy(filelist[i].text,text);
      filelist[i].min=min;
      filelist[i].sec=sec;
      if (strcmp(s,"")==0) i--;
  }
  f.close();
/*  if (number > 0)
  {
    f.open(file);
    if (f.good())
    while (!f.eof())
    { 
      i++;
      f.getline (s,sizeof(s));
      filelist[i].tag=id3(s,&my_id3);
      strcpy (filelist[i].name,s);
      strcpy(filelist[i].artist,my_id3.artist);
      strcpy(filelist[i].song,my_id3.song);
      strcpy(filelist[i].text,text);
      filelist[i].min=min;
      filelist[i].sec=sec;
      if (strcmp(s,"")==0) i--;
      setcolor (1,0);
//      mvprintw (scr+9,1,"Loading playlist %d%%                                                        ",((i+1)*100)/number);
      refresh();
    }	
    f.close();
  }
  else return -1;  */
  return i;
}

int importle3 (char *file)
{
    int i;
    ifstream f;
    char s[1000];
    i=-1;
    f.open(file);
    f.getline (s,sizeof(s),'=');
    if (strcmp(s,"eypl")==0)
    {
      f.getline (s,sizeof(s));
      strcpy (eypl,s);
    }
    else strcpy (eypl,"(no name)");
    f.getline (s,sizeof (s));
    if (!f.fail())
    while ((!f.eof()) && (!f.fail()))
    { 
      i++;
      f.getline (s,sizeof(s),'\n');
      if (strcmp (s,"}")!=0)
      {
        strcpy (filelist[i].name,s);
        f.getline (s,sizeof(s),'\n');
        strcpy (filelist[i].text,s);
        f >>filelist[i].min >>filelist[i].sec;
	  f.getline (s,sizeof(s));
      }
//	f.getline(s,sizeof(s),'\n');
//	f.getline (s,sizeof(s));
//	f.getline (s,sizeof (filelist[i].min),':');
//	strcpy(filelist[i].text,s);
/*        id3(s);
        strcpy (filelist[i].name,s);
        strcpy(filelist[i].artist,artist);
        strcpy(filelist[i].song,song);
        strcpy(filelist[i].text,text);
        filelist[i].min=min;
        filelist[i].sec=sec;
        filelist[i].tag=tag; 
	filelist[i].curent=0; */
      if (strcmp(s,"}")==0) i--;
    }	
    f.close();
    return i;
}

int importm3u (char *file)
{
  int i=-1;
  char s[1000];
  ifstream f(file);
 if (!f.fail())
 {
 if (!f.eof()) f.getline (s,sizeof (s)); else strcpy (s,"");
 if (strcmp (s,"#EXTM3U")==0)
  while (!f.eof())
  { 
    f.getline (s,sizeof(s));
      if (!f.eof())
      {
      i++;
      f.getline (s,sizeof(s));
      filelist[i].tag=id3(s,&my_id3);
      strcpy (filelist[i].name,s);
      strcpy(filelist[i].artist,my_id3.artist);
      strcpy(filelist[i].song,my_id3.song);
      strcpy(filelist[i].text,text);
      filelist[i].min=min;
      filelist[i].sec=sec;
      if (strcmp(s,"")==0) i--;
      setcolor (1,0);
//      mvprintw (scr+9,1,"Loading playlist %d%%                                                        ",((i+1)*100)/number);
      refresh();
      }
    if (strcmp(s,"")==0) i--;
  }
  f.close();
 }
/*  if ((number > 0) && (e==1))
  {
    f.open(file);
    if (f.good())
    {
    if (!f.eof()) f.getline (s,sizeof(s));
    while (!f.eof())
    { 
      
    }
    }	
    f.close();
  }
  else return -1;  */
  return i;
}

int importle5(char *file)
{
    int scr2=4;
    WINDOW *w;
    w=newwin (scr2-1,36,7+((nrscr-scr2)/2),(nrcols-36)/2);
    wsetcolor (w,13,0);
    mvwprintw (w,2,0,"Please wait...");
    for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
    wsetcolor (w,12,0);
    le_border (w,36,scr2-1);
    wrefresh(w);
    int i=0;
    FILE *f;
    f=fopen (file,"r");
    if (f!=NULL)
    {
      int number=0;
      char playlistinfo[5];
      fread (&playlistinfo,sizeof(playlistinfo),1,f);
      fread (&number,sizeof(number),1,f);
      while ((!feof(f)) && (i<=number))
      {
        fread (&le05[i],sizeof(le05[i]),1,f);
	strcpy (filelist[i].name,le05[i].name);
	strcpy (filelist[i].artist,le05[i].artist);
	strcpy (filelist[i].song,le05[i].song);
	strcpy (filelist[i].text,le05[i].text);
        filelist[i].tag=le05[i].tag;
	i++;
      }
      fclose (f);
    }
    wsetcolor (w,12,0);
//    mvwprintw (w,1,2,"Loading playlist %d%% ",((i+1)*100)/n);
    wrefresh(w);
    wrefresh(w);
    werase (w);
    i--;
    return i;
}

void export2xmms (char *file)
{
  ofstream f(file);
  for (int i=0;i<=n;i++)
  {
    f <<filelist[i].name <<endl;
  }
  f.close();
}

void export2le3 (char *file)
{
  ofstream f(file);
  f <<"eypl=LinuxEyes Playlist" <<endl;
  f <<"{" <<endl;
  for (int i=0;i<=n;i++)
  { 
    if (i<n) f <<filelist[i].name <<"\n" <<filelist[i].text <<"\n" <<filelist[i].min <<" " <<filelist[i].sec <<endl;
    if (i==n) f <<filelist[i].name <<"\n" <<filelist[i].text <<"\n" <<filelist[i].min <<" " <<filelist[i].sec <<endl;
  }  
  f <<"}";
  f.close();
}

void export2le5(char *file)
{
      FILE *f;
      f=fopen (file,"w");
      if (f!=NULL)
      {
        char playlistinfo[5];
	strcpy (playlistinfo,"LE5PL");
	fwrite (&playlistinfo,sizeof(playlistinfo),1,f);
	fwrite (&n,sizeof(n),1,f);
        int i=0;
        for (i=0;i<=n;i++) 
	{
	  strcpy (le05[i].name,filelist[i].name);
	  strcpy (le05[i].artist,filelist[i].artist);
	  strcpy (le05[i].song,filelist[i].song);
	  strcpy (le05[i].text,filelist[i].text);
	  le05[i].tag=filelist[i].tag;
	  le05[i].curent=0;
	  le05[i].mark=0;
	  fwrite (&le05[i],sizeof(le05[i]),1,f);
	}
        fclose (f);
      } 
}
