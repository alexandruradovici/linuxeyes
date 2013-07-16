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
  strcpy (s[4],"    LinuxEyes 0.9, build 0.9.3 (March 9, 2003 @ 22:23)");
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
  strcpy (s[25],"    Cosmin Chertes");
  strcpy (s[26],"    Ovidiu Stoica - oviska@hotmail.com");
  strcpy (s[27],"    Alexandru Armean - alex@lug.orizont.net");
  strcpy (s[28],"    Valeriu Moldovan - valeriu_moldovan@hotmail.com");
  strcpy (s[29],"    Cristian Klein - cristiklein@yahoo.com");
  strcpy (s[30],"");
  strcpy (s[31],"CURRENT SESSION STATISTICS");
  sprintf (s[32],"    Songs Played: %d",(int)n_songs);
  sprintf (s[33],"    Time Played: %d:%.2d:%.2d",(int)n_secs/(60*60),(int)(n_secs/60)%60,(int)n_secs%60);
  strcpy (s[34],"");
  strcpy (s[35],"GLOBAL STATISTICS");
  sprintf (s[36],"    Songs Played: %d",(int)songs);
  sprintf (s[37],"    Time Played: %d:%.2d:%.2d",(int)secs/(60*60),(int)(secs/60)%60,(int)secs%60);
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
    if (k<37-(scr-5)) mvwaddch (w,scr-1,28,ACS_DARROW);
    wrefresh(w);
    do
    {
      sprintf (s[32],"    Songs Played: %d",(int)n_songs);
      sprintf (s[33],"    Time Played: %d:%.2d:%.2d",(int)n_secs/(60*60),(int)(n_secs/60)%60,(int)n_secs%60);
      sprintf (s[36],"    Songs Played: %d",(int)songs);
      sprintf (s[37],"    Time Played: %d:%.2d:%.2d",(int)secs/(60*60),(int)(secs/60)%60,(int)secs%60);
      for (int i=0;i<=scr-5;i++) if (((i+k)==32) || ((i+k)==33) || ((i+k)==36) || ((i+k)==37))
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
        if (v==66) if (k < 37-(scr-5)) k++;
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
  int more=0;
  int cont=0;
  char s[200][100];
  strcpy(s[0],"COMMAND LINE");
  strcpy(s[1]," -p           : play");
  strcpy(s[2]," --colors     : force color usage");
  strcpy(s[3]," --nocolors   : B&W, for dummy terminals (telnet)");
  strcpy(s[4]," --autoscr    : force autodetect the screen's size");
  strcpy(s[5]," --noautoscr  : don't autodetect the screen's size");
  strcpy(s[6]," --fakelines  : draw lines on terminals without ACS");
  strcpy(s[7]," --new_start  : start with default configuration");
  strcpy(s[8],"");
  strcpy(s[9],"PLAYER");
  strcpy(s[10]," z            : previous");
  strcpy(s[11]," x            : play");
  strcpy(s[12]," c            : pause");
  strcpy(s[13]," v            : stop");
  strcpy(s[14]," b            : next");
  strcpy(s[15]," s            : Shuffle On/Off");
  strcpy(s[16]," <ENTER>      : Play ");
  strcpy(s[17]," <SPACE BAR>  : Set As Next ");
  strcpy(s[18]," <TAB>        : Add/Remove to/from filter ");
  strcpy(s[19]," <LEFT>       : Backward 1%");
  strcpy(s[20]," <RIGHT>      : Forward 1%");
  strcpy(s[21]," <            : Backward 5%");
  strcpy(s[22]," >            : Forward 5%");
  strcpy(s[23]," f            : On/Off persistent filter ");
  strcpy(s[24]," F            : Clear filter ");
  strcpy(s[25]," r            : Repreat current song ");
  strcpy(s[26]," i or ALT+3   : ID3v1.1 TAG Editor (for selected song)");
  strcpy(s[27]," I            : ID3v1.1 TAG Editor (for current song))");
  strcpy(s[28]," j or F3      : Jump to file");
  strcpy(s[29]," <INSERT>     : Volume + ");
  strcpy(s[30]," <DELETE>     : Volume - ");
  strcpy(s[31]," <HOME>       : PCM + ");
  strcpy(s[32]," <END>        : PCM - ");
  strcpy(s[33]," ,            : Balance left ");
  strcpy(s[34]," .            : Balance right ");
  strcpy(s[35]," e            : Equalizer");
  strcpy(s[36]," A            : Automatic Equalizer On/Off");
  strcpy(s[37]," '            : Repaint Desktop");
  strcpy(s[38]," *            : Increase desktop width");
  strcpy(s[39]," /            : Decrease desktop width");
  strcpy(s[40]," +            : Increase desktop height");
  strcpy(s[41]," -            : Decrease desktop height");
  strcpy(s[42]," t            : Switch clock display mode");
  strcpy(s[43]," \\            : Change Password");
  strcpy(s[44]," !            : Lock Display");
  strcpy(s[45]," =            : Cycle Status Bar Modes");
  strcpy(s[46]," h or F1      : Help");
  strcpy(s[47]," ?            : About and Statistics");
  strcpy(s[48]," {            : Set Alarm On Time");
  strcpy(s[49]," }            : Set Alarm Off Time");
  strcpy(s[50]," T            : Set Sleep mode");
  strcpy(s[51]," |            : On/Off Shut Down mode");
  strcpy(s[52]," o            : Settings");
  strcpy(s[53]," ESC          : Screen Saver");
  strcpy(s[54]," ALT+SHIFT+Q  : Quit");
  strcpy(s[55],"");
  strcpy(s[56],"PLAYLIST");
  strcpy(s[57]," a            : Add File");
  strcpy(s[58]," d            : Delete File");
  strcpy(s[59]," D            : Add Directory");
  strcpy(s[60]," R            : Delete All");
  strcpy(s[61]," S            : Sort Playlist");
  strcpy(s[62]," <UP>         : Cursor Up");
  strcpy(s[63]," <DOWN>       : Cursor Down");
  strcpy(s[64]," <PAGE UP>    : Page Up");
  strcpy(s[65]," <PAGE DOWN>  : Page Down");
  strcpy(s[66]," 0..9         : Fast Scroll");
  strcpy(s[67]," [            : Move Up");
  strcpy(s[68]," '            : Move Down");
  strcpy(s[69]," l            : Locate Current Song");
  strcpy(s[70]," L            : Autolocate Current Song");
  strcpy(s[71]," p            : Playlist Options");
  strcpy(s[72]," p,n          : New Playlist");
  strcpy(s[73]," p,l          : Load Playlist");
  strcpy(s[74]," p,s          : Save Playlist");
  strcpy(s[75]," p,i          : Import Playlist");
  strcpy(s[76]," p,e          : Export Playlist");
  strcpy(s[77]," E            : Edit playlist file entry");
  strcpy(s[78]," n            : Refresh list");
  strcpy(s[79]," ;            : On/Off save playlist position on exit");
  strcpy(s[80],"");
  strcpy(s[81],"JUMP TO FILE");
  strcpy(s[82]," <ENTER>      : Play");
  strcpy(s[83]," <SPACE BAR>  : Set as next");
  strcpy(s[84]," <TAB>        : Add/Remove to/from filter");
  strcpy(s[85]," F            : Add/Remove all songs to filter");
  strcpy(s[86]," i            : ID3 TAG Edditor");
  strcpy(s[87]," ESC or q     : Close window");
  strcpy(s[88],"");
  strcpy(s[89],"EQUALIZER WINDOW");
  strcpy(s[90]," <PAGE UP>    : Up ALL");
  strcpy(s[91]," <PAGE DOWN>  : Down ALL");
  strcpy(s[92]," a/z          : Up/Down Band #1");
  strcpy(s[93]," s/x          : Up/Down Band #2");
  strcpy(s[94]," d/c          : Up/Down Band #3");
  strcpy(s[95]," f/v          : Up/Down Band #4");
  strcpy(s[96]," g/b          : Up/Down Band #5");
  strcpy(s[97]," h/n          : Up/Down Band #6");
  strcpy(s[98]," j/m          : Up/Down Band #7");
  strcpy(s[99]," k/,          : Up/Down Band #8");
  strcpy(s[100]," l/.          : Up/Down Band #9");
  strcpy(s[101]," ;//          : Up/Down Band #10");
  strcpy(s[102]," r            : Set all bands to 0 (reset equalizer)");
  strcpy(s[103]," L            : Load Preset");
  strcpy(s[104]," S            : Save Preset");
  strcpy(s[105]," I            : Import Preset(s)");
  strcpy(s[106]," D            : Delete Preset(s)");
  strcpy(s[107]," A            : On/Off Automatic Equalizer");
  strcpy(s[108],"");
  strcpy(s[109],"STATISTICS");
  strcpy(s[110]," R            : Reset current session statistics");
  strcpy(s[111],"");
  strcpy(s[112],"SPECIAL FUNCTIONS");
  strcpy(s[113]," P            : Save playlist for MP3 CD Player");
  strcpy(s[114],"                * Save your playlist (p,s). Make a");
  strcpy(s[115],"                  new playlist (p,n).Load Directory (D)");
  strcpy(s[116],"                  from the CD in your playlist.");
  strcpy(s[117],"                * Tested on JazzPIPER MCD650S");
  strcpy(s[118],"");
  strcpy(s[119],"PLAYER MODES");
  strcpy(s[120]," Normal       : Next song in playlist (don\'t shuffle)");
  strcpy(s[121]," Shuffle      : Random next song (shuffle)");
  strcpy(s[122]," Next Song    : Next song is already selected");
  strcpy(s[123]," Filter       : There are files in the filter");
  strcpy(s[124]," P-Filter     : The filter is persistent");
  strcpy(s[125]," Password     : Display is locked with password");
  strcpy(s[126]," Sleep        : Shut Down at a specific time");
  strcpy(s[127]," Shut Down    : Shut Down after current song");
  strcpy(s[128],"");
  strcpy(s[129],"STATUS BAR");
  strcpy(s[130]," Mode 1       : Displays mode, vol, pcm, bal & flags");
  strcpy(s[131]," Mode 2       : Displays next song's name");
  strcpy(s[132]," Mode 3       : Displays nr of files in filter");
  strcpy(s[133]," Mode 4       : Displays alram start & stop time");
  strcpy(s[134]," Mode 5       : Displays shut down time");
  strcpy(s[135]," Flags   S - save playlist on exit");
  strcpy(s[136],"         E - auto equalizer");
  strcpy(s[137],"         L - autolocate current song");
  strcpy(s[138],"         P - use persistent filter");
  strcpy(s[139],"         A - Alarm is set");
  const int help_lines=139;
  
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
    if (more < 0) {k--; more++; cont=1;}
    if (more > 0) {k++; more--; cont=1;}
    if (k < 0) k=0;
    if (k > help_lines-(scr-5)) k=help_lines-(scr-5);
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
    if (k<help_lines-(scr-5)) mvwaddch (w,scr-1,28,ACS_DARROW);
    wrefresh(w);
    do
    {
      messages();
      v=getch();
    } while ((v==ERR) && (cont==0));
    cont=0;
    if (v == 27) 
    {
      v=getch();
      if (v==ERR) v='q';
      if (v==91)
      {
        v=getch();
	if (v==65) k--; 
        if (v==66) k++;
	if (v==53) more=-scr+4;
	if (v==54) more=scr-4;
      }
    }
  }    
  while (v!='q');
  werase (w);
  reread=1;
}

