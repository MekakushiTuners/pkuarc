import os

current_directory = os.path.dirname(os.path.abspath(__file__))

for name in os.listdir(current_directory):
    sub_path = current_directory+ '\\' + name
    #print(sub_path)
    if(os.path.isdir(sub_path) and len(os.listdir(sub_path))) == 3:
        jpgpath = "\":/res/"+name+"/"
        oggpath = "\"qrc:/res/"+name+"/"
        mcpath = "\":/res/"+name+"/"
        for son in os.listdir(sub_path):
            if son[-3:] == 'ogg' or son[-3:] == 'mp3' :
                oggpath += son
            elif son[-2:] == 'mc':
                mcpath += son
            else: jpgpath += son

        jpgpath += "\""
        oggpath += "\""
        mcpath += "\""

        print("Song(0"+", "+jpgpath+", "+"\""+name+"\""+", "+oggpath+", "+mcpath+", "+"\"\""+", 0),")
    #break