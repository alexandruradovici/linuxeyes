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
  strcpy (s[4],"    LinuxEyes 0.8, build 0.8.6 (February 8, 2003)");
  strcpy (s[5],"");
  strcpy (s[6],"ROMANIAN SOFTWARE");
  strcpy (s[7],"    This software was made in Romania!");
  strcpy (s[8],"");
  strcpy (s[9],"WEBSITE");
  strcpy (s[10],"    http://lug.orizont.net/~linuxeyes");
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
  strcpy (s[21],"email me. (linuxeyes@lug.orizont.net) Thank you!");
  strcpy (s[22],"");
  strcpy (s[23],"LOTS OF THANKS TO");
  strcpy (s[24],"    Vera and Iuliu Radovici");
  strcpy (s[25],"    Ovidiu Stoica - oviska@hotmail.com");
  strcpy (s[26],"    Alexandru Armean - alex@lug.orizont.net");
  strcpy (s[27],"    Valeriu Moldovan - valeriu_moldovan@hotmail.com");
  strcpy (s[28],"    Cristian Klein - cristiklein@yahoo.com");
  strcpy (s[29],"");
  strcpy (s[30],"CURRENT SESSION STATISTICS");
  sprintf (s[31],"    Songs Played: %d",(int)n_songs);
  sprintf (s[32],"    Time Played: %d:%.2d:%.2d",(int)n_secs/(60*60),(int)(n_secs/60)%60,(int)n_secs%60);
  strcpy (s[33],"");
  strcpy (s[34],"GLOBAL STATISTICS");
  sprintf (s[35],"    Songs Played: %d",(int)songs);
  sprintf (s[36],"    Time Played: %d:%.2d:%.2d",(int)secs/(60*60),(int)(secs/60)%60,(int)secs%60);
  WINDOW *w1;
  w1=newwin (scr+2,62,7,(nrcols-62)/2);
  wrefresh (w1);
  werase (w1);
  WINDOW *w;
  w=newwin (scr,60,8,(nrcols-60)/2);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr+2;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,60,scr);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," About LinuxEyes ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr-1,46," ESC - quit ");
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
      sprintf (s[31],"    Songs Played: %d",(int)n_songs);
      sprintf (s[32],"    Time Played: %d:%.2d:%.2d",(int)n_secs/(60*60),(int)(n_secs/60)%60,(int)n_secs%60);
      sprintf (s[35],"    Songs Played: %d",(int)songs);
      sprintf (s[36],"    Time Played: %d:%.2d:%.2d",(int)secs/(60*60),(int)(secs/60)%60,(int)secs%60);
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
      if (v==ERR) v='q';
      if (v==91)
      {
        v=getch();
	if (v==65) if (k > 0) k--;
        if (v==66) if (k < 36-(scr-5)) k++;
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
  char s[200][100];
  strcpy (s[0],"COMMAND LINE");
  strcpy (s[1]," -p           : play");
  strcpy (s[2]," --nocolors   : B&W, for dummy terminals (telnet)");
  strcpy (s[3]," --autoscr    : autodetect the screen's size (BETA)");
  strcpy (s[4]," --fakelines  : draw lines on terminals without ACS");
  strcpy (s[5]," --new_start  : start with default configuration");
  strcpy (s[6],"");
  strcpy (s[7],"PLAYER");
  strcpy (s[8]," z            : previous");
  strcpy (s[9]," x            : play");
  strcpy (s[10]," c            : pause");
  strcpy (s[11]," v            : stop");
  strcpy (s[12]," b            : next");
  strcpy (s[13]," s            : Shuffle On/Off");
  strcpy (s[14]," <ENTER>      : Play ");
  strcpy (s[15]," <SPACE BAR>  : Set As Next ");
  strcpy (s[16]," <TAB>        : Add/Remove to/from filter ");
  strcpy (s[17]," f            : On/Off persistent filter ");
  strcpy (s[18]," F            : Clear filter ");
  strcpy (s[19]," <LEFT>       : Backward");
  strcpy (s[20]," <RIGHT>      : Forward");
  strcpy (s[21]," r            : Repreat current song ");
  strcpy (s[22]," i            : ID3v1.1 TAG Editor (for selected song)");
  strcpy (s[23]," I            : ID3v1.1 TAG Editor (for current song))");
  strcpy (s[24]," j or F3      : Jump to file");
  strcpy (s[25]," <INSERT>     : Volume + ");
  strcpy (s[26]," <DELETE>     : Volume - ");
  strcpy (s[27]," <HOME>       : PCM + ");
  strcpy (s[28]," <END>        : PCM - ");
  strcpy (s[29]," <            : Balance left ");
  strcpy (s[30]," >            : Balance right ");
  strcpy (s[31]," e            : Equalizer");
  strcpy (s[32]," '            : Repaint Desktop");
  strcpy (s[33]," *            : Increase desktop width");
  strcpy (s[34]," /            : Decrease desktop width");
  strcpy (s[35]," +            : Increase desktop height");
  strcpy (s[36]," -            : Decrease desktop height");
  strcpy (s[37]," t            : Switch clock display mode");
  strcpy (s[38]," \\            : Change Password");
  strcpy (s[39]," !            : Lock Display");
  strcpy (s[40]," =            : Switch Status Bar Format");
  strcpy (s[41]," h or F1      : Help");
  strcpy (s[42]," ?            : About and Statistics");
  strcpy (s[43]," {            : Set Alarm (\"Radio\") On");
  strcpy (s[44]," }            : Set Alarm (\"Radio\") Off");
  strcpy (s[45]," T            : Set Sleep mode");
  strcpy (s[46]," |            : On/Off Shut Down mode");
  strcpy (s[47]," o            : Settings");
  strcpy (s[48]," Q            : Quit");
  strcpy (s[49],"");
  strcpy (s[50],"PLAYLIST");
  strcpy (s[51]," a            : Add File");
  strcpy (s[52]," d            : Delete File");
  strcpy (s[53]," D            : Add Directory");
  strcpy (s[54]," R            : Delete All");
  strcpy (s[55]," S            : Sort Playlist");
  strcpy (s[56]," <UP>         : Cursor Up");
  strcpy (s[57]," <DOWN>       : Cursor Down");
  strcpy (s[58]," <PAGE UP>    : Page Up");
  strcpy (s[59]," <PAGE DOWN>  : Page Down");
  strcpy (s[60]," 0..9         : Fast Scroll");
  strcpy (s[61]," [            : Move Up");
  strcpy (s[62]," '            : Move Down");
  strcpy (s[63]," l            : Locate Current Song");
  strcpy (s[64]," L            : Autolocate Current Song");
  strcpy (s[65]," p            : Playlist Options");
  strcpy (s[66]," p,n          : New Playlist");
  strcpy (s[67]," p,l          : Load Playlist");
  strcpy (s[68]," p,s          : Save Playlist");
  strcpy (s[69]," p,i          : Import Playlist");
  strcpy (s[70]," p,e          : Export Playlist");
  strcpy (s[71]," E            : Edit playlist file entry");
  strcpy (s[72]," n            : Refresh list");
  strcpy (s[73]," ;            : On/Off save playlist position on exit");
  strcpy (s[74],"");
  strcpy (s[75],"JUMP TO FILE");
  strcpy (s[76]," <ENTER>      : Play");
  strcpy (s[77]," <SPACE BAR>  : Set as next");
  strcpy (s[78]," <TAB>        : Add/Remove to/from filter");
  strcpy (s[79]," F            : Add/Remove all songs to filter");
  strcpy (s[80]," i            : ID3 TAG Edditor");
  strcpy (s[81]," ESC or q     : Close window");
  strcpy (s[82],"");
  strcpy (s[83],"EQUALIZER WINDOW");
  strcpy (s[84]," <PAGE UP>    : Up ALL");
  strcpy (s[85]," <PAGE DOWN>  : Down ALL");
  strcpy (s[86]," a/z          : Up/Down Band #1");
  strcpy (s[87]," s/x          : Up/Down Band #2");
  strcpy (s[88]," d/c          : Up/Down Band #3");
  strcpy (s[89]," f/v          : Up/Down Band #4");
  strcpy (s[90]," g/b          : Up/Down Band #5");
  strcpy (s[91]," h/n          : Up/Down Band #6");
  strcpy (s[92]," j/m          : Up/Down Band #7");
  strcpy (s[93]," k/,          : Up/Down Band #8");
  strcpy (s[94]," l/.          : Up/Down Band #9");
  strcpy (s[95]," ;//          : Up/Down Band #10");
  strcpy (s[96]," r            : Set all bands to 0 (reset equalizer)");
  strcpy (s[97]," L            : Load Preset");
  strcpy (s[98]," S            : Save Preset");
  strcpy (s[99]," I            : Import Preset(s)");
  strcpy (s[100]," D            : Delete Preset(s)");
  strcpy (s[101]," A            : On/Off Automatic Equalizer");
  strcpy (s[102],"");
  strcpy (s[103],"STATISTICS");
  strcpy (s[104]," R            : Reset current session statistics");
  strcpy (s[105],"");
  strcpy (s[106],"SPECIAL FUNCTIONS");
  strcpy (s[107]," P            : Save playlist for MP3 CD Player");
  strcpy (s[108],"                * Save your playlist (p,s). Make a");
  strcpy (s[109],"                  new playlist (p,n).Load Directory (D)");
  strcpy (s[110],"                  from the CD in your playlist.");
  strcpy (s[111],"                * Tested on JazzPIPER MCD650S");
  strcpy (s[112],"");
  strcpy (s[113],"PLAYER MODES");
  strcpy (s[114]," Normal       : Next song in playlist (don\'t shuffle)");
  strcpy (s[115]," Shuffle      : Random next song (shuffle)");
  strcpy (s[116]," Next Song    : Next song is already selected");
  strcpy (s[117]," Filter       : There are files in the filter");
  strcpy (s[118]," P-Filter     : The filter is persistent");
  strcpy (s[119]," Password     : Display is locked with password");
  strcpy (s[120]," Radio        : Start/Stop music at a specific time");
  strcpy (s[121]," Sleep        : Shut Down at a specific time");
  strcpy (s[122]," Shut Down    : Shut Down after current song");
  WINDOW *w1;
  w1=newwin (scr+2,62,7,(nrcols-62)/2);
  wrefresh (w1);
  werase (w1);
  WINDOW *w;
  w=newwin (scr,60,8,(nrcols-60)/2);
  wsetcolor (w,12,0);
  for (int h=0;h<=scr+2;h++) mvwprintw (w,h,0,"                                                             ");
  wsetcolor (w,12,0);
  le_border (w,60,scr);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Help ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr-1,46," ESC - quit ");
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
      if (v==ERR) v='q';
      if (v==91)
      {
        v=getch();
	if (v==65) if (k > 0) k--;
        if (v==66) if (k < 122-(scr-5)) k++;
      }
    }
  }    
  while (v!='q');
  werase (w);
  reread=1;
}
