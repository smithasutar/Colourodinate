@echo off
echo Testing OpenCV Installation...

REM Test if OpenCV headers exist
if exist "C:\opencv\build\include\opencv2\imgcodecs.hpp" (
    echo ✓ OpenCV headers found
) else (
    echo ✗ OpenCV headers not found at C:\opencv\build\include\opencv2\
    echo Please install OpenCV first by running install_opencv.bat
    pause
    exit /b 1
)

REM Test if OpenCV libraries exist
if exist "C:\opencv\build\x64\vc16\lib\opencv_core*.lib" (
    echo ✓ OpenCV libraries found
) else (
    echo ✗ OpenCV libraries not found at C:\opencv\build\x64\vc16\lib\
    echo Please install OpenCV first by running install_opencv.bat
    pause
    exit /b 1
)

echo.
echo OpenCV installation looks good!
echo You can now compile your face detection app.
echo.
pause
