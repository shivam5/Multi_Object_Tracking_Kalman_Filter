import os, sys
import numpy as np
import cv2
import glob
from PIL import Image, ImageDraw, ImageFont
import ntpath

def path_leaf(path):
    head, tail = ntpath.split(path)
    return tail or ntpath.basename(head)

image_file = "../example/test_video.txt"
file = open(image_file, "r")
lines = file.readlines()

label_folder = "../example/yolo_predictions/"
filtered_labels = "../example/yolo_predictions_filtered/"
save_folder = "../example/result_images/"

for filepath in lines:
    filepath = filepath.rstrip()
    	
    label_name = os.path.splitext(path_leaf(filepath))[0]+'.txt'
    label_path = os.path.join(label_folder, label_name)
    filtered_label_path = os.path.join(filtered_labels, label_name)

    image = cv2.imread(filepath)

    file_handle = open(label_path, 'r')
    lines_list = file_handle.readlines()

    # print lines_list
    for line in lines_list:
        # print line
        line_split = line.split()
        # print "lines_split is"
        # print line_split

        l0 = line_split[0]
        x0 = float(line_split[1])
        y0 = float(line_split[2])
        w0 = float(line_split[3])
        h0 = float(line_split[4])
        # print image.shape
        (w,h,depth) = image.shape

        centerx = x0*w
        centery = y0*h
        offsetx = w0*w/2
        offsety = h0*h/2

        coordx = [centerx - offsetx, centerx + offsetx, centerx + offsetx, centerx - offsetx ]
        coordy = [centery - offsety, centery + offsety, centery + offsety, centery - offsety]
        x1 = coordx[0]
        x2 = coordx[2]
        y1 = coordy[0]
        y2 = coordy[2]
        # cv2.putText(image , l0, (int(x1)-5, int(y1)-5), cv2.FONT_HERSHEY_SIMPLEX, 1.1, (0, 255, 0), 2)
        # print int(x1), int(y1), int(x2), int(y2)
        cv2.rectangle(image, (int(x1), int(y1)), (int(x2), int(y2)), (255, 255, 255), 1)

    file_handle = open(filtered_label_path, 'r')
    lines_list = file_handle.readlines()

    # print lines_list
    for line in lines_list:
        # print line
        line_split = line.split()
        # print "lines_split is"
        # print line_split

        l0 = line_split[0]
        x0 = float(line_split[1])
        y0 = float(line_split[2])
        w0 = float(line_split[3])
        h0 = float(line_split[4])
        # print image.shape
        (w,h,depth) = image.shape

        centerx = x0*w
        centery = y0*h
        offsetx = w0*w/2
        offsety = h0*h/2

        coordx = [centerx - offsetx, centerx + offsetx, centerx + offsetx, centerx - offsetx ]
        coordy = [centery - offsety, centery + offsety, centery + offsety, centery - offsety]
        x1 = coordx[0]
        x2 = coordx[2]
        y1 = coordy[0]
        y2 = coordy[2]
        cv2.putText(image , l0, (int(x1)-5, int(y1)-5), cv2.FONT_HERSHEY_SIMPLEX, 1.1, (0, 255, 255), 2)
        # print int(x1), int(y1), int(x2), int(y2)
        cv2.rectangle(image, (int(x1), int(y1)), (int(x2), int(y2)), (0, 255, 255), 1)


    cv2.imwrite(os.path.join(save_folder, path_leaf(filepath)), image)