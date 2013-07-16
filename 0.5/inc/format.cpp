#include <fstream.h>

void readname (char *text, char *caption)
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
  mvwprintw (w,0,1," %s ",caption);
  wsetcolor (w,12,0);
  mvwprintw (w,scr2-3,2,"Filename");
  wrefresh(w);
  readstring (w,1,11,46,text);
}

int formatselect()
{
  int format=0;
  int scr2=7;
  int t=0;
  WINDOW *w;
  w=newwin (scr2-1,29,7+((scr-scr2)/2),24);
  wsetcolor (w,13,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  box (w,ACS_VLINE,ACS_HLINE);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Select Format ");
  wsetcolor (w,12,0);
  mvwprintw (w,2,2,"x : XMMS (files list)");
  mvwprintw (w,3,2,"l : LP03 (LinuxEyes v0.3)");
  mvwprintw (w,5,16," q - quit ");
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
  } while (t!='q');
  werase (w);
  wrefresh (w);
  return format;
}

int importxmms (char *file)
{
  int i=-1;
  char s[1000];
  int number=0;
  ifstream f(file);
  if (!f.fail())
  while (!f.eof())
  { 
    i++;
    f.getline (s,sizeof(s));
    if (strcmp(s,"")==0) i--;
  }
  f.close();
  number=i+1;
  i=-1;
  if (number > 0)
  {
    f.open(file);
    if (!f.fail())
    while (!f.eof())
    { 
      i++;
      f.getline (s,sizeof(s));
      id3(s);
      strcpy (filelist[i].name,s);
      strcpy(filelist[i].artist,artist);
      strcpy(filelist[i].song,song);
      strcpy(filelist[i].text,text);
      filelist[i].min=min;
      filelist[i].sec=sec;
      filelist[i].tag=tag; 
      if (strcmp(s,"")==0) i--;
      setcolor (1,0);
//      mvprintw (scr+9,1,"Loading playlist %d%%                                                        ",((i+1)*100)/number);
      refresh();
    }	
    f.close();
  }
  else return -1;  
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
