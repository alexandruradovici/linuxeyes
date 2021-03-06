#include <string.h>
  char help_s[58][189];
  const int help_lines=189;
  void make_help()
  {
    strcpy(help_s[0],"COMMAND LINE");
    strcpy(help_s[1]," -p           : play");
    strcpy(help_s[2]," --colors     : force color usage");
    strcpy(help_s[3]," --nocolors   : B&W, for dummy terminals (telnet)");
    strcpy(help_s[4]," --autoscr    : force autodetect the screen's size");
    strcpy(help_s[5]," --noautoscr  : don't autodetect the screen's size");
    strcpy(help_s[6]," --fakelines  : draw lines on terminals without ACS");
    strcpy(help_s[7]," --new_start  : start with default configuration");
    strcpy(help_s[8]," --debug      : show debug (not for users)");
    strcpy(help_s[9],"");
    strcpy(help_s[10],"PLAYER");
    strcpy(help_s[11]," z            : previous");
    strcpy(help_s[12]," x            : play");
    strcpy(help_s[13]," c            : pause");
    strcpy(help_s[14]," v            : stop");
    strcpy(help_s[15]," b            : next");
    strcpy(help_s[16]," s            : Shuffle On/Off");
    strcpy(help_s[17]," <ENTER>      : Play ");
    strcpy(help_s[18]," <SPACE BAR>  : Set As Next ");
    strcpy(help_s[19]," <TAB>        : Add/Remove to/from filter ");
    strcpy(help_s[20]," <LEFT>       : Backward 1%");
    strcpy(help_s[21]," <RIGHT>      : Forward 1%");
    strcpy(help_s[22]," <            : Backward 5%");
    strcpy(help_s[23]," >            : Forward 5%");
    strcpy(help_s[24]," f            : Filter Options");
    strcpy(help_s[25]," f,c          : Clear Filter");
    strcpy(help_s[26]," f,p          : On/Off persistent filter");
    strcpy(help_s[27]," f,a          : Add filter (load, don't delete old)");
    strcpy(help_s[28]," f,l          : Load filter (delete old)");
    strcpy(help_s[29]," f,s          : Save filter");
    strcpy(help_s[30]," r            : Repreat current song ");
    strcpy(help_s[31]," i or ALT+3   : ID3v1.1 TAG Editor (for selected song)");
    strcpy(help_s[32]," I            : ID3v1.1 TAG Editor (for current song)");
    strcpy(help_s[33]," j or F3      : Jump to file");
    strcpy(help_s[34]," <INSERT>     : Volume + ");
    strcpy(help_s[35]," <DELETE>     : Volume - ");
    strcpy(help_s[36]," <HOME>       : PCM + ");
    strcpy(help_s[37]," <END>        : PCM - ");
    strcpy(help_s[38]," ,            : Balance left ");
    strcpy(help_s[39]," .            : Balance right ");
    strcpy(help_s[40]," e            : Equalizer");
    strcpy(help_s[41]," A            : Automatic Equalizer On/Off");
    strcpy(help_s[42]," '            : Repaint Desktop");
    strcpy(help_s[43]," *            : Increase desktop width");
    strcpy(help_s[44]," /            : Decrease desktop width");
    strcpy(help_s[45]," +            : Increase desktop height");
    strcpy(help_s[46]," -            : Decrease desktop height");
    strcpy(help_s[47]," @            : Full Screen Desktop");
    strcpy(help_s[48]," t            : Switch clock display mode");
    strcpy(help_s[49]," \\            : Change Password");
    strcpy(help_s[50]," !            : Lock Display");
    strcpy(help_s[51]," =            : Cycle Status Bar Modes");
    strcpy(help_s[52]," h or F1      : Help");
    strcpy(help_s[53]," ?            : About and Statistics");
    strcpy(help_s[54]," {            : Set Alarm On Time");
    strcpy(help_s[55]," }            : Set Alarm Off Time");
    strcpy(help_s[56]," T            : Set Sleep mode");
    strcpy(help_s[57]," |            : On/Off Shut Down mode");
    strcpy(help_s[58]," o            : Settings");
    strcpy(help_s[59]," ESC          : Screen Saver");
    strcpy(help_s[60]," ALT+SHIFT+Q  : Quit");
    strcpy(help_s[61],"");
    strcpy(help_s[62],"PLAYLIST");
    strcpy(help_s[63]," a            : Add File");
    strcpy(help_s[64]," d            : Delete File");
    strcpy(help_s[65]," D            : Add Directory");
    strcpy(help_s[66]," R            : Delete All");
    strcpy(help_s[67]," S            : Sort Playlist");
    strcpy(help_s[68]," <UP>         : Cursor Up");
    strcpy(help_s[69]," <DOWN>       : Cursor Down");
    strcpy(help_s[70]," <PAGE UP>    : Page Up");
    strcpy(help_s[71]," <PAGE DOWN>  : Page Down");
    strcpy(help_s[72]," 0..9         : Fast Scroll");
    strcpy(help_s[73]," [            : Move Up");
    strcpy(help_s[74]," '            : Move Down");
    strcpy(help_s[75]," l            : Locate Current Song");
    strcpy(help_s[76]," L            : Autolocate Current Song");
    strcpy(help_s[77]," p            : Playlist Options");
    strcpy(help_s[78]," p,n          : New Playlist");
    strcpy(help_s[79]," p,l          : Load Playlist");
    strcpy(help_s[80]," p,s          : Save Playlist");
    strcpy(help_s[81]," p,i          : Import Playlist");
    strcpy(help_s[82]," p,e          : Export Playlist");
    strcpy(help_s[83]," E            : Edit playlist file entry");
    strcpy(help_s[84]," n            : Refresh list");
    strcpy(help_s[85]," ;            : On/Off save playlist position on exit");
    strcpy(help_s[86],"");
    strcpy(help_s[87],"JUMP TO FILE");
    strcpy(help_s[88]," <ENTER>      : Play");
    strcpy(help_s[89]," <SPACE BAR>  : Set as next");
    strcpy(help_s[90]," <TAB>        : Add/Remove to/from filter");
    strcpy(help_s[91]," F            : Add/Remove all songs to filter");
    strcpy(help_s[92]," i            : ID3 TAG Edditor");
    strcpy(help_s[93]," ESC or q     : Close window");
    strcpy(help_s[94],"");
    strcpy(help_s[95],"EQUALIZER WINDOW");
    strcpy(help_s[96]," <PAGE UP>    : Up ALL");
    strcpy(help_s[97]," <PAGE DOWN>  : Down ALL");
    strcpy(help_s[98]," a/z          : Up/Down Band #1");
    strcpy(help_s[99]," s/x          : Up/Down Band #2");
    strcpy(help_s[100]," d/c          : Up/Down Band #3");
    strcpy(help_s[101]," f/v          : Up/Down Band #4");
    strcpy(help_s[102]," g/b          : Up/Down Band #5");
    strcpy(help_s[103]," h/n          : Up/Down Band #6");
    strcpy(help_s[104]," j/m          : Up/Down Band #7");
    strcpy(help_s[105]," k/,          : Up/Down Band #8");
    strcpy(help_s[106]," l/.          : Up/Down Band #9");
    strcpy(help_s[107]," ;//          : Up/Down Band #10");
    strcpy(help_s[108]," r            : Set all bands to 0 (reset equalizer)");
    strcpy(help_s[109]," L            : Load Preset");
    strcpy(help_s[110]," S            : Save Preset");
    strcpy(help_s[111]," I            : Import Preset(s)");
    strcpy(help_s[112]," D            : Delete Preset(s)");
    strcpy(help_s[113]," A            : On/Off Automatic Equalizer");
    strcpy(help_s[114]," ");
    strcpy(help_s[115],"FILE DIALOG");
    strcpy(help_s[116]," <Up>         : Move Up");
    strcpy(help_s[117]," <Down>       : Move Down");
    strcpy(help_s[118]," <Left>       : Backward 1%");
    strcpy(help_s[119]," <Right>      : Forward 1%");
    strcpy(help_s[120]," <PgUp>       : Page Up");
    strcpy(help_s[121]," <PgDn>       : Page Down");
    strcpy(help_s[122]," <            : Backward 5%");
    strcpy(help_s[123]," >            : Forward 5%");
    strcpy(help_s[124]," <ENTER>      : End Selection (Open)");
    strcpy(help_s[125]," <SPACE BAR>  : Select");
    strcpy(help_s[126]," <TAB>        : Play");
    strcpy(help_s[127]," ALT+<SPACE>  : Set As Next");
    strcpy(help_s[128]," z            : previous");
    strcpy(help_s[129]," x            : play");
    strcpy(help_s[130]," c            : pause");
    strcpy(help_s[131]," v            : stop");
    strcpy(help_s[132]," b            : next");
    strcpy(help_s[133]," i or ALT+3   : ID3v1.1 Tag Editor");
    strcpy(help_s[134]," ALT + _      : Goto a _*.mp3 file (_:[A..Z,a..z])");
    strcpy(help_s[135]," ESC or q     : Close Dialog");
    strcpy(help_s[136],"");
    strcpy(help_s[137],"ID3 TAG EDITOR");
    strcpy(help_s[138]," Load +       : Load Settings from ID3+ Info");
    strcpy(help_s[139]," Save +       : Save Settings to ID3+ Info");
    strcpy(help_s[140],"                * Save + won't have any effect");
    strcpy(help_s[141],"                  if you close the dialog with");
    strcpy(help_s[142],"                  the ESC key.");
    strcpy(help_s[143]," <Enter>      : Save Information");
    strcpy(help_s[144]," <ESC>        : Close, don't save");
    strcpy(help_s[145],"");
    strcpy(help_s[146],"STATISTICS");
    strcpy(help_s[147]," R            : Reset current session statistics");
    strcpy(help_s[148],"");
    strcpy(help_s[149],"SPECIAL FUNCTIONS");
    strcpy(help_s[150]," P            : Make playlist for MP3 CD Player");
    strcpy(help_s[151],"                * The player will ask you for the CD");
    strcpy(help_s[152],"                  mount path (usualy /mnt/cdrom)");
    strcpy(help_s[153],"                * A list with the files on that CD");
    strcpy(help_s[154],"                  will be displayed.");
    strcpy(help_s[155],"                * Press <ENTER> to save the list.");
    strcpy(help_s[156],"                * Tested on JazzPIPER MCD650S");
    strcpy(help_s[157],"");
    strcpy(help_s[158],"PLAYER MODES");
    strcpy(help_s[159]," Normal       : Next song in playlist (don\'t shuffle)");
    strcpy(help_s[160]," Shuffle      : Random next song (shuffle)");
    strcpy(help_s[161]," Next Song    : Next song is already selected");
    strcpy(help_s[162]," Filter       : There are files in the filter");
    strcpy(help_s[163]," P-Filter     : The filter is persistent");
    strcpy(help_s[164]," Password     : Display is locked with password");
    strcpy(help_s[165]," Sleep        : Shut Down at a specific time");
    strcpy(help_s[166]," Shut Down    : Shut Down after current song");
    strcpy(help_s[167],"");
    strcpy(help_s[168],"STATUS BAR");
    strcpy(help_s[169]," Mode 1       : Displays mode, vol, pcm, bal & flags");
    strcpy(help_s[170]," Mode 2       : Displays next song's name");
    strcpy(help_s[171]," Mode 3       : Displays nr of files in filter");
    strcpy(help_s[172]," Mode 4       : Displays alram start & stop time");
    strcpy(help_s[173]," Mode 5       : Displays shut down time");
    strcpy(help_s[174]," Flags   S - save playlist on exit");
    strcpy(help_s[175],"         E - auto equalizer");
    strcpy(help_s[176],"         L - autolocate current song");
    strcpy(help_s[177],"         P - use persistent filter");
    strcpy(help_s[178],"         A - Alarm is set");
    strcpy(help_s[179],"         + - Use ID3 Plus Information");
    strcpy(help_s[180],"");
    strcpy(help_s[181],"SONG DISPLAY FORMAT");
    strcpy(help_s[182]," %1 or %t     : Track Number");
    strcpy(help_s[183]," %2 or %a     : Artist");
    strcpy(help_s[184]," %3 or %s     : Song");
    strcpy(help_s[185]," %4 or %A     : Album");
    strcpy(help_s[186]," %5 or %y     : Year");
    strcpy(help_s[187]," %6 or %g     : Genre");
    strcpy(help_s[188]," %7 or %c     : Comment");
    strcpy(help_s[189]," %8 or %f     : File Name");
  }

