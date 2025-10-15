# Colourodinate

Colourodinate is a C++ application that detects faces in an image and identifies the skin undertone (cool, warm, or neutral) using OpenCV. The project demonstrates computer vision techniques including face detection and color analysis.

---

## Features

- Detects human faces in images using OpenCV's Haar Cascade classifier.
- Extracts skin regions from detected faces.
- Determines skin undertone based on color analysis in YCrCb color space.
- Displays the original image with a rectangle around the face and the predicted undertone as text.

---

## Requirements

- **C++17** or later
- **OpenCV 4.12.0** (or compatible version)
- **Visual Studio 2022** (x64)
- `haarcascade_frontalface_default.xml` (OpenCV Haar Cascade for face detection)
- An input image (`test.jpg`) in the project folder

---

## Setup Instructions

1. **Clone or download the project** to your local machine.

2. **Install OpenCV**  
   Make sure OpenCV 4.12.0 is installed and note the path to the include and lib directories.

3. **Place required files** in the project folder:
   - `main.cpp`
   - `haarcascade_frontalface_default.xml`
   - `test.jpg` (your test image)

4. **Open the x64 Developer Command Prompt for VS 2022** and navigate to the project folder:

   ```bash
   cd C:\path\to\Colourodinate
