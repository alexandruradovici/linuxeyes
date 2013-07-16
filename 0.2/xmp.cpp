char artist[100],song[100],text[100];
static unsigned long duration=0;
int scr=15;
int min,sec;
int tag;
int vol=90,pcm=90,balance=50;
int n;
int next=-1,curent=-1;
int reread=1;
bool paused=false;
int n1=0;
int v=50;
bool rnext=true;
int autoplay=false;
int songs_played=0;
int songs[5000];
char playlistfile[1000];
char memstring[1000];
int prev[1000];
int nr_prev=-1;
int playerror=0;
int nocolor=0;
char mpegfile[1000][1000];
int mpegnumber=-1;
char path[1000];

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

void readstring(char *text)
{
  setcolor (1,0);
  mvprintw (scr+9,1,"%s:                                                                             ",text);
  char s[500];
  timeout (-1);
  echo();
  mvgetstr (scr+9,strlen(text)+3,s);
  noecho();
  timeout (1);
  strcpy (memstring,s);
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
    mvprintw (0,0,"LinuxEyes [%.66s]",filelist[curent].name);
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
    nr_prev++;
    prev[nr_prev]=curent;
    filelist[curent].curent=0;
    int p;
    do
    {
      srand (time(NULL));
      p = (int)(random()%n);
    } while (p==curent);  
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
     f >>scr >>vol >>pcm >>balance;
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
     f <<scr <<" " <<vol <<" " <<pcm <<" " <<balance;
  }
  else r=0;
  f.close();
  return r;
}

int loadlist(char *file)
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
	filelist[i].curent=0;
        if (strcmp(s,"")==0) i--;
        setcolor (1,0);
        mvprintw (scr+9,1,"Loading playlist %d%%                                                        ",((i+1)*100)/number);
        refresh();
      }	
      f.close();
    }
    else return -1;  
    return i;
}

void savelist(char *file)
{
    ofstream f(file);
    for (int i=0;i<=n;i++)
    { 
      if (i<n) f <<filelist[i].name <<endl;
      if (i==n) f <<filelist[i].name;
    }  
    f.close();
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
  struct dirent **namelist;
  int i=scandir (dir,&namelist,0,alphasort);
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
  }    
  reread=1;
}

void protect(char *password)
{
   char text[100];
   int v;
   int i=0;
   strcpy (text,"");
   mvprintw (scr+9,1,"Password:                                                                ");
   mvprintw (scr+9,1,"Password: %s",text);
   do 
   {
     if (v==94)
     {
       v=getch();
       if ((v==63) && (i > 0))
       {
         i--;
	 text[i+1]='\0';
       }
     }
     if (v=='\n') 
     {
       strcpy (text,"");
       i=0; 
       mvprintw (scr+9,1,"Password:                                                                ");
       mvprintw (scr+9,1,"Password: %s",text);
     }
     v=getch();
     if ((v!=ERR) && (v!='\n'))
     {
       text[i]=v;
       text[i+1]='\0';
       i++;
       mvprintw (scr+9,1,"Password:                                                                ");
       mvprintw (scr+9,1,"Password: %s",text);
     }
     messages();
     if (playerror == 1) { playerror=0; playnext(); }
     mvprintw (scr+9,78," ");
     refresh ();
   } while ((v!='\n') || (strcmp (text,password)!=0)); 	  
   reread=1;
}

void playlist ()
{
    int k=0,m=0,l=0;
    int v;
    setcolor (1,0);
    mvprintw (4,1,"Artist: ");
    mvprintw (5,1,"  Song: ");
    setcolor (1,1);
    mvhline (6,0,ACS_HLINE,80);
    mvhline (scr+8,0,ACS_HLINE,80);
    n = loadlist (playlistfile);
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
      if (k < 0) { m--;k++; }
      if (k > scr) { m++;k--; }
      if (m < 0) {m=0; k=0;}
      if (((m+scr) > n) && (n > scr)) {k=scr; m=n-k;}
      if (k > n) k=n;
      for (int i=0;i<=l;i++) 
      {
        int color=1;
	if ((m+i)==curent) color = 6;
	if ((m+i)==next) color = 4;
	if (i==k) color++;
	setcolor (color,1);
	mvprintw (7+i,1,"                                                                              ");
        mvprintw (7+i,1,"%d. %.60s",m+i+1,filelist[m+i].text);
	if ((filelist[m+i].min != 0) && (filelist[m+i].sec != 0)) mvprintw (7+i,74,"%.2d:%.2d",filelist[m+i].min,filelist[m+i].sec);
      }
      setcolor (1,0);
      for (int i=l+1;i<=scr;i++) mvprintw (7+i,1,"                                                                              ");
      if (n > scr) l=scr;
      else l=n;
      char s[7];
      if (rnext==1) strcpy (s,"Shuffle");
      else strcpy (s,"       ");
      setcolor (1,0);
      mvprintw (scr+9,1,"%s | Volume[%d] | Pcm[%d] | Balance[%d] | Playlist [%s]",s,vol,pcm,balance-50,rindex(playlistfile,'/'));
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
	mvprintw (scr+9,78," ");
      } while ((v==ERR) && (reread==0)); 	
      reread=0;
      if (v=='\n') { nr_prev++; prev[nr_prev]=curent; curent=m+k; play (filelist[m+k].name); }
      if (v==' ') { if (next!=m+k) next=m+k; else next=-1; }
      if (v=='r') { if (next!=curent) next=curent; else next=-1; }
      if (v=='z') playprev();
      if (v=='x') play (filelist[curent].name);
      if (v=='c') mpegpause ();
      if (v=='v') stop ();
      if (v=='b') playnext();
      if (v=='s') rnext=!rnext;
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
      if (v=='l')
      {
        readstring ("Filename");
	if (strcmp(memstring,"")!=0)
	{
          savelist (memstring); 
	}  
      } 
      if (v=='p')
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
      } 
      if (v=='a')
      {
        showfiles (scr-1,".","Select a file to add",0);
	if (strcmp(mpegfile[0],"")!=0)
	  if (mpegnumber > -1) for (int i=0;i<=mpegnumber;i++) addfile(mpegfile[i]);
	reread=1;
      }
      if (v=='u')
      {
        readstring ("URL");
	if (strcmp(memstring,"")!=0)
	{
          addfile (memstring); 
	}  
      } 
 
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
      if (v=='!') protect ("parola");
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
	  if (v==53) {m=m-scr; k=0;}
	  if (v==54) {m=m+scr; k=scr;}
	  if (v==52) if (pcm > 0) {pcm--; setvolumes (vol,pcm,balance); }
          if (v==49) if (pcm < 100) {pcm++; setvolumes (vol,pcm,balance); }
	  if (v==51) if (vol > 0) {vol--; setvolumes (vol,pcm,balance);}
	  if (v==50) if (vol < 100) {vol++; setvolumes (vol,pcm,balance);}
	}
      }
      if (v==45) {if (scr > 0) scr--; reread=1;}
      if (v==43) {scr++; reread=1;}
    }  
    while (v!='q');
    chdir (path);
    savelist (playlistfile);
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
    mvprintw (0,0," Wellcome to LinuxEyes Player v0.2 [press h for help]                           ");
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
