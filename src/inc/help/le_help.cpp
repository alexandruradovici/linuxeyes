#include <string.h>
  char help_s[58][203];
  const int help_lines=203;
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
    strcpy(help_s[16]," Z            : previous in playlist");
    strcpy(help_s[17]," B            : next in playlist");
    strcpy(help_s[18]," s            : Shuffle On/Off");
    strcpy(help_s[19]," <ENTER>      : Play ");
    strcpy(help_s[20]," <SPACE BAR>  : Set As Next ");
    strcpy(help_s[21]," <TAB>        : Add/Remove to/from filter ");
    strcpy(help_s[22]," <LEFT>       : Backward 1%");
    strcpy(help_s[23]," <RIGHT>      : Forward 1%");
    strcpy(help_s[24]," <            : Backward 5%");
    strcpy(help_s[25]," >            : Forward 5%");
    strcpy(help_s[26]," f            : Filter Options");
    strcpy(help_s[27]," f,c          : Clear Filter");
    strcpy(help_s[28]," f,p          : On/Off persistent filter");
    strcpy(help_s[29]," f,a          : Add filter (load, don't delete old)");
    strcpy(help_s[30]," f,l          : Load filter (delete old)");
    strcpy(help_s[31]," f,s          : Save filter");
    strcpy(help_s[32]," r            : Repreat current song ");
    strcpy(help_s[33]," i or ALT+3   : ID3v1.1 TAG Editor (for selected song)");
    strcpy(help_s[34]," I            : ID3v1.1 TAG Editor (for current song)");
    strcpy(help_s[35]," j or F3      : Jump to file");
    strcpy(help_s[36]," m            : Quick Message");
    strcpy(help_s[37]," M            : Messages List");
    strcpy(help_s[38]," <INSERT>     : Volume + ");
    strcpy(help_s[39]," <DELETE>     : Volume - ");
    strcpy(help_s[40]," <HOME>       : PCM + ");
    strcpy(help_s[41]," <END>        : PCM - ");
    strcpy(help_s[42]," ,            : Balance left ");
    strcpy(help_s[43]," .            : Balance right ");
    strcpy(help_s[44]," e            : Equalizer");
    strcpy(help_s[45]," A            : Automatic Equalizer On/Off");
    strcpy(help_s[46]," '            : Repaint Desktop");
    strcpy(help_s[47]," *            : Increase desktop width");
    strcpy(help_s[48]," /            : Decrease desktop width");
    strcpy(help_s[49]," +            : Increase desktop height");
    strcpy(help_s[50]," -            : Decrease desktop height");
    strcpy(help_s[51]," @            : Full Screen Desktop");
    strcpy(help_s[52]," t            : Switch clock display mode");
    strcpy(help_s[53]," \\            : Change Password");
    strcpy(help_s[54]," !            : Lock Display");
    strcpy(help_s[55]," =            : Cycle Status Bar Modes");
    strcpy(help_s[56]," h or F1      : Help");
    strcpy(help_s[57]," F2           : What's New");
    strcpy(help_s[58]," ?            : About and Statistics");
    strcpy(help_s[59]," {            : Set Alarm On Time");
    strcpy(help_s[60]," }            : Set Alarm Off Time");
    strcpy(help_s[61]," T            : Set Sleep mode");
    strcpy(help_s[62]," |            : On/Off Shut Down mode");
    strcpy(help_s[63]," o            : Settings");
    strcpy(help_s[64]," ESC          : Screen Saver");
    strcpy(help_s[65]," ALT+SHIFT+Q  : Quit");
    strcpy(help_s[66],"");
    strcpy(help_s[67],"PLAYLIST");
    strcpy(help_s[68]," a            : Add File");
    strcpy(help_s[69]," d            : Delete File");
    strcpy(help_s[70]," D            : Add Directory");
    strcpy(help_s[71]," R            : Delete All");
    strcpy(help_s[72]," S            : Sort Playlist");
    strcpy(help_s[73]," <UP>         : Cursor Up");
    strcpy(help_s[74]," <DOWN>       : Cursor Down");
    strcpy(help_s[75]," <PAGE UP>    : Page Up");
    strcpy(help_s[76]," <PAGE DOWN>  : Page Down");
    strcpy(help_s[77]," 0..9         : Fast Scroll");
    strcpy(help_s[78]," [            : Move Up");
    strcpy(help_s[79]," '            : Move Down");
    strcpy(help_s[80]," l            : Locate Current Song");
    strcpy(help_s[81]," L            : Autolocate Current Song");
    strcpy(help_s[82]," p            : Playlist Options");
    strcpy(help_s[83]," p,n          : New Playlist");
    strcpy(help_s[84]," p,l          : Load Playlist");
    strcpy(help_s[85]," p,s          : Save Playlist");
    strcpy(help_s[86]," p,i          : Import Playlist");
    strcpy(help_s[87]," p,e          : Export Playlist");
    strcpy(help_s[88]," E            : Edit playlist file entry");
    strcpy(help_s[89]," n            : Refresh list");
    strcpy(help_s[90]," ;            : On/Off save playlist position on exit");
    strcpy(help_s[91],"");
    strcpy(help_s[92],"JUMP TO FILE");
    strcpy(help_s[93]," <ENTER>      : Play");
    strcpy(help_s[94]," <SPACE BAR>  : Set as next");
    strcpy(help_s[95]," <TAB>        : Add/Remove to/from filter");
    strcpy(help_s[96]," F            : Add/Remove all songs to filter");
    strcpy(help_s[97]," i            : ID3 TAG Edditor");
    strcpy(help_s[98]," ESC or q     : Close window");
    strcpy(help_s[99],"");
    strcpy(help_s[100],"EQUALIZER WINDOW");
    strcpy(help_s[101]," <PAGE UP>    : Up ALL");
    strcpy(help_s[102]," <PAGE DOWN>  : Down ALL");
    strcpy(help_s[103]," a/z          : Up/Down Band #1");
    strcpy(help_s[104]," s/x          : Up/Down Band #2");
    strcpy(help_s[105]," d/c          : Up/Down Band #3");
    strcpy(help_s[106]," f/v          : Up/Down Band #4");
    strcpy(help_s[107]," g/b          : Up/Down Band #5");
    strcpy(help_s[108]," h/n          : Up/Down Band #6");
    strcpy(help_s[109]," j/m          : Up/Down Band #7");
    strcpy(help_s[110]," k/,          : Up/Down Band #8");
    strcpy(help_s[111]," l/.          : Up/Down Band #9");
    strcpy(help_s[112]," ;//          : Up/Down Band #10");
    strcpy(help_s[113]," r            : Set all bands to 0 (reset equalizer)");
    strcpy(help_s[114]," L            : Load Preset");
    strcpy(help_s[115]," S            : Save Preset");
    strcpy(help_s[116]," I            : Import Preset(s)");
    strcpy(help_s[117]," D            : Delete Preset(s)");
    strcpy(help_s[118]," A            : On/Off Automatic Equalizer");
    strcpy(help_s[119]," ");
    strcpy(help_s[120],"FILE DIALOG");
    strcpy(help_s[121]," <Up>         : Move Up");
    strcpy(help_s[122]," <Down>       : Move Down");
    strcpy(help_s[123]," <Left>       : Backward 1%");
    strcpy(help_s[124]," <Right>      : Forward 1%");
    strcpy(help_s[125]," <PgUp>       : Page Up");
    strcpy(help_s[126]," <PgDn>       : Page Down");
    strcpy(help_s[127]," <            : Backward 5%");
    strcpy(help_s[128]," >            : Forward 5%");
    strcpy(help_s[129]," <ENTER>      : End Selection (Open)");
    strcpy(help_s[130]," <SPACE BAR>  : Select");
    strcpy(help_s[131]," <TAB>        : Play");
    strcpy(help_s[132]," ALT+<SPACE>  : Set As Next");
    strcpy(help_s[133]," z            : previous");
    strcpy(help_s[134]," x            : play");
    strcpy(help_s[135]," c            : pause");
    strcpy(help_s[136]," v            : stop");
    strcpy(help_s[137]," b            : next");
    strcpy(help_s[138]," i or ALT+3   : ID3v1.1 Tag Editor");
    strcpy(help_s[139]," ALT + _      : Goto a _*.mp3 file (_:[A..Z,a..z])");
    strcpy(help_s[140]," ESC or q     : Close Dialog");
    strcpy(help_s[141],"");
    strcpy(help_s[142],"ID3 TAG EDITOR");
    strcpy(help_s[143]," Load +       : Load Settings from ID3+ Info");
    strcpy(help_s[144]," Save +       : Save Settings to ID3+ Info");
    strcpy(help_s[145],"                * Save + won't have any effect");
    strcpy(help_s[146],"                  if you close the dialog with");
    strcpy(help_s[147],"                  the ESC key.");
    strcpy(help_s[148]," <Enter>      : Close and Save Information");
    strcpy(help_s[149]," <ESC>        : Close, don't save");
    strcpy(help_s[150],"");
    strcpy(help_s[151],"MESSAGES LIST");
    strcpy(help_s[152]," <INSERT>     : Add a message");
    strcpy(help_s[153]," <DELETE>     : Delete selected message");
    strcpy(help_s[154]," <TAB>        : Edit selected message");
    strcpy(help_s[155]," L            : Load messages form a file");
    strcpy(help_s[156]," S            : Save messages to a file");
    strcpy(help_s[157]," <ENTER>      : Close and Save");
    strcpy(help_s[158]," <ESC>        : Close, don't save");
    strcpy(help_s[159],"");
    strcpy(help_s[160],"STATISTICS");
    strcpy(help_s[161]," R            : Reset current session statistics");
    strcpy(help_s[162],"");
    strcpy(help_s[163],"SPECIAL FUNCTIONS");
    strcpy(help_s[164]," P            : Make playlist for MP3 CD Player");
    strcpy(help_s[165],"                * The player will ask you for the CD");
    strcpy(help_s[166],"                  mount path (usualy /mnt/cdrom)");
    strcpy(help_s[167],"                * A list with the files on that CD");
    strcpy(help_s[168],"                  will be displayed.");
    strcpy(help_s[169],"                * Press <ENTER> to save the list.");
    strcpy(help_s[170],"                * Tested on JazzPIPER MCD650S");
    strcpy(help_s[171],"");
    strcpy(help_s[172],"PLAYER MODES");
    strcpy(help_s[173]," Normal       : Next song in playlist (don\'t shuffle)");
    strcpy(help_s[174]," Shuffle      : Random next song (shuffle)");
    strcpy(help_s[175]," Next Song    : Next song is already selected");
    strcpy(help_s[176]," Filter       : There are files in the filter");
    strcpy(help_s[177]," P-Filter     : The filter is persistent");
    strcpy(help_s[178]," Password     : Display is locked with password");
    strcpy(help_s[179]," Sleep        : Shut Down at a specific time");
    strcpy(help_s[180]," Shut Down    : Shut Down after current song");
    strcpy(help_s[181],"");
    strcpy(help_s[182],"STATUS BAR");
    strcpy(help_s[183]," Mode 1       : Displays mode, vol, pcm, bal & flags");
    strcpy(help_s[184]," Mode 2       : Displays next song's name");
    strcpy(help_s[185]," Mode 3       : Displays nr of files in filter");
    strcpy(help_s[186]," Mode 4       : Displays alram start & stop time");
    strcpy(help_s[187]," Mode 5       : Displays shut down time");
    strcpy(help_s[188]," Flags   S - save playlist on exit");
    strcpy(help_s[189],"         E - auto equalizer");
    strcpy(help_s[190],"         L - autolocate current song");
    strcpy(help_s[191],"         P - use persistent filter");
    strcpy(help_s[192],"         A - Alarm is set");
    strcpy(help_s[193],"         + - Use ID3 Plus Information");
    strcpy(help_s[194],"");
    strcpy(help_s[195],"SONG DISPLAY FORMAT");
    strcpy(help_s[196]," %1 or %t     : Track Number");
    strcpy(help_s[197]," %2 or %a     : Artist");
    strcpy(help_s[198]," %3 or %s     : Song");
    strcpy(help_s[199]," %4 or %A     : Album");
    strcpy(help_s[200]," %5 or %y     : Year");
    strcpy(help_s[201]," %6 or %g     : Genre");
    strcpy(help_s[202]," %7 or %c     : Comment");
    strcpy(help_s[203]," %8 or %f     : File Name");
  }

