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
  strcpy (s[1],"    Alexandru Radovici - alex_amysoft@hotmail.com");
  strcpy (s[2],"");
  strcpy (s[3],"AMYSOFT");
  strcpy (s[4],"    http://nike.lem.uttgm.ro/eclipse/amysoft");
  strcpy (s[5],"");
  strcpy (s[6],"LOTS OF THANKS");
  strcpy (s[7],"    Xaudio - http://www.xaudio.com");
  strcpy (s[8],"");
  strcpy (s[9],"COPYRIGHT & DISTRIBUTION");
  strcpy (s[10],"    This software is freeware, you may use it on your");
  strcpy (s[11],"own risk. You may distribute it only integral.");
  strcpy (s[12],"");
  strcpy (s[13],"UPDATE");
  strcpy (s[14],"    http://nike.lem.uttgm.ro/eclipse/linuxeyes");
  strcpy (s[15],"");
  strcpy (s[16],"BUGS & SUGGESTIONS");
  strcpy (s[17],"    If you find any bugs or have any suggestion please");
  strcpy (s[18],"e-mail me. (alex_amysoft@hotmail.com)");
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
  mvwprintw (w,0,1," Amysoft LinuxEyes ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr-1,46," q - quit ");
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
        if (v==66) if (k < 18-(scr-5)) k++;
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
  strcpy (s[33]," p            : Load Playlist");
  strcpy (s[34]," l            : Save Playlist");
  strcpy (s[35]," ?            : About");
  strcpy (s[36]," h            : Help");
  strcpy (s[37]," '            : Repaint Desktop");
  strcpy (s[38]," +            : Increase Playlist");
  strcpy (s[39]," -            : Decrease Playlist");
  strcpy (s[40]," q            : Quit");
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
  mvwprintw (w,0,1," Help ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr-1,46," q - quit ");
  wrefresh(w);
  noecho();
  timeout (1);
  k=0;
  do
  {
    for (int i=0;i<=scr-5;i++) 
    {
      mvwprintw (w,2+i,2,"                                                ");
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
        if (v==66) if (k < 40-(scr-5)) k++;
      }
    }
  }    
  while (v!='q');
  werase (w);
  reread=1;
}
