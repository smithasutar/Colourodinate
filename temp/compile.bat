@echo off
echo Compiling Face Detection App...

REM Check if OpenCV is installed
if not exist "C:\opencv\build\include\opencv2\imgcodecs.hpp" (
    echo ERROR: OpenCV not found!
    echo.
    echo Please install OpenCV first:
    echo 1. Run install_opencv.bat for instructions
    echo 2. Or download from: https://opencv.org/releases/
    echo 3. Extract to C:\opencv\
    echo.
    pause
    exit /b 1
)

echo OpenCV found, attempting compilation...

REM Try different compilation methods
echo.
echo Method 1: Using g++ with specific OpenCV paths...
g++ -std=c++11 main.cpp -o face_detection.exe ^
    -I"C:\opencv\build\include" ^
    -L"C:\opencv\build\x64\vc16\lib" ^
    -lopencv_core4 ^
    -lopencv_imgproc4 ^
    -lopencv_imgcodecs4 ^
    -lopencv_highgui4 ^
    -lopencv_objdetect4 ^
    -lopencv_videoio4

if %errorlevel% equ 0 (
    echo ✓ Compilation successful! Run face_detection.exe
    goto :success
)

echo.
echo Method 2: Using pkg-config (if available)...
g++ -std=c++11 main.cpp -o face_detection.exe `pkg-config --cflags --libs opencv4`

if %errorlevel% equ 0 (
    echo ✓ Compilation successful! Run face_detection.exe
    goto :success
)

echo.
echo Method 3: Using opencv_world (single library)...
g++ -std=c++11 main.cpp -o face_detection.exe ^
    -I"C:\opencv\build\include" ^
    -L"C:\opencv\build\x64\vc16\lib" ^
    -lopencv_world4

if %errorlevel% equ 0 (
    echo ✓ Compilation successful! Run face_detection.exe
    goto :success
)

echo.
echo ✗ All compilation methods failed!
echo.
echo Troubleshooting:
echo 1. Make sure OpenCV is installed at C:\opencv\
echo 2. Check if you have a C++ compiler (g++, MinGW, or Visual Studio)
echo 3. Try running test_opencv.bat to verify OpenCV installation
echo.
echo Manual compilation commands:
echo.
echo For MinGW:
echo g++ -std=c++11 main.cpp -o face_detection.exe -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_objdetect -lopencv_videoio
echo.
echo For Visual Studio:
echo cl main.cpp /I"C:\opencv\build\include" /link "C:\opencv\build\x64\vc16\lib\opencv_world4.lib"

:success
pause
