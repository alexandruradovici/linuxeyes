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
  strcpy (s[4],"    LinuxEyes 0.6, build 0.6.4 (July 14, 2002)");
  strcpy (s[5],"");
  strcpy (s[6],"ROMANIAN SOFTWARE");
  strcpy (s[7],"    This software was made in Romania!");
  strcpy (s[8],"");
  strcpy (s[9],"WEBSITE");
  strcpy (s[10],"    http://linuxeyes.go.ro");
  strcpy (s[11],"");
  strcpy (s[12],"COPYRIGHT & DISTRIBUTION");
  strcpy (s[13],"    This software is freeware, you may use it on your");
  strcpy (s[14],"own risk. You may distribute it only integral.");
  strcpy (s[15],"");
  strcpy (s[16],"MPEG Audio Layer 3");
  strcpy (s[17],"    Xaudio - http://www.xaudio.com");
  strcpy (s[18],"");
  strcpy (s[19],"BUGS & SUGGESTIONS");
  strcpy (s[20],"    If you find any bugs or have any suggestion please");
  strcpy (s[21],"email me. (alexandru_radovici@hotmail.com)");
  strcpy (s[22],"");
  strcpy (s[23],"LOTS OF THANKS TO");
  strcpy (s[24],"    Vera and Iuliu Radovici");
  strcpy (s[25],"    Ovidiu Stoica - oviska@hotmail.com");
  strcpy (s[26],"    Alexandru Armean - alex@papiu.orizont.net");
  strcpy (s[27],"    Valeriu Moldovan - valeriu_moldovan@hotmail.com");
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
  mvwprintw (w,0,1," About LinuxEyes ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr-1,48," q - quit ");
  wrefresh(w);
  noecho();
  timeout (1);
  k=0;
  do
  {
    wsetcolor (w,12,0);
    for (int i=0;i<=scr-5;i++) 
    {
      mvwprintw (w,2+i,2,"                                                         ");
      mvwprintw (w,2+i,2,"%s",s[i+k]);
    }
    wsetcolor (w,12,0);
    mvwaddch (w,0,28,ACS_HLINE);
    mvwaddch (w,scr-1,28,ACS_HLINE);
    wsetcolor (w,12,1);
    if (k>0) mvwaddch (w,0,28,ACS_UARROW);
    if (k<27-(scr-5)) mvwaddch (w,scr-1,28,ACS_DARROW);
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
        if (v==66) if (k < 27-(scr-5)) k++;
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
  strcpy (s[2]," --nocolors   : B&W, for dummy terminals (telnet)");
  strcpy (s[3]," --autoscr    : autodetect the screen's size (BETA)");
  strcpy (s[4],"");
  strcpy (s[5],"PLAYER");
  strcpy (s[6]," z            : previous");
  strcpy (s[7]," x            : play");
  strcpy (s[8]," c            : pause");
  strcpy (s[9]," v            : stop");
  strcpy (s[10]," b            : next");
  strcpy (s[11]," s            : Shuffle On/Off");
  strcpy (s[12]," <ENTER>      : Play ");
  strcpy (s[13]," <SPACE BAR>  : Set As Next ");
  strcpy (s[14]," <LEFT>       : Backward");
  strcpy (s[15]," <RIGHT>      : Forward");
  strcpy (s[16]," r            : Repreat current song ");
  strcpy (s[17]," i            : Song Information (id3 tag)");
  strcpy (s[18]," j            : Jump to file");
  strcpy (s[19]," <INSERT>     : Volume + ");
  strcpy (s[20]," <DELETE>     : Volume - ");
  strcpy (s[21]," <HOME>       : PCM + ");
  strcpy (s[22]," <END>        : PCM - ");
  strcpy (s[23]," <            : Balance left ");
  strcpy (s[24]," >            : Balance right ");
  strcpy (s[25]," e            : Equalizer");
  strcpy (s[26]," '            : Repaint Desktop");
  strcpy (s[27]," *            : Increase desktop width");
  strcpy (s[28]," /            : Decrease desktop width");
  strcpy (s[29]," +            : Increase desktop height");
  strcpy (s[30]," -            : Decrease desktop height");
  strcpy (s[31]," t            : Switch clock display mode");
  strcpy (s[32]," \\            : Change Password");
  strcpy (s[33]," !            : Lock Display");
  strcpy (s[34]," =            : Switch Status Bar Format");
  strcpy (s[35]," h            : Help");
  strcpy (s[36]," ?            : About");
  strcpy (s[37]," 0            : On/Off Shut Down mode");
  strcpy (s[38]," Q            : Quit");
  strcpy (s[39],"");
  strcpy (s[40],"PLAYLIST");
  strcpy (s[41]," a            : Add File");
  strcpy (s[42]," d            : Delete File");
  strcpy (s[43]," D            : Add Directory");
  strcpy (s[44]," R            : Delete All");
  strcpy (s[45]," S            : Sort Playlist");
  strcpy (s[46]," <UP>         : Cursor Up");
  strcpy (s[47]," <DOWN>       : Cursor Down");
  strcpy (s[48]," <PAGE UP>    : Page Up");
  strcpy (s[49]," <PAGE DOWN>  : Page Down");
  strcpy (s[50]," [            : Move Up");
  strcpy (s[51]," '            : Move Down");
  strcpy (s[52]," p            : Playlist Options");
  strcpy (s[53]," p,n          : New Playlist");
  strcpy (s[54]," p,l          : Load Playlist");
  strcpy (s[55]," p,s          : Save Playlist");
  strcpy (s[56]," p,i          : Import Playlist");
  strcpy (s[57]," p,e          : Export Playlist");
  strcpy (s[58]," E            : Edit playlist file entry");
  strcpy (s[59]," n            : Refresh list");
  strcpy (s[60],"");
  strcpy (s[61],"EQUALIZER WINDOW");
  strcpy (s[62]," <PAGE UP>    : Up ALL");
  strcpy (s[63]," <PAGE DOWN>  : Down ALL");
  strcpy (s[64]," a/z          : Up/Down Band #1");
  strcpy (s[65]," s/x          : Up/Down Band #2");
  strcpy (s[66]," d/c          : Up/Down Band #3");
  strcpy (s[67]," f/v          : Up/Down Band #4");
  strcpy (s[68]," g/b          : Up/Down Band #5");
  strcpy (s[69]," h/n          : Up/Down Band #6");
  strcpy (s[70]," j/m          : Up/Down Band #7");
  strcpy (s[71]," k/,          : Up/Down Band #8");
  strcpy (s[72]," l/.          : Up/Down Band #9");
  strcpy (s[73]," ;//          : Up/Down Band #10");
  strcpy (s[74]," r            : Set all bands to 0 (reset equalizer)");
  strcpy (s[75]," L            : Load Equalizer");
  strcpy (s[76]," S            : Save Equalizer");
  strcpy (s[77],"");
  strcpy (s[78],"SPECIAL FUNCTIONS");
  strcpy (s[79]," P            : Save playlist for MP3 CD Player");
  strcpy (s[80],"                * Save your playlist (p,s). Make a");
  strcpy (s[81],"                  new playlist (p,n).Load Directory (D)");
  strcpy (s[82],"                  from the CD in your playlist.");
  strcpy (s[83],"                * Tested on JazzPIPER MCD650S");
  strcpy (s[84],"");
  strcpy (s[85],"PLAYER MODES");
  strcpy (s[86]," Normal       : Next song in playlist (don\'t shuffle)");
  strcpy (s[87]," Shuffle      : Random next song (shuffle)");
  strcpy (s[88]," Next Song    : Next song is already selected");
  strcpy (s[89]," Shut Down    : Shut Down after current song");
  strcpy (s[90]," Password     : Display is locked with password");
  WINDOW *w1;
  w1=newwin (scr+2,62,7,9);
  wrefresh (w1);
  werase (w1);
  WINDOW *w;
  w=newwin (scr,60,8,10);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr+2;h++) mvwprintw (w,h,0,"                                                             ");
  wsetcolor (w,12,0);
  le_border (w,60,scr);
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
    wsetcolor (w,12,0);
    for (int i=0;i<=scr-5;i++) 
    {
      mvwprintw (w,2+i,2,"                                                         ");
      mvwprintw (w,2+i,2,"%s",s[i+k]);
    }
    wsetcolor (w,12,0);
    mvwaddch (w,0,28,ACS_HLINE);
    mvwaddch (w,scr-1,28,ACS_HLINE);
    wsetcolor (w,12,1);
    if (k>0) mvwaddch (w,0,28,ACS_UARROW);
    if (k<90-(scr-5)) mvwaddch (w,scr-1,28,ACS_DARROW);
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
        if (v==66) if (k < 90-(scr-5)) k++;
      }
    }
  }    
  while (v!='q');
  werase (w);
  reread=1;
}
