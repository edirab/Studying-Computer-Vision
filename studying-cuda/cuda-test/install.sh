echo "Compiling and linking project..."
g++ -Wall -Wno-unused-variable -Wno-parentheses -o a.out\
	cuda-test.cpp \
	-I/usr/local/include/opencv4/ \
	-L/usr/local/lib/ \
	-pthread \
	-lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio \
	-lopencv_cudaarithm -lopencv_cudaimgproc -lopencv_cudawarping
