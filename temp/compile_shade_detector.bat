@echo off
echo Compiling Face Shade Detector...

REM Check if OpenCV is installed
if not exist "C:\opencv\build\include\opencv2\imgcodecs.hpp" (
    echo ERROR: OpenCV not found!
    echo.
    echo Please install OpenCV first:
    echo 1. Download from: https://opencv.org/releases/
    echo 2. Extract to C:\opencv\
    echo 3. Run test_opencv.bat to verify
    echo.
    pause
    exit /b 1
)

echo OpenCV found, compiling shade detector...

REM Try compilation with different methods
echo.
echo Method 1: Using g++ with OpenCV modules...
g++ -std=c++11 face_shade_detector.cpp -o face_shade_detector.exe ^
    -I"C:\opencv\build\include" ^
    -L"C:\opencv\build\x64\vc16\lib" ^
    -lopencv_core4 ^
    -lopencv_imgproc4 ^
    -lopencv_imgcodecs4 ^
    -lopencv_highgui4 ^
    -lopencv_objdetect4 ^
    -lopencv_videoio4

if %errorlevel% equ 0 (
    echo ✓ Compilation successful!
    echo.
    echo To run: face_shade_detector.exe
    echo Controls: 'q' to quit, 's' to save frame
    goto :success
)

echo.
echo Method 2: Using opencv_world (single library)...
g++ -std=c++11 face_shade_detector.cpp -o face_shade_detector.exe ^
    -I"C:\opencv\build\include" ^
    -L"C:\opencv\build\x64\vc16\lib" ^
    -lopencv_world4

if %errorlevel% equ 0 (
    echo ✓ Compilation successful!
    echo.
    echo To run: face_shade_detector.exe
    echo Controls: 'q' to quit, 's' to save frame
    goto :success
)

echo.
echo ✗ Compilation failed!
echo.
echo Troubleshooting:
echo 1. Make sure OpenCV is properly installed
echo 2. Check if haarcascade_frontalface_default.xml is in the same folder
echo 3. Try running test_opencv.bat to verify OpenCV installation
echo.
echo Manual compilation:
echo g++ -std=c++11 face_shade_detector.cpp -o face_shade_detector.exe -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_objdetect -lopencv_videoio

:success
pause
