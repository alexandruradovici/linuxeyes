var
  i:integer;
  f:text;
  t:text;
  s:string;
  
begin
  assign (f,'help.le');
  reset (f);
  assign (t,'le_help.cpp');
  rewrite (t);
  i:=-1;
  while not (eof(f)) do
  begin
    readln (f,s);
    i:=i+1;
    writeln (t,'  strcpy(s[',i,'],"',s,'");');
  end;
  writeln (t,'  const int help_lines=',i,';');
  close (t);
  close (f);
  writeln ('help.cpp created.');
end.