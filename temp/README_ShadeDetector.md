# Face Shade Detector

A sophisticated face detection application that analyzes skin tone and provides foundation shade matching recommendations.

## Features

### 🎯 Core Functionality
- **Real-time face detection** using Haar cascades
- **Skin tone analysis** with color space conversion
- **Undertone detection** (Cool, Warm, Neutral)
- **Foundation shade matching** with 21+ shade categories
- **Fitzpatrick scale classification** (1-6)
- **Visual color swatches** for each detected shade

### 🎨 Shade Categories
- **Fair Light** to **Very Deep** shades
- **Undertone classification**: Cool, Warm, Neutral
- **Foundation matching** with detailed descriptions
- **Color accuracy** with RGB analysis

### 🖥️ User Interface
- **Real-time video feed** with face detection
- **Shade information overlay** on detected faces
- **Color swatches** showing matched shades
- **Frame saving** capability ('s' key)
- **Graceful exit** ('q' or ESC key)

## Technical Details

### Color Analysis
- **Multi-color space analysis**: BGR, HSV, Lab, YUV
- **Center region sampling** for accurate skin tone
- **Undertone detection** using color ratios
- **Euclidean distance matching** for shade selection

### Shade Database
- **21 foundation shades** covering all skin tones
- **Fitzpatrick scale** classification (1-6)
- **Undertone categorization** for precise matching
- **RGB color values** for each shade

## Installation & Setup

### Prerequisites
- OpenCV 4.x
- C++ compiler (g++, Visual Studio, MinGW)
- Webcam
- `haarcascade_frontalface_default.xml` file

### Quick Start
1. **Install OpenCV** (if not already installed):
   ```bash
   # Download from: https://opencv.org/releases/
   # Extract to: C:\opencv\
   ```

2. **Compile the application**:
   ```bash
   compile_shade_detector.bat
   ```

3. **Run the detector**:
   ```bash
   face_shade_detector.exe
   ```

### Manual Compilation
```bash
# For MinGW/GCC
g++ -std=c++11 face_shade_detector.cpp -o face_shade_detector.exe -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_objdetect -lopencv_videoio

# For Visual Studio
cl face_shade_detector.cpp /I"C:\opencv\build\include" /link "C:\opencv\build\x64\vc16\lib\opencv_world4.lib"
```

## Usage

### Controls
- **'q' or ESC**: Exit the application
- **'s'**: Save current frame as image
- **Mouse**: Click and drag to interact with window

### Understanding the Output

#### Shade Information Display
- **Shade Name**: Foundation shade recommendation
- **Undertone**: Cool, Warm, or Neutral
- **Description**: Detailed shade characteristics
- **Color Swatch**: Visual representation of the shade

#### Example Output
```
Shade: Light Medium
Undertone: Warm
Light medium with yellow undertones
[Color Swatch]
```

### Shade Categories

#### Fair Shades (Fitzpatrick 1-2)
- Fair Light (Cool)
- Fair (Neutral)
- Fair Medium (Warm)

#### Light Shades (Fitzpatrick 2-3)
- Light (Cool/Neutral/Warm)
- Light Medium (Cool/Neutral/Warm)

#### Medium Shades (Fitzpatrick 3-4)
- Medium (Cool/Neutral/Warm)
- Medium Deep (Cool/Neutral/Warm)

#### Deep Shades (Fitzpatrick 5-6)
- Deep (Cool/Neutral/Warm)
- Very Deep (Cool/Neutral/Warm)

## Troubleshooting

### Common Issues

#### "Could not load face cascade classifier"
- Ensure `haarcascade_frontalface_default.xml` is in the same directory
- Check file permissions and path

#### "Could not open camera"
- Close other applications using the camera
- Try different camera indices (0, 1, 2)
- Check camera permissions

#### Compilation Errors
- Verify OpenCV installation at `C:\opencv\`
- Check include and library paths
- Ensure all OpenCV modules are available

#### Poor Shade Detection
- Ensure good lighting conditions
- Position face clearly in camera view
- Avoid shadows and harsh lighting
- Clean camera lens

### Performance Tips
- **Good lighting**: Use natural or white light
- **Camera positioning**: Face the camera directly
- **Background**: Use neutral backgrounds
- **Distance**: Stay 1-2 feet from camera

## Advanced Features

### Color Analysis Algorithm
1. **Face Detection**: Haar cascade for face localization
2. **Region Sampling**: Center face region for skin analysis
3. **Color Space Conversion**: BGR → HSV, Lab, YUV
4. **Statistical Analysis**: Mean color calculation
5. **Undertone Detection**: Red/Green and Blue ratios
6. **Shade Matching**: Euclidean distance in RGB space

### Customization Options
- Modify shade database in `initializeShadeDatabase()`
- Adjust color analysis parameters
- Add new shade categories
- Customize display information

## File Structure
```
├── face_shade_detector.cpp    # Main application
├── compile_shade_detector.bat # Compilation script
├── haarcascade_frontalface_default.xml # Face detection model
├── README_ShadeDetector.md    # This documentation
└── face_shade_detector.exe    # Compiled executable
```

## Contributing
Feel free to enhance the shade database, improve color analysis algorithms, or add new features!

## License
This project is open source. Please ensure you have proper OpenCV licensing for commercial use.
