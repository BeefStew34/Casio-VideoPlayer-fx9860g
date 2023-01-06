import cv2
import numpy as np
import re
import math

cap = cv2.VideoCapture("AdventureTime.mp4")
captions = []
sub_index = []

def ConvertVideo():
        output = ""
        #return
        #3 = 8 fps
        #2 = 12 fps
        #1 = 24 fps
        fps_scale = 3
        frames = 2000

        output = ""
        caption_index = 0
        #A text offset to allows for a scrolling text subtitle because screen can only fit 24 chars
        #-6 too add delay so you have time to read first word
        caption_slide_index = -4

        for i in range(frames):
                #+300 is important for Subs
                actual_frame = (i*fps_scale)+300
                cap.set(1, actual_frame)

                #Subtitle Stuff
                print(i)
                caption = ""
                LR = (int(sub_index[caption_index].split("-")[0]))+100
                HR = (int(sub_index[caption_index].split("-")[1]))+100
                is_between = HR <= i <= LR

                if(is_between):
                        caption = captions[caption_index]
                        if i == LR:
                                caption_index += 1
                                caption_slide_index = -8


                res, frame = cap.read()
                #crop the frame to try get a close aspect ratio to 128:64(2:1) so it looks better on the calc
                frame = frame[ 15:345, 0:640]
                frame = cv2.resize(frame,(128,64),interpolation = cv2.INTER_LINEAR )
                
                if i == 20:
                        cv2.imwrite('sample_.png', frame)  

                gray_thresh = 190
                imgray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
                ret,thresh_img = cv2.threshold(imgray, gray_thresh, 255, cv2.THRESH_BINARY)
                contours, hierarchy = cv2.findContours(thresh_img, cv2.RETR_CCOMP, cv2.RETR_TREE)
                img_contours = np.zeros(frame.shape)
                cv2.drawContours(img_contours, contours, -1, (255,255,255), 1)

                #img_contours = cv2.resize(img_contours,(128,64),interpolation = cv2.INTER_LINEAR )

                #Sample Image for Debug
                if caption != "":
                        if len(caption) > 24:
                                caption_slide_index += (2*((LR-HR)/len(caption)))+0.5
                        else:
                                caption_slide_index = -8
                        cv2.rectangle(img_contours,(0,56),(127,63),(255,255,255),-1)
                        j = math.floor(max(caption_slide_index,0))
                        cv2.putText(img_contours,caption[j:j+24],(0,63),cv2.FONT_HERSHEY_PLAIN,0.5,(0,0,0),1)
                      
                
                #cv2.imwrite('sample.png', img_contours)  

                #Work out if scene is dark or not
                pxlavg = 0
                dark = False
                for j in range(64):
                        if img_contours[j,j*2,0] != 0:
                                pxlavg +=1
                if pxlavg > 0.035:
                        dark = True
                else:
                        dark = False

                cv2.imwrite('testImages/'+str(i)+'.png', img_contours)
                render = True
                debug_index = 0
                if render:
                        for y in range(128):
                                for x in range(64):
                                        debug_index += 1
                                        if dark:
                                                if img_contours[x,y,0] == 0:
                                                       output += "0"
                                                else:
                                                       output += "1"
                                        else:
                                                if img_contours[x,y,0] == 0:
                                                       output += "1"
                                                else:
                                                       output += "0" 
                
        #BinFile_Old(output)
        #Format For Compression
        temp = re.findall('.{1,8}', output)
        output = []
        for i in temp:
                output.append(int(i, 2))

        intArray = Compress(output)
        BinFile(intArray)                    
        

def Compress(data):
        RAWNibbleList = []
        Output = []
        for x in data:
                high, low = x >> 4, x & 0x0F
                RAWNibbleList.append(high)
                RAWNibbleList.append(low)
        NibbleAmmount = []
        NibbleCount = 1
        for inx,x in enumerate(RAWNibbleList):
                if inx == len(RAWNibbleList)-1:
                        break

                if x == RAWNibbleList[inx+1] and NibbleCount < 15:
                        NibbleCount += 1
                else:  
                        NibbleAmmount.append(int(NibbleCount))
                        NibbleCount = 1
                        Output.append(int(x))
                        
                        
                #New FRAME
                if inx % 2048 == 0 and inx != 0:
                        NibbleCount = 1
                        NibbleAmmount.append(0x0)
                        Output.append(0x0)
        
        Compressed = []
        for index,x in enumerate(Output):
                Compressed.append(NibbleAmmount[index]<<4 | x)
                #print(NibbleAmmount[index]<<4 | x)
        return Compressed
                

def BinFile(intArray):
        file = open('num.joe','wb')
        for x in intArray:
                file.write(x.to_bytes(1, byteorder='little'))

def BinFile_Old(code):
        file = open('num.joe','wb')
        cur = 0
        while cur < len(code):
                c = int(code[cur:cur+8], 2)
                file.write(bytes(chr(c), 'iso8859-1'))
                cur += 8


def format_subtitles():
        f = open("AdventureTime.srt", "r").read().split("\n")
        caption = ""
        rx = re.compile('([.,!\'-?])')
        for inx,i in enumerate(f):   
                if i != "" and i[0].isdigit() == False:
                        caption += rx.sub("",i) + " "
                if  i != "" and i[0] == "0":
                        seconds2 = 0
                        for index,x in enumerate(i.split(" --> ")):
                                seconds = 0
                                for inx,y in enumerate(x[0:8].split(":")):
                                        if inx == 0:
                                                seconds += int(y)*3600
                                        elif inx == 1:
                                                seconds += int(y)*60
                                        else:
                                                seconds += int(y)
                                if index == 0:
                                        seconds2 = seconds
                                elif index == 1:
                                        captions.append(caption)
                                        sub_index.append(str((seconds)*8)+"-"+str((seconds2)*8))
                                        caption = ""
        captions.pop(0)
        
format_subtitles()
ConvertVideo()
#cv2.destroyAllWindows()

