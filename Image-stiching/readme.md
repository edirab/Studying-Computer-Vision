### Склеивание изображений

- Пример 1

		Image-stiching.exe ^
		../../Image-stiching/stitching/boat1.jpg ^
		../../Image-stiching/stitching/boat2.jpg ^
		../../Image-stiching/stitching/boat3.jpg ^
		../../Image-stiching/stitching/boat4.jpg ^
		../../Image-stiching/stitching/boat5.jpg ^
		../../Image-stiching/stitching/boat6.jpg ^
		--try_use_gpu yes

![](./boat-stitching.jpg)

For Linux:

		Image-stiching.exe\
		../../Image-stiching/stitching/boat1.jpg\
		../../Image-stiching/stitching/boat2.jpg\
		../../Image-stiching/stitching/boat3.jpg\
		../../Image-stiching/stitching/boat4.jpg\
		../../Image-stiching/stitching/boat5.jpg\
		../../Image-stiching/stitching/boat6.jpg


- Пример 2

		Image-stiching.exe ^
		--mode scans ^
		../../Image-stiching/stitching/newspaper1.jpg ^
		../../Image-stiching/stitching/newspaper2.jpg ^
		../../Image-stiching/stitching/newspaper3.jpg ^
		../../Image-stiching/stitching/newspaper4.jpg

![](./newspaper-stitching.jpg)

- Пример 3

		Image-stiching.exe ^
		../../Image-stiching/stitching/s1.jpg ^
		../../Image-stiching/stitching/s2.jpg 
		

Ссылки: https://docs.opencv.org/4.1.1/d8/d19/tutorial_stitcher.html

Можно бы улучшить: https://docs.opencv.org/4.1.1/d6/dba/group__core__utils__samples.html#ga3a33b00033b46c698ff6340d95569c13