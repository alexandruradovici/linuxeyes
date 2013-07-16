Summary: A very nice console MP3 Player
Name: linuxeyes
Version: 1.1
Release: pre3
URL: http://lug.orizont.net/~linuxeyes
License: GPL
ExclusiveOS: Linux
Group: Applications/Sound and Video
BuildRoot: /home/alex/programe/lineyes/download
BuildArch: i386
Source: (none)
Requires: ncurses >= 5

%description
LinuxEyes is a very nice console MP3 Player. If you want to
listen to mp3 music on your linux text mode, this is exactly
what you need.
Also it can import and export XMMS and M3U playlist, import
XMMS, Winamp and EQF equalizers.

%prep
cp /home/alex/programe/lineyes/xmp /home/alex/programe/lineyes/download/usr/local/bin/linuxeyes
cp /home/alex/programe/lineyes/linuxeyes /home/alex/programe/lineyes/download/usr/lib/linuxeyes/linuxeyes.whats-new
cp /home/alex/programe/lineyes/music/linuxeyes.mp3 /home/alex/programe/lineyes/download/usr/lib/linuxeyes/music/linuxeyes.mp3

%install

%preun

%files
%defattr(-,root,root)
#/usr/local/bin/xmp
#/usr/lib/linuxeyes/music/linuxeyes.mp3
#/usr/lib/linuxeyes/eq/*
#/usr/lib/linuxeyes/linuxeyes
#/usr/lib/linuxeyes/readme
%attr(0555,root,root) /usr/local/bin/linuxeyes
%attr(0444,root,root) /usr/lib/linuxeyes/eq/*
%attr(0444,root,root) /usr/lib/linuxeyes/music/*
%attr(0444,root,root) /usr/lib/linuxeyes/linuxeyes.whats-new
%attr(0444,root,root) /usr/lib/linuxeyes/readme

%changelog
* Sun May 26 2005 Alexandru Radovici <linuxeyes@lug.orizont.net> 1.1.pre3
A lot has been modified, read /usr/lib/linuxeyes/linuxeyes.whats-new
* Fri Dec 26 2003 Alexandru Radovici <linuxeyes@lug.orizont.net> 1.1.pre1
A lot has been modified, read /usr/lib/linuxeyes/linuxeyes.whats-new
* Mon Jun 2 2003 Alexandru Radovici <linuxeyes@lug.orizont.net> 1.0.2
First full RPM release
* Tue Mar 11 2003 Alexandru Radovici <linuxeyes@lug.orizont.net> 0.9
First RPM release


