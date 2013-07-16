int nocolor=0; //dummy terminal problem (inverse colors)
char server[500]; //server to get message bar from
int connected=0; //is the client connected to a server

#include <curses.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <fstream.h>
#include <stream.h>
#include "../../inc/misc.cpp"
#include "../init.cpp"
#include "socket/ClientSocket.h"
#include "socket/SocketException.h"

ClientSocket clock_client;//the socket  

time_t currenttime;  //current time
std::string mesaje;

typedef char list[200][30];

list numbers[11] =
{
  { "******","**  **","**  **","**  **","******"},
  { "    **","    **","    **","    **","    **"},
  { "******","    **","******","**    ","******"},
  { "******","    **","******","    **","******"},
  { "**  **","**  **","******","    **","    **"},
  { "******","**    ","******","    **","******"},
  { "******","**    ","******","**  **","******"},
  { "******","    **","    **","    **","    **"},
  { "******","**  **","******","**  **","******"},
  { "******","**  **","******","    **","******"},
  { "      ","**    ","      ","**    ","      "},
//{ "  **  ","**  **","******","**  **","**  **"},
//{ "**  **","  **  ","**  **","    **","    **"},
};

void print_nr (WINDOW *w, int y, int x, int nr)
{
  for (int j=0;j<=5;j++)
    for (int i=0;i<=6;i++)
    {
      if (numbers[nr][j][i]=='*') wsetcolor (w,3,1);
      else wsetcolor (w,4,1);
      mvwprintw (w,y+j,x+i," ");
    }
}

void screen_clock ()
{
  int t=0;
  int q=0;
  char ora[256];
  int m=0;
  WINDOW *w;
  w=newwin (nrscr+10,nrcols+2,0,0);
  wclear (w);
  wrefresh (w);
  timeout (1);
  do
  {
//    if (connected) q=1;
    if (!connected)
    {
      mvwprintw (w,0,0,"Connecting to %s",server);
      connected=clock_client.link (server, 6006);
      if (connected) 
      {
        clock_client << "LE.ADD Screen Clock v0.1";
	clock_client << "REQEST: Message Bar";
	mvwprintw (w,1,0,"Connected            ");
      }
    }
    t=getch();
    time (&currenttime);
    tm *mytime;
    mytime=localtime (&currenttime);
    strftime (ora,256,"%T",mytime);
    m=0;
    for (int l=0;l<=7;l++) 
    {
      m=m+7;
      if ((l==3) || (l==6)) m=m-4;
      print_nr (w,(nrscr)/2,(nrcols-69)/2+l+m,ora[l]-48);
    }
    wrefresh (w);
    strftime (ora,256,"%A, %B %d, %G",mytime);
    wsetcolor (w,17,0);
    int k=strlen(ora);
//    wmove (w,(nrscr)/2+6,((nrcols-k)/2));
//    wprintw (w,ora);
    labelw (w,(nrscr)/2+6,((nrcols-k)/2),ora,strlen(ora)+1);
    if (connected) 
    {
      try
      {
        clock_client >> mesaje;
	cout << mesaje <<'\n';
      }
      catch ( SocketException& ) 
      {
        connected=0;
      }
      char s[500];
      int x=0;
      while ((mesaje[x]!='\0') && (x<nrcols+1)) 
      {
        s[x]=mesaje[x];
	x++;
      }
      s[x]='\0';
      wsetcolor (w,1,0);
      labelw  (w,nrscr+9,1,s,nrcols+1);
    }
    wrefresh(w);
    if (t!=ERR) q=1;
  } while (q==0);
  while (t!=ERR) t=getch();
}

int main(int argc,char *argv[])
{
    if (argc > 1)
    for (int i=1;i<argc;i++)
    {
      if (strcmp(argv[i],"--colors")==0) nocolor=2; else
      if (strcmp(argv[i],"--nocolors")==0) nocolor=1; else
      if (strcmp(argv[i],"--fakelines")==0) nolines=1; else
      if (strcmp(argv[i],"--autoscr")==0) scr_autodetect=1; else
      if (strcmp(argv[i],"--noautoscr")==0) scr_autodetect=0; else
      strcpy (server,argv[i]);
    } 
    connected=0;
    printf ("Welcome to LinuxEyes Screen Clock v0.1\n");
    if (loadconfig ()) printf ("LinuxEyes configuration file loaded.\n");
    else printf ("LinuxEyes configuration file not found, using default settings.\n");
    printf ("Starting...\n");
    start();
    screen_clock();
    stop();
    printf ("LinuxEyes Screen Clock v0.1\nA part of LinuxEyes MP3 Player\nCopyright 2003 Alexandru Radovici\nThis software is provided AS IS! NO WARRANTY!\nThank you for using LinuxEyes Screen Clock\n\rPlease report bugs to linueyes@lug.orizont.net\n\r");
}

