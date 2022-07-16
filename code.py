#!/usr/bin/python3
from maix import image, display, camera, gpio
import serial,time

image.load_freetype("/home/res/sans.ttf")

ser = serial.Serial("/dev/ttyS1",9600,timeout=0.2)    # 连接串口
tmp = ser.readline()
ser.write(b"{ }")
time.sleep(1)

Color = {
    "red" : (255, 0, 0),
    "green": (0, 255,0),
    "blue":(0, 0,255),
    "yellow":(255,255,0),
    "white":(255,255,255),
    "black":(0,0,0),
    "set":(0,0,0),
}

bar_list = []
qr_list = []
bar_flag = 1
leave_flag = 0
time_flag = 0
show_str = [0,0]
bar_num = 0
qr_num = 9
time_last = 0

ser.write(b"{V831:get}") #给一个
while True:
    img = camera.capture()
    if bar_flag == 1:  #条形码
        barcode = img.find_barcodes()
        for mk in barcode:
          #条形码信息
            string = mk['payload']
            TYPE = mk['type']
            if string not in bar_list:
                bar_flag = 0
                bar_list.append(string)
                bar_num = bar_num + 1
                qr_num = 0
                show_str[0] = "试管 " + str(bar_num) + " 号"
                show_str[1] = "人数：" + str(qr_num) + " 个 / 10"
                
          #内框数据
            x1,y1 = mk['corners'][0]   #访问字典的列表
            x2,y2 = mk['corners'][1]
            x3,y3 = mk['corners'][2]
            x4,y4 = mk['corners'][3]
              #画内框
            img.draw_line(x1, y1, x2, y2, color = (0, 255, 0), thickness = 3)  
            img.draw_line(x2, y2, x3, y3, color = (0, 255, 0), thickness = 3)  
            img.draw_line(x3, y3, x4, y4, color = (0, 255, 0), thickness = 3)  
            img.draw_line(x4, y4, x1, y1, color = (0, 255, 0), thickness = 3)
    elif bar_flag == 0:  #二维码
        mks = img.find_qrcodes()
        for mk in mks:
          #外框数据
            X = mk['x']
            Y = mk['y']
            W = mk['w']
            H = mk['h']
            #二维码信息
            string = mk['payload']
            if string[0] == "G":
                if string not in qr_list:
                    ser.write(b"{V831:go}")
                    leave_flag = 0
                    qr_list.append(string)
                    qr_num = qr_num + 1
                    if qr_num >= 10 :
                        qr_list = []
                        time_flag = 1
                        time_last = time.time()
                        bar_flag = 6
            else :
                if leave_flag != string:
                    leave_flag = string
                    ser.write(b"{V831:leave}")
            show_str[1] = "人数：" + str(qr_num) + " 个 / 10"
            #内框数据
            x1,y1 = mk['corners'][0]   #访问字典的列表
            x2,y2 = mk['corners'][1]
            x3,y3 = mk['corners'][2]
            x4,y4 = mk['corners'][3]
            img.draw_string(8 , 30*2 , string, scale = 2.0, color = Color["yellow"], thickness = 1)
            #画外框
            img.draw_rectangle(X, Y, X + W, Y + H, color=(0, 0, 255), thickness = 2)
            #画内框
            img.draw_line(x1, y1, x2, y2, color = (0, 255, 0), thickness = 3)  
            img.draw_line(x2, y2, x3, y3, color = (0, 255, 0), thickness = 3)  
            img.draw_line(x3, y3, x4, y4, color = (0, 255, 0), thickness = 3)  
            img.draw_line(x4, y4, x1, y1, color = (0, 255, 0), thickness = 3)  
                
            
    if show_str[0] != 0:
        img.draw_string(8 , 0 , str(show_str[0]), scale = 2.0, color = Color["blue"], thickness = 1)
    if show_str[1] != 0:
        if qr_num >= 10:
            img.draw_string(8 , 30 , str(show_str[1]), scale = 2.0, color = Color["yellow"], thickness = 1)
        else :
            img.draw_string(8 , 30 , str(show_str[1]), scale = 2.0, color = Color["blue"], thickness = 1)
    display.show(img)
    if time_flag == 1:
        if time.time() - time_last > 3 :
            time_flag = 0
            ser.write(b"{V831:get}") #给一个
            bar_flag = 1



