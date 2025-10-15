@echo off
echo Compiling Simple Face Shade Detector...

REM Check if OpenCV is installed
if not exist "C:\opencv\build\include\opencv2\imgcodecs.hpp" (
    echo ERROR: OpenCV not found!
    echo Please install OpenCV first by running install_opencv.bat
    pause
    exit /b 1
)

echo OpenCV found, compiling simple shade detector...

g++ -std=c++11 simple_shade_detector.cpp -o simple_shade_detector.exe ^
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
    echo To run: simple_shade_detector.exe
    echo Press 'q' to quit
) else (
    echo ✗ Compilation failed!
    echo Try running test_opencv.bat to verify OpenCV installation
)

pause
