#include <unistd.h>
#include <sys/stat.h>

void showfiles(int scr, int nrcols2, char *file,char s[100],int typeofshow, char *dir)
{
  int reset_d=0;
  nrcols2=nrcols2-18;
  int more=0;
  int reread=0;
  int q=0;
  int v;
  int y=0,k=0,m=0,l=0,numar=0,n=0;
  int nrsel=0;
  char buf[5000];
  struct
  {
    char name[1200];
    int sel;
  } filestoshow[6000];    
  struct dirent **namelist;
  struct stat BUF;
  WINDOW *w1;
  w1=newwin (scr+2,nrcols2+2,(nrscr-(scr+2))/2+7,(nrcols-nrcols2-2)/2);
  wrefresh (w1);
  werase (w1);
  WINDOW *w;
  w=newwin (scr,nrcols2,(nrscr-(scr+2))/2+8,(nrcols-nrcols2)/2);
  nrcols2=nrcols2+18;
  wsetcolor (w,12,0);
  for (int h=0;h<=scr+2;h++) 
    for (int z=0;z<=nrcols2-18;z++)
       mvwprintw (w,h,0+z," ");
  wsetcolor (w,12,0);
  le_border (w,nrcols2-18,scr);
  //wborder_set (w,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," %s ",s);
  wsetcolor (w,12,0);
  mvwprintw (w,scr-1,nrcols2-61," TAB - play | space - select | ESC - quit ");
  wrefresh(w);
  noecho();
  do
  {
    y=-1;
    k=0;
    m=0;
    numar=scandir (dir,&namelist,0,alphasort);
    for (int x=0;x<numar;x++) 
    {
      stat (namelist[x]->d_name,&BUF);	
      if ((S_ISDIR(BUF.st_mode) != 0) && (strcmp(namelist[x]->d_name,".")!=0))
      {
        y++;
	strcpy (filestoshow[y].name,namelist[x]->d_name);
	filestoshow[y].sel=0;
      }
    }  
    if (typeofshow == 0)
    {
      for (int x=0;x<numar;x++)
      {
        stat (namelist[x]->d_name,&BUF);	
        if ((S_ISDIR(BUF.st_mode) == 0) && (strcmp(namelist[x]->d_name,".")!=0))
        {
          y++;
	  strcpy (filestoshow[y].name,namelist[x]->d_name);
	  filestoshow[y].sel=0;
        }
      }
      n=numar-1;
    }
    else n=y+1;
    if (n > scr-2) l=scr-2;
    else l=n;
    do
    {
      if (reset_d==1)
      {
        wsetcolor (w,12,0);
        for (int h=0;h<=scr+2;h++) 
          for (int z=0;z<=nrcols2-18;z++)
            mvwprintw (w,h,0+z," ");
        wsetcolor (w,12,0);
        le_border (w,nrcols2-18,scr);
        wsetcolor (w,13,1);
        mvwprintw (w,0,1," %s ",s);
        wsetcolor (w,12,0);
        mvwprintw (w,scr-1,nrcols2-61," TAB - play | space - select | ESC - quit ");
        wrefresh(w);
	reset_d=0;
      }
      for (int i=0;i<l;i++)
      {
        int col;
        if (k==i) col=10;
	else col=8;
	if (filestoshow[m+i].sel==1) col=col+1;
	wsetcolor (w,col,0);
	for (int z=0;z<nrcols2-22;z++) mvwprintw (w,i+1,2+z," ");
	stat (filestoshow[m+i].name,&BUF);	
	char tempstr2[1000];
	strcpy (tempstr2,"/");
	strcat (tempstr2,filestoshow[m+i].name);
	if (S_ISDIR(BUF.st_mode) != 0) labelw (w,i+1,2,tempstr2,nrcols2-25);//mvwprintw (w,i+1,2,"/%.56s",filestoshow[m+i].name);
	else labelw (w,i+1,2,(char*)filestoshow[m+i].name,nrcols2-24);//mvwprintw (w,i+1,2,"%.56s",filestoshow[m+i].name);
      }
      wsetcolor (w,8,0);
      for (int i=l;i<scr-2;i++) for (int z=0;z<nrcols2-22;z++) mvwprintw (w,i+1,2+z," "); //mvwprintw (w,i,2,"                                                        ");
      wrefresh(w);
      timeout (1);
      do
      {
        messages();
        v=getch();
	if ((try_again) && (v==ERR)) playnext();
      } while ((v==ERR) && (reread==0));
      reread=0;
      if ((v==' ') && (typeofshow==0)) 
      {
        if (filestoshow[m+k].sel==0) filestoshow[m+k].sel=1;
        else filestoshow[m+k].sel=0;
	k++;
      }				       			      
      if (v=='q') q=2;
      if (v=='i') 
	{
          getcwd (buf,sizeof(buf));
          strcat (buf,"/");
          strcat (buf,filestoshow[m+k].name);
	  showid3 (buf,0);
	  reset_d=1;
	}
      if (v==9) 
      {
        getcwd (buf,sizeof(buf));
        strcat (buf,"/");
        strcat (buf,filestoshow[m+k].name);
        play (buf);
      }
      if (v=='z') playprev();
      if (v=='x') play (curent.name);
      if (v=='c') mpegpause ();
      if (v=='v') stop ();
      if (v=='b') playnext();
//      if (v==9) play ("/usr/lib/linuxeyes/music/linuxeyes.mp3");
      if (v=='>') position (5);
      if (v=='<') position (-5);
      if (v==27)
      {
        v=getch();
	if (((v>=97) && (v<=122)) || ((v>=65) && (v<=90)))
	{
	  int f=-1;
	  for (int q=m+k+1;((q<=n) && (f==-1));q++)
	  {
	    if (filestoshow[q].name[0]==(char)v) f=q;
	  }
	  if (m+k>0) for (int q=0;((q<=n) && (f==-1));q++) if (filestoshow[q].name[0]==(char)v) f=q;
	  if (f>-1) 
	  {
	    int h=f/(scr-3);
	    k=f%(scr-3);
	    m=(scr-3)*h;
	  }
	  v=0;
	}
	if (v==32)
        {
          getcwd (buf,sizeof(buf));
          strcat (buf,"/");
          strcat (buf,filestoshow[m+k].name);
	  id3 (buf,&my_id3);
          strcpy (next.name,buf); 
  	  strcpy (next.text,text);
        }
	if (v==51) 
	{
          getcwd (buf,sizeof(buf));
          strcat (buf,"/");
          strcat (buf,filestoshow[m+k].name);
	  showid3 (buf,0);
	  reset_d=1;
	}
	if (v==91)
	{
	  v=getch();
	  if (v==65) k--;
	  if (v==66) k++;
	  if (v==67) position (1);
	  if (v==68) position (-1);
	  if (v==53) more=-scr+2;
	  if (v==54) more=scr-2;
	}
	if (v==ERR) v='q';
      }
      if (more < 0) {k=0; more++;m--; reread=1;}
      if (more > 0) {k=l-1; more--;if ((m+k+1) < n) m++; reread=1;}
      if (k < 0) if (m > 0) { k++;m--; }
      else k++;
      if ((m+k) > n-1) k--;
      if (k > scr-3) { m++;k--; } 
      if (m<0) m=0;
      if ((typeofshow==1) && (v==' ')) { v='\n';q=3; }
    }
    while ((v!='\n') && (v!='q'));
    stat (filestoshow[m+k].name,&BUF);
    if (v=='\n') if (S_ISDIR(BUF.st_mode) == 0) { q=1;filestoshow[m+k].sel=1; }
    else if (q!=3) chdir (filestoshow[m+k].name);
    if (v=='q') q=2;
    if (quit==1) q=1;
    while (v!=ERR) v=getch();
  } while (q==0);
  werase (w);
  getcwd (buf,sizeof(buf));
  nrsel=-1;
  for (int i=0;i<n;i++)
  if (filestoshow[i].sel==1)
  {
    nrsel++;
    strcpy (mpegfile[nrsel],buf);
    strcat (mpegfile[nrsel],"/");
    strcat (mpegfile[nrsel],filestoshow[i].name);
  }    
  mpegnumber=nrsel;
  if (q==2) mpegnumber=-1;
  if (q==3) 
  {
    strcpy (mpegfile[0],buf);
    strcat (mpegfile[0],"/");
    strcat (mpegfile[0],filestoshow[m+k].name);
    mpegnumber=0;
  }    
}

int showlist(int scr,char s[100],int typeofshow, list_type list, int numar)
{
  int key=0;
  int more=0;
  int reread=0;
  int q=0;
  int v;
  int y=0,k=0,m=0,l=0,n=0;
  int nrsel=0;
  struct
  {
    char name[1200];
    int sel;
  } filestoshow[6000];    
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
  //wborder_set (w,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," %s ",s);
  wsetcolor (w,12,0);
  mvwprintw (w,scr-1,28," space - select | ESC - quit ");
  wrefresh(w);
  noecho();
  do
  {
    y=-1;
    k=0;
    m=0;
    for (int i=0;i<=numar;i++) 
    {
      strcpy (filestoshow[i].name,list[i]);
      filestoshow[i].sel=0;
    }
    n=numar+1;
    if (n > scr-2) l=scr-2;
    else l=n;
    do
    {
      for (int i=0;i<l;i++)
      {
        int col;
        if (k==i) col=10;
	else col=8;
	if (filestoshow[m+i].sel==1) col=col+1;
	wsetcolor (w,col,0);
	mvwprintw (w,i+1,2,"                                                        ");
	labelw (w,i+1,2,filestoshow[m+i].name,56);
//	mvwprintw (w,i+1,2,"%.56s",filestoshow[m+i].name);
      }
      wsetcolor (w,8,0);
      for (int i=l+1;i<scr-1;i++) mvwprintw (w,i,2,"                                                        ");
      wrefresh(w);
      timeout (1);
      do
      {
        messages();
        v=getch();
	if ((try_again) && (v==ERR)) playnext();
      } while ((v==ERR) && (reread==0));
      reread=0;
      if ((v==' ') && (typeofshow==0)) 
      {
        if (filestoshow[m+k].sel==0) filestoshow[m+k].sel=1;
        else filestoshow[m+k].sel=0;
	k++;
      }				       			      
      if (v=='q') q=2;
      if (v==27)
      {
        v=getch();
	if (v==ERR) v='q';
	if (v==91)
	{
	  v=getch();
	  if (v==65) k--;
	  if (v==66) k++;
	  if (v==53) more=-scr+2;
	  if (v==54) more=scr-2;
	}
      }
      if (more < 0) {k=0; more++;m--; reread=1;}
      if (more > 0) {k=l-1; more--;if ((m+k+1) < n) m++; reread=1;}
      if (k < 0) if (m > 0) { k++;m--; }
      else k++;
      if ((m+k) > n-1) k--;
      if (k > scr-3) { m++;k--; } 
      if (m<0) m=0;
      if ((typeofshow==1) && (v==' ')) { v='\n';q=3; }
    }
    while ((v!='\n') && (v!='q'));
    if (v=='\n') { q=1;filestoshow[m+k].sel=1;key=1; }
    if (v=='q') 
    {
      q=2;
      key=0;
    }
    if (quit==1) q=1;
    while (v!=ERR) v=getch();
  } while (q==0);
  werase (w);
  nrsel=-1;
  for (int i=0;i<n;i++)
  if (filestoshow[i].sel==1)
  {
    nrsel++;
    strcpy (mpegfile[nrsel],filestoshow[i].name);
  }    
  mpegnumber=nrsel;
  if (q==2) mpegnumber=-1;
  if (q==3) 
  {
    strcpy (mpegfile[0],filestoshow[m+k].name);
    mpegnumber=0;
  }  
  return key;  
}
