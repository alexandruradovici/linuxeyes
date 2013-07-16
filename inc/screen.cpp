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
  screen=1;
  WINDOW *w;
  w=newwin (nrscr+10,nrcols+2,0,0);
  wclear (w);
  wrefresh (w);
  timeout (1);
  do
  {
    t=getch();
    messages();
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
    labelw (w,(nrscr)/2+6,((nrcols-k)/2),ora,strlen(ora)+1);
    wsetcolor (w,1,0);
    wrefresh(w);
    if ((t!=ERR) && (password==1))
	{
	  strcpy (memstring,"");
	  if (readstring_window ("Unlock Display","Password",1,'*',0)) if (strcmp (passwordstr,memstring)==0) 
	  { 
	    password=0; 
	    q=1;
	  }
	  else q=0;;
	}
    if ((t!=ERR) && (password==0)) q=1;
    if ((try_again) && (t==ERR)) playnext();
    if (quit==1) q=1;
  } while (q==0);
  screen=0;
  while (t!=ERR) t=getch();
}
