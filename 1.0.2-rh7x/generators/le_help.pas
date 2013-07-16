var
  i:integer;
  f:text;
  t:text;
  s:string;
  
begin
  write ('Generating help (help generator v0.2) ... ');
  assign (f,'./generators/help.le');
  reset (f);
  i:=-1;
  while not (eof(f)) do
  begin
    readln (f,s);
    i:=i+1;
  end;
  reset (f);
  assign (t,'inc/help/le_help.cpp');
  rewrite (t);
  writeln (t,'#include <string.h>');
  writeln (t,'  char help_s[58][',i,'];');
  writeln (t,'  const int help_lines=',i,';');
  writeln (t,'  void make_help()');
  writeln (t,'  {');
  i:=-1;
  while not (eof(f)) do
  begin
    readln (f,s);
    i:=i+1;
    writeln (t,'    strcpy(help_s[',i,'],"',s,'");');
  end;
  writeln (t,'  }');
  writeln (t);
  close (t);
  close (f);
  writeln ('done.');
end.