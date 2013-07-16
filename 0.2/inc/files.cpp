#include <unistd.h>
#include <sys/stat.h>
void showfiles(int scr,char *file,char s[100],int typeofshow)
{
  int q=0;
  int v;
  int y=0,k=0,m=0,l=0,numar=0,n=0;
  int nrsel=0;
  char buf[5000];
  struct
  {
    char name[1000];
    int sel;
  } filestoshow[1000];    
  struct dirent **namelist;
  struct stat BUF;
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
  mvwprintw (w,0,1," %s ",s);
  wsetcolor (w,12,0);
  mvwprintw (w,scr-1,30," space - select | q - quit ");
  wrefresh(w);
  noecho();
  do
  {
    y=-1;
    k=0;
    m=0;
    numar=scandir (".",&namelist,0,alphasort);
    for (int x=0;x<numar;x++) 
    {
      stat (namelist[x]->d_name,&BUF);	
      if (S_ISDIR(BUF.st_mode) != 0)
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
        if (S_ISDIR(BUF.st_mode) == 0)
        {
          y++;
	  strcpy (filestoshow[y].name,namelist[x]->d_name);
	  filestoshow[y].sel=0;
        }
      }
      n=numar;
    }
    else n=y+1;
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
	stat (filestoshow[m+i].name,&BUF);	
	if (S_ISDIR(BUF.st_mode) != 0) mvwprintw (w,i+1,2,"/%s",filestoshow[m+i].name);
	else mvwprintw (w,i+1,2,"%s",filestoshow[m+i].name);
      }
      wsetcolor (w,8,0);
      for (int i=l+1;i<scr-1;i++) mvwprintw (w,i,2,"                                                        ");
      wrefresh(w);
      timeout (1);
      do
      {
        messages();
        v=getch();
      } while (v==ERR);
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
	if (v==91)
	{
	  v=getch();
	  if (v==65) k--;
	  if (v==66) k++;
	}
      }
      if (k < 0) if (m > 0) { k++;m--; }
      else k++;
      if ((m+k) > n-1) k--;
      if (k > scr-3) { m++;k--; } 
      if ((typeofshow==1) && (v==' ')) { v='\n';q=3; }
    }
    while ((v!='\n') && (v!='q'));
    stat (filestoshow[m+k].name,&BUF);
    if (v=='\n') if (S_ISDIR(BUF.st_mode) == 0) { q=1;filestoshow[m+k].sel=1; }
    else if (q!=3) chdir (filestoshow[m+k].name);
    if (v=='q') q=2;
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
