# Face Detection App

A real-time face detection application using OpenCV and C++.

## Features
- Real-time face detection from webcam
- Visual feedback with bounding boxes around detected faces
- Face count display
- Graceful exit with 'q' or ESC key

## Requirements
- OpenCV 4.x installed
- C++ compiler (g++, Visual Studio, etc.)
- Webcam

## Installation & Setup

### 1. Install OpenCV
Download OpenCV from: https://opencv.org/releases/
Extract to `C:\opencv\` (or update paths in compile.bat)

### 2. Compile the Application
Run the compilation script:
```bash
compile.bat
```

Or manually compile:
```bash
# For MinGW/GCC
g++ -std=c++11 main.cpp -o face_detection.exe -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_objdetect -lopencv_videoio

# For Visual Studio
cl main.cpp /I"C:\opencv\build\include" /link "C:\opencv\build\x64\vc16\lib\opencv_world4.lib"
```

### 3. Run the Application
```bash
face_detection.exe
```

## Usage
- The app will automatically try different camera indices (0, 1, 2)
- Press 'q' or ESC to exit
- Make sure `haarcascade_frontalface_default.xml` is in the same directory

## Troubleshooting

### Common Issues:
1. **"Could not open camera"**: 
   - Check if webcam is connected and not used by another application
   - Try different camera indices

2. **"Could not load cascade classifier"**:
   - Ensure `haarcascade_frontalface_default.xml` is in the same directory as the executable

3. **Compilation errors**:
   - Verify OpenCV installation
   - Check include and library paths
   - Ensure all OpenCV modules are linked

### Camera Issues:
- If camera index 0 doesn't work, the app will automatically try indices 1 and 2
- Close other applications that might be using the camera (Skype, Zoom, etc.)

## Files
- `main.cpp` - Main application code
- `haarcascade_frontalface_default.xml` - Haar cascade classifier for face detection
- `compile.bat` - Compilation script
- `README.md` - This file
