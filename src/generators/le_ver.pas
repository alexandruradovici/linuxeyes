uses sysutils, dos;
const wday:array[0..6] of string = ('Sun','Mon','Tue','Wed','Thu','Fri','Sat');
      month:array[1..12] of string = ('January','February','March','April','May','June','July','August','September','October','November','December');

var
  f:text;
  ft:text;
  version:string;
  pre:string;
  build:integer;
  bdate:string;
  y,m,d,wd:integer;
  h,min,sec,hs:integer;
  v_name:string;

begin
  write ('Setting version (ver version 0.3) ... ');
  getdate (y,m,d,wd);
  gettime (h,min,sec,hs);
  bdate:=format ('%s %d, %d @ %.2d:%.2d:%.2d',[month[m],d,y,h,min,sec]);
  assign (f,'./generators/le_data.build');
  reset (f);
  readln (f,version);
  readln (f,pre);
  readln (f,build);
  readln (f,v_name);
  close (f);
  build:=build+1;
  rewrite (f);
  writeln (f,version);
  writeln (f,pre);
  writeln (f,build);
  writeln (f,v_name);
  close (f);
  assign (ft,'inc/version.cpp');
  rewrite (ft);
  writeln (ft,'const char version[10]="',version+pre,'"; //LinuxEyes version');
  writeln (ft,'const char build[10]="',version,'.',build,'"; //LinuxEyes build number');
  writeln (ft,'const char bdate[40]="',bdate,'"; //LinuxEyes build date');
  writeln (ft,'const char bday[40]="',wday[wd],'"; //LinuxEyes build day of week');
  writeln (ft,'const char v_name[',length(v_name)+1,']="',v_name,'"; //LinuxEyes version name');
  close (ft);
  writeln ('done.');
end.