import cv2
import os
import re

def sorted_nicely( l ): 
    convert = lambda text: int(text) if text.isdigit() else text 
    alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key) ] 
    return sorted(l, key = alphanum_key)

DIR = '../example/result_images/'
VIDEO_DIR = '../example/result_video'

video_file  = VIDEO_DIR + '.avi'
image_count=0
for file in os.listdir(DIR):	
	image_count = image_count+1

fourcc = cv2.cv.CV_FOURCC(*'XVID')
video = cv2.VideoWriter(video_file,fourcc, 15.0, (1080,1080),True)

img_files = sorted_nicely(os.listdir(DIR))

for img_file in img_files:
	img_path = os.path.join(DIR, img_file)
	img = cv2.imread(img_path)
	video.write(img)
video.release()
cv2.destroyAllWindows()

