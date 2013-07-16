char artist[100],song[100],text[100]; //id3 main
static unsigned long duration=0; //duration
int scr=15,scrx=80; //the screen size, normal terminal 16
int min,sec; //duration main
int tag; //if file has id3 tag
int vol=90,pcm=90,balance=50; //volumes
int n,n2; //nr of files in playlist, n2 for search
int next=-1,curent=-1; //next song and current song
int reread=1; //reread playlist befor pressing a key
bool paused=false; //paused ?
int n1=0; //?
int v=50; //?
bool rnext=true; //random next
int autoplay=false; //-p parameter
char playlistfile[1000]; //playlist filename with path
char memstring[1000]; //memory string, for readstring
int prev[1000]; //previous songs list
int nr_prev=-1; //nr of previous songs
int playerror=0; //error on play
int nocolor=0; //--nocolors parameter
char mpegfile[1000][1000]; //files
int mpegnumber=-1; //nr of files
char path[1000]; //player path
int nclose=0; //"0" key function
int less=0; //scrolling up
int more=0; //scrolling down
char upcase[100]; //uppercase result
char eypl[100]; //playlist name
int tunknown,thour,tmin,tsec; //total time
int m=0,k=0,l=0;

#include "xaudio.h"
#include "player.h"
#include "decoder.h"
#include "file_input.h"
#include "mpeg_codec.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <string.h>
#include <fstream.h>
#include <dirent.h>
#include <unistd.h>
#include "inc/misc.cpp"
#include <ctype.h>

struct
{
   char name[500];
   char artist[100];
   char song[100];
   char text[100];
   int min;
   int sec;
   int tag;    
   int curent;
}filelist[5000],temp;

struct
{
  char text[100];
  int nr;
}filterlist[5000];

XA_Control *player;

int fileexists (char *file)
{
   int e; 
   e=access (file,R_OK);
   if (e==0) e=1;
   else e=0;
/*   ifstream test (file, ios::binary);
   if (test == NULL) e=0;
   else e=1; 
   test.close(); */
   return e;
}

void id3 (char *name)
{
    XA_DecoderInfo *decoder;            
    XA_InputModule module;
    XA_PropertyList list;
    XA_CodecModule codec;
    decoder_new (&decoder);
    file_input_module_register(&module);
    decoder_input_module_register(decoder, &module);
    mpeg_codec_module_register(&codec);
    decoder_codec_module_register(decoder, &codec);
    decoder_input_new(decoder, name,XA_DECODER_INPUT_AUTOSELECT);
    decoder_input_open(decoder);
    if (properties_get_list(decoder->status->info.properties, &list) == 
        XA_SUCCESS &&
        list.nb_properties > 0) 
        { 
	  int nr=list.nb_properties;
	  strcpy(artist,"Unknown");
	  strcpy(song,"Unknown");
	  strcpy(text,"");
	  tag=1;
	  if (list.properties[nr-2].type == XA_PROPERTY_TYPE_STRING) 
	      if (nr > 7) if (list.properties[nr-2].value.string != NULL) strcpy (artist,list.properties[nr-2].value.string);      
	  if (list.properties[nr-1].type == XA_PROPERTY_TYPE_STRING) 
	      if (nr > 7) if (list.properties[nr-1].value.string != NULL) strcpy (song,list.properties[nr-1].value.string);
	}
	if (decoder->status->info.duration != duration) duration = decoder->status->info.duration; 
	duration=duration / 1000;
	min=duration / 60;
	sec=duration % 60;
    decoder_input_close(decoder);	
    decoder_delete (decoder);	
    strcpy (text,artist);
    strcat (text," - ");
    strcat (text,song);
    if (!fileexists(name))
    {
      strcpy (artist,"Unknown");
      strcpy (song,"Unknown");
    }
    if ((strcmp(artist,"Unknown")==0) && (strcmp(song,"Unknown")==0)) 
    {
      tag=0;
      unsigned int pos=0,ext=0,i;
      char *s;
      s=strdup(name);
      if (s[0]=='.') ext=0;
      else ext=strlen(rindex(s,'.'));
      pos=strlen(name)-strlen(rindex(s,'/'))+1;
      for (i=pos;i<=strlen(name)-ext;i++) s[i-pos]=s[i];
      s[i-pos-1]='\0';
      /* fprintf (stderr,"%s %d %d\n\r",name,pos,ext);
      getch(); */
      strcpy(text,s);
    }
}

void sort(int l,int r)
{
  int i=l;
  int j=r;
  char y[100];
  strcpy (y,"");
  strcpy (y,filelist[(l+r) / 2].text);
  do
  {
    while (strcasecmp(filelist[i].text,y) < 0) i++;
    while (strcasecmp(filelist[j].text,y) > 0) j--;
    if (i <= j)
    {
      temp=filelist[i];
      filelist[i]=filelist[j];
      filelist[j]=temp;
      i++;
      j--;
    }
  }
  while (i <= j);
  if (l < j) sort (l,j);
  if (i < r) sort (i,r);
}

void uppercase (char s[100])
{
  strcpy (upcase,s);
  for (unsigned int i=0;i<=strlen(s);i++) upcase[i]=toupper (s[i]);
}

void getcurent()
{
  for (int i=0;i<=n;i++) if (filelist[i].curent==1) curent=i;
}

void resettime()
{
    setcolor (1,0);
    mvprintw (4,72,"[00:00]");
    mvprintw (5,57,"[--------------------]");
    n1=-100;
}

void reset()
{
    setcolor (3,1);
    mvprintw (0,0,"                                                                                ");
    mvprintw (0,0,"XMP [%.66s]",filelist[curent].name);
    setcolor (1,0);
    mvprintw (4,9,"                                                    ");
    mvprintw (5,9,"                                                    ");
    if (filelist[curent].tag==0) 
    {
      mvprintw (4,1,"        ");
      mvprintw (5,9,"%s",filelist[curent].text);
    } 
    else
    {
      mvprintw (4,1,"Artist: ");  
      mvprintw (4,9,"%s",filelist[curent].artist);
      mvprintw (5,9,"%s",filelist[curent].song);
    }
    resettime();
}

void position(int n)
{
    control_message_send (player,XA_MSG_COMMAND_SEEK,n1+n,20);
}

void mpegpause()
{
    if (paused==true) control_message_send (player,XA_MSG_COMMAND_PLAY);
    else control_message_send (player,XA_MSG_COMMAND_PAUSE);
    paused = !paused;
}

void play (char *name)
{
    filelist[prev[nr_prev]].curent=0;
    if (fileexists(name))
    {
      id3 (name);
      strcpy(filelist[curent].artist,artist);
      strcpy(filelist[curent].song,song);
      strcpy(filelist[curent].text,text);
      filelist[curent].min=min;
      filelist[curent].sec=sec;
      filelist[curent].tag=tag; 
      control_message_send(player,XA_MSG_COMMAND_INPUT_OPEN,name);
      control_message_send (player,XA_MSG_SET_OUTPUT_VOLUME,balance,pcm,vol);
      control_message_send(player,XA_MSG_COMMAND_PLAY);
      setcolor (3,1);
      mvprintw (0,0,"                                                                                ",name);
      mvprintw (0,0,"LinuxEyes [%.66s]",name);
      setcolor (1,0);
      mvprintw (4,9,"                                                    ");
      mvprintw (5,9,"                                                    ");
      if (filelist[curent].tag==0) 
      {
        mvprintw (4,1,"        ");
        mvprintw (5,9,"%s",filelist[curent].text);
      } 
      else
      {
        mvprintw (4,1,"Artist: ");  
        mvprintw (4,9,"%s",filelist[curent].artist);
        mvprintw (5,9,"%s",filelist[curent].song);
      }
      filelist[curent].curent=1;
      resettime();
    }
    else playerror=1;
    reread=1;
}

void stop ()
{
    control_message_send(player,XA_MSG_COMMAND_STOP);
    resettime();
}

void playprev()
{
  if (nr_prev > -1)
  {
    filelist[curent].curent=0;
    curent=prev[nr_prev];
    nr_prev--;
    filelist[curent].curent=1;
    play (filelist[curent].name);
  }
}

void playnext()
{
    if (nclose==1) system ("halt -p");
    nr_prev++;
    prev[nr_prev]=curent;
    filelist[curent].curent=0;
    int p;
    if (n > 0)
    do
    {
      srand (time(NULL));
      p = (int)(random()%n);
    } while (p==curent);
    else p=n;
    if (rnext == false) p = ++curent; 
    if (next==-1) { curent=p; play (filelist[p].name); }
    else  { curent=next; play (filelist[next].name); }
    filelist[curent].curent=1;
    next=-1;
    reread=1;
}

void getvolumes ()
{
  control_message_send (player,XA_MSG_GET_OUTPUT_VOLUME);
}

void setvolumes (int vol,int pcm, int balance)
{
  control_message_send (player,XA_MSG_SET_OUTPUT_VOLUME,balance,pcm,vol);
}

int loadconfig()
{
  int r=1;
  ifstream f("linuxeyes.config");
  if (!f.fail())
  {
     f.getline(playlistfile,sizeof(playlistfile));
     f >>scr >>vol >>pcm >>balance >>rnext;
  }
  else r=0;
  f.close();
  playlistfile[strlen(playlistfile)]='\0';
  return r;
}

int saveconfig()
{
  int r=1;
  ofstream f("linuxeyes.config");
  if (!f.fail())
  {
     f <<playlistfile <<endl;
     f <<scr <<" " <<vol <<" " <<pcm <<" " <<balance <<" " <<rnext;
  }
  else r=0;
  f.close();
  return r;
}

void refreshlist()
{
  for (int i=0;i<=n;i++)
  {
    id3(filelist[i].name);
    strcpy(filelist[i].artist,artist);
    strcpy(filelist[i].song,song);
    strcpy(filelist[i].text,text);
    filelist[i].min=min;
    filelist[i].sec=sec;
    filelist[i].tag=tag;
  }
  reread=1;
}

int loadlist(char *file)
{
    int scr2=4;
    WINDOW *w;
    w=newwin (scr2-1,36,7+((scr-scr2)/2),21);
    wsetcolor (w,13,0);
    mvwprintw (w,2,0,"Please wait...");
    for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
    wsetcolor (w,12,0);
    box (w,ACS_VLINE,ACS_HLINE);
    wrefresh(w);
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
        wsetcolor (w,12,0);
        mvwprintw (w,1,2,"Loading playlist %d%% ",((i+1)*100)/number);
	wrefresh(w);
      }	
      f.close();
    }
    else i=-1;  
    wrefresh(w);
    werase (w);
    return i;
}

void messages()
{
    XA_Message message;
    control_message_get (player,&message);
    setcolor (1,0);
    if (message.code==XA_MSG_NOTIFY_INPUT_TIMECODE) mvprintw (4,72,"[%.2d:%.2d]",message.data.timecode.m,message.data.timecode.s);
    if (message.code==XA_MSG_NOTIFY_PLAYER_STATE) 
      switch (message.data.state)
      {
        case XA_PLAYER_STATE_EOS: playnext();
      }
    if (message.code==XA_MSG_NOTIFY_ERROR) playnext();
    if (message.code==XA_MSG_NOTIFY_INPUT_POSITION)
    {
      int n;
      n = ((message.data.position.offset*20)/message.data.position.range);
      if (n==0) n=1;
      if (n!=n1) 
      {
        setcolor (1,0);
        mvprintw (5,57,"[--------------------]");
        mvprintw (5,57+n,"*");
	n1=n;
      }	
    }
    if (message.code==XA_MSG_NOTIFY_OUTPUT_MASTER_LEVEL) 
    { 
      vol=message.data.volume.master_level; 
      reread=1; 
    } 
    if (message.code==XA_MSG_NOTIFY_OUTPUT_PCM_LEVEL) 
    { 
      pcm=message.data.volume.pcm_level; 
      reread=1; 
    }
    if (message.code==XA_MSG_NOTIFY_OUTPUT_BALANCE) 
    { 
      balance=message.data.volume.balance; 
      reread=1; 
    }
    if (message.code==XA_MSG_NOTIFY_STREAM_DURATION) 
    {
      long duration;
      duration=message.data.duration;
      filelist[curent].min=duration / 60;
      filelist[curent].sec=duration % 60;
      reread=1;
    }
}

void showid3 (char *name)
{
  int scr2=10;
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
  mvwprintw (w,0,1," ID3 Tag ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr2-2,48," q - quit ");
  wrefresh(w);
  XA_DecoderInfo *decoder;            
  XA_InputModule module;
  XA_PropertyList list;
  XA_CodecModule codec;
  decoder_new (&decoder);
  file_input_module_register(&module);
  decoder_input_module_register(decoder, &module);
  mpeg_codec_module_register(&codec);
  decoder_codec_module_register(decoder, &codec);
  decoder_input_new(decoder, name,XA_DECODER_INPUT_AUTOSELECT);
  decoder_input_open(decoder);
  if (properties_get_list(decoder->status->info.properties, &list) == 
      XA_SUCCESS &&
      list.nb_properties > 7) 
      { 
        int nr=list.nb_properties;
	wsetcolor (w,12,0);
	mvwprintw (w,2,2," ARTIST: ");
	mvwprintw (w,3,2,"   SONG: ");
	mvwprintw (w,4,2,"  ALBUM: ");
	mvwprintw (w,5,2,"   YEAR: ");
	mvwprintw (w,6,2,"COMMENT: ");
	mvwprintw (w,7,2,"   FILE: ");
	wsetcolor (w,12,1);
	mvwprintw (w,7,11,"%.46s",name);
	if (list.properties[nr-5].type == XA_PROPERTY_TYPE_STRING) if (nr > 7) if (list.properties[nr-5].value.string != NULL) mvwprintw (w,6,11,"%s",list.properties[nr-5].value.string);
	if (list.properties[nr-4].type == XA_PROPERTY_TYPE_STRING) if (nr > 7) if (list.properties[nr-4].value.string != NULL) mvwprintw (w,5,11,"%s",list.properties[nr-4].value.string);
        if (list.properties[nr-3].type == XA_PROPERTY_TYPE_STRING) if (nr > 7) if (list.properties[nr-3].value.string != NULL) mvwprintw (w,4,11,"%s",list.properties[nr-3].value.string);
	if (list.properties[nr-2].type == XA_PROPERTY_TYPE_STRING) if (nr > 7) if (list.properties[nr-2].value.string != NULL) mvwprintw (w,2,11,"%s",list.properties[nr-2].value.string);
	if (list.properties[nr-1].type == XA_PROPERTY_TYPE_STRING) if (nr > 7) if (list.properties[nr-1].value.string != NULL) mvwprintw (w,3,11,"%s",list.properties[nr-1].value.string);
      }
      else 
      {
        mvwprintw (w,7,2,"   FILE: ");
	wsetcolor (w,12,0);
        wsetcolor (w,12,1);
        mvwprintw (w,2,5,"Could not find id3 tag.");
	mvwprintw (w,7,11,"%.46s",name);
      }
/*	if (decoder->status->info.duration != duration) duration = decoder->status->info.duration; 
	duration=duration / 1000;
	min=duration / 60;
	sec=duration % 60;*/
  decoder_input_close(decoder);	
  decoder_delete (decoder);	
  wrefresh(w);
  noecho();
  timeout (1);
  int v;
  do
  do
  {
    messages();
    v=getch();
  } while (v==ERR);
  while (v!='q');
  v='\0';
  reread=1;
  werase (w);
}

void readstring(WINDOW *w,int j,int i ,unsigned int l,char *text)
{
  strcpy(memstring,"");
  strcat (memstring,text);
  unsigned ln;
  ln=strlen (memstring);
  unsigned int k=0;
  unsigned int p=0;
  int t=0;
  wsetcolor (w,14,1);
/*  timeout (-1);
  echo();
  mvgetstr (j,i,s);
  noecho(); */
  timeout (1);
  do
  {
    if (ln > l) p=ln-l;
    else p=0;
    for (k=0;k<=l;k++) mvwprintw (w,j,i+k," ");
    for (k=0;k<=l;k++) if (ln >= k+p) mvwprintw (w,j,i+k,"%c",memstring[k+p]);
    wrefresh (w);
    do
    {
      t=getch();
      messages();
      mvwprintw (w,j,i+ln,"");
      wrefresh (w);
    } while (t==ERR);
    if ((t!='\n') && (t!=127) && (t!=9) && (t!=27))
    {
      memstring[ln]=t;
      memstring[ln+1]='\0';
      ln++;
    }
    if (t==127)
    {
      if (ln > 0) 
      {
        ln--;
        memstring[ln]='\0';
      }
    }
    if (t==27)
    {
      t=getch();
      if (t == ERR) 
      {
        strcpy (memstring,"");
	t=1000;
      }
      else t='\0';
    }
/*    mvprintw (j,i,"%s",memstring); */
  } while ((t!='\n') && (t!=9) && (t!=1000));
//  mvprintw (2,2,"                                                ");
//  mvprintw (2,2,"%s",memstring);
}

int search()
{
  int sendcmd=-1;
  int scr2=4;
  WINDOW *w1;
  w1=newwin (scr2+1,62,(6+(scr-scr2)/2),9);
  wrefresh (w1);
  WINDOW *w;
  w=newwin (scr2-1,60,7+((scr-scr2)/2),10);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  box (w,ACS_VLINE,ACS_HLINE);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Search ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr2-3,2,"Song");
  wrefresh(w);
  readstring (w,1,7,46,"");
  werase (w);
  werase (w1);
  if (strcmp(memstring,"")!=0)
  {
    int i,nr=-1;
    int t='\0';
    char s1[100],s2[100];
    for (i=0;i<=n;i++)
    {
      uppercase(filelist[i].text);
      strcpy (s1,upcase);
      uppercase(memstring);
      strcpy (s2,upcase);
      if (strstr (s1,s2)!=NULL)
      {
        nr++;
        strcpy (filterlist[nr].text,filelist[i].text);
        filterlist[nr].nr=i;
      }
    }
    if (nr>-1)
    {
      int scr2=scr-4;
      WINDOW *w1;
      w1=newwin (scr2+1,62,(6+(scr-scr2)/2),9);
      wrefresh (w1);
      WINDOW *w;
      w=newwin (scr2-1,60,7+((scr-scr2)/2),10);
      wsetcolor (w,12,0);
      for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
      wsetcolor (w,12,0);
      box (w,ACS_VLINE,ACS_HLINE);
      wsetcolor (w,13,1);
      mvwprintw (w,0,1," Songs List ");
      wsetcolor (w,12,0);
      mvwprintw (w,scr2-2,47," q - quit ");
      wrefresh(w);
      int l,k=0,m=0,col;
      if (nr > scr2-4) l=scr2-4;
      else l=nr;
      do
      {
        for (i=0;i<=l;i++)
	{
	  if (k==i) col=10;
	  else col=8;
	  wsetcolor (w,col,0);
	  mvwprintw (w,i+1,2,"                                                        ");
	  mvwprintw (w,i+1,2,"%s",filterlist[m+i].text);
	}
	wsetcolor (w,8,0);
	for (i=l+1;i<=scr2-4;i++) mvwprintw (w,i+1,2,"                                                        ");
	wrefresh(w);
        noecho();
	timeout (1);
	do
	{
	  t=getch();
	  messages();
	} while (t==ERR);
	if (t==27)
	{
	  t=getch();
	  if (t==91)
	  {
	    t=getch();
	    if (t==65) k--;
	    if (t==66) k++;
	  }
	}
	if (k < 0) if (m > 0) { k++;m--; }
        else k++;
        if ((m+k) > nr) k--;
        if (k > scr-8) { m++;k--; } 
      } while ((t!='\n') && (t!='q') && (t!=' '));
      werase (w);
      werase (w1);
      if (t=='\n') sendcmd=filterlist[m+k].nr;
      if (t==' ') next=filterlist[m+k].nr;
    }
  }
  reread=1;
  return sendcmd;
}

void readurl()
{
  int scr2=4;
  WINDOW *w1;
  w1=newwin (scr2+1,62,(6+(scr-scr2)/2),9);
  wrefresh (w1);
  WINDOW *w;
  w=newwin (scr2-1,60,7+((scr-scr2)/2),10);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  box (w,ACS_VLINE,ACS_HLINE);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Add URL ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr2-3,2,"Song URL");
  wrefresh(w);
  readstring (w,1,11,46,"http://");
  werase (w);
  werase (w1);
}

void savelist(char *file,int t)
{
  if (t==1)
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
    mvwprintw (w,0,1," Save Playlist ");
    wsetcolor (w,12,0);
    mvwprintw (w,scr2-3,2,"Playlist");
    wrefresh(w);
    readstring (w,1,11,46,file);
  } else strcpy (memstring,"linuxeyes.playlist");
    if (strcmp(memstring,"")!=0)
    {
      ofstream f(memstring);
      f <<"eypl=LinuxEyes Playlist" <<endl;
      f <<"{" <<endl;
      for (int i=0;i<=n;i++)
      { 
        if (i<n) f <<filelist[i].name <<"\n" <<filelist[i].text <<"\n" <<filelist[i].min <<" " <<filelist[i].sec <<endl;
        if (i==n) f <<filelist[i].name <<"\n" <<filelist[i].text <<"\n" <<filelist[i].min <<" " <<filelist[i].sec <<endl;
      }  
      f <<"}";
      f.close();
      strcpy (playlistfile,memstring);
    }
}

void fileentry (int nr)
{
  int scr2=4;
  WINDOW *w1;
  w1=newwin (scr2+1,62,(6+(scr-scr2)/2),9);
  wrefresh (w1);
  WINDOW *w;
  w=newwin (scr2-1,60,7+((scr-scr2)/2),10);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  box (w,ACS_VLINE,ACS_HLINE);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Playlist Entry ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr2-3,2,"Filename");
  wrefresh(w);
  readstring (w,1,11,46,filelist[nr].name);
  werase (w);
  werase (w1);
  if (strcmp(memstring,"")!=0) strcpy (filelist[nr].name,memstring);
}

#include "inc/help.cpp"
#include "inc/files.cpp"

void deletefile (int k)
{
  for (int i=k;i<n;i++) filelist[i]=filelist[i+1];
  n--;
  reread=1;
}

void addfile(char *file)
{
  int i=n+1;
  id3(file);
  strcpy (filelist[i].name,file);
  strcpy(filelist[i].artist,artist);
  strcpy(filelist[i].song,song);
  strcpy(filelist[i].text,text);
  filelist[i].min=min;
  filelist[i].sec=sec;
  filelist[i].tag=tag; 
  n++;
}

void adddir (char *dir)
{
  int scr2=4;
  WINDOW *w;
  w=newwin (scr2-1,36,7+((scr-scr2)/2),21);
  wsetcolor (w,13,0);
  mvwprintw (w,2,0,"Please wait...");
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  box (w,ACS_VLINE,ACS_HLINE);
  wrefresh(w);
  struct dirent **namelist;
  int i=scandir (dir,&namelist,0,alphasort);
  int nrfiles=i;
  char *s;
  if (i>0) while (i--) 
  if (rindex(namelist[i]->d_name,'.') != NULL) 
  { 
    s=strdup (rindex(namelist[i]->d_name,'.'));
    if ((strcasecmp(s,".mpg")==0) || (strcasecmp(s,".mp2")==0) || (strcasecmp(s,".mp3")==0))
    {
      n++;
      strcpy(filelist[n].name,dir); 
      strcat(filelist[n].name,namelist[i]->d_name);
      s=strdup (filelist[n].name);
      id3(s);
      strcpy (filelist[n].name,s);
      strcpy(filelist[n].artist,artist);
      strcpy(filelist[n].song,song);
      strcpy(filelist[n].text,text);
      filelist[n].min=min;
      filelist[n].sec=sec;
      filelist[n].tag=tag; 
    }
    wsetcolor (w,12,0);
    mvwprintw (w,1,2,"Loading files %d%% ",((nrfiles-i)*100)/nrfiles);
    wrefresh(w);  
  }    
  reread=1;
  werase (w);
}

void playlistoptions()
{
  int scr2=10;
  int t=0;
  WINDOW *w;
  w=newwin (scr2-1,25,7+((scr-scr2)/2),25);
  wsetcolor (w,13,0);
//  mvwprintw (w,2,1," Playlist Options ");
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  box (w,ACS_VLINE,ACS_HLINE);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Playlist Options ");
  wsetcolor (w,12,0);
  mvwprintw (w,2,4,"n : New Playlist");
  mvwprintw (w,3,4,"l : Load Playlist");
  mvwprintw (w,4,4,"s : Save Playlist");
  mvwprintw (w,8,12," q - quit ");
  wrefresh(w);
  timeout (1);
  do
  {
    do
    {
      messages();
      t=getch();
    } while (t==ERR);
    if (t=='n')
    {
      werase (w);
      wrefresh (w);
      k=-1; m=0; n=-1; l=-1;
      strcpy (playlistfile,"");
      t='q';
    }
    if (t=='l')
    {
      werase (w);
      wrefresh (w);
      showfiles (scr-1,".","Select a playlist to load",0);
      if (mpegnumber > -1)
      {
	strcpy (playlistfile,mpegfile[0]);
        n=loadlist(mpegfile[0]); 
	m=0;
	k=0;
	reread=1;
      }
      t='q';
    }
    if (t=='s')
    {
      werase (w);
      wrefresh (w);
      savelist(playlistfile,1);
      t='q';
    }
  } while (t!='q');
  reread=1;
}

void playlist ()
{
//    int k=0,m=0,l=0;
    int v;
    setcolor (1,0);
    mvprintw (4,1,"Artist: ");
    mvprintw (5,1,"  Song: ");
    setcolor (1,1);
    mvhline (6,0,ACS_HLINE,80);
    mvhline (scr+8,0,ACS_HLINE,80);
    n = loadlist ("linuxeyes.playlist");
    if (autoplay==true) playnext();
    setcolor (1,0);
// test if n > 16
    if (n > scr) l=scr;
    else l=n;
    do
    {
      setcolor (1,1);
      mvhline (6,0,ACS_HLINE,80);
      mvhline (scr+8,0,ACS_HLINE,80);
      mvprintw (scr+7,0,"                                                                                ");        
      mvprintw (scr+9,0,"                                                                                ");        
      mvprintw (scr+10,0,"                                                                                ");        
      if (less > 0) {k=0; less--;m--; reread=1;}
      if (more > 0) {k=scr; more--;m++; reread=1;}
      if (k < 0) { m--;k++; }
      if (k > scr) { m++;k--; }
      if (m < 0) {m=0; k=0;}
      if (((m+scr) > n) && (n > scr)) {k=scr; m=n-k;}
      if (k > n) k=n;
      for (int i=0;i<=l;i++) 
      {
        int color=1;
	int t=1;
	if ((m+i)==curent) color = 6;
	if ((m+i)==next) color = 4;
	if (i==k) color++;
	if (!(fileexists(filelist[m+i].name))) t=0;
	setcolor (color,t);
	mvprintw (7+i,1,"                                                                              ");
        mvprintw (7+i,1,"%d. %.60s",m+i+1,filelist[m+i].text);
	if ((filelist[m+i].min != 0) && (filelist[m+i].sec != 0)) mvprintw (7+i,74,"%.2d:%.2d",filelist[m+i].min,filelist[m+i].sec);
      }
      setcolor (1,0);
      for (int i=l+1;i<=scr;i++) mvprintw (7+i,1,"                                                                              ");
      if (n > scr) l=scr;
      else l=n;
      char s[7];
      strcpy (s,"Normal   ");
      if (rnext==1) strcpy (s,"Shuffle  ");
      if (next>-1) strcpy (s,"Next Song");
      if (nclose!=0) strcpy (s,"Shut Down");
      tunknown=0;
      thour=0;
      tmin=0;
      tsec=0;
      for (int i=0;i<=n;i++)
      {
        tsec=tsec+filelist[i].sec;
	if (tsec > 59) { tmin++; tsec=tsec%60; }
	tmin=tmin+filelist[i].min;
	if (tmin > 59) { thour=thour+(tmin/60); tmin=tmin%60; }
	if ((filelist[i].min==0) && (filelist[i].sec==0)) tunknown=1;
      }
      setcolor (1,0);
      mvprintw (scr+9,1,"%s | Volume[%d] | Pcm[%d] | Balance[%d]",s,vol,pcm,balance-50);
      setcolor (1,1);
      if (tunknown==0) mvprintw (scr+9,71,"%.2d:%.2d:%.2d",thour,tmin,tsec);
      else mvprintw (scr+9,70,"~%.2d:%.2d:%.2d",thour,tmin,tsec);
      refresh();
      if (v=='?') about(scr-1);
      if (v=='h') help(scr-1);
      noecho();
      timeout (1);
      do 
      {
        v=getch();
	messages();
	if (playerror == 1) { playerror=0; playnext(); }
	mvprintw (scr+9,80," ");
      } while ((v==ERR) && (reread==0)); 	
      reread=0;
      if (v=='i') showid3 (filelist[m+k].name);
      if (v=='\n') { nr_prev++; prev[nr_prev]=curent; curent=m+k; play (filelist[m+k].name); }
      if (v==' ') { if (next!=m+k) next=m+k; else next=-1; }
      if (v=='r') { if (next!=curent) next=curent; else next=-1; }
      if (v=='z') playprev();
      if (v=='x') play (filelist[curent].name);
      if (v=='c') mpegpause ();
      if (v=='v') stop ();
      if (v=='b') playnext();
      if (v=='s') rnext=!rnext;
      if (v=='e') fileentry (m+k);
      if (v=='j') 
      {
        int x=search();
	if (x > -1)
	{  
	  nr_prev++; 
	  prev[nr_prev]=curent; 
	  curent=x; 
	  play (filelist[x].name);
	}
      }
      if (v=='d') {deletefile (m+k); if (((m+scr) > n) && (n > scr)) m--;}
      if (v=='S') { sort (0,n);getcurent(); }
      if (v=='`') reset();
      if (v=='R') {k=-1; m=0; n=-1; l=-1;}
      if (v=='[')
      {
        if ((m+k) > 0)
	{
          temp=filelist[m+k-1];
	  filelist [m+k-1]=filelist[m+k];
	  filelist[m+k]=temp;
	  getcurent();
	  k--;
	}
 	reread=1;
      }
      if (v=='\'')
      {
        if ((m+k) < n)
	{
          temp=filelist[m+k];
	  filelist [m+k]=filelist[m+k+1];
	  filelist[m+k+1]=temp;
	  getcurent();
	  k++;
	}
	reread=1;
      }
//      if (v=='l') savelist(playlistfile,1);
      if (v=='n') refreshlist();
      if (v=='p') playlistoptions();
      /*
      {
        showfiles (scr-1,".","Select a playlist to load",0);
	if (mpegnumber > -1)
	{
	  strcpy (playlistfile,mpegfile[0]);
          n=loadlist(mpegfile[0]); 
	  m=0;
	  k=0;
	  reread=1;
	}  
      } */
      if (v=='a')
      {
        showfiles (scr-1,".","Select a file to add",0);
	if (strcmp(mpegfile[0],"")!=0)
	  if (mpegnumber > -1) for (int i=0;i<=mpegnumber;i++) addfile(mpegfile[i]);
	reread=1;
      }
      if (v=='u') readurl();
      /*{
        readstring (NULL,2,2,20,"URL");
	if (strcmp(memstring,"")!=0)
	{
          addfile (memstring); 
	} 
      } */
 
      if (v=='D') 
      { 
        showfiles (scr-1,".","Select a directory to add",1);
	if (mpegnumber > -1)
	{
	  if (s[strlen(mpegfile[0])]!='/') strcat (mpegfile[0],"/");
          adddir (mpegfile[0]); 
	}  
	reread=1;
      }
      if (v==',') if (balance > 0) {balance--; setvolumes (vol,pcm,balance); }
      if (v=='.') if (balance < 100) {balance++; setvolumes (vol,pcm,balance);}
      if (v==27) 
      {
        v=getch();
	if (v==91) 
	{
	  v=getch();
	  if (v==65) k--; 
	  if (v==66) k++; 
	  if (v==67) position(1);
          if (v==68) position(-1);
/*	  if (v==53) {m=m-scr; k=0;}
	  if (v==54) {m=m+scr; k=scr;}*/
	  if (v==53) less=scr;
	  if (v==54) more=scr;
	  if (v==52) if (pcm > 0) {pcm--; setvolumes (vol,pcm,balance); }
          if (v==49) if (pcm < 100) {pcm++; setvolumes (vol,pcm,balance); }
	  if (v==51) if (vol > 0) {vol--; setvolumes (vol,pcm,balance);}
	  if (v==50) if (vol < 100) {vol++; setvolumes (vol,pcm,balance);}
	}
      }
      if (v==45) {if (scr > 0) scr--; reread=1;}
      if (v==43) {scr++; reread=1;}
      if (v=='0') if (nclose!=0) nclose=0; else nclose=1;
    }  
    while (v!='q');
    chdir (path);
    savelist (playlistfile,0);
}

int main(int argc,char *argv[])
{
    getcwd (path,sizeof(path));
    strcpy (playlistfile,"linuxeyes.playlist");
    printf ("Amysoft Linux Eyes v0.2 (C) Amysoft 2001\n\r");
    printf ("Loading configuration... ");
    if (loadconfig ()) printf ("ok\n\r");
    else printf ("failed, using default configuration\n\r");
    printf ("Starting LinuxEyes\n\r");
    if (argc > 1)
    for (int i=1;i<argc;i++)
    {
      if (strcmp(argv[i],"-p") == 0) autoplay=true;
      if (strcmp(argv[i],"--nocolors")==0) nocolor=1;
    } 
    initscr();
    keypad (NULL,TRUE);
    colors();
    setcolor (3,1);
    mvprintw (0,0," Wellcome to LinuxEyes Player v0.4 [press h for help]                           ");
    player_new (&player,NULL);
    resettime();
    playlist();
    clear();
    refresh();
    endwin();
    player_delete (player);
    if (saveconfig ()) printf ("Configuration saved\n\r");
    else printf ("Configuration could bot be saved\n\r");
    printf ("Thank you for using LinuxEyes Player\n\rPlease report bugs to alex_amysoft@hotmail.com\n\r");
    control_message_send (player,XA_MSG_COMMAND_EXIT);
    return 0;
}
