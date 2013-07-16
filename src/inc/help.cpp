#include "help/le_help.cpp"

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
  int q=0;
  char s[100][100];
  strcpy (s[0],"AUTHOR");
  strcpy (s[1],"    Alexandru Radovici - msg4alex@rdslink.ro");
  strcpy (s[2],"");
  strcpy (s[3],"VERSION");
  sprintf (s[4],"    LinuxEyes %s (%s)",version,v_name);
  sprintf (s[5],"      Build: %s",build);
  sprintf (s[6],"      Date: %s",bdate);
  /*
  strcpy (s[4],"    LinuxEyes ");
    strcat (s[4],version);
    strcat (s[4],", build ");
    strcat (s[4],build);
    strcat (s[4]," (");
    strcat (s[4],bdate);
    strcat (s[4],")");*/
  strcpy (s[7],"");
  if (sysinfo!=-1) strcpy (s[8],"SYSTEM INFORMATION");
  else strcpy (s[8],"SYSTEM INFORMATION (may not be correct)");
  sprintf (s[9],"    OS: %s",computer.sysname);
  sprintf (s[10],"    Release: %s",computer.release);
  sprintf (s[11],"    Version: %s",computer.version);
  sprintf (s[12],"    Processor: %s",computer.machine);
  sprintf (s[13],"    Hostname: %s",computer.nodename);
  sprintf (s[14],"    Domain: %s",computer.domainname);
  strcpy (s[15],"");
  strcpy (s[16],"ROMANIAN SOFTWARE");
  strcpy (s[17],"    This software was made in Romania!");
  strcpy (s[18],"");
  strcpy (s[19],"WEBSITE");
  strcpy (s[20],"    http://lug.orizont.net/~linuxeyes");
  strcpy (s[21],"");
  strcpy (s[22],"COPYRIGHT & DISTRIBUTION");
  strcpy (s[23],"    This software is freeware, you may use it on your");
  strcpy (s[24],"own risk. You may distribute it only integral.");
  strcpy (s[25],"");
  strcpy (s[26],"MPEG Audio Layer 3");
  strcpy (s[27],"    Xaudio - http://www.xaudio.com");
  strcpy (s[28],"");
  strcpy (s[29],"BUGS & SUGGESTIONS");
  strcpy (s[30],"    If you find any bugs or have any suggestion please");
  strcpy (s[31],"email me. (linuxeyes@lug.orizont.net) Thank you!");
  strcpy (s[32],"");
  strcpy (s[33],"LOTS OF THANKS TO");
  strcpy (s[34],"    Vera and Iuliu Radovici");
  strcpy (s[35],"    Cosmin Chertes");
  strcpy (s[36],"    Ovidiu Stoica - oviska@hotmail.com");
  strcpy (s[37],"    Alexandru Armean - alex@sparetimegroup.net");
  strcpy (s[38],"    Valeriu Moldovan - valeriu_moldovan@hotmail.com");
  strcpy (s[39],"    Cristian Klein - cristiklein@yahoo.com");
  strcpy (s[40],"");
  strcpy (s[41],"CURRENT SESSION STATISTICS");
  sprintf (s[42],"    Songs Played: %d",(int)n_songs);
  sprintf (s[43],"    Time Played: %d:%.2d:%.2d",(int)n_secs/(60*60),(int)(n_secs/60)%60,(int)n_secs%60);
  strcpy (s[44],"");
  strcpy (s[45],"GLOBAL STATISTICS");
  sprintf (s[46],"    Songs Played: %d",(int)songs);
  sprintf (s[47],"    Time Played: %d:%.2d:%.2d",(int)secs/(60*60),(int)(secs/60)%60,(int)secs%60);
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
    if (k<47-(scr-5)) mvwaddch (w,scr-1,28,ACS_DARROW);
    wrefresh(w);
    do
    {
      sprintf (s[42],"    Songs Played: %d",(int)n_songs);
      sprintf (s[43],"    Time Played: %d:%.2d:%.2d",(int)n_secs/(60*60),(int)(n_secs/60)%60,(int)n_secs%60);
      sprintf (s[46],"    Songs Played: %d",(int)songs);
      sprintf (s[47],"    Time Played: %d:%.2d:%.2d",(int)secs/(60*60),(int)(secs/60)%60,(int)secs%60);
      for (int i=0;i<=scr-5;i++) if (((i+k)==42) || ((i+k)==43) || ((i+k)==46) || ((i+k)==47))
      {
        wsetcolor (w,12,0);
        mvwprintw (w,2+i,2,"                                                         ");
        mvwprintw (w,2+i,2,"%s",s[i+k]);
	wrefresh (w);
      }
      messages();
      v=getch();
      if ((try_again) && (v==ERR)) playnext();
    } while (v==ERR);
    if (v=='q') q=1;
    if (v == 27) 
    {
      v=getch();
      if (v==ERR) q=1;
      if (v==91)
      {
        v=getch();
	if (v==65) if (k > 0) k--;
        if (v==66) if (k < 47-(scr-5)) k++;
      }
    }
    if (v=='R')
    {
      n_songs=0;
      n_secs=0;
    }
    if (quit==1) q=1;
    while (v!=ERR) v=getch();
  }    
  while (q==0);
  werase (w);
  reread=1;
}

void help(int scr)
{
  int v,k;
  int more=0;
  int cont=0;
  int q=0;
  make_help();
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
      mvwprintw (w,2+i,2,"%s",help_s[i+k]);
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
      if ((try_again) && (v==ERR)) playnext();
    } while ((v==ERR) && (cont==0));
    cont=0;
    if (v == 'q') q=1;
    if (v == 27) 
    {
      v=getch();
      if (v==ERR) q=1;
      if (v==91)
      {
        v=getch();
	if (v==65) k--; 
        if (v==66) k++;
	if (v==53) more=-scr+4;
	if (v==54) more=scr-4;
      }
    }
    if (quit==1) q=1;
    while (v!=ERR) v=getch();
  }    
  while (q==0);
  werase (w);
  reread=1;
}

void hello()
{
  int scr=14;
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
  mvwprintw (w,0,1," Welcome to LinuxEyes ");
  wsetcolor (w,12,0);
  mvwprintw (w,scr-1,46," ESC - quit ");
  wrefresh(w);
  char s[11][100];
  strcpy (s[0],"    Thank you for installing LinuxEyes. I hope you will");
  strcpy (s[1],"enjoy using this player as much as I enjoyed makeing it.");
  strcpy (s[2],"");
  strcpy (s[3],"    If you have any questions or you would like to send");
  strcpy (s[4],"me some suggestions or some bugs information please just");
  strcpy (s[5],"email me at linuxeyes@lug.orizont.net. Thank you!");
  strcpy (s[6],"    For more information about using LinuxEyes, please");
  strcpy (s[7],"press 'h' to view the help page or visit the website.");
  strcpy (s[8],"                                               Have Fun!");
  strcpy (s[9],"http://lug.orizont.net/~linuxeyes");
  strcpy (s[10],"LinuxEyes v");
    strcat (s[10],version);
    strcat (s[10]," - ");
    strcat (s[10],bday);
    strcat (s[10],", ");
    strcat (s[10],bdate);
  noecho();
  play ("/usr/lib/linuxeyes/music/linuxeyes.mp3");
  timeout (1);
  int t=0;
  int q=0;
  wsetcolor (w,12,0);
  for (int i=0;i<=10;i++) 
  {
    mvwprintw (w,2+i,2,"                                                         ");
    mvwprintw (w,2+i,2,"%s",s[i]);
  }
  wrefresh (w);
  do
  {
    t=getch();
    messages();
    if (t==27)
    {
      t=getch();
      if (t==ERR) q=1;
    }
    if ((try_again) && (t==ERR)) playnext();
    if (quit==1) q=1;
    while (t!=ERR) t=getch();
  } while (q==0);
  werase (w);
  reread=1;
}
