list_type presets;

int load_xmms_preset (char *file, char *preset, char *path);
int load_winamp_preset (char *file, char *preset, char *path);
int load_equ_preset (char *file, char*preset);
int save_to_equ (char *file, char *name);
int delete_equ (char *file, char *name);

// LE v0_6 presets

int load_from_le0_6()
{
  showfiles (14,78,".","Select an equalizer file to import",0,".");
  if (mpegnumber > -1)
  {
    std::ifstream f(mpegfile[0]);
    if (!f.fail())
    {
       f >>eq.left >>eq.right;
      for (int i=0;i<=31;i++) 
      {
        //f >>equalizer.left[i];
        //equalizer.right[i]=equalizer.left[i];
      }
    }
  }
  return 0;
}

// EQF

int load_from_eqf()
{
  int e=0;
  char eqf[27];
  showfiles (14,78,".","Select an EQF file to import",0,".");
  if (mpegnumber > -1)
  {
    FILE *f;
    f=fopen (mpegfile[0],"r");
    if (f!=NULL)
    {
      fseek (f,0,SEEK_SET);
      fread (&eqf,27,1,f);
//      fprintf (stderr,"%s",eqf);
      if (eqf!=NULL) if (memcmp (eqf,"Winamp EQ library file v1.1",27)==0) e=0;else e=2;
      else e=2;
      fseek (f,-11,SEEK_END);
      if (e==0) e=fread (&imported_eq_preset,10,1,f);
      if (e==1)
      {
        for (int i=0;i<=9;i++) imported_eq_preset[i]=((-imported_eq_preset[i]+31)*4);
      }
      fclose (f);
    }
  }
  if (e!=1) e=0;
  return e;
}

// Winamp

int list_from_winamp (char *file)
{
  int i=-1;
  int e=0;
  char eqf[27];
  char temp[268];
  char *eq_file;
  eq_file=strdup (file);
  FILE *f;
  f=fopen (file,"r");
  if (f!=NULL)
  {
    fseek (f,0,SEEK_SET);
    fread (&eqf,27,1,f);
    if (eqf!=NULL) if (memcmp (eqf,"Winamp EQ library file v1.1",27)==0) e=0;else e=2;
    else e=2;
    if (e==0)
    {
      e=fseek (f,31,SEEK_SET);
//      for (unsigned int j=0;j++;j<=((sizeof (f)-31)/268))
      while (!feof(f))
      {
        i++;
	fread (&temp,268,1,f);
	presets[i][0]='\0';
	int j=-1;
	int found=0;
	while ((j<=45) && (found==0))
	{
	  j++;
	  if (temp[j]=='\0') found=1;
	  else presets[i][j]=temp[j];
	}
	presets[i][j]='\0';
      }
    }
    fclose (f);
    i--;
  }
  //window
  showlist (14,"Winamp eq presets",0,presets,i);
  int noload=1;
  if (mpegnumber > -1)
  {
    char path[1000];
    strcpy (path,getenv("HOME"));
    strcat (path,"/.linuxeyes.eq");
    if (mpegnumber==0) return load_winamp_preset (eq_file, mpegfile[0], "");
    else
    {
      for (int i=0;i<=mpegnumber;i++) load_winamp_preset (eq_file, mpegfile[i], path);
      if (mpegnumber>0) noload=0;
    }
  } else return 0;
  if (noload==0) return 0;
  return i;
}

int load_winamp_preset (char *file, char *preset, char *path)
{
   char eqf[27];
   char temp[268];
   char *eq_file;
   char preset1[100];
   int e=0;
   int loaded=0;
   eq_file=strdup (file);
   FILE *f;
   f=fopen (file,"r");
   if (f!=NULL)
   {
     fseek (f,0,SEEK_SET);
     fread (&eqf,27,1,f);
     if (eqf!=NULL) if (memcmp (eqf,"Winamp EQ library file v1.1",27)==0) e=0;else e=2;
     else e=2;
     if (e==0)
     {
       e=fseek (f,31,SEEK_SET);
       while (!feof(f))
       {
 	 fread (&temp,268,1,f);
	 preset1[0]='\0';
	 int j=-1;
	 int found=0;
	 while ((j<=45) && (found==0))
	 {
	   j++;
	   if (temp[j]=='\0') found=1;
	   else preset1[j]=temp[j];
	 }
	 preset1[j]='\0';
	 if (preset1!=NULL) if (strcmp ((char*)preset,preset1)==0)
	 {
	   loaded=1;
	   for (int i=0;i<=9;i++)
	     if (strcmp(path,"")!=0) exported_eq_preset[i]=((-temp[257+i]+31)*4)+127;
	     else imported_eq_preset[i]=((-temp[257+i]+31)*4);
	 }
       }
     }
     fclose (f);
     if ((strcmp (path,"")!=0) && (loaded==1)) save_to_equ (path,preset);
   } else return 0;
   return 1;
}

// XMMS presets

int list_from_xmms (char *file)
{
   int i=-1;
   char *eq_file;
   eq_file=strdup (file);
   std::ifstream f;
   f.open (file);
   if (!f.fail())
   {
     char data[200];
     f.getline (data,sizeof(data));
     if (strcmp (data,"[Presets]")==0)
     {
       f.getline (data,sizeof(data));
       while ((strcmp(data,"")!=0) && (!f.eof()))
       {
	 i++;
	 strcpy (presets[i],(char*)index(data,'=')+1);
	 f.getline (data,sizeof(data));
       }
     }
     f.close();
   }
   else return 0;
   //window
   showlist (14,"XMMS eq presets",0,presets,i);
   int noload=1;
   if (mpegnumber > -1)
   {
     char path[1000];
     strcpy (path,getenv("HOME"));
     strcat (path,"/.linuxeyes.eq");
     if (mpegnumber==0) return load_xmms_preset (eq_file, mpegfile[0], "");
     else
     {
       for (int i=0;i<=mpegnumber;i++) load_xmms_preset (eq_file, mpegfile[i], path);
       if (mpegnumber>0) noload=0;
     }
   } else return 0;
   if (noload==0) return 0;
   return i;
}

int load_xmms_preset (char *file, char *preset, char *path)
{
   int i=-1;
   int loaded=0;
   std::ifstream f;
   f.open (file);
   if (!f.fail())
   {
     char data[200];
     char temp[200];
     char *preset1;
     preset1=strdup (preset);
     strcpy (temp,"[");
     strcat (temp,(char*)preset);
     strcat (temp,"]");
     f.getline (data,sizeof(data));
     while ((strcmp(data,temp)!=0) && (!f.eof())) f.getline (data,sizeof(data));
     if (strcmp(data,temp)==0)
     {
       loaded=1;
       f.getline (data,sizeof(data));
       f.getline (data,sizeof(data));
       while ((strcmp(data,"")!=0) && (!f.eof()))
       {
         float x;
	 i++;
	 strcpy (temp,(char*)index(data,'=')+1);
	 sscanf (temp,"%f",&x);
	 x=x+19.375;
	 x=(x*256)/39.375;
	 if (strcmp(path,"")!=0)
	 {
	   exported_eq_preset[i]=(int)x;
	 }
	 else
	 {
	   x=x-127;
	   imported_eq_preset[i]=(signed int)x;
	 }
         f.getline (data,sizeof(data));
       }
     }
     f.close();
     if ((strcmp (path,"")!=0) && (loaded==1)) save_to_equ (path,preset1);
   }
   else return 0;
   return 1;
}

// linuxeyes presets

int list_from_equ (char *file, int action)
{
   int i=-1;
   char *eq_file;
   eq_file=strdup (file);
   std::ifstream f;
   f.open (file);
   if (!f.fail())
   {
     char data[200];
     f.getline (data,sizeof(data));
     if (strcmp (data,"LE_EQU0_8Presets")==0)
     {
       while (!f.eof())
       {
         f.getline (data,sizeof(data));
         if (data[0]=='@')
         {
	   i++;
	   strcpy (presets[i],(char*)(index(data,'@')+1));
	   //printf ("%s\n",presets[i]);
         }
       }
     }
     f.close();
   }
   else return 0;
   //window
   if (action==1) showlist (14,"Load Equalizer Preset",1,presets,i);
   if (action==2) showlist (14,"Delete Equalizer Preset",0,presets,i);
   if (mpegnumber > -1)
   {
     if (action==1) return load_equ_preset (eq_file, mpegfile[0]);
     if (action==2) 
     for (int i=0;i<=mpegnumber;i++) delete_equ (eq_file, mpegfile[i]);
   }
   return 0;
}

int save_to_equ (char *file, char *name)
{
   int i=-1;
   int e=0; // error = 0
   int n=0; // new preset=0
   std::ifstream f;
   char *eq_file;
   char temp[200];
   eq_file = strdup (file);
   std::ofstream t;
   f.open (file);
   if (!f.fail())
   {
     char data[200];
     f.getline (data,sizeof(data));
     if (strcmp (data,"LE_EQU0_8Presets")==0)
     {
       f.getline (data,sizeof(data));
       while (!f.eof())
       {
	 i++;
         if (data[0]=='@') strcpy (temp,(char*)(index(data,'@')+1));
	 else strcpy (temp,"");
	 if ((strcmp (temp,(char*)name)==0) && (!f.eof()))
	 {
	   strcpy (presets[i],data);
	   i++;
	   strcpy (presets[i],exported_eq_preset);
	   n=1;
	 } else strcpy (presets[i],data);
	 //printf ("%s\n",presets[i]);
         f.getline (data,sizeof(data));
       }
     }
     f.close();
   } else e=1;
   if (n==0)
   {
     i++;
     strcpy (presets[i],"@");
     strcat (presets[i],(char*)name);
     i++;
     strcpy (presets[i],exported_eq_preset);
   }
   t.open (eq_file);
   t <<"LE_EQU0_8Presets" <<endl;
   for (int j=0;j<=i;j++) t <<presets[j] <<endl;
   t.close();
   return i;
}

int load_equ_preset (char *file, char*preset)
{
   int loaded=0;
   std::ifstream f;
   f.open (file);
   if (!f.fail())
   {
     char data[200];
     char temp[200];
     strcpy (temp,"@");
     strcat (temp,(char*)preset);
     f.getline (data,sizeof(data));
     if (strcmp (data,"LE_EQU0_8Presets")==0)
     {
       while ((strcmp(data,temp)!=0) && (!f.eof())) f.getline (data,sizeof(data));
       if ((strcmp(data,(char*)temp)==0) && (!f.eof()))
       {
         f.getline (data,sizeof(data));
	 for (int i=0;i<=9;i++) imported_eq_preset[i]=(signed char)(data[i]-127);
	 loaded=1;
//	 strcpy (imported_eq_preset,data);
       }
     }
     f.close();
   }
   else return 0;
   return loaded;
}

// delete preset

int delete_equ (char *file, char *name)
{
   int i=-1;
   int deleted=0; // deleted ?
   int e=0; // error = 0
   std::ifstream f;
   char *eq_file;
   char temp[200];
   eq_file = strdup (file);
   std::ofstream t;
   f.open (file);
   if (!f.fail())
   {
     char data[200];
     f.getline (data,sizeof(data));
     if (strcmp (data,"LE_EQU0_8Presets")==0)
     {
       f.getline (data,sizeof(data));
       while (!f.eof())
       {
	 i++;
         if (data[0]=='@') strcpy (temp,(char*)(index(data,'@')+1));
	 else strcpy (temp,"");
	 if ((strcmp (temp,(char*)name)==0) && (!f.eof()))
	 {
/*	   strcpy (presets[i],data);
	   i++;
	   strcpy (presets[i],exported_eq_preset);
	   n=1;*/
	   f.getline (data,sizeof(data));
	   i--;
	   deleted=1;
	 } else strcpy (presets[i],data);
	 //printf ("%s\n",presets[i]);
         f.getline (data,sizeof(data));
       }
     }
     f.close();
   } else e=1;
   t.open (eq_file);
   t <<"LE_EQU0_8Presets" <<endl;
   for (int j=0;j<=i;j++) t <<presets[j] <<endl;
   t.close();
   return deleted;
}


int eq_formatselect()
{
  int format=0;
  int scr2=9;
  int t=0;
  int q=0;
  WINDOW *w;
  w=newwin (scr2-1,29,7+((nrscr-scr2)/2),(nrcols-29)/2);
  wsetcolor (w,13,0);
  for (int h=0;h<=scr2-1;h++) mvwprintw (w,h,0,"                                                            ");
  wsetcolor (w,12,0);
  le_border (w,29,scr2-1);
  wsetcolor (w,13,1);
  mvwprintw (w,0,1," Select Format ");
  wsetcolor (w,12,0);
  mvwprintw (w,2,2,"x : XMMS");
  mvwprintw (w,3,2,"l : LinuxEyes v0.6");
  mvwprintw (w,4,2,"w : Winamp 2.x");
  mvwprintw (w,5,2,"e : EQF File");
  mvwprintw (w,7,14," ESC - quit ");
  wrefresh(w);
  timeout (1);
  format=0;
  do
  {
    do
    {
      messages();
      t=getch();
      if ((try_again) && (t==ERR)) playnext();
    } while (t==ERR);
    if (t == 'q') q=1;
    if (t=='x')
    {
      format=1;
      t='q';
      q=1;
    }
    if (t=='l')
    {
      format=2;
      t='q';
      q=1;
    }
    if (t=='w')
    {
      format=3;
      t='q';
      q=1;
    }
    if (t=='e')
    {
      format=4;
      t='q';
      q=1;
    }
    if (t==27)
    {
      t=getch();
      if (t==ERR) q=1;
    }
    if (quit==1) q=1;
  } while (q==0);
  while (t!=ERR) t=getch();
  werase (w);
  wrefresh (w);
  return format;
}
