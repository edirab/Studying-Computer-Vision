set "opencvSource=opencv-4.1.1-cuda"
set "opencvExtraModules=opencv_contrib-4.1.1/modules"
set "opencvBuild=%opencvSource%\build"
set "compiler=Visual Studio 16 2019"
set "buildType=Release"

set "python2_executable=C:/Python27/python.exe"
set "python2_include_dir=C:/Python27/include"
set "python2_library=C:/Python27/libs/python27.lib"
set "python2_numpy_include_dirs=C:/Python27/Lib/site-packages/numpy/core/include"
set "python2_packages_path=C:/Python27/Lib/site-packages"

set "python3_executable=C:/Python37/python.exe"
set "python3_include_dir=C:/Python37/include"
set "python3_library=C:/Python37/libs/python37.lib"
set "python3_numpy_include_dirs=C:/Python37/lib/site-packages/numpy/core/include"
set "python3_packages_path=C:/Python37/Lib/site-packages"

set "cudnnLibrary=C:/Program Files/cuda"
set "cudnnInclude=C:/Program Files/cuda/include"

cmake ^
-B"%opencvBuild%/" ^
-H"%opencvSource%/" ^
-G"%compiler%" ^
-Ax64 ^
-DCMAKE_BUILD_TYPE=%buildType% ^
-DBUILD_opencv_world=OFF ^
-DINSTALL_TESTS=OFF ^
-DINSTALL_C_EXAMPLES=OFF ^
-DBUILD_EXAMPLES=OFF ^
-DOPENCV_EXTRA_MODULES_PATH="%opencvExtraModules%/" ^
-DBUILD_PROTOBUF=OFF ^
-DBUILD_opencv_python_bindings_generator=ON ^
-DOPENCV_ENABLE_NONFREE=ON ^
-DENABLE_FAST_MATH=ON ^
-DWITH_CUDA=ON ^
-DCUDA_ARCH_BIN=6.1 ^
-DCUDA_FAST_MATH=ON ^
-DWITH_CUBLAS=ON ^
-DCUDA_ARCH_PTX=7.5 ^
-DBUILD_opencv_python2=ON ^
-DPYTHON2_EXECUTABLE="%python2_executable%" ^
-DOPENCV_PYTHON2_VERSION=2.7.16 ^
-DPYTHON2_INCLUDE_DIR="%python2_include_dir%" ^
-DPYTHON2_LIBRARY="%python2_library%" ^
-DPYTHON2_NUMPY_INCLUDE_DIRS="%python2_numpy_include_dirs%" ^
-DPYTHON2_PACKAGES_PATH="%python2_packages_path%" ^
-DBUILD_opencv_python3=ON ^
-DPYTHON3_EXECUTABLE="%python3_executable%" ^
-DOPENCV_PYTHON3_VERSION=3.7.3 ^
-DPYTHON3_INCLUDE_DIR="%python3_include_dir%" ^
-DPYTHON3_LIBRARY="%python3_library%" ^
-DPYTHON3_NUMPY_INCLUDE_DIRS="%python3_numpy_include_dirs%" ^
-DPYTHON3_PACKAGES_PATH="%python3_packages_path%"


19>C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.0\include\crt/host_config.h(143): fatal error C1189: #error:  -- unsupported Microsoft Visual Studio version! Only the versions between 2013 and 2017 (inclusive) are supported!
19>CMake Error at cuda_compile_1_generated_gpu_mat.cu.obj.Release.cmake:220 (message):
19>  Error generating
19>  C:/OpenCV/opencv-4.1.1-cuda/build/modules/core/CMakeFiles/cuda_compile_1.dir/src/cuda/Release/cuda_compile_1_generated_gpu_mat.cu.obj


-- General configuration for OpenCV 4.1.1 =====================================
--   Version control:               unknown
--
--   Extra modules:
--     Location (extra):            C:/OpenCV/opencv_contrib-4.1.1/modules
--     Version control (extra):     unknown
--
--   Platform:
--     Timestamp:                   2020-08-30T21:24:19Z
--     Host:                        Windows 10.0.17763 AMD64
--     CMake:                       3.18.2
--     CMake generator:             Visual Studio 16 2019
--     CMake build tool:            C:/Program Files (x86)/Microsoft Visual Studio/2019/Enterprise/MSBuild/Current/Bin/MSBuild.exe
--     MSVC:                        1923
--
--   CPU/HW features:
--     Baseline:                    SSE SSE2 SSE3
--       requested:                 SSE3
--     Dispatched code generation:  SSE4_1 SSE4_2 FP16 AVX AVX2 AVX512_SKX
--       requested:                 SSE4_1 SSE4_2 AVX FP16 AVX2 AVX512_SKX
--       SSE4_1 (15 files):         + SSSE3 SSE4_1
--       SSE4_2 (2 files):          + SSSE3 SSE4_1 POPCNT SSE4_2
--       FP16 (1 files):            + SSSE3 SSE4_1 POPCNT SSE4_2 FP16 AVX
--       AVX (5 files):             + SSSE3 SSE4_1 POPCNT SSE4_2 AVX
--       AVX2 (29 files):           + SSSE3 SSE4_1 POPCNT SSE4_2 FP16 FMA3 AVX AVX2
--       AVX512_SKX (5 files):      + SSSE3 SSE4_1 POPCNT SSE4_2 FP16 FMA3 AVX AVX2 AVX_512F AVX512_COMMON AVX512_SKX
--
--   C/C++:
--     Built as dynamic libs?:      YES
--     C++ Compiler:                C:/Program Files (x86)/Microsoft Visual Studio/2019/Enterprise/VC/Tools/MSVC/14.23.28105/bin/Hostx64/x64/cl.exe  (ver 19.23.28105.4)
--     C++ flags (Release):         /DWIN32 /D_WINDOWS /W4 /GR  /D _CRT_SECURE_NO_DEPRECATE /D _CRT_NONSTDC_NO_DEPRECATE /D _SCL_SECURE_NO_WARNINGS /Gy /bigobj /Oi  /fp:fast     /EHa /wd4127 /wd4251 /wd4324 /wd4275 /wd4512 /wd4589 /MP12   /MD /O2 /Ob2 /DNDEBUG
--     C++ flags (Debug):           /DWIN32 /D_WINDOWS /W4 /GR  /D _CRT_SECURE_NO_DEPRECATE /D _CRT_NONSTDC_NO_DEPRECATE /D _SCL_SECURE_NO_WARNINGS /Gy /bigobj /Oi  /fp:fast     /EHa /wd4127 /wd4251 /wd4324 /wd4275 /wd4512 /wd4589 /MP12   /MDd /Zi /Ob0 /Od /RTC1
--     C Compiler:                  C:/Program Files (x86)/Microsoft Visual Studio/2019/Enterprise/VC/Tools/MSVC/14.23.28105/bin/Hostx64/x64/cl.exe
--     C flags (Release):           /DWIN32 /D_WINDOWS /W3  /D _CRT_SECURE_NO_DEPRECATE /D _CRT_NONSTDC_NO_DEPRECATE /D _SCL_SECURE_NO_WARNINGS /Gy /bigobj /Oi  /fp:fast       /MP12    /MD /O2 /Ob2 /DNDEBUG
--     C flags (Debug):             /DWIN32 /D_WINDOWS /W3  /D _CRT_SECURE_NO_DEPRECATE /D _CRT_NONSTDC_NO_DEPRECATE /D _SCL_SECURE_NO_WARNINGS /Gy /bigobj /Oi  /fp:fast       /MP12  /MDd /Zi /Ob0 /Od /RTC1
--     Linker flags (Release):      /machine:x64  /INCREMENTAL:NO
--     Linker flags (Debug):        /machine:x64  /debug /INCREMENTAL
--     ccache:                      NO
--     Precompiled headers:         NO
--     Extra dependencies:          cudart_static.lib C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.0/lib/x64/cuda.lib nppc.lib nppial.lib nppicc.lib nppicom.lib nppidei.lib nppif.lib nppig.lib nppim.lib nppist.lib nppisu.lib nppitc.lib npps.lib cublas.lib cudnn.lib cufft.lib -LIBPATH:C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.0/lib/x64
--     3rdparty dependencies:
--
--   OpenCV modules:
--     To be built:                 aruco bgsegm bioinspired calib3d ccalib core cudaarithm cudabgsegm cudacodec cudafeatures2d cudafilters cudaimgproc cudalegacy cudaobjdetect cudaoptflow cudastereo cudawarping cudev datasets dnn dnn_objdetect dpm face features2d flann fuzzy gapi hdf hfs highgui img_hash imgcodecs imgproc line_descriptor ml objdetect optflow phase_unwrapping photo plot python2 python3 quality reg rgbd saliency shape stereo stitching structured_light superres surface_matching text tracking ts video videoio videostab world xfeatures2d ximgproc xobjdetect xphoto
--     Disabled:                    -
--     Disabled by dependency:      -
--     Unavailable:                 cnn_3dobj cvv freetype java js matlab ovis sfm viz
--     Applications:                tests perf_tests apps
--     Documentation:               NO
--     Non-free algorithms:         YES
--
--   Windows RT support:            NO
--
--   GUI:
--     Win32 UI:                    YES
--     VTK support:                 NO
--
--   Media I/O:
--     ZLib:                        build (ver 1.2.11)
--     JPEG:                        build-libjpeg-turbo (ver 2.0.2-62)
--     WEBP:                        build (ver encoder: 0x020e)
--     PNG:                         build (ver 1.6.37)
--     TIFF:                        build (ver 42 - 4.0.10)
--     JPEG 2000:                   build (ver 1.900.1)
--     OpenEXR:                     build (ver 2.3.0)
--     HDR:                         YES
--     SUNRASTER:                   YES
--     PXM:                         YES
--     PFM:                         YES
--
--   Video I/O:
--     DC1394:                      NO
--     FFMPEG:                      YES (prebuilt binaries)
--       avcodec:                   YES (58.35.100)
--       avformat:                  YES (58.20.100)
--       avutil:                    YES (56.22.100)
--       swscale:                   YES (5.3.100)
--       avresample:                YES (4.0.0)
--     GStreamer:                   NO
--     DirectShow:                  YES
--     Media Foundation:            YES
--       DXVA:                      YES
--
--   Parallel framework:            Concurrency
--
--   Trace:                         YES (with Intel ITT)
--
--   Other third-party libraries:
--     Intel IPP:                   2019.0.0 Gold [2019.0.0]
--            at:                   C:/OpenCV/opencv-4.1.1-cuda/build/3rdparty/ippicv/ippicv_win/icv
--     Intel IPP IW:                sources (2019.0.0)
--               at:                C:/OpenCV/opencv-4.1.1-cuda/build/3rdparty/ippicv/ippicv_win/iw
--     Lapack:                      YES (C:/Users/corsair/Anaconda3/Library/lib/lapack.lib C:/Users/corsair/Anaconda3/Library/lib/blas.lib)
--     Eigen:                       NO
--     Custom HAL:                  NO
--     Protobuf:                    build (3.5.1)
--
--   NVIDIA CUDA:                   YES (ver 10.0, CUFFT CUBLAS FAST_MATH)
--     NVIDIA GPU arch:             61
--     NVIDIA PTX archs:            75
--
--   cuDNN:                         YES (ver 7.6.2)
--
--   OpenCL:                        YES (NVD3D11)
--     Include path:                C:/OpenCV/opencv-4.1.1-cuda/3rdparty/include/opencl/1.2
--     Link libraries:              Dynamic load
--
--   Python 2:
--     Interpreter:                 C:/Python27/python.exe (ver 2.7.16)
--     Libraries:                   C:/Python27/libs/python27.lib (ver 2.7.16)
--     numpy:                       C:/Python27/Lib/site-packages/numpy/core/include (ver 1.16.6)
--     install path:                C:/Python27/Lib/site-packages/cv2/python-2.7
--
--   Python 3:
--     Interpreter:                 C:/Python37/python.exe (ver 3.7.3)
--     Libraries:                   C:/Python37/libs/python37.lib (ver 3.7.3)
--     numpy:                       C:/Python37/lib/site-packages/numpy/core/include (ver 1.19.1)
--     install path:                C:/Python37/Lib/site-packages/cv2/python-3.7
--
--   Python (for build):            C:/Python27/python.exe
--
--   Java:
--     ant:                         NO
--     JNI:                         NO
--     Java wrappers:               NO
--     Java tests:                  NO
--
--   Install to:                    C:/OpenCV/opencv-4.1.1-cuda/build/install
-- -----------------------------------------------------------------
--
-- Configuring done
-- Generating done
-- Build files have been written to: C:/OpenCV/opencv-4.1.1-cuda/build