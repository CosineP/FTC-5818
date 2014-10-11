FTC-5818
========

Year of 2014 - 2015 FTC for team 5818.

The code in teleop.c is for what's exclusively for the driver-controlled period.
The code in autonomous.c is for what's exclusively the anonamous mode.
The code in library.c is for what will be used by both files.

The branch "master" is for the most current code that we're testing and creating.
The branch "current-robot" is for the code that works best and is tested with the current hardware.


                  ..??=.                                                        
                    ..I?~,.                             .:.                     
                      .$$?=. ..                       . .,                      
                        Z$?=?..                       .?=.                      
                      ...ZZ$+?,  .. ,..             ,I7=..                      
           .. .         ..OZ$?+....~7Z$.          ..II+,                        
           ..,.         ...8ZZIII..~$$O$         .$77+~                         
             .~I....       $8OZII7.=Z7$O.      .+7$7+=..                        
               .,?$?..     .7DOZ7IZZI?78O.   . 7$Z$I=.  .....                   
                ..~?$7     ..DD8Z78Z?+~OOZ    Z$$$I=, ..8, .                    
                  ...IZO...  .DDOZ8O?I=+O8   ~$$77+:.:N?,.   ..                 
                    ..?$ZO.. .:DDO8OII?~ZZ:.,$$7I?~.NN$.  . .=.                 
               . ... ...$88....NND8O7??==$Z.$77I?=NNM, ....,=.                  
             ....?I......+O8D?..NDDOZII++$OZ7$II=NMM= ..7I?:...                 
                  .=III,...O8DDD8NDD8$I?=+8$77I?DNN7~?I7I=. .                   
                    .:I7I$..8DDODNNND7I+=~Z$7ID8INOZ$77I,.                      
                    ....7$$7I8DD8NNDD87?==Z788OI=8$?7I+  .                      
                    . ...+Z$778DNDNND8$I+=88OO77=$?7?...      .                 
                      .:7ZDZ$$$ZNNDND8Z7?DDO$II+I?II  .....+=..                 
                      .. 7I+=+7ZZNNND8O$DDD8Z7?=??+.~8$.O+=...                  
                  .:77:... IIII?I$NNND8ODD8O$7+?Z88Z$O?+..  .                   
                     .+7$$...ZOO7Z==DDODD8OO$7O88ZZ?++I7?+...                   
                      ...+OD7.:8DZO+==?ND8OZDDD8OZI?88~......                   
                  .?$+I?I+.ZNNN8NN8O7?+?8OODDD8O$7+D=?8D$7=~.                   
                      ..=7O?7+=MMMNNDZI??OZO$=+$7?O8N87.... .                   
                      ...  =8$I$7MMNN8OO8Z$$?+$78D8O7...?Z77,                   
                      ..~+$D:.8DZ?::~$DNN8O7?+OOZ$IO$77I?=.....                 
                     ,==,..=8MNNNI??==+8D8ODD8Z$IO$7$,.?7$,.                    
                      ....=7$8NMMN8Z$??I88DDDOZIZ8$7?.. ... .                   
                       ..:.++??DNMMDDN8$$==+Z$D8Z7?IOI+. .. .                   
                     .... ..:7Z7$$OMNMMNOZ77Z8$7$$7+=.....                      
                           .+IONNN8++==I8ONN8Z7+O?,=+: .                        
                           .=. INMMN8Z$OZZ777OO$I+$+I~:.                        
                           ....I$O8DMNNNDOZ7ZNO++......                         
                           ...IZONMMDZZ$88N8Z7$7.......                         
                           ,...:DNNDMMNON++?O7?7I~~=....                        
                        ....,Z88$I~I7Z8+?7Z~I?ID$I7$7,..                        
                      ....?7?~$O=+???I$++=Z8$8$I7=~:~??=..                      
                      ..OOD?O+77DO8=O+~:+=+=NZ+~+:?ZI=II~.                      
                      .$ZZZ8DNIOI~==7O7~+?D7=O~::,?=$$??$=                      
                    ..ZIIZOO8OZ?II$7?+?O7+~:,IIO~??8I+?7:?...                   
                     .?OZDO7~ZZZ+?=7$O=8I?I7~=+=Z8D7++Z=77$..                   
                  . .=D88D$7DO$7D8Z==~I??8?~~:I8Z8OI?:~=~7Z..                   
                    .$?IO8OI=D$ZIO777=I?IDZZ78D+:,,:=++Z8??..                   
                  ...D7$O888NO~7I$D7:~~:$8O+I7$+=7+I:?Z?ZI=..                   
                  ..,?7OIDD8$8~~I$$$O7$$Z+++:??D?+$$ZZ8=::7..                   
                   .788N=Z$8D??=?IZD?+ZOI?O=+7?DOZ+?Z7Z+,~I7.                   
                    O$DZ??7OO88Z?$$$ZO=I8I~:I$7ZZO?:~,=O~78:..                  
                    ?OO8??IZNO8ND$7I~=~$DZ$ZD8Z=8$~?=?+?7Z$I,..                 
                  ..+$8ZO$Z88ZOOIZ+?7OZ=?78==??=ID$=+:7$7I=I. .                 
                  ..IOZDNMNO7:~$ZN777O8DO8I7IO~+$?8OZZ87==7=+..                 
                  .$Z8N8O8N7O8$I7OOO8+Z~$7NI:~:,+I8OIO$?O=7O$..                 
                  .,8D8~=ZZ7IO8ZZODNZI?~,IID$$IID+=+,?D+::?+I..                 
                  .~$D?$$ZZ8ONNOOZ8O7=?=~=I7$N88O++$+=I$II$:?..                 
                  .~IOII8$8DD$I:~+OZD77$$IOO$$7I8+::~:II$II~+..                 
                  ..OD8OND8D$?=+=I$OO8$Z$87?~I:7Z8I?IZ++~=7,?~.                 
                  ..$788O7+O88Z?++788?7$I$+I=?==?$8OZ777Z:???..                 
                  ..Z8N8Z$7OZ88Z$Z$77~=~7$7+?=7+$I$$7Z?~===I:..                 
                    Z?$Z$$?7ZD8ZD8Z8Z~:+?IO$$77Z7I~~:+O=+7III..                 
                    ,Z7OD?$ODO7$7$77=+I~7IOI7ZI??I++~?$+I7+~~.                  
                    ~7I7N8$D87+?=$$D?IIZ8$$77IIOI+~I~?ZI:+?+,                   
                    .+IZO8D8OOO=+$7OOZ7I$O=?==I?$Z+?III+7?=7.                   
                    ..78O7I+ZZ??I?I7Z?OZI77~I+??7?III7?~7I++...                 
                      :$Z+IIZ8$778$I$Z$OIII$7=?I$$+7=I7+Z??,,.                  
                      .?$8$I8$D7$O7?I+IZD7?7II77$+$7~7II+?:.. .                 
                      ..I+$7$?OO8I77+$?$ZZ7Z7?II?$I?+7$=+~...                   
                        .:II?7ZOZI7IIZ7?7?77III$$I7=7+?I=.                      
                        ..~777I777?7Z=IZ7O8Z+?7I+I??$I$~..                      
                           ..7IZZ=IOZ$O8I~?7IO??Z$$=+:..                        
                           ..,7=.IZ?Z?... $DZ8++$~..:..                         
                           .. ...... ...................

       