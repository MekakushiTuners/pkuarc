#include <utils.h>

Song songs[song_size] = {
//Song(6,":/res/apollo/base.jpg","Apollo","qrc:/res/apollo/1631797224.ogg",":/res/apollo/1633332680.mc","TJ.hangneil",137),
//                        Song(9,":/res/chronostasis/base.jpg","Chronostasis","qrc:/res/chronostasis/Chronostasis.ogg",":/res/chronostasis/Chronostasis.mc","黒皇帝",196),
//
//                        Song(2,":/res/Vicious Heroism/base.jpg","Vicious Heroism","qrc:/res/Vicious Heroism/1555620010.ogg",":/res/Vicious Heroism/1561219884.mc","Kobaryo",256),
//                        Song(6,":/res/worldender/base.jpg","World Ender","qrc:/res/worldender/1659610730.ogg",":/res/worldender/1659610730.mc","sasakure.UK×Tj.hangneil",280),

//                        Song(5,":/res/the EmpError/The EmpErroR.jpg","the EmpErroR","qrc:/res/the EmpError/the EmpEror.ogg",":/res/the EmpError/1565417119.mc","sasakure.UK",120),
//                        Song(9,":/res/PRAGMATISM -RESURRECTION-/base.jpg","PRAGMATISM -RESURRECTION-","qrc:/res/PRAGMATISM -RESURRECTION-/1643522058.ogg",":/res/PRAGMATISM -RESURRECTION-/1663773858.mc","Laur",174),
                         Song(3, ":/res/Vicious Heroism/base.jpg", "Vicious Heroism", "qrc:/res/Vicious Heroism/1555620010.ogg", ":/res/Vicious Heroism/1561219884.mc", "Kobaryo", 256),
                         Song(10, ":/res/1f1e33/base.jpg", "#1f1e33", "qrc:/res/1f1e33/1612411734.ogg", ":/res/1f1e33/1630475348.mc", "Cameilla", 181),
                         Song(8, ":/res/Additional Memory/base.jpg", "Additional Memory", "qrc:/res/Additional Memory/1582955597.ogg", ":/res/Additional Memory/1582955597.mc", "Jin", 200),
                         Song(9, ":/res/AIUEOON/base.jpg", "AI[UE]OON", "qrc:/res/AIUEOON/1634363932.ogg", ":/res/AIUEOON/1634363932.mc", "N[I]TRO", 145),
                         Song(8, ":/res/Alexandrite/base.jpg", "Alexandrite", "qrc:/res/Alexandrite/onoken - Alexandrite.ogg", ":/res/Alexandrite/key_4k_hard.mc", "BlackY", 175),
                         // 5
                         Song(6, ":/res/apollo/base.jpg", "Apollo", "qrc:/res/apollo/1631797224.ogg", ":/res/apollo/1633332680.mc", "TJ.hangneil", 137),
                         Song(9, ":/res/AttraqtiA/base.jpg", "AttraqtiA", "qrc:/res/AttraqtiA/1612835868.ogg", ":/res/AttraqtiA/1612835868.mc", "Cameilla", 202),
                         Song(7, ":/res/Black Lotus/base.jpg", "Black Lotus", "qrc:/res/Black Lotus/Black Lotus.ogg", ":/res/Black Lotus/pm.mc", "wa.", 200),
                         Song(10, ":/res/chronostasis/base.jpg", "Chronostasis", "qrc:/res/chronostasis/Chronostasis.ogg", ":/res/chronostasis/Chronostasis.mc", "黒皇帝", 196),
                         Song(9, ":/res/Climax/base.jpg", "Climax", "qrc:/res/Climax/1550746067.ogg", ":/res/Climax/1587089997.mc", "USAO", 190),
                         //10
                         Song(8, ":/res/Cybernecia Catharsis/base.jpg", "Cybernecia Catharsis", "qrc:/res/Cybernecia Catharsis/1627166647.ogg", ":/res/Cybernecia Catharsis/1627372699.mc", "Tanchiky", 70),
                         Song(8, ":/res/Dreadnought/base.jpg", "Dreadnought", "qrc:/res/Dreadnought/1502709579.ogg", ":/res/Dreadnought/1556039181.mc", "Mastermind (xi + nora2r)", 192),
                         Song(11, ":/res/Einherjar Joker/base.jpg", "Einherjar Joker", "qrc:/res/Einherjar Joker/1677308237.ogg", ":/res/Einherjar Joker/1677308237.mc", "DJ Genki vs Gram", 222),
                         Song(8, ":/res/Ether Strike/base.jpg", "Ether Strike", "qrc:/res/Ether Strike/1616215376.ogg", ":/res/Ether Strike/1627743882.mc", "Akira Complex", 156),
                         Song(7, ":/res/Felis/base.jpg", "Felis", "qrc:/res/Felis/1613199798.ogg", ":/res/Felis/1615603410.mc", "M2U", 155),
                         //15
                         Song(10, ":/res/Galaxy Friends/base.jpg", "Galaxy Friends", "qrc:/res/Galaxy Friends/Kobaryo - Galaxy Friends.mp3", ":/res/Galaxy Friends/Kobaryo - Galaxy Friends (biemote) [4K Expert].mc", "Kobaryo", 300),
                         Song(8, ":/res/GOODTEK/base.jpg", "GOODTEK", "qrc:/res/GOODTEK/1497057582.ogg", ":/res/GOODTEK/1509800885.mc", "EBIMAYO",190),
                         Song(11,":/res/infinity heaven/base.jpg","Infinity Heaven","qrc:/res/infinity heaven/InfinityHeaven.ogg",":/res/infinity heaven/InfinityHeaven.mc","HyuN",160),
                         Song(9, ":/res/IZANA/base.jpg", "IZANA", "qrc:/res/IZANA/1634533978.ogg", ":/res/IZANA/1634533978.mc", "t+pazolite vs P*Light", 222),
                         Song(10, ":/res/LAMIA/base.jpg", "LAMIA", "qrc:/res/LAMIA/Lamia.ogg", ":/res/LAMIA/1631827293.mc", "BlackY", 199),
                         //20
                         Song(7, ":/res/Life is PIANO/base.jpg", "Life is PIANO", "qrc:/res/Life is PIANO/1571174740.ogg", ":/res/Life is PIANO/1633170839.mc", "Junk", 133),
                         Song(8, ":/res/Loschen/base.jpg", "Löschen", "qrc:/res/Loschen/1622282644.ogg", ":/res/Loschen/1622282644.mc", "BlackY feat. Risa Yuzuki", 181),
                         Song(7, ":/res/Lost Desire/base.jpg", "Lost Desire", "qrc:/res/Lost Desire/1620470817.ogg", ":/res/Lost Desire/1632458025.mc", "Powerless feat. Sennzai", 170),
                         Song(8, ":/res/Lower/bg.jpg", "Lower", "qrc:/res/Lower/audio.ogg", ":/res/Lower/Master.mc", "nulut", 132),
                         Song(7, ":/res/Our 16bit Wars/base.jpg", "Our 16bit Wars", "qrc:/res/Our 16bit Wars/16bwar.ogg", ":/res/Our 16bit Wars/1573386540.mc", "sasakure.UK", 244),
                         //25
                         Song(10, ":/res/PRAGMATISM -RESURRECTION-/base.jpg", "PRAGMATISM -RESURRECTION-", "qrc:/res/PRAGMATISM -RESURRECTION-/1643522058.ogg", ":/res/PRAGMATISM -RESURRECTION-/1663773858.mc", "Laur", 174),
                         Song(9, ":/res/PRIMITIVE LIGHTS/base.jpg", "PRIMITIVE LIGHTS", "qrc:/res/PRIMITIVE LIGHTS/1678332184.ogg", ":/res/PRIMITIVE LIGHTS/1678447341.mc", "TAG", 205),
                         Song(8, ":/res/PUPA/base.jpg", "PUPA", "qrc:/res/PUPA/1488631483.ogg", ":/res/PUPA/1502265124.mc", "モリモリあつし", 202),
                         Song(8, ":/res/Redraw the Colorless World/base.jpg", "Redraw the Colorless World", "qrc:/res/Redraw the Colorless World/1637161609.ogg", ":/res/Redraw the Colorless World/1637161609.mc", "MisomyL", 155),
                         Song(9, ":/res/Scarlet Cage/base.jpg", "Scarlet Cage", "qrc:/res/Scarlet Cage/1596727022.ogg", ":/res/Scarlet Cage/1596727022.mc", "Daisuke Kurosawa", 166),
                         //30
                         Song(8, ":/res/sheriruth/base.jpg", "Sheriruth", "qrc:/res/sheriruth/1635578955.ogg", ":/res/sheriruth/1635582628.mc", "Team Grimoire", 200),
                         Song(10, ":/res/Singularity/base.jpg", "Singularity", "qrc:/res/Singularity/1595302665.ogg", ":/res/Singularity/1595302665.mc", "ETIA.", 175),
                         Song(10, ":/res/Stasis/0.jpg", "Stasis", "qrc:/res/Stasis/1536922897.ogg", ":/res/Stasis/1536995149.mc", "Maozon", 180),
                         Song(9, ":/res/Tempestissimo/base.jpg", "Tempestissimo", "qrc:/res/Tempestissimo/1590574801.ogg", ":/res/Tempestissimo/1591511883.mc", "t+pazolite", 231),
                         Song(9, ":/res/TEmPTaTiON/base.jpg", "TEmPTaTiON", "qrc:/res/TEmPTaTiON/TEmPTaTiON.ogg", ":/res/TEmPTaTiON/1578758172.mc", "かねこちはる", 160),
                         //35
                         Song(6, ":/res/the EmpError/The EmpErroR.jpg", "the EmpError", "qrc:/res/the EmpError/the EmpEror.ogg", ":/res/the EmpError/1565417119.mc", "sasakure.UK", 120),
                         Song(8, ":/res/Vindication/base.jpg", "Vindication", "qrc:/res/Vindication/1635848244.ogg", ":/res/Vindication/1635848244.mc", "Laur", 174),
                         Song(3, ":/res/w4/base.jpg", "ω4", "qrc:/res/w4/w4.ogg", ":/res/w4/1644653159.mc", "穴山大輔 vs 光吉猛修 vs Kai", 192),
                         Song(10, ":/res/World Fragments I/base.jpg", "World Fragments I", "qrc:/res/World Fragments I/1613374137.ogg", ":/res/World Fragments I/1613374725.mc", "xi", 180),
                         Song(7, ":/res/worldender/base.jpg", "worldender", "qrc:/res/worldender/1659610730.ogg", ":/res/worldender/1659610730.mc", "sasakure.UK × TJ.hangneil", 280),
                         //40
                         Song(5, ":/res/worldexecuteme/base.jpg", "world.execute(me);", "qrc:/res/worldexecuteme/1517405629.ogg", ":/res/worldexecuteme/1582030307.mc", "mili", 130),
                         Song(12, ":/res/Malody Regular dan10/r1000.jpg", "Malody Regular dan10","qrc:/res/Malody Regular dan10/mrv20.ogg", ":/res/Malody Regular dan10/1584338873.mc", "LiSijie" ,230)};

QString font_path[font_size] = {":/res/fonts/Exo-Regular.ttf",
                   ":/res/fonts/GeosansLight.ttf",
                  ":/res/fonts/kingsgmb.ttf",
                  ":/res/fonts/NanumBarunGothic-Regular.otf",
                  ":/res/fonts/NotoSansCJKsc-Regular.otf",
                  ":/res/fonts/NotoSansCJKsc-Bold.otf"};

string pack_name[9] = {"",
                      "Lost World",
                      "Outer Reaches",
                       "Spire of Convergence",
                      "Dormant Echoes",
                      "Boundless Divide",
                      "Forgotten Construct",
                      "Horizon of Anamnesis",
                       "Beyond"};
string help_text[help_tot] = {"欢迎来到 Eisaea 喵!\n在开始游戏之前，请记住游戏内4个音轨\n对应的按键分别是A、S、K和L！",
                             "你说上面那个设定是干什么用的喵？\n左边是调节流速\n右边是调节延迟的喵！",
                             "怎么没有Testify？\n光光不知道喵",
                             "喵喵!",
                             "听说只要ap了所有的歌曲\n就会有神奇的事情发生诶！"};
double FALL_SPEED = 2.0;
int WAIT_TIME = -500;
int ORI_WAIT_TIME = -500;


