list_type presets;

int load_xmms_preset (char *file, char *preset, char *path);
int load_equ_preset (char *file, char*preset);
int save_to_equ (char *file, char *name);

// LE v0_6 presets

int load_from_le0_6()
{
  showfiles (14,".","Select an equalizer file to load",0,".");
  if (mpegnumber > -1)
  {
    ifstream f(mpegfile[0]);
    if (!f.fail())
    {
       f >>eq.left >>eq.right;
      for (int i=0;i<=31;i++) 
      {
        f >>equalizer.left[i];
        equalizer.right[i]=equalizer.left[i];
      }
    }
  }
  return 0;
}

// XMMS presets

int list_from_xmms (char *file)
{
   int i=-1;
   char *eq_file;
   eq_file=strdup (file);
   ifstream f;
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
	 //printf ("%s\n",presets[i]);
         f.getline (data,sizeof(data));
       }
     }
     f.close();
   }
   else return 0;
   //window
   showlist (14,"XMMS eq presets",0,presets,i);
   if (mpegnumber > -1)
   {
     char path[1000];
     strcpy (path,getenv("HOME"));
     strcat (path,"/.linuxeyes.eq");
     if (mpegnumber==0) return load_xmms_preset (eq_file, mpegfile[0], "");
     else
     {
       for (int i=0;i<=mpegnumber;i++) load_xmms_preset (eq_file, mpegfile[i], path);
     }
   } else return 0;
   return i;
}

int load_xmms_preset (char *file, char *preset, char *path)
{
   int i=-1;
   ifstream f;
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
     if (strcmp (path,"")!=0) save_to_equ (path,preset1);
   }
   else return 0;
   return 1;
}

// linuxeyes presets

int list_from_equ (char *file)
{
   int i=-1;
   char *eq_file;
   eq_file=strdup (file);
   ifstream f;
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
   showlist (14,"Equalizer Presets",1,presets,i);
   if (mpegnumber > -1)
   {
     return load_equ_preset (eq_file, mpegfile[0]);
   }
   return 0;
}

int save_to_equ (char *file, char *name)
{
   int i=-1;
   int e=0; // error = 0
   int n=0; // new preset=0
   ifstream f;
   char *eq_file;
   char temp[200];
   eq_file = strdup (file);
   ofstream t;
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

// nu e buna !!!!!!!!!!!!!!!!!!!!!!!!

int load_equ_preset (char *file, char*preset)
{
   ifstream f;
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
//	 strcpy (imported_eq_preset,data);
       }
     }
     f.close();
   }
   else return 0;
   return 1;
}


int eq_formatselect()
{
  int format=0;
  int scr2=9;
  int scr=18;
  int t=0;
  WINDOW *w;
  w=newwin (scr2-1,29,7+((scr-scr2)/2),24);
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
  mvwprintw (w,6,16," q - quit ");
  wrefresh(w);
  timeout (1);
  format=0;
  do
  {
    do
    {
      messages();
      t=getch();
    } while (t==ERR);
    if (t=='x')
    {
      format=1;
      t='q';
    }
    if (t=='l')
    {
      format=2;
      t='q';
    }
    if (t=='w')
    {
      format=3;
      t='q';
    }
    if (t=='e')
    {
      format=4;
      t='q';
    }
  } while (t!='q');
  werase (w);
  wrefresh (w);
  return format;
}
