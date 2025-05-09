# Audio FX Engine v2.01

Professional audio processing application with real-time effects (echo, pitch shift, speed control) for WAV files.

## ✨ Features
- **Pitch Shifting**: Frequency modification without speed alteration
- **Echo Effects**: Customizable delay/decay parameters
- **Time-Stretching**: Speed control with preserved pitch
- **Multi-Channel Support**: Stereo audio processing
- **Libsndfile Integration**: High-quality WAV file I/O

## 🛠️ Tech Stack
- C++17 (STL, Filesystem)
- Libsndfile (v1.2.2)
- CMake (Cross-platform builds)
- Visual Studio 2022 (Windows)

## 🗺️ Project Roadmap

### 🚀 Upcoming Features
```mermaid
gantt
    title Development Timeline
    dateFormat  YYYY-MM-DD
    section Core Features
    Real-time Audio Input      :active, 2025-04-19, 30d
    GUI Interface (Qt)         :
    VST Plugin Support         :
    
    section Optimization
    Multi-thread Processing    :
    WASM Build Support         :
