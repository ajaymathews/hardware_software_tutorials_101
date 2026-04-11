#install pyzbar,cv2,numpy


from __future__ import print_function
import pyzbar.pyzbar as pyzbar
import numpy as np
import cv2
 
def decode(im) : 
  decodedObjects = pyzbar.decode(im)  # Find barcodes and QR codes

#  print(decodedObjects) #the decoded object contains the following data
              #[Decoded(data=b'blynk://token/clone/112a7d1ce22f46e485c27a3ccf1f45db?server=blynk-cloud.com&port=443',
              #type='QRCODE', rect=Rect(left=35, top=35, width=442, height=442),
              #polygon=[Point(x=35, y=35), Point(x=35, y=476), Point(x=477, y=477), Point(x=476, y=35)])]

  for obj in decodedObjects:  # Print results
    print('Type : ', obj.type)
    print('Data : ', obj.data.decode('ascii'),'\n')   #decode the encrypted data to ascii
  return decodedObjects
 
 
def display(im, decodedObjects):# Display barcode and QR code location  
  for decodedObject in decodedObjects: # Loop over all decoded objects
    points = decodedObject.polygon #finding the points in the decoded objects
    if len(points) > 4 : # If the points do not form a quad (ie in a square form), find convex hull(finding the new points)
      hull = cv2.convexHull(np.array([point for point in points], dtype=np.float32))
      hull = list(map(tuple, np.squeeze(hull)))
    else : 
      hull = points;
    n = len(hull)    # Number of points in the convex hull usually 4 points in  qr code
    for j in range(0,n):    # Draw the convext hull one line by line
      cv2.line(im, hull[j], hull[ (j+1) % n], (255,0,0), 3)
  cv2.imshow("Results", im);# Display results 
  cv2.waitKey(0);

 
if __name__ == '__main__':# Main 
  im = cv2.imread('barcode_code128.png')  # Read image
 
  decodedObjects = decode(im)
  display(im, decodedObjects)
