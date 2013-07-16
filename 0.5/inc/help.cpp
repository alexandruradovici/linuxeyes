void about(int scr)
{
/*    initscr();
    WINDOW *w;
    w=newwin (16,78,7,1);
    werase(w);
    setcolor (1,1);
    mvprintw (7,34,"LinuxEyes");
    setcolor (1,1);
    mvprintw (9,2,"AUTHOR");
    mvprintw (13,2,"COPYRIGHT");
    mvprintw (17,2,"LOTS OF THANKS TO");
    mvprintw (20,2,"BUGS AND SUGGESTIONS");
    setcolor (1,0);
    mvprintw (10,5,"Alexandru Radovici - alex@papiu.netsoft.ro");
    mvprintw (11,5,"                     amy_ro@hotmail.com");
    mvprintw (14,5,"This program is free. You may use it on your own risk. You may distribute");
    mvprintw (15,2,"it only integral.");
    mvprintw (18,5,"Xaudio - http://www.xaudio.com"); 
    mvprintw (21,5,"If you have found bugs or have some suggestions to make please send me an");
    mvprintw (22,2,"e-mail. Thank you.");
    wrefresh (w); */
  int v,k;
  char s[100][100];
  strcpy (s[0],"AUTHOR");
  strcpy (s[1],"    Alexandru Radovici - alexandru_radovici@hotmail.com");
  strcpy (s[2],"");
  strcpy (s[3],"VERSION");
  strcpy (s[4],"    LinuxEyes 0.6, build 2 (December 15, 2001)");
  strcpy (s[5],"");
  strcpy (s[6],"ECLIPSE");
  strcpy (s[7],"    http://nike.lem.uttgm.ro/eclipse/");
  strcpy (s[8],"");
  strcpy (s[9],"LOTS OF THANKS");
  strcpy (s[10],"    Xaudio - http://www.xaudio.com");
  strcpy (s[11],"");
  strcpy (s[12],"COPYRIGHT & DISTRIBUTION");
  strcpy (s[13],"    This software is freeware, you may use it on your");
  strcpy (s[14],"own risk. You may distribute it only integral.");
  strcpy (s[15],"");
  strcpy (s[16],"UPDATE");
  strcpy (s[17],"    http://linuxeyes.tripod.com");
  strcpy (s[18],"");
  strcpy (s[19],"BUGS & SUGGESTIONS");
  strcpy (s[20],"    If you find any bugs or have any suggestion please");
  strcpy (s[21],"e-mail me. (alexandru_radovici@hotmail.com)");
  WINDOW *w1;
  w1=newwin (scr+2,62,7,9);
  wrefresh (w1);
  werase (w1);
  WINDOW *w;
  w=newwin (scr,60,8,10);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr+2;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  box (w,ACS_VLINE,ACS_HLINE);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Eclipse LinuxEyes ");
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
      if ((i+k) <= 21) mvwprintw (w,2+i,2,"%s",s[i+k]);
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
        if (v==66) if (k < 21-(scr-5)) k++;
      }
    }
  }    
  while (v!='q');
  werase (w);
  reread=1;
}

void help(int scr)
{
  int v,k;
  char s[100][100];
  strcpy (s[0],"COMMAND LINE");
  strcpy (s[1]," -p           : play");
  strcpy (s[2]," --nocolors   : for dummy terminals (telnet)");
  strcpy (s[3],"");
  strcpy (s[4],"KEYBOARD");
  strcpy (s[5]," z            : previous");
  strcpy (s[6]," x            : play");
  strcpy (s[7]," c            : pause");
  strcpy (s[8]," v            : stop");
  strcpy (s[9]," b            : next");
  strcpy (s[10]," s            : Shuffle On/Off");
  strcpy (s[11]," <ENTER>      : Play ");
  strcpy (s[12]," <SPACE BAR>  : Set As Next ");
  strcpy (s[13]," r            : Repreat current song ");
  strcpy (s[14]," <INSERT>     : Volume + ");
  strcpy (s[15]," <DELETE>     : Volume - ");
  strcpy (s[16]," <HOME>       : PCM + ");
  strcpy (s[17]," <END>        : PCM - ");
  strcpy (s[18]," <            : Balance left ");
  strcpy (s[19]," >            : Balance right ");
  strcpy (s[20]," a            : Add File");
  strcpy (s[21]," d            : Delete File");
  strcpy (s[22]," D            : Add Directory");
  strcpy (s[23]," R            : Delete All");
  strcpy (s[24]," S            : Sort Playlist");
  strcpy (s[25]," <UP>         : Cursor Up");
  strcpy (s[26]," <DOWN>       : Cursor Down");
  strcpy (s[27]," <PAGE UP>    : Page Up");
  strcpy (s[28]," <PAGE DOWN>  : Page Down");
  strcpy (s[29]," <LEFT>       : Backward");
  strcpy (s[30]," <RIGHT>      : Forward");
  strcpy (s[31]," [            : Move Up");
  strcpy (s[32]," '            : Move Down");
  strcpy (s[33]," p            : Playlist Options");
  strcpy (s[34]," p,n          : New Playlist");
  strcpy (s[35]," p,l          : Load Playlist");
  strcpy (s[36]," p,s          : Save Playlist");
  strcpy (s[37]," ?            : About");
  strcpy (s[38]," h            : Help");
  strcpy (s[39]," '            : Repaint Desktop");
  strcpy (s[40]," *            : Increase desktop width");
  strcpy (s[41]," /            : Decrease desktop width");
  strcpy (s[42]," +            : Increase desktop height");
  strcpy (s[43]," -            : Decrease desktop height");
  strcpy (s[44]," i            : Song Information (id3 tag)");
  strcpy (s[45]," e            : Edit playlist file entry");
  strcpy (s[46]," j            : Jump to file");
  strcpy (s[47]," n            : Refresh list");
  strcpy (s[48]," 0            : On/Off Shut Down mode");
  strcpy (s[49]," q            : Quit");
  strcpy (s[50],"");
  strcpy (s[51],"SPECIAL FUNCTIONS");
  strcpy (s[52]," P            : Save playlist for MP3 CD Player");
  strcpy (s[53],"                * Save your playlist (p,s). Make a");
  strcpy (s[54],"                  new playlist (p,n).Load Directory (D)");
  strcpy (s[55],"                  from the CD in your playlist.");
  strcpy (s[56],"                * Tested on JazzPIPER MCD650S");
  strcpy (s[57],"");
  strcpy (s[58],"PLAYER MODES");
  strcpy (s[59]," Normal       : Next song in playlist");
  strcpy (s[60]," Shuffle      : Random next song");
  strcpy (s[61]," Next Song    : Next song already selected");
  strcpy (s[62]," Shut Down    : Shut Down after next song");
  WINDOW *w1;
  w1=newwin (scr+2,62,7,9);
  wrefresh (w1);
  werase (w1);
  WINDOW *w;
  w=newwin (scr,60,8,10);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr+2;h++) mvwprintw (w,h,0,"                                                             ");
  wsetcolor (w,12,0);
  box (w,ACS_VLINE,ACS_HLINE);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Help ");
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
      mvwprintw (w,2+i,2,"%s",s[i+k]);
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
        if (v==66) if (k < 62-(scr-5)) k++;
      }
    }
  }    
  while (v!='q');
  werase (w);
  reread=1;
}
