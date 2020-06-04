### Запуск tesseract из командной строки


- tesseract.exe test_marker.jpg data

- tesseract.exe test_marker.jpg data -c tessedit_char_whitelist=01234567890 --psm 11 --oem 0

- tesseract.exe test_marker.jpg data -c tessedit_char_whitelist=0123456789. --psm 11 --dpi 72

- tesseract.exe test_marker.jpg data -c tessedit_char_whitelist=0123456789.

- tesseract.exe test_filtered.jpg data -c tessedit_char_whitelist=0123456789.

https://github.com/tesseract-ocr/tesseract/blob/master/doc/tesseract.1.asc

		NB: psm - Page Segmentation Mode
