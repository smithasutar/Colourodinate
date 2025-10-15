@echo off
echo Installing OpenCV for Windows...

echo.
echo Step 1: Download OpenCV
echo Please download OpenCV from: https://opencv.org/releases/
echo Choose "Windows" version and download the .exe file
echo.
echo Step 2: Install OpenCV
echo 1. Run the downloaded .exe file
echo 2. Extract to C:\opencv\
echo 3. You should have: C:\opencv\build\include\opencv2\
echo.
echo Step 3: Set Environment Variables
echo Add these to your PATH:
echo C:\opencv\build\x64\vc16\bin
echo.
echo Step 4: Test Installation
echo After installation, run: test_opencv.bat
echo.
pause
