const char endl='\n'; //gcc3 fstream bug fix
//char artist[100],song[100]
char text[100]; //id3 main
static unsigned long duration=0; //duration
int scr=0; //the screen size, normal terminal 16
int min,sec; //duration main
//int tag; //if file has id3 tag
int vol=90,pcm=90,balance=50; //volumes
int n,n2; //nr of files in playlist, n2 for search
int reread=1; //reread playlist befor pressing a key
bool paused=false; //paused ?
int n1=0; //?
int v=50; //?
bool rnext=true; //random next
int autoplay=false; //-p parameter
char playlistfile[1000]; //playlist filename with path
char memstring[1000]; //memory string, for readstring
char prev[1000][1000]; //previous songs list
int nr_prev=-1; //nr of previous songs
int playerror=0; //error on play
int nocolor=0; //--nocolors parameter
char mpegfile[1000][1000]; //files
int mpegnumber=-1; //nr of files
char path[1000]; //player path
int nclose=0; //"0" key function
int more=0; //scrolling down
char upcase[100]; //uppercase result
char eypl[100]; //playlist name
int tunknown,thour,tmin,tsec; //total time
int m=0,k=0,l=0;  //playlist variables
unsigned int nrcols=78,old_nrcols=78; //number of colums of screen
char consmsg[100][1000]; //console messages
int nr_consmsg=0; //number of console messages
char strtmp[100]; //temp string
char fs_command[9][100]; //fs commands
int scr_autodetect=0; //audetect screen
int init_text; //init text, ... [press h for help]
char timeformat[10]; // the clock display format
int nr_timeformat=5; //number of clock display formats
int current_timeformat=1; //the current clock format
int timeformat_size; //the size of the clock display
int password=0; //password mode on/off
char passwordstr[100]; //password string
int curent_playlist_nr=-1; //nr of current position in playlist
int dx=4; //x value for control panel display, defaul 4, depends on "Next Song"
int status_bar=0; //status bar display type, 0 normal, 1 next song, 2 filter, default 0
int quit=0; //quit varable, used for "Shut Down" mode, 0 don't quit, 1 quit
long songs=0; //nr of played songs
long secs=0; //nr of seconds played
long n_songs=0; //nr of played songs during the last session
long n_secs=0; //nr of seconds played during the last session
int nolines=0; //remap acs characters to skip ncurses terminal bug
signed char imported_eq_preset[9]; //equalizer imported data
char exported_eq_preset[9]; //equalizer exported data
int filternr=-1; //nr of files in filter
int save_pos=0; //used for save playlist position
int persistent_filter=0; //persistent filter=1, nonpersistent=0, delault=0
int sleepmode=0; //sleep mode
char sleeptime[10]; // time to shut down for sleep mode
char list_result=0; // result of list_with_key[18~
int new_start=0; // new configuration at startup, default

struct read_text
{
  char text[1000];
};

typedef char list_type[100][1000]; //presets list

const char genres[][30] = {
    "Blues", "Classic Rock", "Country", "Dance", "Disco", "Funk", "Grunge",
    "Hip-Hop", "Jazz", "Metal", "New Age", "Oldies", "Other", "Pop", "R&B",
    "Rap", "Reggae", "Rock", "Techno", "Industrial", "Alternative", "Ska",
    "Death Metal", "Pranks", "Soundtrack", "Euro-Techno", "Ambient",
    "Trip-Hop", "Vocal", "Jazz+Funk", "Fusion", "Trance", "Classical",
    "Instrumental", "Acid", "House", "Game", "Sound Clip", "Gospel",
    "Noise", "AlternRock", "Bass", "Soul", "Punk", "Space", "Meditative",
    "Instrumental Pop", "Instrumental Rock", "Ethnic", "Gothic",
    "Darkwave", "Techno-Industrial", "Electronic", "Pop-Folk",
    "Eurodance", "Dream", "Southern Rock", "Comedy", "Cult", "Gangsta",
    "Top 40", "Christian Rap", "Pop/Funk", "Jungle", "Native American",
    "Cabaret", "New Wave", "Psychadelic", "Rave", "Showtunes", "Trailer",
    "Lo-Fi", "Tribal", "Acid Punk", "Acid Jazz", "Polka", "Retro",
    "Musical", "Rock & Roll", "Hard Rock", "Folk", "Folk-Rock",
    "National Folk", "Swing", "Fast Fusion", "Bebob", "Latin", "Revival",
    "Celtic", "Bluegrass", "Avantgarde", "Gothic Rock", "Progressive Rock",
    "Psychedelic Rock", "Symphonic Rock", "Slow Rock", "Big Band",
    "Chorus", "Easy Listening", "Acoustic", "Humour", "Speech", "Chanson",
    "Opera", "Chamber Music", "Sonata", "Symphony", "Booty Bass", "Primus",
    "Porn Groove", "Satire", "Slow Jam", "Club", "Tango", "Samba",
    "Folklore", "Ballad", "Power Ballad", "Rhythmic Soul", "Freestyle",
    "Duet", "Punk Rock", "Drum Solo", "Acapella", "Euro-House", "Dance Hall","Unknown"
};

// id3 tag structure

struct mpeg_id3 {
	char song[31];
	char artist[31];
	char album [31];
	char year[5];
	char comment[31];
	char track;
	signed char genre;
} my_id3;

// function forward
void savelist(char *file,int t);
void add_console_message(char *s);
int saveconfig();

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
#include <sys/stat.h>

int readstring_with_key(WINDOW *w,int j,int i ,unsigned int l, unsigned int maxl, read_text *text, char pass, char *chars, int active);
int list_with_key(WINDOW *w,int j,int i, unsigned int l, int min, int max, char res, int active);
void show_msg (char *message);

// ---------------
/*#ifdef HAVE_SLANG
void init_curses ()
{
    SLtt_get_terminfo ();
#ifndef HAS_ACS_AS_PCCHARS
    if (force_ugly_line_drawing)
	SLtt_Has_Alt_Charset = 0;
#endif
    SLsmg_init_smg ();
    do_enter_ca_mode ();
    init_colors ();
    keypad (stdscr, TRUE);
    nodelay (stdscr, FALSE);
}*/

static const struct {
    int acscode;
    int character;
} acs_approx [] = {
    { 'q',  '-' }, /* ACS_HLINE */
    { 'x',  '|' }, /* ACS_VLINE */
    { 'l',  '+' }, /* ACS_ULCORNER */
    { 'k',  '+' }, /* ACS_URCORNER */
    { 'm',  '+' }, /* ACS_LLCORNER */
    { 'j',  '+' }, /* ACS_LRCORNER */
    { 'a',  '#' }, /* ACS_CKBOARD */
    { 'u',  '+' }, /* ACS_RTEE */
    { 't',  '+' }, /* ACS_LTEE */
    { 'w',  '+' }, /* ACS_TTEE */
    { 'v',  '+' }, /* ACS_BTEE */
    { 'n',  '+' }, /* ACS_PLUS */
    { '-',  '^' }, /* ACS_UARROW */
    { '.',  'v' }, /* ACS_DARROW */
    { ',',  '<' }, /* ACS_LARROW */
    { '+',  '>' }, /* ACS_RARROW */
    { 0, 0 } };

void fakelines ()
{
    for (int i = 0; acs_approx[i].acscode != 0; i++) 
    {
      acs_map[acs_approx[i].acscode] = acs_approx[i].character;
    }
}
// ---------------

time_t currenttime; //current time

struct
{
   char name[1000];
   char artist[30];
   char song[30];
   char text[80];
   int min;
   int sec;
   int tag;    
}filelist[10000],temp,curent,next; //filelist, temp list, current song and next song info

struct
{
  char text[200];
  int nr;
}filterlist[10000]; 

char filesfilter[10000][1000];

// Backspace thing

typedef struct nextlist_type
{
  char name[1000];
  nextlist_type *next;
};

typedef nextlist_type *pnextlist;

// ----------------------

struct
{
  signed char left;
  signed char right;
} eq;

XA_Control *player;
XA_EqualizerInfo equalizer;

int fileexists (char *file)
{
   int e; 
   e=access (file,R_OK);
   if (e==0) 
   {
     struct stat BUF;
     stat (file,&BUF);	
     if (S_ISDIR(BUF.st_mode) != 0) e=0;
     else e=1;
   }
   else e=0;
/*   ifstream test (file, ios::binary);
   if (test == NULL) e=0;
   else e=1; 
   test.close(); */
   return e;
}

void rtrim (char *s, unsigned int max)
{
  if (s!=NULL)
  {
	 if (strlen (s)<max) max=strlen (s);
	 int i=max+1;
	 int found=0;
	 do
	 {
		 i--;
		 if ((s[i]==0) || (s[i]==32))
		 {
			 max--;
		 } else found=1;
	 } while ((i!=0) && (!found));
	 s[max+1]='\0';
   } else s[0]='\0';
}

void split_id3 (mpeg_id3 *id3_tag, char *tag_str)
{
	int i=0;
	for (i=3;i<=32;i++)
	{
		id3_tag->song[i-3]=tag_str[i];
	}
	for (i=33;i<=62;i++)
	{
		id3_tag->artist[i-33]=tag_str[i];
	}
	for (i=63;i<=92;i++)
	{
		id3_tag->album[i-63]=tag_str[i];
	}
	for (i=93;i<=96;i++)
	{
		id3_tag->year[i-93]=tag_str[i];
	}
	for (i=97;i<=126;i++)
	{
		id3_tag->comment[i-97]=tag_str[i];
	}
	/*for (i=127;i<=127;i++)
	{
		id3_tag->genre=tag_str[i];
	}*/
	if (id3_tag->genre < 0) id3_tag->genre=126;
	if (id3_tag->genre > 125) id3_tag->genre=126;
	//if (id3_tag->comment[28]==0) 
	id3_tag->track=id3_tag->comment[29];
//	else id3_tag->track=0;
	rtrim (id3_tag->song,30);
	rtrim (id3_tag->artist,30);
	rtrim (id3_tag->album,30);
	rtrim (id3_tag->year,4);
	rtrim (id3_tag->comment,30);
}

void write_id3 (mpeg_id3 id3_tag, char *file)
{
  char id3[128],s[3];
  int e=0;
  strcpy (id3,"TAG");
  int i=0;
	for (i=3;i<=32;i++)
	{
		id3[i]=id3_tag.song[i-3];
	}
	for (i=33;i<=62;i++)
	{
		id3[i]=id3_tag.artist[i-33];
	}
	for (i=63;i<=92;i++)
	{
		id3[i]=id3_tag.album[i-63];
	}
	for (i=93;i<=96;i++)
	{
		id3[i]=id3_tag.year[i-93];
	}
	for (i=97;i<=126;i++)
	{
		id3[i]=id3_tag.comment[i-97];
	}
  id3[126]=id3_tag.track;
  id3[127]=id3_tag.genre;
  FILE *f;
  f=fopen (file,"r+");  
  if (f!=NULL)
  {
    fseek (f,-128,SEEK_END);
    if (fread (&s,3,1,f)==1)
    {
      if (memcmp (s,"TAG",3)==0)
      {
        fseek (f,-128,SEEK_END);
	if (fwrite (id3,128,1,f)==1) e=1;
      }
      else
      {
        fseek (f,1,SEEK_END);
	if (fwrite (id3,128,1,f)==1) e=1;
      }
    }
    if (e==1) 
    fclose (f);
  }
  if (e!=1) show_msg ("Could not write ID3 Tag");
}

int id3 (char *name, mpeg_id3 *my_id3)
{
    XA_DecoderInfo *decoder;            
    XA_InputModule module;
//    XA_PropertyList list;
    XA_CodecModule codec;
    decoder_new (&decoder);
    file_input_module_register(&module);
    decoder_input_module_register(decoder, &module);
    mpeg_codec_module_register(&codec);
    decoder_codec_module_register(decoder, &codec);
    decoder_input_new(decoder, name,XA_DECODER_INPUT_AUTOSELECT);
    decoder_input_open(decoder);
/*    if (properties_get_list(decoder->status->info.properties, &list) == 
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
	}*/
	if (decoder->status->info.duration != duration) duration = decoder->status->info.duration; 
	duration=duration / 1000;
	min=duration / 60;
	sec=duration % 60;
    decoder_input_close(decoder);	
    decoder_delete (decoder);	
    strcpy (text,"");
    FILE *f;
    int tag=0;
	char tag_str[128];
	f=fopen (name,"r");
	if (f!=NULL)
	{
		fseek (f,-128,SEEK_END);
		if (fread (&tag_str,128,1,f)==1) tag=1;
		fseek (f,-1,SEEK_END);
		int t;
		fread (&t,1,1,f);
		my_id3->genre=t;
		fclose (f);
	}
    if (tag)
    {
      if (memcmp (tag_str,"TAG",3)==0)
      {
        split_id3 (my_id3,tag_str);
	if (strcmp(my_id3->artist,"")==0) strcpy (my_id3->artist,"Unknown Artist");
        if (strcmp(my_id3->song,"")==0) strcpy (my_id3->song,"Unknown Song");
        if (!fileexists(name))
        {
          strcpy (my_id3->artist,"Unknown");
          strcpy (my_id3->song,"Unknown");
        }
	strcpy (text,my_id3->artist);
        strcat (text," - ");
        strcat (text,my_id3->song);
      }
      else tag=0;
    }
    if (tag==0)
    {
      strcpy (my_id3->artist,"Unknown Artist");
      strcpy (my_id3->song,"Unknown Song");
      strcpy (my_id3->album,"");
      strcpy (my_id3->year,"");
      strcpy (my_id3->comment,"");
      my_id3->genre=126;
    }
    if (((strcmp(my_id3->artist,"Unknown")==0) && (strcmp(my_id3->song,"Unknown")==0) || (strcmp(my_id3->artist,"Unknown Artist")==0) && (strcmp(my_id3->song,"Unknown Song")==0)) && (name!=NULL))
    {
      tag=0;
      unsigned int pos=0,ext=0,i;
      char *s;
      char *ridx;
      s=strdup(name);
      if (s[0]=='.') ext=0;
      else 
      {
        ridx=rindex (s,'.');
	if (ridx!=NULL) ext=strlen(ridx);else ext=0;
      }
      ridx=rindex (s,'/');
      if (ridx!=NULL) pos=strlen(name)-strlen(ridx)+1; else pos=strlen (name)+1;
      for (i=pos;i<=strlen(name)-ext;i++) s[i-pos]=s[i];
      s[i-pos-1]='\0';
      // fprintf (stderr,"%s %d %d\n\r",name,pos,ext);
      //getch(); 
      strcpy(text,s);
//      strcpy(text,(char*)(rindex(name,'/')+1));
    }
    return tag;
}

void sort(int l,int r)
{
  int i=l;
  int j=r;
  char y[200];
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

void sort_filter(int l,int r)
{
  int i=l;
  int j=r;
  char y[1000];
  char temp[1000];
  strcpy (y,"");
  strcpy (y,filesfilter[(l+r) / 2]);
  do
  {
    while (strcmp(filesfilter[i],y) < 0) i++;
    while (strcmp(filesfilter[j],y) > 0) j--;
    if (i <= j)
    {
      strcpy (temp,filesfilter[i]);
      strcpy (filesfilter[i],filesfilter[j]);
      strcpy (filesfilter[j],temp);
      i++;
      j--;
    }
  }
  while (i <= j);
  if (l < j) sort_filter (l,j);
  if (i < r) sort_filter (i,r);
}

int infilter (char *name)
{
    int l=0, r=filternr;
    int y;
    int res=0;
    char str[1000];
    strcpy (str,(char*)name);
    if (filternr > -1)
    {
      do
      {
        y=strcmp (str,filesfilter[(l+r)/2]);
        if (y==0) res=1;
        if (y<0) r=(l+r)/2-1;
        if (y>0) l=(l+r)/2+1;
      } while ((l<=r) && (res==0));
    } else res=0;
  return res;
}

void delete_from_filter (char *name)
{
  int l=0, r=filternr;
    int y;
    int res=0;
    char str[1000];
    strcpy (str,(char*)name);
    if (filternr > -1)
    {
      do
      {
        y=strcmp (str,filesfilter[(l+r)/2]);
        if (y==0) res=1;
        if (y<0) r=(l+r)/2-1;
        if (y>0) l=(l+r)/2+1;
      } while ((l<=r) && (res==0));
    } else res=0;
    if (res==1)
    {
      int pos=(l+r)/2;
      for (int i=pos+1;i<=filternr;i++) strcpy (filesfilter[i-1],filesfilter[i]);
      filternr--;
      sort_filter (0,filternr);
    }
}

void add_to_filter (char *name)
{
  if (name!=NULL)
  if (!infilter(name))
  {
    filternr++;
    strcpy (filesfilter[filternr],(char*)name);
    sort_filter (0,filternr);
  } else delete_from_filter (name);
//  for (int i=0;i<=filternr;i++) fprintf (stderr,"%s\n\r",filesfilter[i]);
}

void uppercase (char s[100])
{
  strcpy (upcase,s);
  for (unsigned int i=0;i<=strlen(s);i++) upcase[i]=toupper (s[i]);
}

void le_border (WINDOW *w, int x, int y)
{
//  ofstream f;
//  f.open ("fis");
//  f <<ACS_HLINE <<'\n';
//  f.close();
  mvwhline (w,0,0,ACS_HLINE,x);
  mvwhline (w,y-1,0,ACS_HLINE,x);
  mvwvline (w,0,0,ACS_VLINE,y);
  mvwvline (w,0,x-1,ACS_VLINE,y);
  mvwaddch (w,0,0,ACS_ULCORNER);
  mvwaddch (w,0,x-1,ACS_URCORNER);
  mvwaddch (w,y-1,0,ACS_LLCORNER);
  mvwaddch (w,y-1,x-1,ACS_LRCORNER);
}

long getcurent()
{
  curent_playlist_nr=-1;
  for (int i=0;i<=n;i++) if (strcmp (filelist[i].name,curent.name)==0) curent_playlist_nr=i;
  return curent_playlist_nr;
}

void resettime()
{
    // unsigned int maxl;
    setcolor (1,0);
    for (unsigned int j=0;j<=nrcols+1;j++) mvprintw (0,j,"  ");
    setcolor (3,1);
    for (unsigned int j=0;j<=nrcols+1;j++) mvprintw (0,j," ");
    if (init_text == 1) mvprintw (0,0,"Welcome to LinuxEyes MP3 Player v0.8 [press h for help]");
    else 
    {
     /* mvprintw (0,0,"LinuxEyes [");
      maxl=strlen (filelist[curent].name);
      if (maxl > nrcols) maxl=nrcols;
      for (unsigned int j=0;j<=maxl;j++) mvprintw (0,11+j,"%c",filelist[curent].name[j]);
      mvprintw (0,maxl+11,"]");*/
    }
    setcolor (1,0);
    mvprintw (dx,nrcols-7," [00:00] ");
    mvprintw (dx+1,nrcols-22," [--------------------] ");
    n1=-100;
    old_nrcols=nrcols;
}

void reset()
{
    clear();
    setcolor (3,1);
    for (unsigned int j=0;j<=nrcols+1;j++) mvprintw (0,j," ");
    /* unsigned int maxl;
    mvprintw (0,0,"LinuxEyes [");
    maxl=strlen (filelist[curent].name);
    if (maxl > nrcols) maxl=nrcols;
    for (unsigned int j=0;j<=maxl;j++) mvprintw (0,11+j,"%c",filelist[curent].name[j]);
    mvprintw (0,maxl+11,"]");*/
//    mvprintw (0,0,"LinuxEyes [%.66s]",filelist[curent].name);
    setcolor (1,0);
    mvprintw (dx,9,"                                                    ");
    mvprintw (dx+1,9,"                                                    ");
    mvprintw (dx,1,"Artist: ");  
    mvprintw (dx+1,3,"Song: ");  
    if (curent.tag==0) 
    {
      mvprintw (4,1,"        ");
      mvprintw (5,9,"%s",curent.text);
    } 
    else
    {
      mvprintw (dx,1,"Artist: ");  
      mvprintw (dx,9,"%.30s",curent.artist);
      mvprintw (dx+1,3,"Song: ");  
      mvprintw (dx+1,9,"%.30s",curent.song);
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

void position_refresh (int p)
{
  filelist[p].tag=id3 (filelist[p].name,&my_id3);
  strcpy(filelist[p].artist,my_id3.artist);
  strcpy(filelist[p].song,my_id3.song);
  strcpy(filelist[p].text,text);
  filelist[p].min=min;
  filelist[p].sec=sec;
}

void play (char *name)
{
    init_text=0;
//    filelist[prev[nr_prev]].curent=0;
    if (fileexists(name))
    {
      curent.tag=id3 (name,&my_id3);
      strcpy(curent.artist,my_id3.artist);
      strcpy(curent.song,my_id3.song);
      strcpy(curent.text,text);
      curent.min=min;
      curent.sec=sec;
      control_message_send(player,XA_MSG_COMMAND_INPUT_OPEN,name);
      control_message_send (player,XA_MSG_SET_OUTPUT_VOLUME,balance,pcm,vol);
      control_message_send(player,XA_MSG_COMMAND_PLAY);
      setcolor (3,1);
      mvprintw (0,0,"                                                                                ",name);
      mvprintw (0,0,"LinuxEyes [%.66s]",name);
      setcolor (1,0);
      mvprintw (4,9,"                                                    ");
      mvprintw (5,9,"                                                    ");
      if (curent.tag==0) 
      {
        mvprintw (4,1,"        ");
        mvprintw (5,9,"%s",curent.text);
      } 
      else
      {
        mvprintw (dx,1,"Artist: ");  
        mvprintw (dx,9,"%.30s",curent.artist);
        mvprintw (dx+1,9,"%.30s",curent.song);
      }
      resettime();
      songs++;
      n_songs++;
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
  //mvprintw (2,1,"%d",nr_prev);
  if (nr_prev > 0)
  {
    strcpy (curent.name,prev[nr_prev]);
    nr_prev--;
    play (curent.name);
  }
}

void playnext()
{
    if (nclose==1) quit=1;
    nr_prev++;
    strcpy (prev[nr_prev],curent.name);
    getcurent();
    int p;
    if (n > 0)
    do
    {
      srand (time(NULL));
      if (filternr>-1) p = (int)(random()%(filternr+1));
      else p = (int)(random()%n);
    } while (((p==curent_playlist_nr) && (filternr<0)));
    else p=n;
    if (rnext == false) if (filternr<0) p = ++curent_playlist_nr; 
                        else if (!persistent_filter) p=0;
    if (strcmp (next.name,"")==0) if (filternr<0) { strcpy (curent.name,filelist[p].name); play (curent.name); }
                                  else { strcpy (curent.name,filesfilter[p]); if (!persistent_filter) delete_from_filter (curent.name); play (curent.name); }
    else  { strcpy (curent.name,next.name); play (next.name); }
    strcpy (next.name,"");
    strcpy (next.text,"");
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
  strcpy (strtmp,getenv("HOME"));
  strcat (strtmp,"/.linuxeyes.config");
  ifstream f(strtmp);
  if (!f.fail())
  {
     f.getline(playlistfile,sizeof(playlistfile));
     f >>scr >>nrcols >>vol >>pcm >>balance >>rnext;
     f >>eq.left >>eq.right;
     for (int i=0;i<=31;i++) 
     {
       f >>equalizer.left[i];
       equalizer.right[i]=equalizer.left[i];
     }
     f >>current_timeformat >>status_bar >>songs >>secs;
     f >>persistent_filter >>save_pos;
     if (save_pos!=1) save_pos=0;
     f.getline (next.name,sizeof(next.name));
     add_console_message (next.name);
     if (!save_pos) strcpy (next.name,"");
  }
  else r=0;
  f.close();
  playlistfile[strlen(playlistfile)]='\0';
  return r;
}

int saveconfig()
{
  int r=1;
  strcpy (strtmp,getenv("HOME"));
  strcat (strtmp,"/.linuxeyes.config");
  ofstream f(strtmp);
  if (!f.fail())
  {
     f <<playlistfile <<endl;
     f <<scr <<" " <<nrcols <<" " <<vol <<" " <<pcm <<" " <<balance <<" " <<rnext;
     f <<eq.left <<" " <<eq.right;
     for (int i=0;i<=31;i++) 
     {
       f <<equalizer.left[i] <<" ";
     }
     f <<endl;
     f <<current_timeformat <<" " <<status_bar <<" " <<songs <<" " <<secs <<endl;
     f <<persistent_filter <<" " <<save_pos;
     if (save_pos) f <<curent.name <<endl;
     else f <<endl;
  }
  else r=0;
  f.close();
  return r;
}

void refreshlist()
{
  for (int i=0;i<=n;i++)
  {
    filelist[i].tag=id3(filelist[i].name,&my_id3);
    strcpy(filelist[i].artist,my_id3.artist);
    strcpy(filelist[i].song,my_id3.song);
    strcpy(filelist[i].text,text);
    filelist[i].min=min;
    filelist[i].sec=sec;
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
    le_border (w,36,scr2-1);
    wrefresh(w);
//    char s[1000];
//    int number=0;
    /*ifstream f(file);
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
//        id3(s);
        strcpy (filelist[i].name,s);
        strcpy(filelist[i].artist,artist);
        strcpy(filelist[i].song,song);
        strcpy(filelist[i].text,text);
        filelist[i].min=min;
        filelist[i].sec=sec;
        filelist[i].tag=tag; 
	filelist[i].curent=0; 
        if (strcmp(s,"}")==0) i--;
      }	
      f.close();
    }
    else i=-1; */
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
        fread (&filelist[i],sizeof(filelist[i]),1,f);
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

void messages()
{
    // -------- Time -------
    time (&currenttime);
    tm *mytime;
    mytime=localtime (&currenttime);
/*    switch (current_timeformat)
    {
      case 1:{ strcpy (timeformat,""); strcpy(timeformat,"%T"); timeformat_size=8; }
      case 0:{ strcpy (timeformat,""); strcpy(timeformat,"%H:%M"); timeformat_size=5; }
    }*/
    if (current_timeformat==0) strcpy (timeformat,"           ");
    if (current_timeformat==1) { strcpy (timeformat,""); strcpy(timeformat,"   %I:%M %p"); timeformat_size=11; }
    if (current_timeformat==2) { strcpy (timeformat,""); strcpy(timeformat,"%I:%M:%S %p"); timeformat_size=11; }
    if (current_timeformat==3) { strcpy (timeformat,""); strcpy(timeformat,"      %H:%M"); timeformat_size=11; }
    if (current_timeformat==4) { strcpy (timeformat,""); strcpy(timeformat,"   %T"); timeformat_size=11; }
    setcolor (3,1);
    char buffer[256];
    strftime (buffer,256,timeformat,mytime);
    if (init_text==0) mvprintw (0,0,"LinuxEyes MP3 Player");
    mvprintw (0,2+nrcols-timeformat_size,"%s",buffer);
    char stest[10]; //for sleep mode
    strftime (stest,10,"%T",mytime);
    if (strcmp(stest,sleeptime)==0) 
    {
      quit=1;
      nclose=1;
      reread=1;
    }
    free (mytime);
    // ----------------------
    XA_Message message;
    control_message_get (player,&message);
    setcolor (1,0);
    if (message.code==XA_MSG_NOTIFY_INPUT_TIMECODE) 
    {
      mvprintw (dx,nrcols-6,"[%.2d:%.2d]",message.data.timecode.m,message.data.timecode.s);
      secs++;
      n_secs++;
    }
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
        mvprintw (dx+1,nrcols-21,"[--------------------]");
        mvprintw (dx+1,nrcols-21+n,"*");
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
      curent.min=duration / 60;
      curent.sec=duration % 60;
      reread=1;
    }
    if (message.code==XA_MSG_NOTIFY_CODEC_EQUALIZER)
    {
      equalizer=*message.data.equalizer;
    }
//    if (message.code==XA_MSG_NOTIFY_OUTPUT_PCM_LEVEL)
//    {
//      abort();
//    }
}

void set_sleep()
{
  int scr2=8;
  WINDOW *w;
  w=newwin (scr2-1,25,7+((scr-scr2)/2),25);
  wsetcolor (w,13,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,25,scr2-1);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Shut Down At ");
  wsetcolor (w,12,0);
  mvwprintw (w,2,10,":   :");
  mvwprintw (w,4,4,"ENTER - set sleep");
  mvwprintw (w,6,11," ESC - quit ");
  wrefresh(w);
  timeout (1);
  int key=-1;
  read_text hrs;
  read_text min;
  read_text sec;
  char s[1000];
  // -------- Time -------
    time (&currenttime);
    currenttime=currenttime+3600;
    tm *mytime;
    mytime=localtime (&currenttime);
    sprintf (s,"%.2d",mytime->tm_hour);
    strcpy (hrs.text,s);
    sprintf (s,"%.2d",mytime->tm_min);
    strcpy (min.text,s);
    sprintf (s,"%.2d",mytime->tm_sec);
    strcpy (sec.text,s);
    free (mytime);
  // ---------------------
  int curent=1;
  const int max_edit=3;
  do
  {
    if (key==3) curent++;
    if (curent < 1)  curent=max_edit;
    if (curent > max_edit) curent=1;
    readstring_with_key (w,2,7,2,2,&hrs,'\0',"0123456789",0);
    readstring_with_key (w,2,11,2,2,&min,'\0',"0123456789",0);
    readstring_with_key (w,2,15,2,2,&sec,'\0',"0123456789",0);
    if (curent==1) key=readstring_with_key (w,2,7,2,2,&hrs,'\0',"0123456789",1);
    if (curent==2) key=readstring_with_key (w,2,11,2,2,&min,'\0',"0123456789",1);
    if (curent==3)key=readstring_with_key (w,2,15,2,2,&sec,'\0',"0123456789",1);
  } while ((key!=0) && (key!=4));
  if (key==0) 
  {
    strcpy (sleeptime,"");
    sleepmode=0;
  }
  if (key==4)
  {
    strcpy (sleeptime,hrs.text);
    strcat (sleeptime,":");
    strcat (sleeptime,min.text);
    strcat (sleeptime,":");
    strcat (sleeptime,sec.text);
    sleepmode=1;
  }
}

void console(int scr)
{
  WINDOW *w1;
  w1=newwin (scr+2,62,7,9);
  wrefresh (w1);
  werase (w1);
  WINDOW *w;
  w=newwin (scr,60,8,10);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr+2;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,60,scr);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," LinuxEyes Console ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr-1,48," q - quit ");
  wrefresh(w);
  noecho();
  timeout (1);
  k=0;
  do
  {
    for (int i=0;i<=scr-5;i++) 
    {
      mvwprintw (w,2+i,2,"                                                         ");
      if ((i+k) <= nr_consmsg) mvwprintw (w,2+i,2,"%s",consmsg[i+k]);
    }
    wrefresh(w);
    do
    {
      messages();
      v=getch();
    } while (v==ERR);
    if (v == 27) 
    {
      v=getch();
      if (v==91)
      {
        v=getch();
	if (v==65) if (k > 0) k--;
        if (v==66) if (k < nr_consmsg-(scr-5)) k++;
      }
    }
  }    
  while (v!='q');
  werase (w);
  reread=1;
}

void add_console_message(char *s)
{
  char temp[100];
  nr_consmsg++;
  strcpy (consmsg[nr_consmsg],s);
  strcpy (temp,s);
  FILE *f;
  strcpy (strtmp,getenv("HOME"));
  strcat (strtmp,"/.linuxeyes.console");
  f=fopen (strtmp,"a");
  fprintf (f,"%s\n",temp);
  fclose (f);
}

void showid3 (char *name)
{
 if (name!=NULL)
 if (strcmp (name,"")!=0)
 {
  // edit structs;
  char *mp3_name;
  mp3_name=strdup (name);
  read_text e_track;
  read_text e_artist;
  read_text e_song;
  read_text e_album;
  read_text e_year;
  read_text e_comment;
  // actual showid3
  int scr2=12;
  WINDOW *w1;
  w1=newwin (scr2+1,62,(6+(scr-scr2)/2),9);
  wrefresh (w1);
  werase (w1);
  WINDOW *w;
  w=newwin (scr2-1,60,7+((scr-scr2)/2),10);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,60,scr2-1);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," ID3v1.1 Tag Editor");
  wsetcolor (w,12,0);
  mvwprintw (w,scr2-2,31," ENTER - save | ESC - quit ");
  wrefresh(w);
/*  XA_DecoderInfo *decoder;            
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
      list.nb_properties > 7) */
      wsetcolor (w,12,0);
      mvwprintw (w,2,2,"  TRACK: ");
      mvwprintw (w,3,2," ARTIST: ");
      mvwprintw (w,4,2,"   SONG: ");
      mvwprintw (w,5,2,"  ALBUM: ");
      mvwprintw (w,6,2,"   YEAR: ");
      mvwprintw (w,7,2,"  GENRE: ");
      mvwprintw (w,8,2,"COMMENT: ");
      mvwprintw (w,9,2,"   FILE: ");
      mvwprintw (w,7,11,"%c",ACS_LARROW);
      mvwprintw (w,7,29,"%c",ACS_RARROW);
      wsetcolor (w,12,1);
      if (!id3 (name,&my_id3))
      { 
        my_id3.track='\0';
        strcpy (my_id3.artist,"");
        strcpy (my_id3.song,"");
        strcpy (my_id3.album,"");
        strcpy (my_id3.year,"");
        strcpy (my_id3.comment,"");
        my_id3.genre=126; 
      }
      strcpy (e_artist.text,my_id3.artist);
      strcpy (e_comment.text,my_id3.comment);
      strcpy (e_song.text,my_id3.song);
      strcpy (e_album.text,my_id3.album);
      strcpy (e_year.text,my_id3.year);
      char s[3];
      sprintf (s,"%d",my_id3.track);
      strcpy (e_track.text,s);
      //if (my_id3.track>0) mvwprintw (w,2,11,"%d",my_id3.track);
      //if ((my_id3.genre>0) && (my_id3.genre <=125)) mvwprintw (w,7,11,"%s",genres[my_id3.genre]);
      mvwprintw (w,9,11,"%.46s",name);
/*      else 
      {
        mvwprintw (w,9,2,"   FILE: ");
	wsetcolor (w,12,0);
        wsetcolor (w,12,1);
        mvwprintw (w,2,5,"Could not find id3 tag.");
	mvwprintw (w,9,11,"%.46s",name);
      }*
	if (decoder->status->info.duration != duration) duration = decoder->status->info.duration; 
	duration=duration / 1000;
	min=duration / 60;
	sec=duration % 60;
  decoder_input_close(decoder);	
  decoder_delete (decoder);	*/
  wrefresh(w);
  noecho();
  timeout (1);
  int v;
  int key=-1;
  int curent=1;
  const int max_read=7; // nr of readstring_with_key boxes
  do
  {
//    messages();
//    v=getch();
      if (key==1) curent--;
      if (key==2) curent++;
      if (key==3) curent++;
      if (curent < 1) curent=max_read;
      if (curent > max_read) curent=1;
      //display texts;
      readstring_with_key (w,2,11,2,2,&e_track,'\0',"0123456789",0);
      readstring_with_key (w,3,11,30,30,&e_artist,'\0',NULL,0);
      readstring_with_key (w,4,11,30,30,&e_song,'\0',NULL,0);
      readstring_with_key (w,5,11,30,30,&e_album,'\0',NULL,0);
      readstring_with_key (w,6,11,4,4,&e_year,'\0',"0123456789",0);
      list_with_key (w,7,12,16,0,126,my_id3.genre,0);
      readstring_with_key (w,8,11,29,29,&e_comment,'\0',NULL,0);
      if (curent==1) key=readstring_with_key (w,2,11,2,2,&e_track,'\0',"0123456789",1);
      if (curent==2) key=readstring_with_key (w,3,11,30,30,&e_artist,'\0',NULL,1);
      if (curent==3) key=readstring_with_key (w,4,11,30,30,&e_song,'\0',NULL,1);
      if (curent==4) key=readstring_with_key (w,5,11,30,30,&e_album,'\0',NULL,1);
      if (curent==5) key=readstring_with_key (w,6,11,4,4,&e_year,'\0',"0123456789",1);
      if (curent==6) key=list_with_key (w,7,12,16,0,126,my_id3.genre,1);
      if (curent==7) key=readstring_with_key (w,8,11,29,29,&e_comment,'\0',NULL,1);
      my_id3.genre=list_result;
  } while ((key!=0) && (key!=4));
  v='\0';
  if (key==4) 
  {
    strcpy (my_id3.artist,e_artist.text);
    strcpy (my_id3.comment,e_comment.text);
    strcpy (my_id3.song,e_song.text);
    strcpy (my_id3.album,e_album.text);
    strcpy (my_id3.year,e_year.text);
    unsigned int t;
    sscanf (e_track.text,"%u",&t);
    my_id3.track=t;
    write_id3 (my_id3,mp3_name);
  }
  reread=1;
  werase (w);
 }
}

void show_msg (char *message)
{
  int scr2=4;
  int t;
  WINDOW *w;
  w=newwin (scr2-1,36,7+((scr-scr2)/2),21);
  wsetcolor (w,13,0);
  //mvwprintw (w,2,0,"Confirmation");
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,36,scr2-1);
  wrefresh(w);
  mvwprintw (w,1,2,"%s",message);
  wrefresh (w);
  do
  {
    t=getch();
    messages();
  } while (t==ERR);
  werase (w);
  wrefresh (w);
}

int list_with_key(WINDOW *w,int j,int i, unsigned int l, int min, int max, char res, int active)
{
  char r;
  r=res;
  unsigned int k=0;
  int key=-1;
  unsigned int p=0;
  timeout (1);
  int t=0;
  do
  {
    if (r < min) r=min;
    if (r > max) r=max;
    if (!active) wsetcolor (w,2,1);
    else wsetcolor (w,7,1);
    for (k=0;k<=l;k++) mvwprintw (w,j,i+k," ");
    for (k=p;k<strlen(genres[r]);k++) mvwprintw (w,j,i+k-p,"%c",genres[r][k]);
    wrefresh (w);
    do
    {
      t=getch();
      messages();
      wsetcolor (w,7,1);
      wrefresh (w);
      if (active==0) t=1000;
    } while (t==ERR);
    if (t==9) key=3;
    if (t==27)
    {
      t=getch();
      if (t==91)
      {
        t=getch();
        if (t==68) r--;
	if (t==67) r++;
	if (t==65)
	{
	  key=1;
	  t=1000;
	}
	if (t==66)
	{
	  key=2;
	  t=1000;
	}
      } else
      if (t == ERR) 
      {
	key=0;
	t=1000;
      }
    }
    if (t=='\n') key=4;
  } while ((key!=3) && (key!=0) && (key!=4) && (t!=1000));
  list_result=r;
  return key;
}

// nu merg sagetile

int readstring_with_key(WINDOW *w,int j,int i ,unsigned int l, unsigned int maxl, read_text *text, char pass, char *chars, int active)
{
  int res=1;
  char memstring[1000];
  strcpy(memstring,"");
  strcat (memstring,text->text);
  if (strlen (memstring) > maxl) memstring[maxl]='\0';
  int key=-1;
  unsigned ln;
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
    ln=strlen (memstring);
    if (ln > l) p=ln-l;
    else p=0;
    if (!active) wsetcolor (w,2,1);
    else wsetcolor (w,7,1);
    for (k=0;k<=l;k++) mvwprintw (w,j,i+k," ");
    for (k=p;k<strlen(memstring);k++) if (pass=='\0') mvwprintw (w,j,i+k-p,"%c",memstring[k]);
                                      else mvwprintw (w,j,i+k-p,"%c",pass);
//    for (k=0;k<=l;k++) if (ln >= k+p) if (pass=='\0') mvwprintw (w,j,i+k,"%c",memstring[k+p]);
//                                      else if (memstring[k+p]!='\0') mvwprintw (w,j,i+k,"%c",pass);
    wrefresh (w);
    do
    {
      t=getch();
      messages();
      wsetcolor (w,7,1);
      wrefresh (w);
      if (active==0) t=1000;
      else mvwprintw (w,j,i+ln-p,"_");
    } while (t==ERR);
//    if (t!=1000) mvprintw (0,0,"t=%d\n\r",t);
    if ((t!='\n') && (t!=127) && (t!=9) && (t!=27) && (t!=1000) && (strlen (memstring) < maxl))
    {
      if (chars==NULL)
      {
        memstring[ln]=t;
        memstring[ln+1]='\0';
        ln++;
      }
      else if (index (chars,t)!=NULL)
      {
        memstring[ln]=t;
        memstring[ln+1]='\0';
        ln++;
      }
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
        strcpy (memstring,text->text);
	res=0;
	key=0;
	t=1000;
      } else
      if (t==91)
      {
        t=getch();
        if (t==65) key=1;
	if (t==66) key=2;
	if ((t==65) || (t==66)) t=1000;
      }
      else t='\0';
    }
    if (t==9)
    {
      key=3;
      t=1000;
    }
    if (t=='\n') key=4;
    // key maps 0-ESC; 1-UP; 2-DOWN; 3-TAB; 4-ENTER; -1-nothing;
/*    mvprintw (j,i,"%s",memstring); */
  } while ((t!='\n') && (t!=9) && (t!=1000));
//  mvprintw (2,2,"                                                ");
//  mvprintw (2,2,"%s",memstring);
    strcpy (text->text,memstring);
  return key;
}

int readstring(WINDOW *w,int j,int i ,unsigned int l,char *text, char pass)
{
  int res=1;
  strcpy(memstring,"");
  strcat (memstring,text);
  unsigned ln;
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
    ln=strlen (memstring);
    if (ln > l) p=ln-l;
    else p=0;
    wsetcolor (w,2,1);
    for (k=0;k<=l;k++) mvwprintw (w,j,i+k," ");
    for (k=p;k<strlen(memstring);k++) if (pass=='\0') mvwprintw (w,j,i+k-p,"%c",memstring[k]);
                                      else mvwprintw (w,j,i+k-p,"%c",pass);
//    for (k=0;k<=l;k++) if (ln >= k+p) if (pass=='\0') mvwprintw (w,j,i+k,"%c",memstring[k+p]);
//                                      else if (memstring[k+p]!='\0') mvwprintw (w,j,i+k,"%c",pass);
    wrefresh (w);
    do
    {
      t=getch();
      messages();
      wsetcolor (w,7,1);
      mvwprintw (w,j,i+ln-p,"_");
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
	res=0;
	t=1000;
      }
      else t='\0';
    }
/*    mvprintw (j,i,"%s",memstring); */
  } while ((t!='\n') && (t!=9) && (t!=1000));
//  mvprintw (2,2,"                                                ");
//  mvprintw (2,2,"%s",memstring);
  return res;
}

int readstring_window(char *wintitle, char *title, int shadow, char pass, int path)
{
  int scr2=4;
  WINDOW *w1;
  if (shadow==1)
  {
    w1=newwin (scr2+1,64,(6+(scr-scr2)/2),8);
    wrefresh (w1);
  }
  WINDOW *w;
  w=newwin (scr2-1,62,7+((scr-scr2)/2),9);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,62,scr2-1);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," %s ",wintitle);
  wsetcolor (w,12,0);
  mvwprintw (w,scr2-3,2,title);
  wrefresh(w);
  char tempstring[100];
  if (path==1) 
  {
    strcpy (tempstring,getenv("PWD"));
    strcat (tempstring,"/");
  }
  else strcpy (tempstring,"");
  int res=readstring (w,1,strlen (title)+3,48,tempstring, pass);
  werase (w);
  wrefresh (w);
  if (shadow==1) 
  {
    werase (w1);
    wrefresh (w1);
  }
  return res;
}

int search()
{
  char tempstring[2000];
  const char *tokens = " ,.?!-";
  int sendcmd=-1;
  int scr2=4;
  int cansend=0;
  char *found;
  char *tempstr;
  int ok;
  WINDOW *w1;
  w1=newwin (scr2+1,62,(6+(scr-scr2)/2),9);
  wrefresh (w1);
  WINDOW *w;
  w=newwin (scr2-1,60,7+((scr-scr2)/2),10);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,60,scr2-1);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Search ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr2-3,2,"Song");
  wrefresh(w);
  readstring (w,1,8,48,"",'\0');
  werase (w);
  werase (w1);
  if (strcmp(memstring,"")!=0)
  {
    int i,nr=-1;
    int t='\0';
    char s1[2000],s2[2000];
    for (i=0;i<=n;i++)
    {
      ok=1;
      strcpy (tempstring,filelist[i].name);
      strcat (tempstring," ");
      strcat (tempstring,filelist[i].text);
      uppercase(tempstring);
      strcpy (s1,upcase);
      // make the searchstring
      uppercase(memstring);
      strcpy (s2,upcase);
      found=NULL;
      tempstr=strtok (s2,tokens);
      while ((tempstr!=NULL) && (ok))
      {
//	fprintf (stderr,"%s - %s\n",(char*)tempstr,(char*)s2);
	if (tempstr!=NULL) found=strstr (s1,(char*)tempstr);
	if (found==NULL) ok=0;
	tempstr=strtok (NULL,tokens);
      }
      if (ok)
      {
        nr++;
        strcpy (filterlist[nr].text,filelist[i].text);
        filterlist[nr].nr=i;
      }
    }
    if (nr>-1) cansend=1;
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
      le_border (w,60,scr2-1);
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
	  if (infilter (filelist[filterlist[m+i].nr].name)) col=col+1;
	  wsetcolor (w,col,0);
	  mvwprintw (w,i+1,2,"                                                        ");
	  mvwprintw (w,i+1,2,"%.56s",filterlist[m+i].text);
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
	if (t==9) add_to_filter (filelist[filterlist[m+k].nr].name);
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
      } while ((t!='\n') && (t!='q') && (t!=' ') && (t!='F'));
      werase (w);
      werase (w1);
      if (cansend)
      {
        if (t=='\n') sendcmd=filterlist[m+k].nr;
        if (t==' ') { strcpy (next.name,filelist[filterlist[m+k].nr].name); strcpy (next.text,filelist[filterlist[m+k].nr].text); }
	if (t=='F') for (int i=0;i<=nr;i++) add_to_filter (filelist[filterlist[i].nr].name);
      }
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
  le_border (w,60,scr2-1);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Add URL ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr2-3,2,"Song URL");
  wrefresh(w);
  readstring (w,1,11,46,"http://",'\0');
  werase (w);
  werase (w1);
}

void savelist(char *file,int t)
{
  add_console_message ("saveplaylist: saving playlist");
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
    le_border (w,60,scr2-1);
    wsetcolor (w,13,1);
    mvwprintw (w,0,1," Save Playlist ");
    wsetcolor (w,12,0);
    mvwprintw (w,scr2-3,2,"Playlist");
    wrefresh(w);
    char tempstring[100];
    strcpy (tempstring,getenv("PWD"));
    strcat (tempstring,"/");
    readstring (w,1,11,46,tempstring,'\0');
  } else { strcpy (memstring,getenv("HOME")); strcat (memstring,"/"); strcat (memstring,".linuxeyes.playlist"); }
    if (strcmp(memstring,"")!=0)
    {
      strcpy (strtmp,"saveplaylist: filename \"");
      strcat (strtmp,memstring);
      strcat (strtmp,"\"");
      add_console_message (strtmp);
      /*ofstream f(memstring);
      f <<"eypl=LinuxEyes Playlist" <<endl;
      f <<"{" <<endl;
      for (int i=0;i<=n;i++)
      { 
        if (i<n) f <<filelist[i].name <<"\n" <<filelist[i].text <<"\n" <<filelist[i].min <<" " <<filelist[i].sec <<endl;
        if (i==n) f <<filelist[i].name <<"\n" <<filelist[i].text <<"\n" <<filelist[i].min <<" " <<filelist[i].sec <<endl;
      }  
      f <<"}";
      f.close();*/
      FILE *f;
      f=fopen (memstring,"w");
      if (f!=NULL)
      {
        char playlistinfo[5];
	strcpy (playlistinfo,"LE6PL");
	fwrite (&playlistinfo,sizeof(playlistinfo),1,f);
	fwrite (&n,sizeof(n),1,f);
        int i=0;
        for (i=0;i<=n;i++) fwrite (&filelist[i],sizeof(filelist[i]),1,f);
        fclose (f);
	add_console_message ("saveplaylist: playlist saved");
      } else add_console_message ("saveplaylist: faild to save playlist");
      strcpy (playlistfile,memstring);
    } else add_console_message ("saveplaylist: save of playlist aborted");
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
  le_border (w,60,scr2-1);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Playlist Entry ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr2-3,2,"Filename");
  wrefresh(w);
  readstring (w,1,11,46,filelist[nr].name,'\0');
  werase (w);
  werase (w1);
  if (strcmp(memstring,"")!=0) strcpy (filelist[nr].name,memstring);
}

#include "inc/help.cpp"
#include "inc/files.cpp"
#include "inc/specials.cpp"
#include "inc/format.cpp"
#include "inc/eq_import.cpp"

void equ(int scr)
{
  control_message_send (player, XA_MSG_GET_CODEC_EQUALIZER);
  int v,k;
  WINDOW *w1;
  w1=newwin (scr+2,62,7,9);
  wrefresh (w1);
  werase (w1);
  WINDOW *w;
  w=newwin (scr,60,8,10);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr+2;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,60,scr);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Equalizer ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr-1,48," q - quit ");
  wrefresh(w);
  noecho();
  timeout (1);
  k=0;
  do
  {
    int j=0;
    wsetcolor (w,13,1);
    mvwprintw (w,2,3,"ALL");
    mvwvline (w,3,4+j,ACS_VLINE,9);
    mvwprintw (w,2+9-(((((eq.left+eq.right)/2)+128)*9)/256),4+j,"*");
    if ((eq.left+eq.right)/2 < 0) mvwprintw (w,12,2+j,"%.3d ",(eq.left+eq.right)/2);
    else mvwprintw (w,12,2+j," %.3d ",(eq.left+eq.right)/2);
    j=j+5;
    wsetcolor (w,12,0);
    for (int i=1;i<=10;i++) mvwprintw (w,2,4+(i*5),"%d",i);
    for (int i=0;i<=5;i++)
    {
      mvwvline (w,3,4+j,ACS_VLINE,9);
      mvwprintw (w,2+9-(((((equalizer.left[i]+equalizer.right[i])/2)+128)*9)/256),4+j,"*");
      if ((equalizer.left[i]+equalizer.right[i])/2 < 0) mvwprintw (w,12,2+j,"%.3d ",(equalizer.left[i]+equalizer.right[i])/2);
      else mvwprintw (w,12,2+j," %.3d ",(equalizer.left[i]+equalizer.right[i])/2);
      j=j+5;
    }
    int i=0;
    // 6-7
    i=6;
    mvwvline (w,3,4+j,ACS_VLINE,9);
    mvwprintw (w,2+9-(((((equalizer.left[i]+equalizer.right[i])/2)+128)*9)/256),4+j,"*");
    if ((equalizer.left[i]+equalizer.right[i])/2 < 0) mvwprintw (w,12,2+j,"%.3d ",(equalizer.left[i]+equalizer.right[i])/2);
    else mvwprintw (w,12,2+j," %.3d ",(equalizer.left[i]+equalizer.right[i])/2);
    j=j+5;
    // 8-11
    i=8;
    mvwvline (w,3,4+j,ACS_VLINE,9);
    mvwprintw (w,2+9-(((((equalizer.left[i]+equalizer.right[i])/2)+128)*9)/256),4+j,"*");
    if ((equalizer.left[i]+equalizer.right[i])/2 < 0) mvwprintw (w,12,2+j,"%.3d ",(equalizer.left[i]+equalizer.right[i])/2);
    else mvwprintw (w,12,2+j," %.3d ",(equalizer.left[i]+equalizer.right[i])/2);
    j=j+5;
    // 12-19
    i=12;
    mvwvline (w,3,4+j,ACS_VLINE,9);
    mvwprintw (w,2+9-(((((equalizer.left[i]+equalizer.right[i])/2)+128)*9)/256),4+j,"*");
    if ((equalizer.left[i]+equalizer.right[i])/2 < 0) mvwprintw (w,12,2+j,"%.3d ",(equalizer.left[i]+equalizer.right[i])/2);
    else mvwprintw (w,12,2+j," %.3d ",(equalizer.left[i]+equalizer.right[i])/2);
    j=j+5;
    // 20-31
    i=20;
    mvwvline (w,3,4+j,ACS_VLINE,9);
    mvwprintw (w,2+9-(((((equalizer.left[i]+equalizer.right[i])/2)+128)*9)/256),4+j,"*");
    if ((equalizer.left[i]+equalizer.right[i])/2 < 0) mvwprintw (w,12,2+j,"%.3d ",(equalizer.left[i]+equalizer.right[i])/2);
    else mvwprintw (w,12,2+j," %.3d ",(equalizer.left[i]+equalizer.right[i])/2);
    j=j+5;
    // -----------------
    wrefresh(w);
    do
    {
      messages();
      v=getch();
    } while (v==ERR);
    if (v==27)
    {
      v=getch();
      if (v==91)
      {
        v=getch();
	if (v==53)
	{
	  if (eq.left<127) eq.left++;
	  if (eq.right<127) eq.right++;
	  for (int i=0;i<=31;i++) { equalizer.left[i]++; equalizer.right[i]++; }
	}
	if (v==54)
	{
	  if (eq.left>-128) eq.left--;
	  if (eq.right>-128) eq.right--;
	  for (int i=0;i<=31;i++) { equalizer.left[i]--; equalizer.right[i]--; }
	}
      }
    }
    if (v=='a') { if (equalizer.left[0]<127) equalizer.left[0]++; if (equalizer.right[0]<127) equalizer.right[0]++; }
    if (v=='z') { if (equalizer.left[0]>-128) equalizer.left[0]--;if (equalizer.right[0]>-128) equalizer.right[0]--; }
    if (v=='s') { if (equalizer.left[1]<127) equalizer.left[1]++; if (equalizer.right[1]<127) equalizer.right[1]++; }
    if (v=='x') { if (equalizer.left[1]>-128) equalizer.left[1]--;if (equalizer.right[1]>-128) equalizer.right[1]--; }
    if (v=='d') { if (equalizer.left[2]<127) equalizer.left[2]++; if (equalizer.right[2]<127) equalizer.right[2]++; }
    if (v=='c') { if (equalizer.left[2]>-128) equalizer.left[2]--;if (equalizer.right[2]>-128) equalizer.right[2]--; }
    if (v=='f') { if (equalizer.left[3]<127) equalizer.left[3]++; if (equalizer.right[3]<127) equalizer.right[3]++; }
    if (v=='v') { if (equalizer.left[3]>-128) equalizer.left[3]--;if (equalizer.right[3]>-128) equalizer.right[3]--; }
    if (v=='g') { if (equalizer.left[4]<127) equalizer.left[4]++; if (equalizer.right[4]<127) equalizer.right[4]++; }
    if (v=='b') { if (equalizer.left[4]>-128) equalizer.left[4]--;if (equalizer.right[4]>-128) equalizer.right[4]--; }
    if (v=='h') { if (equalizer.left[5]<127) equalizer.left[5]++; if (equalizer.right[5]<127) equalizer.right[5]++; }
    if (v=='n') { if (equalizer.left[5]>-128) equalizer.left[5]--;if (equalizer.right[5]>-128) equalizer.right[5]--; }
    if (v=='j') { if (equalizer.left[6]<127) equalizer.left[6]++; if (equalizer.right[6]<127) equalizer.right[6]++; }
    if (v=='m') { if (equalizer.left[6]>-128) equalizer.left[6]--;if (equalizer.right[6]>-128) equalizer.right[6]--; }
    if (v=='k') { if (equalizer.left[8]<127) equalizer.left[8]++; if (equalizer.right[8]<127) equalizer.right[8]++; }
    if (v==',') { if (equalizer.left[8]>-128) equalizer.left[8]--;if (equalizer.right[8]>-128) equalizer.right[8]--; }
    if (v=='l') { if (equalizer.left[12]<127) equalizer.left[12]++; if (equalizer.right[12]<127) equalizer.right[12]++; }
    if (v=='.') { if (equalizer.left[12]>-128) equalizer.left[12]--;if (equalizer.right[12]>-128) equalizer.right[12]--; }
    if (v==';') { if (equalizer.left[20]<127) equalizer.left[20]++; if (equalizer.right[20]<127) equalizer.right[20]++; }
    if (v=='/') { if (equalizer.left[20]>-128) equalizer.left[20]--;if (equalizer.right[20]>-128) equalizer.right[20]--; }
    equalizer.left[7]=equalizer.left[6];
    equalizer.right[7]=equalizer.right[6];
    for (int i=9;i<=11;i++)
    {
      equalizer.left[i]=equalizer.left[8];
      equalizer.right[i]=equalizer.right[8];
    }
    for (int i=12;i<=19;i++)
    {
      equalizer.left[i]=equalizer.left[12];
      equalizer.right[i]=equalizer.right[12];
    }
    for (int i=21;i<=31;i++)
    {
      equalizer.left[i]=equalizer.left[31];
      equalizer.right[i]=equalizer.right[31];
    }
    for (int i=0;i<=31;i++)
    {
      if (equalizer.left[i]>126) equalizer.left[i]=126;
      if (equalizer.left[i]<-127) equalizer.left[i]=-127;
      if (equalizer.right[i]>126) equalizer.right[i]=126;
      if (equalizer.right[i]<-127) equalizer.right[i]=-127;
    }
    if (v=='L')
    {
      strcpy (strtmp,getenv("HOME"));
      strcat (strtmp,"/.linuxeyes.eq");
      if (list_from_equ (strtmp,1))
      {
        for (int i=0;i<=6;i++) 
	{
          equalizer.left[i]=imported_eq_preset[i];
          equalizer.right[i]=imported_eq_preset[i];
        }
  	  equalizer.left[8]=imported_eq_preset[7];
  	  equalizer.right[8]=imported_eq_preset[7];
	  equalizer.left[12]=imported_eq_preset[8];
	  equalizer.right[12]=imported_eq_preset[8];
	  equalizer.left[20]=imported_eq_preset[9];
          equalizer.right[20]=imported_eq_preset[9];
      }
      for (int h=0;h<=scr+2;h++) mvwprintw (w,h,0,"                                                            ");
      wsetcolor (w,12,0);
      le_border (w,60,scr);
      wsetcolor (w,13,1);
      mvwprintw (w,0,1," Equalizer ");
      wsetcolor (w,12,0);
      mvwprintw (w,scr-1,48," q - quit ");
    }
    if (v=='S')
    {
      readstring_window ("Save Equalizer","Preset",0,'\0',0);
      if (strcmp (memstring,"") != 0)
      {
        for (int i=0;i<=6;i++) exported_eq_preset[i]=((equalizer.left[i]+equalizer.right[i])/2)+127;
	exported_eq_preset[7]=((equalizer.left[8]+equalizer.right[8])/2)+127;
	exported_eq_preset[8]=((equalizer.left[12]+equalizer.right[12])/2)+127;
	exported_eq_preset[9]=((equalizer.left[20]+equalizer.right[20])/2)+127;
	strcpy (strtmp,getenv("HOME"));
        strcat (strtmp,"/.linuxeyes.eq");
	save_to_equ (strtmp,memstring);
        /*ofstream f(memstring);
	if (!f.fail())
	{
	  f <<eq.left <<" " <<eq.right;
          for (int i=0;i<=31;i++) 
          {
            f <<equalizer.left[i] <<" ";
          }
	}*/
      }
      for (int h=0;h<=scr+2;h++) mvwprintw (w,h,0,"                                                            ");
      wsetcolor (w,12,0);
      le_border (w,60,scr);
      wsetcolor (w,13,1);
      mvwprintw (w,0,1," Equalizer ");
      wsetcolor (w,12,0);
      mvwprintw (w,scr-1,48," q - quit ");
    }
    if (v=='I')
    {
      int f;
      f=eq_formatselect();
      if (f)
      {
	  if (f==1)
	  {
	    showfiles (scr,".","Select an XMMS eq presets file to import",0,".");
	    if (mpegnumber>-1)
	    {
	      if (list_from_xmms (mpegfile[0]))
	      {
	        for (int i=0;i<=6;i++) 
	        {
	          equalizer.left[i]=imported_eq_preset[i];
	          equalizer.right[i]=imported_eq_preset[i];
	        }
		equalizer.left[8]=imported_eq_preset[7];
	        equalizer.right[8]=imported_eq_preset[7];
		equalizer.left[12]=imported_eq_preset[8];
	        equalizer.right[12]=imported_eq_preset[8];
		equalizer.left[20]=imported_eq_preset[9];
                equalizer.right[20]=imported_eq_preset[9];
	      }
	    }
	  }
	  if (f==2) load_from_le0_6();
	  if (f==3)
	  {
	    showfiles (scr,".","Select a Winamp eq presets file to import",0,".");
	    if (mpegnumber>-1)
	    {
	      if (list_from_winamp (mpegfile[0]))
	      {
	        for (int i=0;i<=6;i++) 
	        {
	          equalizer.left[i]=imported_eq_preset[i];
	          equalizer.right[i]=imported_eq_preset[i];
	        }
		equalizer.left[8]=imported_eq_preset[7];
	        equalizer.right[8]=imported_eq_preset[7];
		equalizer.left[12]=imported_eq_preset[8];
	        equalizer.right[12]=imported_eq_preset[8];
		equalizer.left[20]=imported_eq_preset[9];
                equalizer.right[20]=imported_eq_preset[9];
	      }
	    }
	  }
	  if (f==4) if (load_from_eqf())
	  {
	    for (int i=0;i<=6;i++) 
	    {
	      equalizer.left[i]=imported_eq_preset[i];
	      equalizer.right[i]=imported_eq_preset[i];
	    }
	    equalizer.left[8]=imported_eq_preset[7];
	    equalizer.right[8]=imported_eq_preset[7];
	    equalizer.left[12]=imported_eq_preset[8];
	    equalizer.right[12]=imported_eq_preset[8];
	    equalizer.left[20]=imported_eq_preset[9];
            equalizer.right[20]=imported_eq_preset[9];
	  }
      }
      for (int h=0;h<=scr+2;h++) mvwprintw (w,h,0,"                                                            ");
      wsetcolor (w,12,0);
      le_border (w,60,scr);
      wsetcolor (w,13,1);
      mvwprintw (w,0,1," Equalizer ");
      wsetcolor (w,12,0);
      mvwprintw (w,scr-1,48," q - quit ");
    }
    if (v=='D')
    {
      strcpy (strtmp,getenv("HOME"));
      strcat (strtmp,"/.linuxeyes.eq");
      list_from_equ (strtmp,2);
      for (int h=0;h<=scr+2;h++) mvwprintw (w,h,0,"                                                            ");
      wsetcolor (w,12,0);
      le_border (w,60,scr);
      wsetcolor (w,13,1);
      mvwprintw (w,0,1," Equalizer ");
      wsetcolor (w,12,0);
      mvwprintw (w,scr-1,48," q - quit ");
    }
    if (v=='r')
    {
      eq.left=0;
      eq.right=0;
      for (int i=0;i<=31;i++) {equalizer.left[i]=0; equalizer.right[i]=0; }
    }
    control_message_send (player, XA_MSG_SET_CODEC_EQUALIZER, &equalizer);
  }
  while (v!='q');
  werase (w);
  reread=1;
}

void deletefile (int k)
{
  for (int i=k;i<n;i++) filelist[i]=filelist[i+1];
  n--;
  reread=1;
}

void addfile(char *file_)
{
  char file[1000];
  int k=-1;
  if (strlen (file_) >= 1) {k++; file[k]=file_[0]; }
  for (unsigned int j=1;j<=strlen (file_)-1;j++) if (!((file_[j-1]==file_[j]) && (file_[j]=='/'))) {k++; file[k]=file_[j]; }
  file[k+1]='\0';
  int i=n+1;
  filelist[i].tag=id3(file,&my_id3);
  strcpy (filelist[i].name,file);
  strcpy(filelist[i].artist,my_id3.artist);
  strcpy(filelist[i].song,my_id3.song);
  strcpy(filelist[i].text,text);
  filelist[i].min=min;
  filelist[i].sec=sec;
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
  le_border (w,36,scr2-1);
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
      //n++;
      strcpy(temp.name,dir); 
      strcat(temp.name,namelist[i]->d_name);
      /*s=strdup (filelist[n].name);
      id3(s);
      strcpy (filelist[n].name,s);
      strcpy(filelist[n].artist,artist);
      strcpy(filelist[n].song,song);
      strcpy(filelist[n].text,text);
      filelist[n].min=min;
      filelist[n].sec=sec;
      filelist[n].tag=tag; */
      addfile (temp.name);
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
  int scr2=11;
  int t=0;
  WINDOW *w;
  w=newwin (scr2-1,25,7+((scr-scr2)/2),25);
  wsetcolor (w,13,0);
//  mvwprintw (w,2,1," Playlist Options ");
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,25,scr2-1);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Playlist Options ");
  wsetcolor (w,12,0);
  mvwprintw (w,2,4,"n : New");
  mvwprintw (w,3,4,"l : Load");
  mvwprintw (w,4,4,"s : Save");
  mvwprintw (w,5,4,"i : Import");
  mvwprintw (w,6,4,"e : Export");
  mvwprintw (w,7,4,"r : Reverse Order");
  mvwprintw (w,9,12," q - quit ");
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
      showfiles (scr-1,".","Select a playlist to load",0,".");
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
    if (t=='i')
    {
      werase (w);
      wrefresh (w);
      int format;
      format=formatselect();
      if (format != 0)
      {
        showfiles (scr-1,".","Select a playlist to import",0,".");
        if (mpegnumber > -1)
        { 
	  strcpy (playlistfile,mpegfile[0]);
	  if (format==1) n=importxmms(mpegfile[0]); 
          if (format==2) n=importle3(mpegfile[0]);
	  if (format==3) n=importle5(mpegfile[0]);
	  if (format==4) n=importm3u(mpegfile[0]);
	  m=0;
	  k=0;
	  reread=1;
        }
      }
      t='q';
    }
    if (t=='e')
    {
      werase (w);
      wrefresh (w);
      int format;
      format=formatselect();
      if (format != 0)
      {
        readname ("","Export Playlist"); 
	if (strcmp (memstring,"")!=0)
	if (format==1) export2xmms (memstring);
	if (format==2) export2le3 (memstring);
	if (format==3) export2le5 (memstring);
      }
      t='q';
    }
    if (t=='r')
    {
      werase (w);
      wrefresh (w);
      int i;
      for (i=0;i<=(n/2);i++)
      {
        temp=filelist[i];
//	fprintf (stderr,"%d   %s\n\r",i,filelist[0].text);
	filelist[i]=filelist[n-i];
	filelist[n-i]=temp;
      }
      t='q';
    }
  } while (t!='q');
  reread=1;
}

void playlist ()
{
//    int k=0,m=0,l=0;
    add_console_message ("playlist: playlist started");
    strcpy (curent.name,"");
    strcpy (next.text,"");
    int v;
    setcolor (1,0);
    mvprintw (dx,1,"Artist: ");
    mvprintw (dx+1,1,"  Song: ");
    setcolor (1,1);
    mvhline (6,0,ACS_HLINE,nrcols+2);
    mvhline (scr+8,0,ACS_HLINE,nrcols+2);
    char tempstring[100];
    strcpy (tempstring,getenv("HOME"));
    strcat (tempstring,"/");
    strcat (tempstring,".linuxeyes.playlist");
    n = loadlist (tempstring);
    if (autoplay==true) playnext();
    setcolor (1,0);
// test if n > 16
    if (n > scr) l=scr;
    else l=n;
    do
    {
      for (unsigned int j=0;j<=nrcols+3;j++)
      {
        mvprintw (6,j," ");        
        mvprintw (scr+8,j," ");        
      }
      if (nrcols != old_nrcols) resettime();
      setcolor (1,1);
      mvhline (6,0,ACS_HLINE,nrcols+2);
      mvhline (scr+8,0,ACS_HLINE,nrcols+2);
      for (unsigned int j=0;j<=nrcols+2;j++)
      {
        mvprintw (scr+7,j," ");        
        mvprintw (scr+9,j," ");        
        mvprintw (scr+10,j," ");        
      }
      if (more < 0) {k=0; more++;m--; reread=1;}
      if (more > 0) {k=l; more--;if ((m+k) < n) m++; reread=1;}
      if (k < 0) { m--;k++; }
      if (k > scr) { m++;k--; }
      if (m < 0) {m=0; k=0;}
      if (((m+scr) > n) && (n > scr)) {k=scr; m=n-k;}
      if (k > n) k=n;
      for (int i=0;i<=l;i++) 
      {
        int color=1;
	int t=1;
	if (infilter (filelist[m+i].name)) color=15;
	if (strcmp (filelist[m+i].name,curent.name)==0) color = 6;
	if (strcmp (filelist[m+i].name,next.name)==0) color = 4;
	if (i==k) color++;
	if (!(fileexists(filelist[m+i].name))) t=0;
	setcolor (color,t);
	unsigned int j=0;
	for (j=1;j<=nrcols;j++) mvprintw (7+i,j," ");
	mvprintw (7+i,1,"%d.",m+i+1);
	unsigned int maxl;
	maxl=strlen (filelist[m+i].text);
	if (maxl > nrcols) maxl=nrcols;
	for (j=0;j<=maxl;j++) 
	{
	  int t;
	  if (m+i+1 <= 9) t=4;
	  else
	  if (m+i+1 <= 99) t=5;
	  else
	  if (m+i+1 <= 999) t=6;
	  else
	  if (m+i+1 <= 9999) t=7;
	  else
	  if (m+i+1 >= 10000) t=8;
	  mvprintw (7+i,j+t,"%c",filelist[m+i].text[j]);
	}
	/*mvprintw (7+i,1,"                                                                              ");
        mvprintw (7+i,1,"%d. %.60s",m+i+1,filelist[m+i].text);*/
	if ((filelist[m+i].min != 0) && (filelist[m+i].sec != 0)) mvprintw (7+i,nrcols-5," %.2d:%.2d",filelist[m+i].min,filelist[m+i].sec);
	setcolor (1,0);
	mvprintw (7+i,nrcols+1,"  ");
      }
      setcolor (1,0);
      for (int i=l+1;i<=scr;i++) 
        for (unsigned int j=1;j<=nrcols+2;j++) mvprintw (7+i,j," ");
      setcolor (1,1);
      mvhline (scr+8,0,ACS_HLINE,nrcols+2);
      setcolor (1,0);
      if (n > scr) l=scr;
      else l=n;
      char s[7];
      strcpy (s,"Normal   ");
      if (rnext==1) strcpy (s,"Shuffle  ");
      if (filternr>-1) strcpy (s,"Filter   ");
      if ((filternr>-1) && (persistent_filter))strcpy (s,"P-Filter ");
      if (strcmp (next.name,"")!=0) strcpy (s,"Next Song");
      if (password==1) strcpy (s,"Password ");
      if (sleepmode==1) strcpy (s,"Sleep    ");
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
      char pos=' ';
      if (save_pos) pos='*';
      if (status_bar==0) mvprintw (scr+9,1,"%s | Volume[%d] | Pcm[%d] | Balance[%d] | %c |",s,vol,pcm,balance-50,pos);
      if (status_bar==1) mvprintw (scr+9,1,"Next Song: %s",next.text);
      if (status_bar==2) mvprintw (scr+9,1,"Filter: %d file(s)",filternr+1);
      setcolor (1,1);
      if (tunknown==0) mvprintw (scr+9,nrcols-7,"%.2d:%.2d:%.2d",thour,tmin,tsec);
      else mvprintw (scr+9,nrcols-8,"~%.2d:%.2d:%.2d",thour,tmin,tsec);
      refresh();
      noecho();
      timeout (1);
      do 
      {
        v=getch();
	messages();
	if (playerror == 1) { playerror=0; playnext(); }
	if ((v!=ERR) && (password==1))
	{
	  if (readstring_window ("Unlock Display","Password",1,'*',0)) if (strcmp (passwordstr,memstring)==0) 
	  { 
	    password=0; 
	    reread=1;
	  }
	  v=ERR;
	}
      } while ((v==ERR) && (reread==0) && (password==0)); 	
      reread=0;
      if (v=='!') password=1;
      if (v=='\\')
      {
        int allow=0;
        if (strcmp (passwordstr,"") != 0) if (readstring_window ("Enter OLD Password","Password",1,'*',0)) if (strcmp (memstring,passwordstr)==0) allow=1;
	else; else; else allow=1;
	if (allow == 1)
	{
          if (readstring_window ("Enter NEW Password","Password",1,'*',0))
          {
            char temp[100];
            strcpy (temp,memstring);
            if (readstring_window ("Retype NEW Password","Password",1,'*',0)) if (strcmp (temp,memstring)==0) 
	    {
	      strcpy (passwordstr,memstring);
	      show_msg ("Password Changed");
	    } else show_msg ("Passwords don\'t match");
          }
	}
      }
      if (v=='?') about(scr-1);
      if (v=='h') help(scr-1);
      if (v==';') save_pos=1-save_pos;
      if (v=='=') status_bar=(status_bar+1)%3;
      if (v=='t') { current_timeformat=(current_timeformat+1)%nr_timeformat; }
      if (v=='i') showid3 (filelist[m+k].name);
      if (v=='I') showid3 (curent.name);
      if (v=='\n') { nr_prev++; strcpy (prev[nr_prev],curent.name); strcpy (curent.name,filelist[m+k].name); play (curent.name); position_refresh (m+k); }
      if (v==' ') { if (strcmp (next.name,filelist[m+k].name)!=0) { strcpy (next.name,filelist[m+k].name); strcpy (next.text,filelist[m+k].text);} else { strcpy (next.name,"");strcpy (next.text,""); }}
      if (v==9) add_to_filter (filelist[m+k].name);
      if (v=='T') set_sleep();
      if (v=='f') persistent_filter=1-persistent_filter;
      if (v=='F') filternr=-1;
      if (v=='r') { if (strcmp (next.name,curent.name)!=0) { strcpy (next.name,curent.name); strcpy (next.text,curent.text); } else { strcpy (next.name,""); strcpy (next.text,""); }}
      if (v=='z') playprev();
      if (v=='x') play (curent.name);
      if (v=='c') mpegpause ();
      if (v=='v') stop ();
      if (v=='b') playnext();
      if (v=='s') rnext=!rnext;
      if (v=='E') fileentry (m+k);
      if (v=='e') equ(14);
      if (v=='j') 
      {
        int x=search();
	if (x > -1)
	{  
	  nr_prev++; 
	  strcpy (prev[nr_prev],curent.name); 
	  strcpy (curent.name,filelist[x].name); 
	  play (curent.name);
	}
      }
      if (v=='d') {deletefile (m+k); if (((m+scr) > n) && (n > scr)) m--;}
      if (v=='S') { sort (0,n); getcurent();}
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
      if (v=='P') jazzpiper();
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
      /*if ((v>=49) && (v<=57))
      {
        clear ();
	endwin();
        fprintf (stderr,"FS Command: %s\n\r",fs_command[v-48]);
        system (fs_command[v-48]);
	refresh();
	reset ();
	reread=1;
      }*/ 
      if (v=='a')
      {
        showfiles (scr-1,".","Select a file to add",0,".");
	if (strcmp(mpegfile[0],"")!=0)
	  if (mpegnumber > -1) for (int i=0;i<=mpegnumber;i++) addfile(mpegfile[i]);
	reread=1;
      }
      //if (v=='u') readurl();
      /*{
        readstring (NULL,2,2,20,"URL");
	if (strcmp(memstring,"")!=0)
	{
          addfile (memstring); 
	} 
      } */
 
      if (v=='D') 
      { 
        showfiles (scr-1,".","Select a directory to add",1,".");
	if (mpegnumber > -1)
	{
	  if (s[strlen(mpegfile[0])]!='/') strcat (mpegfile[0],"/");
          adddir (mpegfile[0]); 
	}  
	reread=1;
      }
      if (v==',') if (balance > 0) {balance--; setvolumes (vol,pcm,balance); }
      if (v=='.') if (balance < 100) {balance++; setvolumes (vol,pcm,balance);}
      if (v=='l') 
      {
        m=getcurent()-(scr/2);
	k=(scr/2);
//	if (more < 0) more=more+(scr/2);
//	if (more > 0) more=more-(scr/2);
      }
      if ((v>=48) && (v<=57))
      {
        m=(v-48)*(n/9)-(scr/2);
      }
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
	  if (v==53) more=-scr;//less=scr;
	  if (v==54) more=scr;
	  if (v==52) if (pcm > 0) {pcm--; setvolumes (vol,pcm,balance); }
          if (v==49) if (pcm < 100) {pcm++; setvolumes (vol,pcm,balance); }
	  if (v==51) if (vol > 0) {vol--; setvolumes (vol,pcm,balance);}
	  if (v==50) if (vol < 100) {vol++; setvolumes (vol,pcm,balance);}
	}
      }
      if (v==45) {if (scr > 15) scr--; reread=1;}
      if (v==43) {scr++; reread=1;}
      if (v==47) {if (nrcols > 78) nrcols--; reread=1;}
      if (v==42) {nrcols++; reread=1;}
      if (v=='|') if (nclose!=0) nclose=0; else nclose=1;
      if (v=='m') console(scr-1);
    }  
    while ((v!='Q') && (quit==0));
    chdir (path);
    savelist (playlistfile,0);
}

int main(int argc,char *argv[])
{
/*    printf ("%s\n",genres[1]);
    getchar();*/
    strcpy (fs_command[1],"mount /dev/hdc");
    strcpy (fs_command[2],"umount /dev/hdc");
    strcpy (fs_command[3],"mount /dev/hdd");
    strcpy (fs_command[4],"umount /dev/hdd");
    strcpy (fs_command[5],"mount /dev/hdb1");
    strcpy (fs_command[6],"umount /dev/hdb1");
    getcwd (path,sizeof(path));
    strcat (path,"/");
    strcpy (playlistfile,"linuxeyes.playlist");
    add_console_message ("Hello, welcome to LinuxEyes v0.8");
    add_console_message ("--------------------------------");
    strcpy (strtmp,"xmp: starting in: \"");
    strcat (strtmp,path);
    strcat (strtmp,"\"");
    add_console_message (strtmp);
    printf ("Linux Eyes v0.8 (C) Alexandru Radovici 2002 - 2100\n\r");
    if (argc > 1)
    for (int i=1;i<argc;i++)
    {
      add_console_message ("xmp: procesing arguments");
      if (strcmp(argv[i],"-p") == 0) autoplay=true;
      if (strcmp(argv[i],"--nocolors")==0) nocolor=1;
      if (strcmp(argv[i],"--autoscr")==0) scr_autodetect=1;
      if (strcmp(argv[i],"--fakelines")==0) nolines=1;
      if (strcmp(argv[i],"--new_start")==0) new_start=1;
    } 
    printf ("Starting console...\n\r");
    printf ("Loading configuration... ");
    add_console_message ("xmp: loading configuration");
    if (new_start==0)
    if (loadconfig ()) 
    {
      printf ("ok\n\r");
      add_console_message ("xmp: configuration OK");
    }
    else 
    {
      printf ("failed, using default configuration\n\r");
      add_console_message ("xmp: configuration loading failed, using default");
    }
    else
    {
      printf ("\"--new_start\" argument found, making a new configuration\n\r");
      add_console_message ("xmp: \"--new_start\" argument found => new config");
    }
    printf ("Starting LinuxEyes\n\r");
    if (scr_autodetect == 1) 
    {
      system ("export COLUMNS");
      system ("export LINES");
      if (getenv ("COLUMNS")!=NULL)
      {
//        add_console_message (getenv("COLUMNS"));
        sscanf (getenv("COLUMNS"),"%d",&nrcols);
	nrcols=nrcols-2;
      }
      if (getenv ("LINES")!=NULL)
      {
//        add_console_message (getenv("LINES"));
        sscanf (getenv("LINES"),"%d",&scr);
        scr=scr-10;
      }
    }
    if (nrcols<78) nrcols=78;
    if (scr<=15) scr=15;
    add_console_message ("xmp: starting interface");
    initscr();
    cbreak();
    if (nolines) fakelines();
//    keypad (NULL,TRUE);
    curs_set (0);
    colors();
    setcolor (3,1);
    init_text=1;
    mvprintw (0,0,"Welcome to LinuxEyes MP3 Player v0.8 [press h for help]");
    add_console_message ("xmp: starting player");
    player_new (&player,NULL);
    control_message_send (player, XA_MSG_SET_CODEC_EQUALIZER, &equalizer);
    resettime();
    playlist();
    clear();
    refresh();
    curs_set (1);
    nocbreak();
    endwin();
    add_console_message ("xmp: closing player");
    control_message_send (player,XA_MSG_COMMAND_EXIT);
    player_delete (player);
    add_console_message ("xmp: saving configuration");
    if (saveconfig ()) printf ("xmp: configuration saved\n\r");
    else printf ("xmp: configuration could bot be saved\n\r");
    add_console_message ("xmp: almost done");
    printf ("Thank you for using LinuxEyes Player\n\rPlease report bugs to linueyes@lug.orizont.net\n\r");
    add_console_message ("--------------------------------");
    add_console_message ("Bye Bye");
    add_console_message ("");
    if (nclose==1) 
    {
      add_console_message ("Shutting Down");
      printf ("Shutting Down....");
      system ("halt -p");
    }
    return 0;
}
