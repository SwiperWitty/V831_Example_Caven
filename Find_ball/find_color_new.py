#!/usr/bin/python3

from maix import image, display, camera, gpio
import serial,time

led = gpio.gpio(14, "H", 1)
print(led.source)
led.set_value(0)
time.sleep(0.5)
led.set_value(1)
time.sleep(0.5)
led.release()

ser = serial.Serial("/dev/ttyS1",115200,timeout=0.2)    # 连接串口
tmp = ser.readline()
print('serial test start ...') 
ser.write(b" \r\n")
time.sleep(1)
ser.write(b"{V831:Ready!}\n")

Set_LAB = [[(23, 74, 36, 65, -44, 55)],     #red
           [(11, 36, -6, 60, -93, -40)]]     #blue
color = {
    "red" : (255, 0, 0),
    "green": (0, 255,0),
    "blue":(0, 0,255),
    "yellow":(255,255,0),
    "white":(255,255,255),
    "black":(0,0,0),
    "set":(0,0,0),
}
flag = '1'
string = "0"
now_time = time.time()

ser.write(b"ok\n")
while True:
    img = camera.capture()
    for j in range(2):
        blobs = img.find_blobs(Set_LAB[j])    #在图片中查找lab阈值内的颜色色块
        if blobs :
            for i in blobs:
                size = i["w"] * i["h"]#最大是240 *240也就是57600
                if size > 2000 : 
                    x_start = i["x"]
                    x_end = i["x"] + i["w"]
                    x_center = int((x_start + x_end) / 2)    #中心坐标
                    y_start = i["y"]
                    y_end = i["y"] + i["h"]
                    y_center = int((y_start + y_end) / 2)
                    m = max((x_center - i["w"]*0.3) ,0)
                    n = max((y_center - i["h"]*0.3) ,0)
                    m = min((x_center - i["w"]*0.3) ,240)
                    n = min((y_center - i["h"]*0.3) ,240)
                    mk = [int(m),int(n), 20, 20]

                    git_color = img.get_blob_color(mk, 0, 0)
                    img.draw_rectangle(9, 9, 21, 21, color["white"], thickness=1) #左上角颜色区域画出来
                    color = (int(git_color[0]), int(git_color[1]), int(git_color[2]))
                    img.draw_rectangle(10, 10, 20, 20, color, thickness=-1) #将颜色填充到左上角
                    img.draw_rectangle(i["x"], i["y"], i["x"] + i["w"], i["y"] + i["h"],color, thickness=2) #将找到的颜色区域画出来
#                     img.draw_circle(x_center, y_center, int(i["h"]/2 + 8), color, thickness=3)   #画一个中心点在（50,50），半径为20的空心 圆
                    if(j == 0):
                        string = 'Red'
                    elif j == 1 :
                        string = 'Blue'
                    str_size = image.get_string_size(string)
                    img.draw_string(x_center - int(str_size[0]/2) - 5, y_start - 35, string, scale = 1.5,color = (int(git_color[0]), int(git_color[1]), int(git_color[2])), thickness = 2)
                    if flag == '1' :
                        flag = '0'
                        now_time = time.time() #time.asctime()
                    
    display.show(img)
    time_t = time.time() - now_time
    if(time_t > 0.03) :
        if flag == 'A':   #源 0 ,SET A
            tep = "{V831:Space_x->" + str(x_center-120) + "}"   #先获得数据
            ser.write(tep.encode("utf-8"))                      #变成串口能发送的格式发出去
            flag = 'x'                                          #先发X再发Y，需要等等不然32会反映不过来，但又不能阻塞
        elif flag == 'x' :
            flag = '1'
            tep = "{V831:Space_y->" + str(y_center-120) + "}"   #先获得数据
            ser.write(tep.encode("utf-8"))                      #变成串口能发送的格式发出去
        if ('Red' in string):
            string = "0"
            tep = "{V831:color->red}"
            ser.write(tep.encode("utf-8"))
        elif 'Blue' in string :
            string = "0"
            tep = "{V831:color->blue}"
            ser.write(tep.encode("utf-8"))
        