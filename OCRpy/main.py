
import cv2  # 3.4.2
import pytesseract  # 5.0.0-alpha.20200328
from PIL import Image, ImageEnhance

print(cv2.__version__)
pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'
print(pytesseract.get_tesseract_version())

orig_name  = "imgs/test_marker.jpg"
rotated  = "imgs/rotated.jpg"

resize = False
params = '-c tessedit_char_whitelist=0123456789. --psm 11 --dpi 72'

img = cv2.imread(rotated)

height, width, channels = img.shape

imgResized = img
if resize:
    imgResized = cv2.resize(img, ( width*3, height*3))
    im = Image.fromarray(imgResized)

cv2.imshow("img",imgResized)
cv2.waitKey()


data = pytesseract.image_to_string(img, config=params)
print(data)

h, w, c = img.shape
boxes = pytesseract.image_to_boxes(img,  lang='rus', config=params)

for b in boxes.splitlines():
    b = b.split(' ')
    img = cv2.rectangle(img, (int(b[1]), h - int(b[2])), (int(b[3]), h - int(b[4])), (0, 255, 0), 2)

cv2.imshow('img', img)
cv2.waitKey(0)
