char playlistfile[1000]; //playlist filename with path
int nrscr=16;//the screen size, normal terminal 16
unsigned int nrcols=78;//number of colums of screen
int vol=90,pcm=90,balance=50; //volumes
bool rnext=true; //random next
struct
{
  signed char left;
  signed char right;
} eq;
int current_timeformat=1; //the current clock format
int auto_equ=0; //automatic eq load, after song genre
int auto_goto=0; //auto goto current song
int status_bar=0; //status bar display type, 0 normal, 1 next song, 2 filter, 3 radio time, 4 shutdown time, default 0
long songs=0; //nr of played songs
long secs=0; //nr of seconds played
int save_pos=0; //used for save playlist position
int persistent_filter=0; //persistent filter=1, nonpersistent=0, delault=0
char messages [5000]; //message bar got from server
struct
{
   char name[1000];
   char artist[30];
   char song[30];
   char text[150];
   int min;
   int sec;
   int tag;    
}curent; //current song info
int screensaver_time=3; //screen saver time
int nolines=0;
char ok_char='.';
int scr_autodetect=1; //audetect screen

int loadconfig()
{
  int r=1;
  char strtmp [1000];
  strcpy (strtmp,getenv("HOME"));
  strcat (strtmp,"/.linuxeyes.config");
  ifstream f(strtmp);
  if (!f.fail())
  {
     f.getline(playlistfile,sizeof(playlistfile));
     f >>nrscr >>nrcols >>vol >>pcm >>balance >>rnext;
     f >>eq.left >>eq.right;
     f >>current_timeformat >>status_bar >>songs >>secs;
     f >>persistent_filter >>save_pos;
     if (save_pos!=1) save_pos=0;
     f.getline (curent.name,sizeof(curent.name));
     f >>auto_equ >>auto_goto;
     f >>ok_char;
     f >>screensaver_time;
     if (!save_pos) strcpy (curent.name,"");
     if ((status_bar<1) && (status_bar>5)) status_bar=1;
     if ((current_timeformat<0) && (current_timeformat>4)) current_timeformat=0;
     if ((rnext!=0) && (rnext!=1)) rnext=0;
     if ((auto_equ!=0) && (auto_equ!=1)) auto_equ=0;
     if ((auto_goto!=0) && (auto_goto!=1)) auto_goto=0;
  }
  else r=0;
  f.close();
  return r;
}

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
  if (nolines==1) f=1;
  return f;
}

void fakelines ()
{
    for (int i = 0; acs_approx[i].acscode != 0; i++) 
    {
      acs_map[acs_approx[i].acscode] = acs_approx[i].character;
    }
}

void start()
{
    initscr();
    if (scr_autodetect == 1) 
    {
      nrscr=LINES-10;
      nrcols=COLS-2;
    }
    if (nrcols<78) nrcols=78;
    if (nrscr<=15) nrscr=15;
    raw();
    if (nolines) fakelines();
    keypad (NULL,TRUE);
    curs_set (0);
    colors();
}

void stop()
{
    clear();
    refresh();
    curs_set (1);
    noraw();
    endwin();
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

