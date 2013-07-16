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
  strcpy (s[1],"    Alexandru Radovici - alex@papiu.uttgm.ro");
  strcpy (s[2],"");
  strcpy (s[3],"VERSION");
  strcpy (s[4],"    LinuxEyes 0.7, build 0.7.2 (December 31, 2002)");
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
  strcpy (s[21],"email me. (alex@papiu.uttgm.ro)");
  strcpy (s[22],"");
  strcpy (s[23],"LOTS OF THANKS TO");
  strcpy (s[24],"    Vera and Iuliu Radovici");
  strcpy (s[25],"    Ovidiu Stoica - oviska@hotmail.com");
  strcpy (s[26],"    Alexandru Armean - pitu@papiu.uttgm.ro");
  strcpy (s[27],"    Valeriu Moldovan - valeriu_moldovan@hotmail.com");
  strcpy (s[28],"");
  strcpy (s[29],"CURRENT SESSION STATISTICS");
  sprintf (s[30],"    Songs Played: %d",(int)n_songs);
  sprintf (s[31],"    Time Played: %d:%.2d:%.2d",(int)n_secs/(60*60),(int)(n_secs/60)%60,(int)n_secs%60);
  strcpy (s[32],"");
  strcpy (s[33],"GLOBAL STATISTICS");
  sprintf (s[34],"    Songs Played: %d",(int)songs);
  sprintf (s[35],"    Time Played: %d:%.2d:%.2d",(int)secs/(60*60),(int)(secs/60)%60,(int)secs%60);
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
    if (k<35-(scr-5)) mvwaddch (w,scr-1,28,ACS_DARROW);
    wrefresh(w);
    do
    {
      sprintf (s[30],"    Songs Played: %d",(int)n_songs);
      sprintf (s[31],"    Time Played: %d:%.2d:%.2d",(int)n_secs/(60*60),(int)(n_secs/60)%60,(int)n_secs%60);
      sprintf (s[34],"    Songs Played: %d",(int)songs);
      sprintf (s[35],"    Time Played: %d:%.2d:%.2d",(int)secs/(60*60),(int)(secs/60)%60,(int)secs%60);
      for (int i=0;i<=scr-5;i++) if (((i+k)==30) || ((i+k)==31) || ((i+k)==34) || ((i+k)==35))
      {
        wsetcolor (w,12,0);
        mvwprintw (w,2+i,2,"                                                         ");
        mvwprintw (w,2+i,2,"%s",s[i+k]);
	wrefresh (w);
      }
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
        if (v==66) if (k < 35-(scr-5)) k++;
      }
    }
    if (v=='R')
    {
      n_songs=0;
      n_secs=0;
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
  strcpy (s[4]," --fakelines  : draw lines on terminals without ACS");
  strcpy (s[5],"");
  strcpy (s[6],"PLAYER");
  strcpy (s[7]," z            : previous");
  strcpy (s[8]," x            : play");
  strcpy (s[9]," c            : pause");
  strcpy (s[10]," v            : stop");
  strcpy (s[11]," b            : next");
  strcpy (s[12]," s            : Shuffle On/Off");
  strcpy (s[13]," <ENTER>      : Play ");
  strcpy (s[14]," <SPACE BAR>  : Set As Next ");
  strcpy (s[15]," <LEFT>       : Backward");
  strcpy (s[16]," <RIGHT>      : Forward");
  strcpy (s[17]," r            : Repreat current song ");
  strcpy (s[18]," i            : Song Information (id3 tag)");
  strcpy (s[19]," j            : Jump to file");
  strcpy (s[20]," <INSERT>     : Volume + ");
  strcpy (s[21]," <DELETE>     : Volume - ");
  strcpy (s[22]," <HOME>       : PCM + ");
  strcpy (s[23]," <END>        : PCM - ");
  strcpy (s[24]," <            : Balance left ");
  strcpy (s[25]," >            : Balance right ");
  strcpy (s[26]," e            : Equalizer");
  strcpy (s[27]," '            : Repaint Desktop");
  strcpy (s[28]," *            : Increase desktop width");
  strcpy (s[29]," /            : Decrease desktop width");
  strcpy (s[30]," +            : Increase desktop height");
  strcpy (s[31]," -            : Decrease desktop height");
  strcpy (s[32]," t            : Switch clock display mode");
  strcpy (s[33]," \\            : Change Password");
  strcpy (s[34]," !            : Lock Display");
  strcpy (s[35]," =            : Switch Status Bar Format");
  strcpy (s[36]," h            : Help");
  strcpy (s[37]," ?            : About and Statistics");
  strcpy (s[38]," |            : On/Off Shut Down mode");
  strcpy (s[39]," Q            : Quit");
  strcpy (s[40],"");
  strcpy (s[41],"PLAYLIST");
  strcpy (s[42]," a            : Add File");
  strcpy (s[43]," d            : Delete File");
  strcpy (s[44]," D            : Add Directory");
  strcpy (s[45]," R            : Delete All");
  strcpy (s[46]," S            : Sort Playlist");
  strcpy (s[47]," <UP>         : Cursor Up");
  strcpy (s[48]," <DOWN>       : Cursor Down");
  strcpy (s[49]," <PAGE UP>    : Page Up");
  strcpy (s[50]," <PAGE DOWN>  : Page Down");
  strcpy (s[51]," 0..9         : Fast Scroll");
  strcpy (s[52]," [            : Move Up");
  strcpy (s[53]," '            : Move Down");
  strcpy (s[54]," l            : Locate Current Song");
  strcpy (s[55]," p            : Playlist Options");
  strcpy (s[56]," p,n          : New Playlist");
  strcpy (s[57]," p,l          : Load Playlist");
  strcpy (s[58]," p,s          : Save Playlist");
  strcpy (s[59]," p,i          : Import Playlist");
  strcpy (s[60]," p,e          : Export Playlist");
  strcpy (s[61]," E            : Edit playlist file entry");
  strcpy (s[62]," n            : Refresh list");
  strcpy (s[63],"");
  strcpy (s[64],"EQUALIZER WINDOW");
  strcpy (s[65]," <PAGE UP>    : Up ALL");
  strcpy (s[66]," <PAGE DOWN>  : Down ALL");
  strcpy (s[67]," a/z          : Up/Down Band #1");
  strcpy (s[68]," s/x          : Up/Down Band #2");
  strcpy (s[69]," d/c          : Up/Down Band #3");
  strcpy (s[70]," f/v          : Up/Down Band #4");
  strcpy (s[71]," g/b          : Up/Down Band #5");
  strcpy (s[72]," h/n          : Up/Down Band #6");
  strcpy (s[73]," j/m          : Up/Down Band #7");
  strcpy (s[74]," k/,          : Up/Down Band #8");
  strcpy (s[75]," l/.          : Up/Down Band #9");
  strcpy (s[76]," ;//          : Up/Down Band #10");
  strcpy (s[77]," r            : Set all bands to 0 (reset equalizer)");
  strcpy (s[78]," L            : Load Equalizer");
  strcpy (s[79]," S            : Save Equalizer");
  strcpy (s[80],"");
  strcpy (s[81],"STATISTICS");
  strcpy (s[82]," R            : Reset current session statistics");
  strcpy (s[83],"");
  strcpy (s[84],"SPECIAL FUNCTIONS");
  strcpy (s[85]," P            : Save playlist for MP3 CD Player");
  strcpy (s[86],"                * Save your playlist (p,s). Make a");
  strcpy (s[87],"                  new playlist (p,n).Load Directory (D)");
  strcpy (s[88],"                  from the CD in your playlist.");
  strcpy (s[89],"                * Tested on JazzPIPER MCD650S");
  strcpy (s[90],"");
  strcpy (s[91],"PLAYER MODES");
  strcpy (s[92]," Normal       : Next song in playlist (don\'t shuffle)");
  strcpy (s[93]," Shuffle      : Random next song (shuffle)");
  strcpy (s[94]," Next Song    : Next song is already selected");
  strcpy (s[95]," Shut Down    : Shut Down after current song");
  strcpy (s[96]," Password     : Display is locked with password");
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
    if (k<93-(scr-5)) mvwaddch (w,scr-1,28,ACS_DARROW);
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
        if (v==66) if (k < 96-(scr-5)) k++;
      }
    }
  }    
  while (v!='q');
  werase (w);
  reread=1;
}
