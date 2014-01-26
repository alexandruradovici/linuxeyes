#include "inc/version.cpp"
const char endl='\n'; //gcc3 fstream bug fix
char text[150]; //id3 main
static unsigned long duration=0; //duration
int nrscr=0; //the screen size, normal terminal 16
int min,sec; //duration main
int vol=90,pcm=90,balance=50; //volumes
int n,n2; //nr of files in playlist, n2 for search
int reread=1; //reread playlist befor pressing a key
bool paused=false; //paused ?
int n1=0; //?
int v=50; //?
bool rnext=true; //random next
int autoplay=false; //-p parameter
char playlistfile[1000], def_playlist[1000]; //playlist filename with path
char memstring[1000]; //memory string, for readstring
char prev[1000][1000]; //previous songs list
int nr_prev=-1; //nr of previous songs
int playerror=0; //error on play
int musicfile = -1;
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
int nrcols=78,old_nrcols=78; //number of colums of screen
//char consmsg[1000][5000]; //console messages
int nr_consmsg=0; //number of console messages
char strtmp[100]; //temp string
char fs_command[9][100]; //fs commands
int scr_autodetect=1; //audetect screen
int init_text; //init text, ... [press h for help]
char timeformat[10]; // the clock display format
int nr_timeformat=5; //number of clock display formats
int current_timeformat=1; //the current clock format
int timeformat_size; //the size of the clock display
int password=0; //password mode on/off
char passwordstr[100]; //password string
int curent_playlist_nr=-1; //nr of current position in playlist
int dx=4; //x value for control panel display, defaul 4, depends on "Next Song"
int status_bar=0; //status bar display type, 0 normal, 1 next song, 2 filter, 3 radio time, 4 shutdown time, default 0
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
char list_result=0; // result of list_with_key
int new_start=0; // new configuration at startup, default
int refresh_curent=0; //after I, refresh curent position
int radio=0; //radio mode;
int auto_equ=0; //automatic eq load, after song genre
int auto_goto=0; //auto goto current song
int song_changed; //song was changed by playnext
int fake_lines=0; //fake lines indicator. for readstring_with_key
char the_time[256]; //current time variable, used for displaying the time in messages (cursor problem)
int cursor_moved=0; //indicates wheater the cursor has been moevd
int writetime=0; //write the time now (yes/no), used for resettome
char ok_char='.'; //bad chars replacement character
int screen=0; //screen active
int screensaver_time=3; //screen saver time
int showhello=0; // show the welcome screen or not
int show_to_logs=0; //save debug to console and show it on syslog
int try_again=0; //if playnext failed, try again after getting keys
char text_format[150]="%a - %s"; //format of files in playlist (text content)
int show_playlist_numbers=1; //show the playlist numbers (1=yes, 0 no)
int use_id3_plus=1; //use id3 plus information (1=yes, 0=no)
int shut_down_timer=30; //time to shutdown, time for warning
int sysinfo=-1; //whether the system info exists (-1=no)
char mesaj[200]; //string for actually displaying messages
const unsigned int max_mesaje=5000; //max nr. of characters in mesaje
char mesaje[max_mesaje]; //string for messages
int pos_mesaj=0; //current position in message
int sys_clock=0; //nr of interrupts (messages)
int clock_speed=14; //speed of the "clock" - used for displaying the messages (mesaje)
const int nr_mesaje_afisate=7;
int mesaje_afisate[nr_mesaje_afisate]; //displayed "auto" messages, used for random display - 0 - current song, 1 - next song, 2 - date, 3 - paused
int afiseaza_acum=-1; //directly queue a message
int stopped=1; // is the player stopped ?
int ultimul_mesaj_afisat=-1; // the last message queued, it is used in order not to repeat the same message one after the other
const char whats_new_file[100] = "/usr/lib/linuxeyes/linuxeyes.whats-new"; // the what's new file name
char messagesfile[1000]; // the file where to store the messages
int ultimul_mesaj_din_lista_afisat=-1; //the last message from the file that was shown, used for random display
int show_system_messages=1; // display system status in messages bar
int show_file_messages=1; // display file messages in messages bar
int refreshlist_position=-1; //if > 0 does the playlist refresh during messages calls
char *str_memout;

//timevar_type radio_on, radio_off; //radio mode times
//timevar_type sleeptime; // time to shut down for sleep mode

const char playlist_type[7]="LEPZ11";

struct read_text
{
  char text[1000];
};

typedef char list_type[1000][1000]; //presets list

typedef char list[200][30];

list genres = {
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
    "Duet", "Punk Rock", "Drum Solo", "A Capella", "Euro-House", "Dance Hall","Unknown"
};

typedef struct f_list // type of functions list
{
    int key[10];
    int id;
};

f_list keys[27] = { // list of functions
    {{10,-1,-1,-1,-1},0}, //Enter
    {{27,-1,-1,-1,-1},1}, //ESC
    {{27,91,65,-1,-1},2}, //Up
    {{27,91,66,-1,-1},3}, //Down
    {{27,91,68,-1,-1},4}, //Left
    {{27,91,67,-1,-1},5}, //Right
    {{27,91,71,-1,-1},6}, //Numpad "5"
    {{27,91,50,126,-1},7}, //Insert
    {{27,91,51,126,-1},8}, //Delete
    {{27,91,49,126,-1},9}, //Home
    {{27,91,52,126,-1},10}, //End
    {{27,91,53,126,-1},11}, //PgUp
    {{27,91,54,126,-1},12}, //PgDn
    {{9,-1,-1,-1,-1},13}, //TAB
    {{27,91,91,65,-1},14}, //F1
    {{27,91,91,66,-1},15}, //F2
    {{27,91,91,67,-1},16}, //F3
    {{27,91,91,68,-1},17}, //F4
    {{27,91,91,69,-1},18}, //F5
    {{27,91,49,55,126},19}, //F6
    {{27,91,49,56,126},20}, //F7
    {{27,91,49,57,126},21}, //F8
    {{27,91,50,48,126},22}, //F9
    {{27,91,50,49,126},23}, //F10
    {{27,91,50,51,126},24}, //F11
    {{27,91,50,52,126},25} //F12
}; 

int nr_keys=26; //nr of elements in keys

list time_display = {
    "Don't display", "    09:00 PM", " 09:00:00 PM", "       21:00", "    21:00:00"
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
	int type;
	char plus[30];
} my_id3;

// function forward
void messages();
void play(char *name);
void stop();
void savelist(char *file,int t);
int add_mesaje (char *s);
void add_console_message(char *s);
int saveconfig();

//#include "inc/mpg123.cpp"
//#include "player.h"
//#include "decoder.h"
//#include "file_input.h"
//#include "mpeg_codec.h"
#include "bass.h"
#include <stdlib.h>
#include <wiringPi.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include "inc/misc.cpp"
#include <ctype.h>
#include <sys/stat.h>
#include <syslog.h>
#include <sys/utsname.h>
#include <zlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

time_t currenttime; //current time
time_t last_key_time; //time when the last key was pressed

struct utsname computer;

struct LE_sleep_type
{
  char time[10]; //time variable def
  int mode; // on/off mode (1=on, 0=off)
} le_sleep,radio_on,radio_off;

void showid3 (char *name, int shadow);
void label (int y, int x, char *text, int l);
void labelw (WINDOW *w, int y, int x, char *text, int l);
int readstring(WINDOW *w,int j,int i ,unsigned int l,char *text, char pass);
int readstring_window(char *wintitle, char *title, int shadow, char pass, int path);
int readstring_with_key(WINDOW *w,int j,int i, int l, int maxl, read_text *text, char pass, char *chars, int active);
int list_with_key(WINDOW *w,int j,int i, unsigned int l, int min, int max, char res, list lista, int active);
int list_nr_with_key(WINDOW *w,int j,int i, unsigned int l, int min, int max, int &res, int active);
int check_with_key(WINDOW *w,int j,int i, char *text, int &res, int active);
int button_with_key(WINDOW *w,int j,int i, char *text, int &res, int active);
void save_equ();
void restore_equ();
void set_equ(char *preset);
void load_id3_plus_equ(char *id3_plus, int unde);
void load_id3_plus_tag(char *id3_plus, int unde);
void show_msg (char *message);
int show_timer (char *message, int timp);
void addfile(char *file_);

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
    
int char_ok (char x)
{
  int f=0;
  if ((x>=32) && (x<=126)) f=1;
  else f=0;
  if (fake_lines==0) f=1;
  return f;
}

void fakelines ()
{
    for (int i = 0; acs_approx[i].acscode != 0; i++) 
    {
      acs_map[acs_approx[i].acscode] = acs_approx[i].character;
    }
    fake_lines=1;
}
// ---------------

int getkey (int v)
{
  if (v==ERR) return -1;
  int nr_v=-1;
  int function=-1;
  int set_of_keys[10];
  int limit = 3;
  // mvprintw (1,1,"                           ");
  // mvprintw (1,1,"T:");
  int g=0;
  do
  {
  while (v!=ERR && nr_v < limit-1)
  {
    nr_v++;
    set_of_keys[nr_v]=v;
    // mvprintw (1,3+nr_v*4,"%d",v);
    if (nr_v < limit-1) v=getch();
  }
  for (int i=0;(i<nr_keys) && (!g);i++)
  {
    g=1;
    for (int j=0;j<=nr_v;j++) if (set_of_keys[j]!=keys[i].key[j]) g=0;
    if (g) function=keys[i].id;
  }
  if (!g)
  {
   limit++;
   v=getch ();
  }
  }
  while (v!=ERR && !g);
//  mvprintw (2,1," Function: %d   ",function);
  if (function!=-1) return 10000+function;
  else if (nr_v==1) return 20000+set_of_keys[1];
  else return set_of_keys[0];
}

int add_mesaje (char *s)
{
  if (strlen (mesaje)+strlen (s)+9<max_mesaje)
  {
    strcat (mesaje,"   ***   ");
    strcat (mesaje,s);
  } else return 0;
  return 1;
}

struct controlfiles
{
   char name[1000];
   char artist[31];
   char song[31];
   char text[150];
   int min;
   int sec;
   int tag;    
}curent,next; //current song and next song info

struct files
{
   char name[1000];
   char text[150];
   int min;
   int sec;
   int tag;    
}filelist[10000],temp; //filelist, temp list

struct
{
  char text[200];
  int nr;
}filterlist[10000]; 

char filesfilter[10000][1000];

// Backspace thing - not used yet

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

//XA_Control *player;
//XA_EqualizerInfo equalizer, def_eq;

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
		id3_tag->plus[i-97]=tag_str[i];
	}
	if (id3_tag->genre < 0) id3_tag->genre=126;
	if (id3_tag->genre > 125) id3_tag->genre=126;
	if (id3_tag->comment[28]==0) 
	{
	  id3_tag->track=id3_tag->comment[29];
	  id3_tag->type=11;
	}
	else 
	{
	  id3_tag->track='\0';;
	  id3_tag->type=1;
	}
	if ((id3_tag->plus[0]=='\0') && (id3_tag->plus[1]==-7)) id3_tag->type=14;
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
  if (id3_tag.track>0) 
  {
    id3[125]='\0';
    id3[126]=id3_tag.track;
  }
  id3[127]=id3_tag.genre;
  if (id3_tag.type==14)
  for (i=97;i<=124;i++)
  {
     id3[i]=id3_tag.plus[i-97];
  } else if (id3[98]==-7) id3[98]=0;
  FILE *f;
  f=fopen (file,"r+");  
    if (f!=NULL)
    {
      fseek (f,-128,SEEK_END);
      if (fread (&s,3,1,f)==1)
      {
        if (memcmp (s,"TAG",3)==0)
	  if (id3_tag.type!=0)
          {
            fseek (f,-128,SEEK_END);
	    if (fwrite (id3,128,1,f)==1) e=1;
          }
	  else
	  {
	    fseek (f,0,SEEK_END);
	    e=truncate (file,ftell(f)-128)+1;
	  }
        else if (id3_tag.type!=0)
        {
          fseek (f,1,SEEK_END);
	  if (fwrite (id3,128,1,f)==1) e=1;
        }
      }
      if (e==1) 
      fclose (f);
    }
  if (e!=1) 
  {
    show_msg ("Could not write ID3 Tag");
    char temp[1000];
    strcpy (temp,"Could not write ID3 TAG to ");
    if (file!=NULL) strcat (temp,file);
    if (file!=NULL) add_console_message (temp);
  } else 
    {
      char temp[1000];
      strcpy (temp,"ID3 TAG wrote to ");
      if (file!=NULL) strcat (temp,file);
      if (file!=NULL) add_console_message (temp);
    }
}

int id3 (char *name, mpeg_id3 *my_id3)
{
/*    XA_DecoderInfo *decoder;            
    XA_InputModule module;
    XA_CodecModule codec;
    decoder_new (&decoder);
    file_input_module_register(&module);
    decoder_input_module_register(decoder, &module);
    mpeg_codec_module_register(&codec);
    decoder_codec_module_register(decoder, &codec);
    decoder_input_new(decoder, name,XA_DECODER_INPUT_AUTOSELECT);
    decoder_input_open(decoder);
	if (decoder->status->info.duration != duration) duration = decoder->status->info.duration; 
	duration=duration / 1000;
	min=duration / 60;
	sec=duration % 60;
    decoder_input_close(decoder);	
    decoder_delete (decoder);	*/
    int namefile = BASS_StreamCreateFile (FALSE, name, 0, 0, 0);
    if (namefile != -1)
    {
	int d = BASS_ChannelBytes2Seconds(namefile, BASS_ChannelGetLength (namefile, BASS_POS_BYTE));
	min = d/60;
	sec = d%60;
	// min = 10;
	// sec=10;
	BASS_StreamFree (namefile);
    }
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
	strcpy (text,"");
	for (unsigned int i=0;(i<=strlen (text_format)) && (strlen(text)<=150);i++)
	{
	  if ((text_format[i]=='%') && (i<strlen (text_format)))
	  {
	    if (text_format[i+1]=='1') 
	    {
	      char s[3];
              sprintf (s,"%d",my_id3->track);
	      strcat (text,s);
	    }
	    
	    if (text_format[i+1]=='t') 
	    {
	      char s[3];
              sprintf (s,"%d",my_id3->track);
	      strcat (text,s);
	    }
	    
	    if (text_format[i+1]=='2') strcat (text,my_id3->artist);
	    if (text_format[i+1]=='3') strcat (text,my_id3->song);
	    if (text_format[i+1]=='4') strcat (text,my_id3->album);
	    if (text_format[i+1]=='5') strcat (text,my_id3->year);
	    if (text_format[i+1]=='6') strcat (text,genres[my_id3->genre]);
	    if (text_format[i+1]=='7') strcat (text,my_id3->comment);
	    if (text_format[i+1]=='8') strcat (text,name);
	    
	    if (text_format[i+1]=='a') strcat (text,my_id3->artist);
	    if (text_format[i+1]=='s') strcat (text,my_id3->song);
	    if (text_format[i+1]=='A') strcat (text,my_id3->album);
	    if (text_format[i+1]=='y') strcat (text,my_id3->year);
	    if (text_format[i+1]=='g') strcat (text,genres[my_id3->genre]);
	    if (text_format[i+1]=='c') strcat (text,my_id3->comment);
	    if (text_format[i+1]=='f') strcat (text,name);
	    
	    if (text_format[i+1]=='%') strcat (text,"%");
	    i++;
	  }
	  else strncat (text,&text_format[i],1);
	}
/*	strcpy (text,my_id3->artist);
        strcat (text," - ");
        strcat (text,my_id3->song);*/
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
      strncpy(text,s,149);
      if (strlen (s) > 149) text[149]='\0'; else text[strlen(s)]='\0';
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
    if (name != NULL) 
    {
      char temp[1000];
      strcpy (temp,"Deleted from filter ");
      if (name!=NULL) strcat (temp,name);
      if (name!=NULL) add_console_message (temp);
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
  {
    char temp[1000];
    strcpy (temp,"Added to filter ");
    if (name!=NULL) strcat (temp,name);
    if (name!=NULL) add_console_message (temp);
  }
}

void uppercase (char s[100])
{
  strcpy (upcase,s);
  for (unsigned int i=0;i<=strlen(s);i++) upcase[i]=toupper (s[i]);
}

void le_border (WINDOW *w, int x, int y)
{
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
  if (screen==0)
  {
    setcolor (1,0);
    for (int j=0;j<=nrcols+1;j++) mvprintw (0,j,"  ");
    setcolor (3,1);
    for (int j=0;j<=nrcols+1;j++) mvprintw (0,j," ");
    if (init_text == 1) mvprintw (0,0,"Welcome to LinuxEyes MP3 Player v%s (%s) [press h for help]",version,v_name);
    if (init_text == 0) mvprintw (0,0,"LinuxEyes MP3 Player");
    setcolor (1,0);
    mvprintw (dx,nrcols-7," [00:00] ");
    mvprintw (dx+1,nrcols-22," [--------------------] ");
    n1=-100;
    old_nrcols=nrcols;
    writetime=1;
  }
}

void reset()
{
    clear();
    setcolor (3,1);
    for (int j=0;j<=nrcols+1;j++) 
    {
      mvprintw (0,j," ");
    }
    setcolor (1,0);
    mvprintw (dx,9,"                                                    ");
    mvprintw (dx+1,9,"                                                    ");
    mvprintw (dx,1,"Artist: ");  
    mvprintw (dx+1,3,"Song: ");  
    if (curent.tag==0) 
    {
      mvprintw (4,1,"        ");
      label (dx+1,9,curent.text,nrcols-33);
    } 
    else
    {
      mvprintw (dx,1,"Artist: ");  
      label (dx,9,curent.artist,nrcols-33);
      mvprintw (dx+1,3,"Song: ");  
      label (dx+1,9,curent.song,nrcols-33);
    }
    resettime();
    reread=1;
    add_console_message ("Display was reset");
}

void position(int n)
{
    // control_message_send (player,XA_MSG_COMMAND_SEEK,n1+n,100);
    if (musicfile!=-1)
    {
	long pos = BASS_ChannelGetPosition (musicfile, BASS_POS_BYTE);
	long s = BASS_ChannelBytes2Seconds (musicfile, pos);
	BASS_ChannelSetPosition (musicfile, BASS_ChannelSeconds2Bytes (musicfile, s+n), BASS_POS_BYTE);
    }
}

void mpegpause()
{
    /*if (paused==true) control_message_send (player,XA_MSG_COMMAND_PLAY);
    else 
    {
      control_message_send (player,XA_MSG_COMMAND_PAUSE);
      afiseaza_acum=3;
    }*/
    if (musicfile != -1)
    {
	afiseaza_acum=3;
	if (!paused) BASS_ChannelPause (musicfile);
	else BASS_ChannelPlay (musicfile, FALSE);
	paused = !paused;
	
    }
}

void position_refresh (int p)
{
  filelist[p].tag=id3 (filelist[p].name,&my_id3);
  strcpy(filelist[p].text,text);
  filelist[p].min=min;
  filelist[p].sec=sec;
}

void play (char *name)
{
    init_text=0;
    if (fileexists(name))
    {
      stop ();
      playerror=0;
      restore_equ();
      curent.tag=id3 (name,&my_id3);
      if (name!=NULL) strcpy(curent.name,(char*)name);
      strcpy(curent.artist,my_id3.artist);
      strcpy(curent.song,my_id3.song);
      strcpy(curent.text,text);
      curent.min=min;
      curent.sec=sec;
      if (auto_equ==1) set_equ ((char*)genres[my_id3.genre]);
      //playmp3 (name);
	musicfile = BASS_StreamCreateFile (FALSE, name, 0, 0, 0);
	if (musicfile !=-1)
	{
	    BASS_SetVolume ((float)vol/100);
	    BASS_ChannelSetAttribute (musicfile, BASS_ATTRIB_VOL, (float)pcm/100);
	    BASS_ChannelSetAttribute (musicfile, BASS_ATTRIB_PAN, (float)balance/50-1);
	    BASS_ChannelPlay (musicfile, TRUE);
	}

      // set position range
      //control_message_send(player,XA_MSG_COMMAND_INPUT_OPEN,name);
      //control_message_send (player,XA_MSG_SET_OUTPUT_VOLUME,balance,pcm,vol);
      //control_message_send(player,XA_MSG_COMMAND_PLAY);
      if ((my_id3.type==14) && (use_id3_plus==1)) load_id3_plus_tag(my_id3.plus,0);
    if (screen==0)
    {
      setcolor (1,0);
      for (int t=0;t<=nrcols-10;t++)
      {
        mvprintw (4,9+t," ");
        mvprintw (5,9+t," ");
      }
      if (curent.tag==0) 
      {
        mvprintw (4,1,"        ");
	label (5,9,curent.text,nrcols-33);
      } 
      else
      {
        mvprintw (dx,1,"Artist: ");  
	label (dx,9,curent.artist,nrcols-33);
        label (dx+1,9,curent.song,nrcols-33);
      }
    }
      resettime();
      songs++;
      n_songs++;
      song_changed=1;
    }
    else playerror=1;
    reread=1;
    if (playerror!=1)
    {
      char temp[1000];
      strcpy (temp,"Playing ");
      if (name!=NULL) strcat (temp,name);
      if (name!=NULL) add_console_message (temp);
      stopped=0;
      afiseaza_acum=0;
    }
    else
    {
      char temp[1000];
      strcpy (temp,"Error playling ");
      if (name!=NULL) strcat (temp,name);
      if (name!=NULL) add_console_message (temp);
    }
}

void stop ()
{
    if (musicfile!=-1)
    {
	BASS_ChannelStop (musicfile);
	BASS_StreamFree (musicfile);
	musicfile = -1;
    }
    //control_message_send(player,XA_MSG_COMMAND_STOP);
    resettime();
    add_console_message ("Player stop");
    stopped=1;
}

void playprev()
{
  if (nr_prev > 0)
  {
    strcpy (curent.name,prev[nr_prev]);
    nr_prev--;
    play (curent.name);
  }
}

int playnext()
{
    int tested=0;
    try_again=0;
    if (nclose==1) quit=1;
    getcurent();
    int p;
    if (n > 0)
    {
      do
      if (tested<=200)
      {
        if (filternr>-1) p = (int)(random()%(filternr+1));
        else p = (int)(random()%n);
        tested++;
      } while (((p==curent_playlist_nr) && (filternr<0)) && (tested<=200));
      if (tested>200) tested=1; else tested=0;
    }
    else p=n;
    if (tested==0)
    {
      if (nr_prev<999) nr_prev++;
      strcpy (prev[nr_prev],curent.name);
      if (rnext == false) if (filternr<0) p = ++curent_playlist_nr; 
                          else if (!persistent_filter) p=0;
      if (strcmp (next.name,"")==0) if (filternr<0) { strcpy (curent.name,filelist[p].name); play (curent.name); }
                                    else { strcpy (curent.name,filesfilter[p]); if (!persistent_filter) delete_from_filter (curent.name); play (curent.name); }
      else  { strcpy (curent.name,next.name); play (next.name); }
      strcpy (next.name,"");
      strcpy (next.text,"");
    }
    reread=1;
    try_again=tested;
    return 0;
}

void getvolumes ()
{
  //control_message_send (player,XA_MSG_GET_OUTPUT_VOLUME);
  add_console_message ("Got volumes");
}

void setvolumes (int vol,int pcm, int balance)
{
  //control_message_send (player,XA_MSG_SET_OUTPUT_VOLUME,balance,pcm,vol);
    BASS_SetVolume ((float)vol/100);
    BASS_ChannelSetAttribute (musicfile, BASS_ATTRIB_VOL, (float)pcm/100);
    BASS_ChannelSetAttribute (musicfile, BASS_ATTRIB_PAN, (float)balance/50-1);
  add_console_message ("Volumes set");
}

int loadconfig()
{
  int r=1;
  strcpy (strtmp,getenv("HOME"));
  strcat (strtmp,"/.linuxeyes.config");
  std::ifstream f(strtmp);
  if (!f.fail())
  {
     f.getline(playlistfile,sizeof(playlistfile));
     f >>nrscr >>nrcols >>vol >>pcm >>balance >>rnext;
     f >>eq.left >>eq.right;
     for (int i=0;i<=31;i++) 
     {
       //f >>equalizer.left[i];
       //equalizer.right[i]=equalizer.left[i];
     }
     f >>current_timeformat >>status_bar >>songs >>secs;
     f >>persistent_filter >>save_pos;
     if (save_pos!=1) save_pos=0;
     f.getline (curent.name,sizeof(curent.name));
     f >>auto_equ >>auto_goto;
     f >>ok_char;
     f >>screensaver_time;
     f >>scr_autodetect;
     f.getline (text_format,sizeof(text_format));
     f.getline (text_format,sizeof(text_format));
     f >>show_playlist_numbers;
     f >>use_id3_plus;
     f >>shut_down_timer;
     f >>show_system_messages;
     f >>show_file_messages;
     f >>clock_speed;
     f.getline (messagesfile,sizeof (messagesfile));
     if (strcmp(text_format,"")==0) strcpy (text_format,"%a - %s");
     if (!save_pos) strcpy (curent.name,"");
     if ((status_bar<1) && (status_bar>5)) status_bar=1;
     if ((current_timeformat<0) && (current_timeformat>4)) current_timeformat=0;
     if ((rnext!=0) && (rnext!=1)) rnext=0;
     if ((auto_equ!=0) && (auto_equ!=1)) auto_equ=0;
     if ((auto_goto!=0) && (auto_goto!=1)) auto_goto=0;
     if ((show_playlist_numbers!=0) && (show_playlist_numbers!=1)) show_playlist_numbers=1;
     if ((use_id3_plus!=0) && (use_id3_plus!=1)) use_id3_plus=1;
     if (clock_speed<=0) clock_speed=14;
  }
  else r=0;
  f.close();
  save_equ();
  playlistfile[strlen(playlistfile)]='\0';
  strcpy (def_playlist,playlistfile);
  if (strlen (messagesfile)==0) sprintf (messagesfile,"%s/.linuxeyes.messages",getenv("HOME"));
  if (r==0) add_console_message ("Failed to load configuration"); else add_console_message ("Configuration loaded successfuly");
  return r;
}

int saveconfig()
{
  if (strcmp (def_playlist,"")==0) 
  {
    strcpy (def_playlist,getenv("HOME")); 
    strcat (def_playlist,"/"); 
    strcat (def_playlist,".linuxeyes.playlist");
  }
  int r=1;
  strcpy (strtmp,getenv("HOME"));
  strcat (strtmp,"/.linuxeyes.config");
  std::ofstream f(strtmp);
  if (!f.fail())
  {
     f <<def_playlist <<endl;
     f <<nrscr <<" " <<nrcols <<" " <<vol <<" " <<pcm <<" " <<balance <<" " <<rnext;
     f <<eq.left <<" " <<eq.right;
     for (int i=0;i<=31;i++) 
     {
       //f <<equalizer.left[i] <<" ";
     }
     f <<endl;
     f <<current_timeformat <<" " <<status_bar <<" " <<songs <<" " <<secs <<endl;
     f <<persistent_filter <<" " <<save_pos;
     if (save_pos) f <<curent.name <<endl;
     else f <<endl;
     f <<auto_equ <<" " <<auto_goto <<endl;
     f <<ok_char <<endl;
     f <<screensaver_time <<" " <<scr_autodetect <<endl;
     f <<text_format <<endl;
     f <<show_playlist_numbers <<" " <<use_id3_plus <<" " <<shut_down_timer <<" " <<show_system_messages <<" " <<show_file_messages <<" " <<clock_speed;
     f <<messagesfile <<endl;
  }
  else r=0;
  f.close();
  if (r==0) add_console_message ("Failed to save configuration"); else add_console_message ("Configuration saved successfuly");
  return r;
}

void refreshlist()
{
  for (int i=0;i<=n;i++)
  {
    filelist[i].tag=id3(filelist[i].name,&my_id3);
    strcpy(filelist[i].text,text);
    filelist[i].min=min;
    filelist[i].sec=sec;
  }
  reread=1;
  add_console_message ("Playlist was refreshed");
}

int loadlist(char *file)
{
    char temp[1000];
    strcpy (temp,"Loading playlist ");
    if (file!=NULL) strcat (temp,file);
    if (file!=NULL) add_console_message (temp);
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
    gzFile f;
    f=gzopen (file,"rb");
    if (f!=NULL)
    {
      int number=0;
      char playlistinfo[7];
      gzread (f,&playlistinfo,sizeof(playlistinfo));
      if (strcmp (playlistinfo,playlist_type)==0)
      {
      gzread (f,&number,sizeof(number));
      while ((!gzeof(f)) && (i<=number))
      {
        gzread (f,&filelist[i],sizeof(filelist[i]));
	i++;
      }
      } else i=0;
      gzclose (f);
    }
    wsetcolor (w,12,0);
    wrefresh(w);
    wrefresh(w);
    werase (w);
    i--;
    return i;
}

#include "inc/help.cpp"
#include "inc/files.cpp"
#include "inc/specials.cpp"
#include "inc/format.cpp"
#include "inc/eq_import.cpp"
#include "inc/screen.cpp"

void messages()
{
    sys_clock ++;
    cursor_moved=0;
    // -------- Time -------
    time (&currenttime);
    tm *mytime;
    mytime=localtime (&currenttime);
    if (current_timeformat==0) strcpy (timeformat,"           ");
    if (current_timeformat==1) { strcpy (timeformat,""); strcpy(timeformat,"   %I:%M %p"); timeformat_size=11; }
    if (current_timeformat==2) { strcpy (timeformat,""); strcpy(timeformat,"%I:%M:%S %p"); timeformat_size=11; }
    if (current_timeformat==3) { strcpy (timeformat,""); strcpy(timeformat,"      %H:%M"); timeformat_size=11; }
    if (current_timeformat==4) { strcpy (timeformat,""); strcpy(timeformat,"   %T"); timeformat_size=11; }
    setcolor (3,1);
    char buffer[256];
    strftime (buffer,256,timeformat,mytime);
    if ((strcmp (buffer,the_time)!=0) || (writetime==1))
    {
      if (screen==0) mvprintw (0,2+nrcols-timeformat_size,"%s",buffer);
      strftime (the_time,256,timeformat,mytime);
      writetime=0;
      cursor_moved=1;
    }
    char stest[10]; //for sleep mode
    strftime (stest,10,"%T",mytime);
    if (strcmp(stest,le_sleep.time)==0) 
    {
      quit=1;
      nclose=1;
      reread=1;
      le_sleep.mode=0;
    }
    if ((strcmp(stest,radio_on.time)==0) && (radio_on.mode==1)) 
    {
      try_again=1;
      radio_on.mode=0;
      reread=1;
    }
    if ((strcmp(stest,radio_off.time)==0) && (radio_off.mode==1))
    {
      stop ();
      radio_off.mode=0;
      reread=1;
    }
    //free (mytime); //Fedore Core 1 problem
    // ----------------------
    //XA_Message message;
    //control_message_get (player,&message);
    setcolor (1,0);
    /*if (message.code==XA_MSG_NOTIFY_INPUT_TIMECODE) 
    {*/
	if (musicfile != -1)
	{
	long pos = BASS_ChannelGetPosition (musicfile, BASS_POS_BYTE);
	long spos = BASS_ChannelBytes2Seconds (musicfile, pos);
      if (screen==0) mvprintw (dx,nrcols-6,"[%.2u:%.2u]",spos/60,spos%60);
      secs++;
      n_secs++;
      cursor_moved=1;
	
	int n;
      //n = ((message.data.position.offset*100)/message.data.position.range);
      n = (BASS_ChannelGetPosition (musicfile, BASS_POS_BYTE)*100 / BASS_ChannelGetLength(musicfile, BASS_POS_BYTE));
	if (n==0) n=1;
      if (n!=n1) 
      {
        int t=(n+3)/5;
	if (t<1) t=1;
	if (t>20) t=20;
	if (screen==0)
	{
          setcolor (1,0);
          mvprintw (dx+1,nrcols-21,"[--------------------]");
          mvprintw (dx+1,nrcols-21+t,"*");
	  n1=n;
	}
    }
	if (getenv ("VUMETER"))
	{
		long level = BASS_ChannelGetLevel(musicfile); // dealing with stereo 
		int LEDS = atoi (getenv ("LEDS"));
		if (level > -1 )
		{
  			int l = ((LOWORD(level)+HIWORD(level))/2 * (LEDS+1)) / 32768; // the left level 
         	 	// mvprintw (dx+1,nrcols-21,"l %d", l);
			for (int i=0; i<LEDS; i++)
			{
				if (i<l) digitalWrite (i, 1);
				else digitalWrite (i, 0);
			}
		}
	}
	int s = BASS_ChannelIsActive (musicfile);
	if (s == BASS_ACTIVE_STOPPED) try_again=1; 
    }
    /* (message.code==XA_MSG_NOTIFY_PLAYER_STATE) 
      switch (message.data.state)
      {
        case XA_PLAYER_STATE_EOS: try_again=1;
      }
    if (message.code==XA_MSG_NOTIFY_ERROR) try_again=1;
    if (message.code==XA_MSG_NOTIFY_INPUT_POSITION)
    {
      int n;
      n = ((message.data.position.offset*100)/message.data.position.range);
      if (n==0) n=1;
      if (n!=n1) 
      {
        int t=(n+3)/5;
	if (t<1) t=1;
	if (t>20) t=20;
	if (screen==0)
	{
          setcolor (1,0);
          mvprintw (dx+1,nrcols-21,"[--------------------]");
          mvprintw (dx+1,nrcols-21+t,"*");
	  n1=n;
	}
	cursor_moved=1;
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
    }*/
    if ((sys_clock>=clock_speed) && (show_system_messages || show_file_messages))
    {
      sys_clock=0;
      if (strcmp (mesaj,"")==0) 
      {
        for (int i=0;i<nrcols;i++) mesaj[i]=' ';
        mesaj[nrcols]='\0';
      }
      strcpy (mesaj,&mesaj[1]);
      if (strlen(mesaje)>0)
      {
        mesaj[nrcols-1]=mesaje[0];
        strcpy (mesaje,&mesaje[1]);
      }
      else mesaj[nrcols-1]=' ';
      mesaj[nrcols]='\0';
      setcolor (1,0);
      if (screen==0) label  (1,1,mesaj,nrcols+1);
      else label  (nrscr+9,1,mesaj,nrcols+1);
    }
    if (sys_clock>=clock_speed) sys_clock=0;
    if (strlen (mesaje)<2)
    {
      int tip=0;
      if (show_system_messages && show_file_messages) tip=(int)random()%100;
      else
      if (show_system_messages==1) tip=0;
      else
      if (show_file_messages==1) tip=1;
      if ((tip%2==1) && (afiseaza_acum==-1) && (show_file_messages))
      {
        LElist lista_mesaje (messagesfile, "", 8);
	int n=lista_mesaje.elements();
	if (n==0) tip=0;
	else
	{
          int i;
	  int poti_afisa=0;
	  while (!poti_afisa)
	  {
	    i=(int)random()%n;
	    if (i!=ultimul_mesaj_din_lista_afisat) poti_afisa=1;
	    if (n==1) poti_afisa=1;
	  }
	  if ((i!=ultimul_mesaj_din_lista_afisat) || (show_system_messages==0))
	  {
	    add_mesaje (strdup(lista_mesaje.element(i)));
	    ultimul_mesaj_din_lista_afisat=i;
	  }
	  else tip=0;
	}
      } 
      if (((tip%2==0) || (afiseaza_acum!=-1)) && (show_system_messages))
      {
        int afiseaza_msg=afiseaza_acum;
        if (afiseaza_acum==-1)
        {
          int toate_afis=1;
          for (int h=0;h<nr_mesaje_afisate;h++) if (mesaje_afisate[h]==0) toate_afis=0;
          if (toate_afis) for (int h=0;h<nr_mesaje_afisate;h++) mesaje_afisate[h]=0;
	  // testeaza daca exista
          if (strcmp (next.name,"")==0) mesaje_afisate[1]=1;
          if (!paused) mesaje_afisate[3]=1;
          if (le_sleep.mode==0) mesaje_afisate[4]=1;
          if (radio_on.mode==0) mesaje_afisate[5]=1;
          if (radio_off.mode==0) mesaje_afisate[6]=1;
          int poti_afisa=0;
          //srand (time(NULL));
	  int l=0;
          while (!poti_afisa)
          {
	    l++;
            afiseaza_msg=(int)random()%(nr_mesaje_afisate+filternr+1);
	    if (afiseaza_msg<nr_mesaje_afisate)
	    {
  	      if ((mesaje_afisate[afiseaza_msg]==0) && (afiseaza_msg!=ultimul_mesaj_afisat))
	      {
	        mesaje_afisate[afiseaza_msg]=1;
	        poti_afisa=1;
  	      }
	    }
	    else if (afiseaza_msg!=ultimul_mesaj_afisat) poti_afisa=1;
	    if (l>10) poti_afisa=1;
          }
        } else
        {
          if (afiseaza_acum<nr_mesaje_afisate) mesaje_afisate[afiseaza_acum]=1;
	  afiseaza_acum=-1;
        }
        char tmp[1000];
        strcpy (tmp,"");
        //mvprintw (2,1,"%d, %d   ",ultimul_mesaj_afisat,afiseaza_msg);
        ultimul_mesaj_afisat=afiseaza_msg;
        if (afiseaza_msg==0) if (!stopped) if (strcmp(curent.text,"")!=0) sprintf (tmp,"Playing \"%s\"",curent.text); else strcpy (tmp,"Stopped"); else strcpy (tmp,"Stopped");
        if (afiseaza_msg==1) if (strcmp(next.name,"")!=0) sprintf (tmp,"\"%s\" will be next",next.text);
        if (afiseaza_msg==2) strftime (tmp,256,"%A, %B %d, %G",mytime);
        if (afiseaza_msg==3) if (paused) strcpy (tmp,"Paused");
        if (afiseaza_msg==4) if (le_sleep.mode==1) sprintf (tmp,"Sutting down at %s",le_sleep.time); else sprintf (tmp,"Shut down has been disabled");
        if (afiseaza_msg==5) if (radio_on.mode==1) sprintf (tmp,"Starting music at %s",radio_on.time); else sprintf (tmp,"Music starting has been disabled");
        if (afiseaza_msg==6) if (radio_off.mode==1) sprintf (tmp,"Stopping music at %s",radio_off.time); else sprintf (tmp,"Music stopping has been disabled");
        if (afiseaza_msg>=nr_mesaje_afisate) 
        {
	  id3 (filesfilter[afiseaza_msg-nr_mesaje_afisate],&my_id3);
          sprintf (tmp,"Comming up \"%s\"",text);
        }
        if (strcmp(tmp,"")!=0) add_mesaje (tmp);
      } 
    }
    if (refreshlist_position > -1)
    {
      if (refreshlist_position >= n) refreshlist_position=-1;
      else
      {
        int i=refreshlist_position;
        filelist[i].tag=id3(filelist[i].name,&my_id3);
        strcpy(filelist[i].text,text);
        filelist[i].min=min;
        filelist[i].sec=sec;
	refreshlist_position++;
      }
    }
    if (!stopped && !paused)
    {
	if (str_memout!=NULL) strcpy (str_memout, curent.text); 
    }
    else 
    {
	if (str_memout!=NULL) strcpy (str_memout, "");
    }
}

void set_sleep(char *title, LE_sleep_type *le_sleep, int secs, int mesaj)
{
  int scr2=8;
  WINDOW *w;
  w=newwin (scr2-1,25,7+((nrscr-scr2)/2),(nrcols-25)/2);
  wsetcolor (w,13,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,25,scr2-1);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," %s ",title);
  wsetcolor (w,12,0);
  mvwprintw (w,2,10,":   :");
  mvwprintw (w,4,7,"ENTER - set");
  mvwprintw (w,6,11," ESC - quit ");
  wrefresh(w);
  timeout(10);
  int key=-1;
  read_text hrs;
  read_text min;
  read_text sec;
  char s[1000];
  // -------- Time -------
    time (&currenttime);
    currenttime=currenttime+secs;
    tm *mytime;
    mytime=localtime (&currenttime);
    sprintf (s,"%.2d",mytime->tm_hour);
    strcpy (hrs.text,s);
    sprintf (s,"%.2d",mytime->tm_min);
    strcpy (min.text,s);
    sprintf (s,"%.2d",mytime->tm_sec);
    strcpy (sec.text,s);
    // free (mytime); //Fedora Core 1 problem
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
    if (curent==3) key=readstring_with_key (w,2,15,2,2,&sec,'\0',"0123456789",1);
  } while ((key!=0) && (key!=4));
  if (key==0) 
  {
    strcpy (le_sleep->time,"");
    le_sleep->mode=0;
  }
  if (key==4)
  {
    strcpy (le_sleep->time,hrs.text);
    strcat (le_sleep->time,":");
    strcat (le_sleep->time,min.text);
    strcat (le_sleep->time,":");
    strcat (le_sleep->time,sec.text);
    le_sleep->mode=1;
  }
  afiseaza_acum=mesaj;
}

void console(int scr)
{

}

void add_console_message(char *s)
{
  if (show_to_logs==1)
  {
    char temp[1000];
    strcpy (temp,s);
    strcpy (strtmp,getenv("HOME"));
    openlog ("LinuxEyes", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
    syslog (LOG_NOTICE,s);
    closelog();
  }
}

void showid3 (char *name, int shadow)
{
 int use_id3=1;
 int id3_plus=0;
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
  int scr2=14;
  if (shadow==1)
  {
    WINDOW *w1;
    w1=newwin (scr2+1,62,(6+(nrscr-scr2)/2)+1,(nrcols-62)/2);
    wrefresh (w1);
    werase (w1);
  }
  WINDOW *w;
  w=newwin (scr2-1,60,7+((nrscr-scr2)/2)+1,(nrcols-60)/2);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,60,scr2-1);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," ID3v1.1 Tag Editor");
  wsetcolor (w,12,0);
  mvwprintw (w,scr2-2,31," ENTER - save | ESC - quit ");
  wrefresh(w);
      wsetcolor (w,12,0);
      mvwhline (w,3,2,ACS_HLINE,56);
      mvwvline (w,1,15,ACS_VLINE,2);
      mvwprintw (w,4,2,"  TRACK: ");
      mvwprintw (w,5,2," ARTIST: ");
      mvwprintw (w,6,2,"   SONG: ");
      mvwprintw (w,7,2,"  ALBUM: ");
      mvwprintw (w,8,2,"   YEAR: ");
      mvwprintw (w,9,2,"  GENRE: ");
      mvwprintw (w,10,2,"COMMENT: ");
      mvwprintw (w,11,2,"   FILE: ");
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
	use_id3=0;
	id3_plus=0;
      }
      if (use_id3==1) if (my_id3.type==14) id3_plus=1;
      strcpy (e_artist.text,my_id3.artist);
      strcpy (e_comment.text,my_id3.comment);
      strcpy (e_song.text,my_id3.song);
      strcpy (e_album.text,my_id3.album);
      strcpy (e_year.text,my_id3.year);
      char s[3];
      sprintf (s,"%d",my_id3.track);
      strcpy (e_track.text,s);
      labelw (w,11,11,name,46);
  wrefresh(w);
  noecho();
  timeout (100);
  int v;
  int key=-1;
  int curent=6;
  int max_read=11; // nr of readstring_with_key boxes
  int max_read_now=11; // efectively max read
  int load_id3_plus=0;
  int save_id3_plus=0;
  int at=0;
  do
  {
      if (id3_plus==1) max_read=10;
      if (id3_plus==0) max_read=11;
      if (use_id3==1) max_read_now=max_read;
      if (use_id3==0) max_read_now=1;
//    messages();
//    v=getch();
      if (key==1) curent--;
      if (key==2) curent++;
      if (key==3) curent++;
      if ((my_id3.type!=14) && (curent==3)) if (key==1) curent--; else curent++;
      if ((id3_plus==0) && (curent==4)) if (key==1) curent--; else curent++;
      if ((my_id3.type!=14) && (curent==3)) if (key==1) curent--; else curent++;
      if ((id3_plus==0) && (curent==4)) if (key==1) curent--; else curent++;
      if (curent < 1) curent=max_read_now;
      if (curent > max_read_now) curent=1;
      // use id3 and id3+
      at=0;
      if (curent!=1) check_with_key (w,2,3,"ID3v1.1",use_id3,at);
      if (max_read_now>=2) at=0; else at=-1; if (curent!=2) check_with_key (w,2,17,"ID3 Plus",id3_plus,at);
      if ((my_id3.type==14) && (use_id3==1)) at=0; else at=-1; if (curent!=3) button_with_key (w,2,31,"Load +",load_id3_plus,at);
      if ((id3_plus==1) && (use_id3==1)) at=0; else at=-1; if (curent!=4) button_with_key (w,2,45,"Save +",save_id3_plus,at);
      //display texts;
      if (max_read_now>=5) at=0; else at=-1; if (curent!=5) readstring_with_key (w,4,11,2,2,&e_track,'\0',"0123456789",at);
      if (max_read_now>=6) at=0; else at=-1; if (curent!=6) readstring_with_key (w,5,11,30,30,&e_artist,'\0',NULL,at);
      if (max_read_now>=7) at=0; else at=-1; if (curent!=7) readstring_with_key (w,6,11,30,30,&e_song,'\0',NULL,at);
      if (max_read_now>=8) at=0; else at=-1; if (curent!=8) readstring_with_key (w,7,11,30,30,&e_album,'\0',NULL,at);
      if (max_read_now>=9) at=0; else at=-1; if (curent!=9) readstring_with_key (w,8,11,4,4,&e_year,'\0',"0123456789",at);
      if (max_read_now>=10) at=0; else at=-1; if (curent!=10) list_with_key (w,9,11,16,0,126,my_id3.genre,genres,at);
      if (max_read_now>=11) at=0; else at=-1; if (curent!=11) readstring_with_key (w,10,11,30,30,&e_comment,'\0',NULL,at);
      if (curent==1) key=check_with_key (w,2,3,"ID3v1.1",use_id3,1);
      if (curent==2) key=check_with_key (w,2,17,"ID3 Plus",id3_plus,1);
      if (curent==3) key=button_with_key (w,2,31,"Load +",load_id3_plus,1);
      if (curent==4) key=button_with_key (w,2,45,"Save +",save_id3_plus,1);
      if (curent==5) key=readstring_with_key (w,4,11,2,2,&e_track,'\0',"0123456789",1);
      if (curent==6) key=readstring_with_key (w,5,11,30,30,&e_artist,'\0',NULL,1);
      if (curent==7) key=readstring_with_key (w,6,11,30,30,&e_song,'\0',NULL,1);
      if (curent==8) key=readstring_with_key (w,7,11,30,30,&e_album,'\0',NULL,1);
      if (curent==9) key=readstring_with_key (w,8,11,4,4,&e_year,'\0',"0123456789",1);
      if (curent==10) key=list_with_key (w,9,11,16,0,126,my_id3.genre,genres,1);
      if (curent==11) key=readstring_with_key (w,10,11,30,30,&e_comment,'\0',NULL,1);
      my_id3.genre=list_result;
      if (load_id3_plus==1)
      {
        load_id3_plus=0;
	load_id3_plus_tag (my_id3.plus,1);
      }
      if (save_id3_plus==1)
      {
        save_id3_plus=0;
	my_id3.type=14;
	my_id3.comment[0]='\0';
	my_id3.plus[0]='\0';
	my_id3.plus[1]=-7;
	my_id3.plus[2]=(char)vol;
	my_id3.plus[3]=(char)pcm;
	my_id3.plus[4]=(char)balance;
	for (int i=0;i<=6;i++) 
	{
	  //my_id3.plus[i+5]=equalizer.left[i];
	  //my_id3.plus[i+15]=equalizer.right[i];
	}
	//my_id3.plus[12]=equalizer.left[8];
	//my_id3.plus[13]=equalizer.left[12];
	//my_id3.plus[14]=equalizer.left[20];
	//my_id3.plus[22]=equalizer.right[8];
	//my_id3.plus[23]=equalizer.right[12];
	//my_id3.plus[24]=equalizer.right[20];
      }
  } while ((key!=0) && (key!=4));
  if (id3_plus==1) my_id3.type=14; else my_id3.type=11;
  if (use_id3==0) my_id3.type=0;
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
  w=newwin (scr2-1,36,7+((nrscr-scr2)/2),(nrcols-36)/2);
  wsetcolor (w,13,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,36,scr2-1);
  wrefresh(w);
  mvwprintw (w,1,2,"%s",message);
  wrefresh (w);
  timeout(10);
  noecho();
  do
  {
    t=getch();
    messages();
    if ((try_again) && (t==ERR)) playnext();
    if (quit==1) t='q';
  } while (t==ERR);
  werase (w);
  wrefresh (w);
}

int show_timer (char *message, int timp)
{
  time_t timpul;
  int scr2=4;
  int t;
  WINDOW *w;
  w=newwin (scr2-1,36,7+((nrscr-scr2)/2),(nrcols-36)/2);
  wsetcolor (w,13,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,36,scr2-1);
  wrefresh(w);
  time (&timpul);
  mvwprintw (w,1,2,"%s %d second(s) ",message,timp-(currenttime-timpul));
  wrefresh (w);
  timeout(10);
  noecho();
  do
  {
    t=getch();
    messages();
    mvwprintw (w,1,2,"%s %d second(s) ",message,timp-(currenttime-timpul));
    wrefresh(w);
    if ((try_again) && (t==ERR)) playnext();
  } while ((t==ERR) && ((currenttime-timpul)<=timp));
  werase (w);
  wrefresh (w);
  if (t==ERR) return 1;
  else 
  {
    while (t!=ERR) t=getch();
    return 0;
  }
}

int check_with_key(WINDOW *w,int j,int i, char *text, int &res, int active)
{
  timeout(10);
  int key=-1;
  int t=0;
  do
  {
    wsetcolor (w,12,0);
    if (active==-1) wsetcolor (w,12,1);
    if (active==1) wsetcolor (w,2,1);
    mvwprintw (w,j,i,"[ ] %s",text);
    if (res==1) mvwprintw (w,j,i+1,"x");
    wrefresh (w);
    if (active == 1)
    do
    {
      t=getch();
      messages();
      //wsetcolor (w,7,1);
      wrefresh (w);
      if (active!=1) t=1000;
      if ((try_again) && (t==ERR)) playnext();
    } while (t==ERR);
    else t = 1000;
    if (t=='\n') key=4;
    if (t==9) key=3;
    if (t==27)
    {
      t=getch();
      if (t==91)
      {
        t=getch();
	if (t==65) key=1;
	if (t==66) key=2;
      } else 
      if (t == ERR) key=0;
    }
    if (t==' ') 
    {
      res=1-res;
      t=1000;
    }
  } while ((key!=0) && (key!=1) && (key!=2) && (key!=3) && (key!=4) && (t!=1000));
  return key;
}

int button_with_key(WINDOW *w,int j,int i, char *text, int &res, int active)
{
  timeout(10);
  int key=-1;
  int t=0;
  do
  {
    wsetcolor (w,12,0);
    if (active==-1) wsetcolor (w,12,1);
    if (active==1) wsetcolor (w,2,1);
    mvwprintw (w,j,i,"<< %s >>",text);
    wrefresh (w);
    if (active == 1)
    do
    {
      t=getch();
      messages();
      //wsetcolor (w,7,1);
      wrefresh (w);
      if (active!=1) t=1000;
      if ((try_again) && (t==ERR)) playnext();
    } while (t==ERR);
    else t = 1000;
    res=0;
    if (t=='\n') 
    {
      res=1;
      key=4;
    }
    if (t==9) key=3;
    if (t==27)
    {
      t=getch();
      if (t==91)
      {
        t=getch();
	if (t==65) key=1;
	if (t==66) key=2;
      } else 
      if (t == ERR) key=0;
    }
    if (t==' ') 
    {
      res=1;
      t=1000;
    }
  } while ((key!=0) && (key!=1) && (key!=2) && (key!=3) && (key!=4) && (t!=1000));
  return key;
}

int list_with_key(WINDOW *w,int j,int i, unsigned int l, int min, int max, char res, list lista, int active)
{
  i=i+1;
  char r;
  r=res;
  unsigned int k=0;
  int key=-1;
  unsigned int p=0;
  timeout(10);
  int t=0;
  do
  {
    if (r < min) r=min;
    if (r > max) r=max;
    if (active==0) wsetcolor (w,2,1);
    else if (active==-1) wsetcolor (w,12,1); 
    else wsetcolor (w,7,1);
    for (k=0;k<=l;k++) mvwprintw (w,j,i+k," ");
    for (k=p;k<strlen(lista[r]);k++) mvwprintw (w,j,i+k-p,"%c",lista[r][k]);
    wsetcolor (w,12,1);
    mvwprintw (w,j,i-1,"%c",ACS_LARROW);
    mvwprintw (w,j,i+l+1,"%c",ACS_RARROW);
    wrefresh (w);
    if (active == 1)
    do
    {
      t=getch();
      messages();
      if (active!=1) t=1000;
      if ((try_again) && (t==ERR)) playnext();
    } while (t==ERR);
    else t = 1000;
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

int list_nr_with_key(WINDOW *w,int j,int i, unsigned int l, int min, int max, int &res, int active)
{
  i=i+1;
  int r;
  r=res;
  unsigned int k=0;
  int key=-1;
  timeout(10);
  int t=0;
  do
  {
    if (r < min) r=min;
    if (r > max) r=max;
    if (!active) wsetcolor (w,2,1);
    else wsetcolor (w,7,1);
    for (k=0;k<=l;k++) mvwprintw (w,j,i+k," ");
    mvwprintw (w,j,i,"%d",r);
    wsetcolor (w,12,1);
    mvwprintw (w,j,i-1,"%c",ACS_LARROW);
    mvwprintw (w,j,i+l+1,"%c",ACS_RARROW);
    wrefresh (w);
    if (active == 1)
    do
    {
      t=getch();
      messages();
      if (active==0) t=1000;
      if ((try_again) && (t==ERR)) playnext();
    } while (t==ERR);
    else t = 1000;
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
  res=r;
  return key;
}

void label (int y, int x, char *text, int l)
{
 if (text!=NULL)
 {
  int puncte_puncte=0;
  int maxl;
  maxl=strlen (text);
  if (maxl > l-1)
  {
    maxl=l-4;
    puncte_puncte=1;
  }
  for (int j=0;j<=maxl-1;j++) 
  {
    if (char_ok(text[j])) mvprintw (y,x+j,"%c",text[j]);
    else mvprintw (y,x+j,"%c",ok_char);
  }
  if (puncte_puncte==1) mvprintw (y,x+maxl+1,"...");
 }
}

void labelw (WINDOW *w, int y, int x, char *text, int l)
{
 if (text!=NULL)
 {
  int puncte_puncte=0;
  int maxl;
  maxl=strlen (text);
  if (maxl > l-1)
  {
    maxl=l-4;
    puncte_puncte=1;
  }
  for (int j=0;j<=maxl-1;j++) 
  {
    if (char_ok(text[j])) mvwprintw (w,y,x+j,"%c",text[j]);
    else mvwprintw (w,y,x+j,"%c",ok_char);
  }
  if (puncte_puncte==1) mvwprintw (w,y,x+maxl+1,"...");
 }
}

int readstring_with_key (WINDOW *w,int j,int i, int l, int maxl, read_text *text, char pass, char *chars, int active)
{
  curs_set (1);
  int res=1;
  char memstring[1000];
  strcpy(memstring,"");
  strcat (memstring,text->text);
  if ((int)strlen (memstring) > maxl) memstring[maxl]='\0';
  int key=-1;
  int ln;
  int k=0;
  int p=0;
  int t=0;
  int pos=0;
  int m=0;
  wsetcolor (w,14,1);
  ln=strlen (memstring);
  if (ln > l) p=l;
  else p=ln;
  pos=ln+1;
  timeout(10);
  do
  {
    //ln=strlen (memstring);
    if (ln > l) p=l;
    else p=ln;
    if (m+pos > ln) pos--;
    if (pos > l) { m=m+(pos-l);pos=l; }
    if (pos < 0) { pos = 0; m--; }
    if (m<0) m=0;
    if (active==0) wsetcolor (w,2,1); 
    else if (active==-1) wsetcolor (w,12,1);
    else wsetcolor (w,7,1);
    for (k=0;k<=l;k++) mvwprintw (w,j,i+k," ");
    for (k=m;k<m+p;k++) if (pass=='\0') if (char_ok (memstring[k])) mvwprintw (w,j,i+k-m,"%c",memstring[k]);
                                                      else mvwprintw (w,j,i+k-m,"%c",ok_char);
                                      else mvwprintw (w,j,i+k-m,"%c",pass);
    wrefresh (w);
    if (active == 1)
    do
    {
      t=getch();
      messages();
      wsetcolor (w,7,1);
      if (active!=1) t=1000;
      else 
      {
        mvwprintw (w,j,i+pos,"");
        wrefresh (w);
      }
      if ((try_again) && (t==ERR)) playnext();
    } while (t==ERR);
    else t = 1000;
    if ((t!='\n') && (t!=127) && (t!=9) && (t!=27) && (t!=1000) && ((int)strlen (memstring) < maxl))
    {
      if (chars==NULL)
      {
        for (int h=ln;h>=m+pos;h--) memstring[h+1]=memstring[h];
        memstring[m+pos]=t;
        memstring[ln+1]='\0';
        ln++;
	pos++;
      }
      else if (index (chars,t)!=NULL)
      {
        for (int h=ln;h>=m+pos;h--) memstring[h+1]=memstring[h];
        memstring[m+pos]=t;
        memstring[ln+1]='\0';
        ln++;
	pos++;
      }
    }
    if (t==127)
    {
      if ((m+pos) > 0) 
      {
        for (int h=m+pos-1;h<=ln;h++) memstring[h]=memstring[h+1];
        memstring[ln]='\0';
        ln--;
	if (m>0) m--;
	else pos--;
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
	if (t==67) pos++;
	if (t==68) pos--;
	if (t==49)
	{
	  t=getch();
	  if (t==126) {m=0;pos=0;}
	}
	if (t==51)
	{
	  t=getch();
	  if (t==126) 
	  {
	    if ((m+pos) < ln) 
            {
              for (int h=m+pos;h<=ln;h++) memstring[h]=memstring[h+1];
	      memstring[ln]='\0';
	      ln--;
	      //m--;
//   	      pos--;
            }
	  }
	}
	if (t==52)
	{
	  t=getch();
	  if (t==126) 
	  {
	    if (ln > l) m=ln-l;
	    pos=p;
	  }
	}
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
  strcpy (text->text,memstring);
  curs_set(0);
  return key;
}

int readstring(WINDOW *w,int j,int i ,unsigned int l,char *text, char pass)
{
  int res=1;
  strcpy(memstring,"");
  if (text!=NULL) strcat (memstring,text);
  unsigned ln;
  unsigned int k=0;
  unsigned int p=0;
  int t=0;
  wsetcolor (w,14,1);
  timeout(100);
  do
  {
    ln=strlen (memstring);
    if (ln > l) p=ln-l;
    else p=0;
    wsetcolor (w,2,1);
    for (k=0;k<=l;k++) mvwprintw (w,j,i+k," ");
    for (k=p;k<strlen(memstring);k++) if (pass=='\0') mvwprintw (w,j,i+k-p,"%c",memstring[k]);
                                      else mvwprintw (w,j,i+k-p,"%c",pass);
    wrefresh (w);
    do
    {
      t=getch();
      messages();
      wsetcolor (w,7,1);
      mvwprintw (w,j,i+ln-p,"_");
      wrefresh (w);
      if ((try_again) && (t==ERR)) playnext();
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
  } while ((t!='\n') && (t!=9) && (t!=1000));
  return res;
}

int readstring_window(char *wintitle, char *title, int shadow, char pass, int path)
{
  int scr2=4;
  WINDOW *w1;
  if (shadow==1)
  {
    w1=newwin (scr2+1,64,(6+(nrscr-scr2)/2),(nrcols-64)/2);
    wrefresh (w1);
  }
  WINDOW *w;
  w=newwin (scr2-1,62,7+((nrscr-scr2)/2),(nrcols-62)/2);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                             ");
  wsetcolor (w,12,0);
  le_border (w,62,scr2-1);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," %s ",wintitle);
  wsetcolor (w,12,0);
  mvwprintw (w,scr2-3,2,title);
  wrefresh(w);
  char tempstring[1000];
  if (path==1) 
  {
    strcpy (tempstring,getenv("PWD"));
    strcat (tempstring,"/");
  }
  else strcpy (tempstring,memstring);
  read_text read_memstring;
  int res=-1;
  strcpy (read_memstring.text,tempstring);
  while ((res!=4) && (res!=0)) res=readstring_with_key (w,1,strlen(title)+3,56-strlen(title),1000, &read_memstring, pass, NULL, 1);
  strcpy (memstring,read_memstring.text);
  werase (w);
  wrefresh (w);
  if (shadow==1) 
  {
    werase (w1);
    wrefresh (w1);
  }
  if (res==4) res=1;
  if (res==0) strcpy (memstring,"");
  return res;
}

int search()
{
  int more=0;
  int reread=0;
  char tempstring[2000];
  const char *tokens = " ,.?!-";
  int sendcmd=-1;
  int cansend=0;
  char *found;
  char *tempstr;
  int ok;
  strcpy (memstring,"");
  readstring_window ("Search","Song",0,'\0',0);
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
      int scr2=nrscr-4;
      WINDOW *w1;
      w1=newwin (scr2+1,62,(6+(nrscr-scr2)/2),(nrcols-62)/2);
      wrefresh (w1);
      WINDOW *w;
      w=newwin (scr2-1,60,7+((nrscr-scr2)/2),(nrcols-60)/2);
      wsetcolor (w,12,0);
      for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
      wsetcolor (w,12,0);
      le_border (w,60,scr2-1);
      wsetcolor (w,13,1);
      mvwprintw (w,0,1," Songs List ");
      wsetcolor (w,12,0);
      mvwprintw (w,scr2-2,45," ESC - quit ");
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
	  labelw (w,i+1,2,filterlist[m+i].text,56);
	}
	wsetcolor (w,8,0);
	for (i=l+1;i<=scr2-4;i++) mvwprintw (w,i+1,2,"                                                        ");
	wrefresh(w);
        noecho();
	timeout(10);
	do
	{
	  t=getch();
	  messages();
	  if ((try_again) && (t==ERR)) playnext();
	} while ((t==ERR) && (reread==0));
	reread=0;
	if (t=='i') 
	{
	  showid3 (filelist[filterlist[m+k].nr].name,0);
	  position_refresh (filterlist[m+k].nr);
	  wsetcolor (w,12,0);
          le_border (w,60,scr2-1);
	  wsetcolor (w,13,1);
          mvwprintw (w,0,1," Songs List ");
          wsetcolor (w,12,0);
	  mvwprintw (w,scr2-2,45," ESC - quit ");
	}
	if (t==9) add_to_filter (filelist[filterlist[m+k].nr].name);
	if (t==27)
	{
	  t=getch();
	  if (t==ERR) t='q';
	  if (t==51)
	  {
	    showid3 (filelist[filterlist[m+k].nr].name,0);
	    position_refresh (filterlist[m+k].nr);
	    wsetcolor (w,12,0);
            le_border (w,60,scr2-1);
	    wsetcolor (w,13,1);
            mvwprintw (w,0,1," Songs List ");
            wsetcolor (w,12,0);
	    mvwprintw (w,scr2-2,45," ESC - quit ");
	  }
	  if (t==91)
	  {
	    t=getch();
	    if (t==65) k--;
	    if (t==66) k++;
	    if (t==53) more=-scr2+4;
	    if (t==54) more=scr2-4;
	  }
	}
	if (more < 0) {k=0; k--; more++; reread=1;}
        if (more > 0) {k=l; k++; more--; reread=1;}
	if (k < 0) if (m > 0) { k++;m--; }
        else k++;
        if ((m+k) > nr) k--;
	if (m<0) m=0;
        if (k > nrscr-8) { m++;k--; } 
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
  strcpy (memstring,"");
  return sendcmd;
}

void readurl()
{
  int scr2=4;
  WINDOW *w1;
  w1=newwin (scr2+1,62,(6+(nrscr-scr2)/2),(nrcols-62)/2);
  wrefresh (w1);
  WINDOW *w;
  w=newwin (scr2-1,60,7+((nrscr-scr2)/2),(nrcols-60)/2);
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
  add_console_message ("Saving playlist");
  if (t==1)
  {
    strcpy (memstring,"");
    readstring_window ("Save Playlist","Playlist",0,'\0',1);
  } else { if (strcmp(def_playlist,"")==0) { strcpy (memstring,getenv("HOME")); strcat (memstring,"/"); strcat (memstring,".linuxeyes.playlist"); } else strcpy (memstring,def_playlist); }
    if (strcmp(memstring,"")!=0)
    {
      strcpy (strtmp,"saveplaylist: filename \"");
      strcat (strtmp,memstring);
      strcat (strtmp,"\"");
      gzFile f;
      f=gzopen (memstring,"wb");
      if (f!=NULL)
      {
        char playlistinfo[7];
	strcpy (playlistinfo,playlist_type);
	gzwrite (f,&playlistinfo,sizeof(playlistinfo));
	gzwrite (f,&n,sizeof(n));
        int i=0;
        for (i=0;i<=n;i++) gzwrite (f,&filelist[i],sizeof(filelist[i]));
        gzclose (f);
	add_console_message ("Playlist saved");
      } else add_console_message ("Faild to save playlist");
      strcpy (playlistfile,memstring);
    } else add_console_message ("Save of playlist aborted");
}

void fileentry (int nr)
{
  strcpy (memstring,filelist[nr].name);
  readstring_window ("Playlist Entry","MP3 File",1,'\0',0);
  if (strcmp(memstring,"")!=0) strcpy (filelist[nr].name,memstring);
}

void lista_de_mesaje ()
{
  LElist lista_mesaje (messagesfile,"Messages List",8);
  if (lista_mesaje.show(nrcols-18,nrscr-1)==10000) lista_mesaje.save_list_to_file ();
}

void definekeys (int scr)
{

}

void set_equ(char *preset)
{
  /*XA_EqualizerInfo equalizer2;
  strcpy (strtmp,getenv("HOME"));
      strcat (strtmp,"/.linuxeyes.eq");
      if (load_equ_preset (strtmp,preset))
      {
        for (int i=0;i<=6;i++) 
	{
          equalizer2.left[i]=imported_eq_preset[i];
          equalizer2.right[i]=imported_eq_preset[i];
        }
  	  equalizer2.left[8]=imported_eq_preset[7];
  	  equalizer2.right[8]=imported_eq_preset[7];
	  equalizer2.left[12]=imported_eq_preset[8];
	  equalizer2.right[12]=imported_eq_preset[8];
	  equalizer2.left[20]=imported_eq_preset[9];
          equalizer2.right[20]=imported_eq_preset[9];
	  
	  equalizer2.left[7]=equalizer2.left[6];
          equalizer2.right[7]=equalizer2.right[6];
          for (int i=9;i<=11;i++)
          {
            equalizer2.left[i]=equalizer2.left[8];
            equalizer2.right[i]=equalizer2.right[8];
          }
          for (int i=12;i<=19;i++)
          {
            equalizer2.left[i]=equalizer2.left[12];
            equalizer2.right[i]=equalizer2.right[12];
          }
          for (int i=21;i<=31;i++)
          {
            equalizer2.left[i]=equalizer2.left[31];
            equalizer2.right[i]=equalizer2.right[31];
          }
          for (int i=0;i<=31;i++)
          {
            if (equalizer2.left[i]>126) equalizer2.left[i]=126;
            if (equalizer2.left[i]<-127) equalizer2.left[i]=-127;
            if (equalizer2.right[i]>126) equalizer2.right[i]=126;
            if (equalizer2.right[i]<-127) equalizer2.right[i]=-127;
          }
	  
	  control_message_send (player, XA_MSG_SET_CODEC_EQUALIZER, &equalizer2);
      }*/
}

void load_id3_plus_equ(char *id3_plus, int unde)
{
  /*XA_EqualizerInfo equalizer2;
  for (int i=5;i<=11;i++) 
	{
          equalizer2.left[i-5]=id3_plus[i];
          equalizer2.right[i-5]=id3_plus[i+10];
        }
  	  equalizer2.left[8]=id3_plus[12];
  	  equalizer2.right[8]=id3_plus[22];
	  equalizer2.left[12]=id3_plus[13];
	  equalizer2.right[12]=id3_plus[23];
	  equalizer2.left[20]=id3_plus[14];
          equalizer2.right[20]=id3_plus[24];
	  
	  equalizer2.left[7]=equalizer2.left[6];
          equalizer2.right[7]=equalizer2.right[6];
          for (int i=9;i<=11;i++)
          {
            equalizer2.left[i]=equalizer2.left[8];
            equalizer2.right[i]=equalizer2.right[8];
          }
          for (int i=12;i<=19;i++)
          {
            equalizer2.left[i]=equalizer2.left[12];
            equalizer2.right[i]=equalizer2.right[12];
          }
          for (int i=21;i<=31;i++)
          {
            equalizer2.left[i]=equalizer2.left[31];
            equalizer2.right[i]=equalizer2.right[31];
          }
          for (int i=0;i<=31;i++)
          {
            if (equalizer2.left[i]>126) equalizer2.left[i]=126;
            if (equalizer2.left[i]<-127) equalizer2.left[i]=-127;
            if (equalizer2.right[i]>126) equalizer2.right[i]=126;
            if (equalizer2.right[i]<-127) equalizer2.right[i]=-127;
          }
	  
	  control_message_send (player, XA_MSG_SET_CODEC_EQUALIZER, &equalizer2);
  if (unde==1)
  {
    def_eq=equalizer2;
    equalizer=equalizer2;
  }*/
}

void load_id3_plus_tag(char *id3_plus, int unde)
{
  load_id3_plus_equ(id3_plus, unde);
  //control_message_send (player,XA_MSG_SET_OUTPUT_VOLUME,(int)id3_plus[4],(int)id3_plus[3],(int)id3_plus[2]);
  if (unde==1)
  {
    vol=(int)id3_plus[2];
    pcm=(int)id3_plus[3];
    balance=(int)id3_plus[4];
  }
}

void restore_equ()
{
  //equalizer=def_eq;
  //control_message_send (player, XA_MSG_SET_CODEC_EQUALIZER, &equalizer);
}

void save_equ()
{
  //def_eq=equalizer;
}

void equ(int scr)
{
  /*
  restore_equ();
  //control_message_send (player, XA_MSG_GET_CODEC_EQUALIZER);
  int v,k;
  WINDOW *w1;
  w1=newwin (scr+2,62,(nrscr-(scr+2))/2+7,(nrcols-62)/2);
  wrefresh (w1);
  werase (w1);
  WINDOW *w;
  w=newwin (scr,60,(nrscr-(scr+2))/2+8,(nrcols-60)/2);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr+2;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,60,scr);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Equalizer ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr-1,46," ESC - quit ");
  wrefresh(w);
  noecho();
  timeout(10);
  k=0;
  do
  {
    wsetcolor (w,12,0);
    le_border (w,60,scr);
    wsetcolor (w,13,1);
    if (auto_equ==1) mvwprintw (w,0,1," Equalizer (Automatic) ");
    if (auto_equ==0) mvwprintw (w,0,1," Equalizer ");
    wsetcolor (w,12,0);
    mvwprintw (w,scr-1,46," ESC - quit ");
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
      if ((try_again) && (v==ERR)) playnext();
    } while (v==ERR);
    v=getkey(v);
    if (v==10011)
    {
      if (eq.left<127) eq.left++;
      if (eq.right<127) eq.right++;
      for (int i=0;i<=31;i++) { equalizer.left[i]++; equalizer.right[i]++; }
    }
    if (v==10012)
    {
      if (eq.left>-128) eq.left--;
      if (eq.right>-128) eq.right--;
      for (int i=0;i<=31;i++) { equalizer.left[i]--; equalizer.right[i]--; }
    }
    if (v==10001) v='q';
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
    if (v=='A') auto_equ=1-auto_equ;
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
      strcpy (memstring,"");
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
	    showfiles (scr,78,".","Select an XMMS eq presets file to import",0,".");
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
	    showfiles (scr,78,".","Select a Winamp eq presets file to import",0,".");
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
    //control_message_send (player, XA_MSG_SET_CODEC_EQUALIZER, &equalizer);
  }
  while (v!='q');
  save_equ();
  werase (w);
  reread=1;
  */
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
  strcpy(filelist[i].text,text);
  filelist[i].min=min;
  filelist[i].sec=sec;
  n++;
}

void adddir (char *dir)
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
      strcpy(temp.name,dir); 
      strcat(temp.name,namelist[i]->d_name);
      addfile (temp.name);
    }
    wsetcolor (w,12,0);
    mvwprintw (w,1,2,"Loading files %d%% ",((nrfiles-i)*100)/nrfiles);
    wrefresh(w);  
  }    
  reread=1;
  werase (w);
}

void main_options()
{
  int scr=20; //dimensiunea ecranului
  WINDOW *w1;
  w1=newwin (scr+2,72,(nrscr+9-(scr+2))/2+0,(nrcols-72)/2);
  wrefresh (w1);
  werase (w1);
  WINDOW *w;
  w=newwin (scr,70,(nrscr+9-(scr+2))/2+1,(nrcols-70)/2);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr+2;h++) mvwprintw (w,h,0,"                                                                      ");
  wsetcolor (w,12,0);
  le_border (w,70,scr);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," LinuxEyes Settings ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr-1,41," ENTER - save | ESC - quit ");
  wrefresh(w);
  timeout(10);
  int key=-1;
  int curent=1;
  const int max_options=18;
  //get settings
  int get_time=current_timeformat;
  int get_shuffle=rnext;
  int get_autoeq=auto_equ;
  int get_filter=persistent_filter;
  int get_save_pos=save_pos;
  int get_auto_goto=auto_goto;
  int get_scr_autodetect=scr_autodetect;
  int get_show_playlist_numbers=show_playlist_numbers;
  int get_use_id3_plus=use_id3_plus;
  int get_show_system_messages=show_system_messages;
  int get_show_file_messages=show_file_messages;
  int get_clock_speed=clock_speed;
  read_text get_ok_char;
  get_ok_char.text[0]=ok_char;
  get_ok_char.text[1]='\0';
  read_text get_playlist;
  read_text get_text_format;
  read_text get_messages_file;
  strcpy (get_playlist.text,def_playlist);
  strcpy (get_text_format.text,text_format);
  strcpy (get_messages_file.text,messagesfile);
  int get_screensaver_time=screensaver_time;
  int get_shut_down_time=shut_down_timer;
  //settings
  do
  {
    // Titles
    wsetcolor (w,12,0);
    mvwprintw (w,1,2,"------------------------------------------------------------------");
    mvwprintw (w,3,2,"------------------------------------------------------------------");
    mvwprintw (w,11,2,"------------------------------------------------------------------");
    mvwprintw (w,13,2,"------------------------------------------------------------------");
    mvwprintw (w,15,2,"------------------------------------------------------------------");
    wsetcolor (w,13,1);
    mvwprintw (w,1,5," Display ");
    mvwprintw (w,3,5," Playlist ");
    mvwprintw (w,11,5," Equalizer ");
    mvwprintw (w,13,5," Screen Saver ");
    mvwprintw (w,15,5," Messages Bar ");
    // Texts
    wsetcolor (w,12,0);
    mvwprintw (w,7,2,"Songs display format");
    mvwprintw (w,8,2,"Auto save playlist to");
    mvwprintw (w,9,2,"Replace undisplayable charcaters with");
    mvwprintw (w,10,2,"Shut down warning time");
    mvwprintw (w,14,2,"Start screen saver after");
    mvwprintw (w,17,2,"Take messages from");
    mvwprintw (w,14,34,"minutes (0 = Off)");
    mvwprintw (w,18,2,"Scrolling speed");
    // Display
    wsetcolor (w,12,0);
    mvwprintw (w,2,2,"Time display format");
    if (curent!=1) list_with_key (w,2,22,12,0,4,get_time,time_display,0);
    if (curent!=2) check_with_key (w,2,40,"Autodetect screen size",get_scr_autodetect,0);
    // Playlist
    if (curent!=3) check_with_key (w,4,2,"Random next song",get_shuffle,0);
    if (curent!=4) check_with_key (w,5,2,"Autolocate current song",get_auto_goto,0);
    if (curent!=5) check_with_key (w,6,2,"Show song's numbers",get_show_playlist_numbers,0);
    if (curent!=6) check_with_key (w,4,32,"Use persistent filter",get_filter,0);
    if (curent!=7) check_with_key (w,5,32,"Save playlist position on exit",get_save_pos,0);
    if (curent!=8) check_with_key (w,6,32,"Use ID3 Plus information",get_use_id3_plus,0);
    if (curent!=9) readstring_with_key (w,7,23,41,150,&get_text_format,'\0',NULL,0);
    if (curent!=10) readstring_with_key (w,8,24,40,500,&get_playlist,'\0',NULL,0);
    if (curent!=11) readstring_with_key (w,9,40,1,1,&get_ok_char,'\0',NULL,0);
    if (curent!=12) list_nr_with_key (w,10,25,3,0,60*3,get_shut_down_time,0);
    // Equalizer
    if (curent!=12) check_with_key (w,12,2,"Use automatic equalization",get_autoeq,0);
    // Screen Saver
    if (curent!=14) list_nr_with_key (w,14,27,3,0,60*24,get_screensaver_time,0);
    // Messages Bar
    if (curent!=15) key=check_with_key (w,16,2,"Show system messages",get_show_system_messages,0);
    if (curent!=16) key=check_with_key (w,16,32,"Show messages from file",get_show_file_messages,0);
    if (curent!=17) key=readstring_with_key (w,17,21,41,150,&get_messages_file,'\0',NULL,0);
    if (curent!=18) list_nr_with_key (w,18,18,3,1,100,get_clock_speed,0);
    //Playlist
    if (curent==1) 
    {
      key=list_with_key (w,2,22,12,0,4,get_time,time_display,1);
      get_time=list_result;
    }
    if (curent==2) key=check_with_key (w,2,40,"Autodetect screen size",get_scr_autodetect,1);
    if (curent==3) key=check_with_key (w,4,2,"Random next song",get_shuffle,1);
    if (curent==4) key=check_with_key (w,5,2,"Autolocate current song",get_auto_goto,1);
    if (curent==5) key=check_with_key (w,6,2,"Show song's numbers",get_show_playlist_numbers,1);
    if (curent==6) key=check_with_key (w,4,32,"Use persistent filter",get_filter,1);
    if (curent==7) key=check_with_key (w,5,32,"Save playlist position on exit",get_save_pos,1);
    if (curent==8) key=check_with_key (w,6,32,"Use ID3 Plus information",get_use_id3_plus,1);
    if (curent==9) key=readstring_with_key (w,7,23,41,150,&get_text_format,'\0',NULL,1);
    if (curent==10) key=readstring_with_key (w,8,24,40,255,&get_playlist,'\0',NULL,1);
    if (curent==11) key=readstring_with_key (w,9,40,1,1,&get_ok_char,'\0',NULL,1);
    if (curent==12) key=list_nr_with_key (w,10,25,3,0,60*3,get_shut_down_time,1);
    // Equalizer
    if (curent==13) key=check_with_key (w,12,2,"Use automatic equalization",get_autoeq,1);
    // Screen Saver
    if (curent==14) key=list_nr_with_key (w,14,27,3,0,24*60,get_screensaver_time,1);
    // Messages Bar
    if (curent==15) key=check_with_key (w,16,2,"Show system messages",get_show_system_messages,1);
    if (curent==16) key=check_with_key (w,16,32,"Show messages from file",get_show_file_messages,1);
    if (curent==17) key=readstring_with_key (w,17,21,41,150,&get_messages_file,'\0',NULL,1);
    if (curent==18) key=list_nr_with_key (w,18,18,3,1,100,get_clock_speed,1);
    if (key==1) curent--;
    if (key==2) curent++;
    if (key==3) curent++;
    if (curent<1) curent=max_options;
    if (curent>max_options) curent=1;
  } while ((key!=0) && (key!=4));
  //set settings
  if (key==4)
  {
    current_timeformat=get_time;
    rnext=get_shuffle;
    auto_equ=get_autoeq;
    persistent_filter=get_filter;
    save_pos=get_save_pos;
    auto_goto=get_auto_goto;
    use_id3_plus=get_use_id3_plus;
    strcpy (def_playlist,get_playlist.text);
    strcpy (text_format,get_text_format.text);
    strcpy (messagesfile,get_messages_file.text);
    ok_char=get_ok_char.text[0];
    shut_down_timer=get_shut_down_time;
    screensaver_time=get_screensaver_time;
    scr_autodetect=get_scr_autodetect;
    show_playlist_numbers=get_show_playlist_numbers;
    show_system_messages=get_show_system_messages;
    show_file_messages=get_show_file_messages;
    clock_speed=get_clock_speed;
  }
  reset();
  reread=1;
}

void playlistoptions()
{
  int scr2=11;
  int t=0;
  WINDOW *w;
  w=newwin (scr2-1,25,7+((nrscr-scr2)/2),(nrcols-25)/2);
  wsetcolor (w,13,0);
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
  mvwprintw (w,9,10," ESC - quit ");
  wrefresh(w);
  timeout(10);
  do
  {
    do
    {
      messages();
      t=getch();
      if ((try_again) && (t==ERR)) playnext();
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
      showfiles (nrscr-1,nrcols,".","Select a playlist to load",0,".");
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
      savelist(memstring,1);
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
        showfiles (nrscr-1,nrcols,".","Select a playlist to import",0,".");
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
	readstring_window ("Export Playlist","Filename",1,'\0',1);
	if (strcmp (memstring,"")!=0)
	{
	  if (format==1) export2xmms (memstring);
	  if (format==2) export2le3 (memstring);
	  if (format==3) export2le5 (memstring);
	  if (format==4) export2m3u (memstring);
	}
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
	filelist[i]=filelist[n-i];
	filelist[n-i]=temp;
      }
      t='q';
    }
    if (t==27)
    {
      t=getch();
      if (t==ERR) t='q';
    }
    if ((try_again) && (t==ERR)) playnext();
    if (quit==1) t='q';
  } while (t!='q');
  reread=1;
}

void loadfilter (char *name, int cl)
{
  if (name!=NULL)
  {
    if (cl==1) filternr=-1;
    std::ifstream f;
    f.open (name);
    if (!f.fail())
    {
      char s[1000];
      if (!f.eof()) f.getline (s,sizeof (s));
      if (strcmp (s,"LEF10")==0)
      while (!f.eof())
      {
        f.getline (s,sizeof (s));
        if (s!=NULL) if (!infilter(s)) add_to_filter (s); 
      }
      f.close ();
    }
  }
}

void savefilter (char *name)
{
  if (name!=NULL)
  {
    std::ofstream f;
    f.open (name);
    if (!f.fail())
    {
      f <<"LEF10" <<endl;
      for (int i=0;i<=filternr;i++) f <<filesfilter[i] <<endl;
      f.close ();
    }
  }
}

void filteroptions()
{
  int scr2=11;
  int t=0;
  WINDOW *w;
  w=newwin (scr2-1,25,7+((nrscr-scr2)/2),(nrcols-25)/2);
  wsetcolor (w,13,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,25,scr2-1);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Filter Options ");
  wsetcolor (w,12,0);
  mvwprintw (w,2,2,"c : Clear");
  mvwprintw (w,3,2,"p : Toggle persistent");
  mvwhline (w,4,1,ACS_HLINE,23);
  mvwprintw (w,5,2,"a : Add");
  mvwprintw (w,6,2,"l : Load");
  mvwprintw (w,7,2,"s : Save");
  mvwprintw (w,9,10," ESC - quit ");
  wrefresh(w);
  timeout(10);
  do
  {
    do
    {
      messages();
      t=getch();
      if ((try_again) && (t==ERR)) playnext();
    } while (t==ERR);
    if (t=='c')
    {
      filternr=-1;
      t='q';
    }
    if (t=='p') 
    {
      persistent_filter=1-persistent_filter;
      t='q';
    }
    if (t=='a')
    {
      werase (w);
      wrefresh (w);
      showfiles (nrscr-1,nrcols,".","Select a filter to add",0,".");
      if (mpegnumber > -1)
      {
        loadfilter(mpegfile[0],0); 
	reread=1;
      }
      t='q';
    }
    if (t=='l')
    {
      werase (w);
      wrefresh (w);
      showfiles (nrscr-1,nrcols,".","Select a filter to load",0,".");
      if (mpegnumber > -1)
      { 
        loadfilter (mpegfile[0],1);
        reread=1;
      }
      t='q';
    }
    if (t=='s')
    {
      werase (w);
      wrefresh (w);
      readstring_window ("Save Filter","Filename",1,'\0',1);
      if (strcmp (memstring,"")!=0) savefilter(memstring);
      t='q';
    }
    if (t==27)
    {
      t=getch();
      if (t==ERR) t='q';
    }
    if ((try_again) && (t==ERR)) playnext();
    if (quit==1) t='q';
  } while (t!='q');
  reread=1;
}

void playlist ()
{
    time(&last_key_time);
    add_console_message ("Playlist started");
    strcpy (next.text,"");
    int v;
    setcolor (1,0);
    mvprintw (dx,1,"Artist: ");
    mvprintw (dx+1,1,"  Song: ");
    setcolor (1,1);
    mvhline (6,0,ACS_HLINE,nrcols+2);
    mvhline (nrscr+8,0,ACS_HLINE,nrcols+2);
    char tempstring[100];
    strcpy (tempstring,getenv("HOME"));
    strcat (tempstring,"/");
    strcat (tempstring,".linuxeyes.playlist");
    n = loadlist (tempstring);
    if (showhello==1) if (fileexists("/usr/lib/linuxeyes/music/linuxeyes.mp3")) addfile ("/usr/lib/linuxeyes/music/linuxeyes.mp3");
    if (autoplay==true) play(curent.name);
    setcolor (1,0);
    if (n > nrscr) l=nrscr;
    else l=n;
    do
    {
      for (int j=0;j<=nrcols+3;j++)
      {
        mvprintw (6,j," ");        
        mvprintw (nrscr+8,j," ");        
      }
      if (nrcols != old_nrcols) resettime();
      setcolor (1,1);
      mvhline (6,0,ACS_HLINE,nrcols+2);
      mvhline (nrscr+8,0,ACS_HLINE,nrcols+2);
      for (int j=0;j<=nrcols+2;j++)
      {
        mvprintw (nrscr+7,j," ");        
        mvprintw (nrscr+9,j," ");        
        mvprintw (nrscr+10,j," ");        
      }
      if ((song_changed==1) && (auto_goto==1))
      {
        song_changed=0;
	m=getcurent()-(nrscr/2);
	k=(nrscr/2);
      }
      if (more < 0) {k=0; more++;m--; reread=1;}
      if (more > 0) {k=l; more--;if ((m+k) < n) m++; reread=1;}
      if (k < 0) { m--;k++; }
      if (k > nrscr) { m++;k--; }
      if (m < 0) {m=0; k=0;}
      if (((m+nrscr) > n) && (n > nrscr)) {k=nrscr; m=n-k;}
      if (k > n) k=n;
      for (int i=0;i<=l;i++) 
      {
        int color=1;
	int t=1;
	if (strcmp (filelist[m+i].name,curent.name)==0) 
	{
	  color = 6;
	  if (refresh_curent==1) position_refresh (m+i);
	}
	if (infilter (filelist[m+i].name)) color=15;
	if (strcmp (filelist[m+i].name,next.name)==0) color = 4;
	if (i==k) color++;
	if (!(fileexists(filelist[m+i].name))) t=0;
	setcolor (color,t);
	int j=0;
	for (j=1;j<=nrcols;j++) mvprintw (7+i,j," ");
	int nr_t;
	if (show_playlist_numbers==1)
	{
	  mvprintw (7+i,1,"%d.",m+i+1);
	  if (m+i+1 <= 9) nr_t=4;
	  else
	  if (m+i+1 <= 99) nr_t=5;
	  else
	  if (m+i+1 <= 999) nr_t=6;
	  else
	  if (m+i+1 <= 9999) nr_t=7;
	  else
	  if (m+i+1 >= 10000) nr_t=8;
	} else nr_t=1;
	label (7+i,nr_t,filelist[m+i].text,nrcols-7-nr_t);
	if ((filelist[m+i].min!=0) || (filelist[m+i].sec != 0)) mvprintw (7+i,nrcols-5," %.2d:%.2d",filelist[m+i].min,filelist[m+i].sec);
	setcolor (1,0);
	mvprintw (7+i,nrcols+1,"  ");
      }
      refresh_curent=0;
      setcolor (1,0);
      for (int i=l+1;i<=nrscr;i++) 
        for (int j=1;j<=nrcols+2;j++) mvprintw (7+i,j," ");
      setcolor (1,1);
      mvhline (nrscr+8,0,ACS_HLINE,nrcols+2);
      setcolor (1,0);
      if (n > nrscr) l=nrscr;
      else l=n;
      char s[7];
      strcpy (s,"Normal   ");
      if (rnext==1) strcpy (s,"Shuffle  ");
      if (filternr>-1) strcpy (s,"Filter   ");
      if ((filternr>-1) && (persistent_filter))strcpy (s,"P-Filter ");
      if (strcmp (next.name,"")!=0) strcpy (s,"Next Song");
      if (password==1) strcpy (s,"Password ");
      if (le_sleep.mode==1) strcpy (s,"Sleep    ");
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
      char flags[7];
      char radioontext[10], radioofftext[10], shutdowntext[100];
      strcpy (radioontext," Disabled ");
      strcpy (radioofftext," Disabled ");
      strcpy (shutdowntext,"Disabled");
      if (radio_on.mode==1) strcpy (radioontext,radio_on.time);
      if (radio_off.mode==1) strcpy (radioofftext,radio_off.time);
      if (le_sleep.mode==1) strcpy (shutdowntext,le_sleep.time);
      if (nclose==1) strcpy (shutdowntext,"After this song");
      if (save_pos) flags[0]='S'; else flags[0]='-';
      if (auto_equ) flags[1]='E'; else flags[1]='-';
      if (auto_goto) flags[2]='L'; else flags[2]='-';
      if (persistent_filter) flags[3]='P'; else flags[3]='-';
      if ((radio_on.mode==1) || (radio_off.mode==1)) flags[4]='A'; else flags[4]='-';
      if (use_id3_plus==1) flags[5]='+'; else flags[5]='-';
      flags[6]='\0';
      char stat_bar[1000];
      if (status_bar==0) sprintf (stat_bar,"%s | Volume[%d] | Pcm[%d] | Balance[%d] | %s |",s,vol,pcm,balance-50,flags);
      if (status_bar==1) sprintf (stat_bar,"Next Song: %s",next.text);
      if (status_bar==2) sprintf (stat_bar,"Filter: %d file(s)",filternr+1);
      if (status_bar==3) sprintf (stat_bar,"Alarm | Start: %s | Stop: %s",radioontext,radioofftext);
      if (status_bar==4) sprintf (stat_bar,"Shut Down At: %s",shutdowntext);
      label (nrscr+9,1,stat_bar,nrcols);
      setcolor (1,1);
      if (tunknown==0) mvprintw (nrscr+9,nrcols-7,"%.2d:%.2d:%.2d",thour,tmin,tsec);
      else mvprintw (nrscr+9,nrcols-8,"~%.2d:%.2d:%.2d",thour,tmin,tsec);
      refresh();
      noecho();
      if (showhello==1)
      {
        showhello=0;
	hello();
      }
      timeout(10);
      do 
      {
        if (reread==1) time (&last_key_time);
        v=getch();
	messages();
	if (((currenttime-last_key_time) > (screensaver_time*60)) && (screensaver_time>0))
	{
	  if (strcmp(passwordstr,"")!=0) password=1;
	  clear();
	  refresh();
	  screen_clock();
	  reset ();
	  time(&last_key_time);
	}
	if (playerror == 1) { playerror=0; try_again=1; }
	if ((v!=ERR) && (password==1))
	{
	  strcpy (memstring,"");
	  if (readstring_window ("Unlock Display","Password",1,'*',0)) if (strcmp (passwordstr,memstring)==0) 
	  { 
	    password=0; 
	    reread=1;
	  }
	  v=ERR;
	  time (&last_key_time);
	}
	if ((try_again) && (v==ERR)) playnext();
      } while ((v==ERR) && (reread==0) && (password==0)); 	
      if ((reread==0) && (password==0)) time (&last_key_time);
      reread=0;
      v=getkey (v); //get real key
      if (v>=10000)
      {
        // Enter
	if (v==10000) { nr_prev++; strcpy (prev[nr_prev],curent.name); strcpy (curent.name,filelist[m+k].name); play (curent.name); position_refresh (m+k); }
        // Volum
        if (v==10010) if (pcm > 0) {pcm--; setvolumes (vol,pcm,balance); }
        if (v==10009) if (pcm < 100) {pcm++; setvolumes (vol,pcm,balance); }
        if (v==10008) if (vol > 0) {vol--; setvolumes (vol,pcm,balance);}
        if (v==10007) if (vol < 100) {vol++; setvolumes (vol,pcm,balance);}
	// Filtru
        if (v==10013) add_to_filter (filelist[m+k].name);
	// Ajutor
        if (v==10014) help(nrscr-1);
	if (v==10015) 
	{
	  LElist lista_mesaje ((char*)whats_new_file,"What's New",8);
	  lista_mesaje.set_read_only (1);
	  lista_mesaje.show(nrcols-18,nrscr-1);
	}
	// Cautare
        if (v==10016) 
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
	// Definire taste functionale
        if (v==10025) { definekeys(nrscr-1); reread=1; }
	// ESC
	if (v==10001)
	{
	  if (strcmp(passwordstr,"")!=0) password=1;
	  screen_clock ();
	  reset ();
	  time (&last_key_time);
	  reread=1;
	}
	// Sageti
	if (v==10002) k--; 
	if (v==10003) k++; 
	if (v==10005) position(1);
        if (v==10004) position(-1);
        if (v==10011) more=-nrscr;
        if (v==10012) more=nrscr;
	// ALT + ...
	int v1=v-20000;
	if (v1>0)
	{
	  if (v1=='Q') quit=1;
	  if (v1=='3') { showid3 (filelist[m+k].name,1); position_refresh (m+k); }
	}
      } else
      {
        if (v=='h') help(nrscr-1);
        if (v=='!') password=1;
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
        if (v=='@')
        {
          nrscr=LINES-10;
          nrcols=COLS-2;
	  reset ();
        }
        if (v=='\\')
        {
          int allow=0;
	  strcpy (memstring,"");
          if (strcmp (passwordstr,"") != 0) if (readstring_window ("Enter OLD Password","Password",1,'*',0)) if (strcmp (memstring,passwordstr)==0) allow=1;
	  else; else; else allow=1;
	  if (allow == 1)
	  {
	    strcpy (memstring,"");
            if (readstring_window ("Enter NEW Password","Password",1,'*',0))
            {
              char temp[100];
              strcpy (temp,memstring);
	      strcpy (memstring,"");
              if (readstring_window ("Retype NEW Password","Password",1,'*',0)) if (strcmp (temp,memstring)==0) 
	      {
	        strcpy (passwordstr,memstring);
	        show_msg ("Password Changed");
	      } else show_msg ("Passwords don\'t match");
            }
	  }
        }
        if (v=='?') about(nrscr-1);
	if (v=='m') 
	{
	  readstring_window ("Quick Message","Message",0,'\0',0);
	  if (strcmp (memstring,"")!=0) 
	  {
	    add_mesaje (memstring);
	    strcpy (memstring,"");
	  }
	}
	if (v=='M') lista_de_mesaje();
        if (v==';') save_pos=1-save_pos;
        if (v=='A') auto_equ=1-auto_equ;
        if (v=='=') status_bar=(status_bar+1)%5;
        if (v=='t') { current_timeformat=(current_timeformat+1)%nr_timeformat; }
        if (v=='i') { showid3 (filelist[m+k].name,1); position_refresh (m+k); }
        if (v=='I') { showid3 (curent.name,1); refresh_curent=1; reread=1; }
        if (v==' ') { if (strcmp (next.name,filelist[m+k].name)!=0) { strcpy (next.name,filelist[m+k].name); strcpy (next.text,filelist[m+k].text); afiseaza_acum=1; } else { strcpy (next.name,"");strcpy (next.text,""); }}
        if (v=='T') set_sleep("Shut Down At", &le_sleep, 3600, 4);
        if (v=='{') set_sleep("Start Music At", &radio_on, 0, 5);
        if (v=='}') set_sleep("Stop Music At", &radio_off, 0, 6);
        if (v=='f') filteroptions(); //persistent_filter=1-persistent_filter;
        if (v=='r') { if (strcmp (next.name,curent.name)!=0) { strcpy (next.name,curent.name); strcpy (next.text,curent.text); } else { strcpy (next.name,""); strcpy (next.text,""); }}
        if (v=='Z') 
        {
          int p=getcurent()-1;
          if (p > -1) { nr_prev++; strcpy (prev[nr_prev],curent.name); strcpy (curent.name,filelist[p].name); play (curent.name); position_refresh(p); }
        }
        if (v=='B') 
        {
          int p=getcurent()+1;
          if (p < n+1) { nr_prev++; strcpy (prev[nr_prev],curent.name); strcpy (curent.name,filelist[p].name); play (curent.name); position_refresh(p); }
        }
        if (v=='z') playprev();
        if (v=='x') play (curent.name);
        if (v=='c') mpegpause ();
        if (v=='v') stop ();
        if (v=='b') playnext();
        if (v=='s') rnext=!rnext;
        if (v=='E') fileentry (m+k);
        if (v=='e') equ(14);
        if (v=='o') main_options();
        if (v=='d') {deletefile (m+k); if (((m+nrscr) > n) && (n > nrscr)) m--;}
        if (v=='S') { sort (0,n); getcurent();}
        if (v=='`') reset();
	if (v=='Q') quit = 1;
        if (v=='R') {k=-1; m=0; n=-1; l=-1;}
        if (v=='>') position(5);
        if (v=='<') position(-5);
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
        if (v=='P') jazzpiper();
        if (v=='n') refreshlist_position=0;
        if (v=='p') playlistoptions();
        if (v=='a')
        {
          showfiles (nrscr-1,nrcols,".","Select a file to add",0,".");
    	  if (strcmp(mpegfile[0],"")!=0)
 	    if (mpegnumber > -1) for (int i=0;i<=mpegnumber;i++) addfile(mpegfile[i]);
	  reread=1;
        }
        if (v=='D') 
        { 
          showfiles (nrscr-1,nrcols,".","Select a directory to add",1,".");
  	  if (mpegnumber > -1)
	  {
	    if (s[strlen(mpegfile[0])]!='/') strcat (mpegfile[0],"/");
            adddir (mpegfile[0]); 
	  }  
	  reread=1;
        }
        if (v==',') if (balance > 0) {balance--; setvolumes (vol,pcm,balance); }
        if (v=='.') if (balance < 100) {balance++; setvolumes (vol,pcm,balance);}
        if (v=='L') auto_goto=1-auto_goto;
        if (v=='l') 
        {
          m=getcurent()-(nrscr/2);
	  k=(nrscr/2);
	  more=0;
        }
        if ((v>=48) && (v<=57))
        {
          m=(v-48)*(n/9)-(nrscr/2);
        }
	if (v=='-') {if (nrscr > 15) nrscr--; reread=1;}
        if (v=='+') {nrscr++; reread=1;}
        if (v=='/') {if (nrcols > 78) nrcols--; reread=1;}
        if (v=='*') {nrcols++; reread=1;}
        if (v=='|') if (nclose!=0) nclose=0; else nclose=1;
        if (v=='m') console(nrscr-1);
        if (v=='H') hello();
      }
      if ((quit==1) && (nclose==1) && (reread==0)) 
      {
        quit=show_timer ("Shutting down in",shut_down_timer);
	nclose=quit;
	if (quit==1) reread=0;
      }
    }  
    while ((quit==0) || (reread==1)); //((v!='Q') && (quit==0));
    chdir (path);
    savelist (playlistfile,0);
}

int main(int argc,char *argv[])
{
    if (getenv("VUMETER"))
    {
      wiringPiSetup ();
      int LEDS = atoi (getenv ("LEDS"));
      for (int i=0; i<LEDS; i++)
      {
        pinMode (i, OUTPUT);
      }
    }
    // text pt. mesaje
    key_t K = ftok ("/",'E');
    int mem_id = shmget (K, 5, IPC_CREAT|0666);
    str_memout = (char*)shmat (mem_id, NULL, 0);
    if (str_memout!=NULL) strcpy (str_memout, "");
    srand (time(NULL));
    strcpy (mesaj,"");
    strcpy (mesaje,"");
    for (int h=0;h<nr_mesaje_afisate;h++) mesaje_afisate[h]=0;
    le_sleep.mode=0;
    strcpy (fs_command[1],"mount /dev/hdc");
    strcpy (fs_command[2],"umount /dev/hdc");
    strcpy (fs_command[3],"mount /dev/hdd");
    strcpy (fs_command[4],"umount /dev/hdd");
    strcpy (fs_command[5],"mount /dev/hdb1");
    strcpy (fs_command[6],"umount /dev/hdb1");
    getcwd (path,sizeof(path));
    strcpy (path,getenv ("HOME"));
    strcat (path,"/");
    strcat (path,".linuxeyes.playlist");
    strcpy (playlistfile,path);
    add_console_message ("Hello, welcome to LinuxEyes v1.0.2");
    printf ("Linux Eyes v%s (C) Alexandru Radovici 2002 - 2100\n\r",version);
    printf ("Getting system information...");
    sysinfo=uname (&computer);
    if (sysinfo!=-1) printf ("done\n\r   System   : %s\n\r   Kernel   : %s\n\r   Version  : %s\n\r   Computer : %s\n\r   Hostname : %s\n\r     Domain : %s\n\r\n\r",computer.sysname,computer.release,computer.version,computer.machine,computer.nodename,computer.domainname);
    else printf ("failed\n\r");
    if (argc > 1)
    for (int i=1;i<argc;i++)
    {
      add_console_message ("Procesing arguments");
      if (strcmp(argv[i],"-p") == 0) autoplay=true;
      if (strcmp(argv[i],"--colors")==0) nocolor=2;
      if (strcmp(argv[i],"--nocolors")==0) nocolor=1;
      if (strcmp(argv[i],"--autoscr")==0) scr_autodetect=1;
      if (strcmp(argv[i],"--noautoscr")==0) scr_autodetect=0;
      if (strcmp(argv[i],"--fakelines")==0) nolines=1;
      if (strcmp(argv[i],"--new_start")==0) new_start=1;
      if (strcmp(argv[i],"--debug")==0) show_to_logs=1;
    } 
    printf ("Starting console...\n\r");
    printf ("Loading configuration... ");
    add_console_message ("Loading configuration");
    if (new_start==0)
    if (loadconfig ()) 
    {
      printf ("ok\n\r");
      add_console_message ("Configuration OK");
    }
    else 
    {
      printf ("failed, using default configuration\n\r");
      add_console_message ("Configuration loading failed, using default");
      showhello=1;
    }
    else
    {
      printf ("\"--new_start\" argument found, making a new configuration\n\r");
      add_console_message ("\"--new_start\" argument found => new config");
    }
    printf ("Starting LinuxEyes\n\r");
    add_console_message ("Starting interface");
    initscr();
    if (LINES<30)
    {
      fprintf (stderr,"\n\r");
      fprintf (stderr,"WARNING:\n\r");
      fprintf (stderr,"Your terminal size is smaller than the RECOMANDED LinuxEyes terminal size.\n\r");
      fprintf (stderr,"In order to get better performante we recomand you to add this parameters to the kernel:\n\r");
      fprintf (stderr,"  vga=0x301 - for medium terminal size\n\r");
      fprintf (stderr,"  vga=791 = for high terminal size (recomanded)\n\r");
      if (!autoplay)
      {
        fprintf (stderr,"Press RETURN to continue...");
        getchar();
	fprintf (stderr,"\n\r");
      }
      fprintf (stderr,"\n\r");
    }
    if ((LINES-10<16) || (COLS-2<78)) 
    {
      fprintf (stderr,"WARINING: Terminal size is too small. LinuxEyes might not run correctly!!!\n\r");
      fprintf (stderr,"  Current terminal size: %dx%d\n\r",COLS,LINES);
      fprintf (stderr,"  Minumum terminal size: 80x25\n\r");
      fprintf (stderr,"Press RETURN to continue...");
      getchar();
      fprintf (stderr,"\n\r\n\r");
    }
    if (scr_autodetect == 1) 
    {
      nrscr=LINES-10;
      nrcols=COLS-2;
    }
    if (nrcols<78) nrcols=78;
    if (nrscr<=15) nrscr=15;
    //cbreak();
    raw();
    if (nolines) fakelines();
    // keypad (stdscr,TRUE);
    curs_set (0);
    colors();
    setcolor (3,1);
    init_text=1;
    mvprintw (0,0,"Welcome to LinuxEyes MP3 Player v%s (%s) [press h for help]",version,v_name);
    add_console_message ("Starting player");
    BASS_SetConfig (BASS_CONFIG_DEV_BUFFER, 6*1024*1024);
    BASS_Init (-1, 48000, 0, 0, NULL);
    //player_new (&player,NULL);
    //control_message_send (player,XA_MSG_SET_OUTPUT_VOLUME,balance,pcm,vol);
    //control_message_send (player,XA_MSG_SET_CODEC_EQUALIZER, &equalizer);
    resettime();
    if ((save_pos==1) && (strcmp(curent.name,"")!=0))
    {
      nr_prev++;
      strcpy (prev[nr_prev],curent.name);
    }
    playlist();
    clear();
    refresh();
    curs_set (1);
    //nocbreak();
    noraw();
    endwin();
    //control_message_send (player,XA_MSG_COMMAND_STOP);
    //control_message_send (player,XA_MSG_SET_OUTPUT_VOLUME,balance,pcm,vol);
    add_console_message ("Closing player");
    BASS_Free ();
    //control_message_send (player,XA_MSG_COMMAND_EXIT);
    //player_delete (player);
    add_console_message ("Saving configuration");
    if (saveconfig ()) printf ("xmp: configuration saved\n\r");
    else printf ("xmp: configuration could bot be saved\n\r");
    add_console_message ("Almost done");
    printf ("Thank you for using LinuxEyes Player\n\rPlease report bugs to linueyes@lug.orizont.net\n\r");
    add_console_message ("Bye Bye");
    if (nclose==1) 
    {
      add_console_message ("Shutting Down");
      printf ("Shutting Down....");
      system ("halt -p");
    }
    strcpy (str_memout, "");
    //if (str_memout!=NULL) free (str_memout);
    return 0;
}
