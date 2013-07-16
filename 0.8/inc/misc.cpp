void colors ()
{
   start_color();
   init_pair (1,COLOR_WHITE,0);
   init_pair (2,COLOR_WHITE,4);
   init_pair (3,COLOR_WHITE,1);
   init_pair (4,COLOR_GREEN,0);
   init_pair (5,COLOR_GREEN,4);
   init_pair (6,COLOR_YELLOW,0);
   init_pair (7,COLOR_YELLOW,4);
   init_pair (8,COLOR_BLUE,6);
   init_pair (9,COLOR_RED,6);
   init_pair (10,COLOR_BLUE,2);
   init_pair (11,COLOR_RED,2);
   init_pair (12,COLOR_BLACK,7);
   init_pair (13,COLOR_WHITE,7);
   init_pair (14,COLOR_WHITE,COLOR_BLUE);
   init_pair (15,COLOR_CYAN,0);
   init_pair (16,COLOR_CYAN,4);
}

void setcolor (int n,int m)
{
   if (m==1) attr_set (A_BOLD,0,0);
   else attr_set (A_NORMAL,0,0);
   color_set (n,0);
   if ((nocolor==1) && ((n==2) || (n==3) || (n==5) || (n==7) || (n==10) || (n==11) || (n==12) || (n==13))) attrset (A_REVERSE);
}

void wsetcolor (WINDOW *w,int n,int m)
{
   if (m==1) wattr_set (w,A_BOLD,0,0);
   else wattr_set (w,A_NORMAL,0,0);
   wcolor_set (w,n,0);
   if ((nocolor==1) && ((n==2) || (n==3) || (n==5) || (n==7) || (n==10) || (n==11) || (n==12) || (n==13))) wattrset (w,A_REVERSE);
}
