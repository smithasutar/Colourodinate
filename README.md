# 🎨 Colourodinate

**Colourodinate** is a C++ application that detects faces in an image and identifies the skin undertone (cool, warm, or neutral) using OpenCV. It demonstrates computer vision techniques including face detection and color analysis.

---

## ✨ Features

- 🧑‍🤝‍🧑 **Face Detection** – Detects human faces using OpenCV Haar Cascade classifier.  
- 🎯 **Skin Region Extraction** – Crops face regions for accurate analysis.  
- 🌈 **Undertone Detection** – Determines skin undertone (Cool, Warm, Neutral) using YCrCb color analysis.  
- 🖼️ **Visualization** – Draws rectangles around faces and labels the predicted undertone.

---

## 🛠️ Requirements

- 💻 **C++17** or later  
- 📦 **OpenCV 4.12.0**  
- 🏗️ **Visual Studio 2022** (x64)  
- 🔹 `haarcascade_frontalface_default.xml` (Haar Cascade)  
- 🖼️ Input image (`test.jpg`)  

---

## ⚡ Setup Instructions

1. **Clone or download the project**.  

2. **Install OpenCV** and note the include/lib paths.  

3. **Place required files** in the project folder:  
   - `main.cpp`  
   - `haarcascade_frontalface_default.xml`  
   - `test.jpg`  

4. **Open the x64 Developer Command Prompt for VS 2022** and navigate to the project folder:  

   ```bash
   cd C:\path\to\Colourodinate
