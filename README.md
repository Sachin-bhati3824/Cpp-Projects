<div align="center">

# 🔥 VisionForge

### Native AI Image Generator for Windows

*Low-level C++ engineering meets modern AI capability*

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![FLTK](https://img.shields.io/badge/FLTK-GUI-orange?style=for-the-badge)
![Playwright](https://img.shields.io/badge/Playwright-2EAD33?style=for-the-badge&logo=playwright&logoColor=white)

**[⬇️ Download VisionForge](https://drive.google.com/uc?export=download&id=1M2aNZF1WMFiUzoUGIN2EiddySPFn2jAw)**  &nbsp;·&nbsp;  **[📖 How It Works](#️-how-it-works)**  &nbsp;·&nbsp;  **[🧠 Architecture](#-architecture)**

</div>

---
How does it look 

<img width="1258" height="719" alt="Screenshot 2026-04-09 032353" src="https://github.com/user-attachments/assets/0ce4af33-ce20-4c02-acaa-3b3d253f2d60" />

---

---

## What Is VisionForge?

VisionForge is a **real native Windows desktop application** that transforms text prompts into AI-generated images — no browser, no cloud dashboard, no manual setup.

Built with **C++ (FLTK)** for performance and **Python + Playwright** for AI automation, it bridges low-level systems programming with modern AI workflows.

> **VisionForge is not a web wrapper.** It runs as a true native `.exe` with an embedded Python runtime, background workers, and a self-configuring setup system.

---

##  What Makes It Special

| Feature | Detail |
|---|---|
|  Standalone binary | No installation wizard, no dependencies to manage |
|  Auto-setup on first launch | Installs its own Python backend silently |
|  Prompt-to-image generation | Describe anything, get an image |
|  Advanced prompt controls | Strength, detail, lighting, camera POV, and more |
|  Responsive UI | Multithreaded — the interface never freezes |
|  Local image gallery | All images saved with timestamps, browsable in-app |
|  Zero manual setup | Just download → extract → run |

---


## 🚀 Download & Run

### 📦 Download

> **👉 [Download VisionForge ZIP](#)**


### ⚙️ Installation

```
1. Download the ZIP file
2. Extract anywhere on your computer
3. Open the extracted folder
4. Double-click VisionForge.exe
```

**That's it.** 

---

##  First Launch Auto-Setup

On first run, VisionForge automatically handles everything:

```
✔  Installs embedded Python environment
✔  Installs required libraries
✔  Sets up AI automation backend
✔  Prepares browsers for image generation
```

> **First launch may take 1–3 minutes.** This happens only once. Subsequent launches are instant.

No Python installation required. No command line needed. Ever.

---

## How It Works

### 1️⃣ Enter a Prompt

Describe the image you want in plain language:

```
cinematic cyberpunk city at night, neon lights, ultra realistic
```

### 2️⃣ Adjust Professional Settings

Open the **Professional Panel** to fine-tune generation:

| Control | What It Does |
|---|---|
| Prompt Strength | How closely the AI follows your prompt |
| Detail Level | Sharpness and complexity of output |
| Imagination | Creative freedom given to the model |
| Weirdness | How surreal or abstract the result gets |
| Lighting | Scene lighting style |
| Camera POV | Perspective and framing |

### 3️⃣ Generate

Click **Generate Image** and watch:

```
✔  Progress bar animates in real time
✔  Backend runs silently in the background
✔  Image appears automatically when ready
```

### 4️⃣ View Your Gallery

All generated images are saved automatically to:

```
output_gallery/
```

With timestamp-based filenames:

```
2026-04-06_22-24-44_PM.jpg
```

Click the **Gallery** button to open the folder directly from the app.

---

## Architecture

VisionForge uses a hybrid layered design:

```
┌─────────────────────────────┐
│        C++ FLTK GUI         │  ← Native Windows interface
└──────────────┬──────────────┘
               │
               ▼
┌─────────────────────────────┐
│   Multithreaded Controller  │  ← Background worker threads
└──────────────┬──────────────┘
               │
               ▼
┌─────────────────────────────┐
│   Embedded Python Runtime   │  ← Bundled, self-configuring
└──────────────┬──────────────┘
               │
               ▼
┌─────────────────────────────┐
│   Playwright Web Automation │  ← AI backend driver
└──────────────┬──────────────┘
               │
               ▼
┌─────────────────────────────┐
│     AI Image Generation     │  ← Output → gallery
└─────────────────────────────┘
```

---

## 🛠️ Technologies Used

| Layer | Technology |
|---|---|
| GUI | C++ · FLTK 1.4 |
| System | Win32 API · Multithreading · Process Management |
| Backend | Embedded Python · Playwright Automation |
| Build | Native Windows Integration · Custom setup system |

---

##  Engineering Highlights

- **Safe GUI threading model** — UI thread never blocked by generation work
- **Background worker execution** — Python subprocess managed from C++
- **Automated dependency installation** — first-run setup with `setup.flag` sentinel
- **Dynamic working directory handling** — runs correctly from any path
- **Native file explorer integration** — gallery opens via Win32 shell call
- **Self-configuring runtime** — embedded Python auto-configures on extraction

---

## 📂 Project Structure

```
VisionForge/
│
├── VisionForge.exe              # Main application binary
├── generate_image.py            # AI automation script
├── requirements.txt             # Python dependencies
├── setup.bat                    # First-run setup script
├── setup.flag                   # Setup completion sentinel
│
├── python/                      # Embedded Python runtime
│   └── ...
│
├── output_gallery/              # Generated images saved here
│   └── YYYY-MM-DD_HH-MM-SS.jpg
│
├── ImageGenApp.cpp / .h         # Main application logic
├── SidePanel.cpp / .h           # Professional settings panel
├── PythonRunner.cpp / .h        # Python process manager
└── main.cpp                     # Entry point
```

---

## Why This Project Exists

Most AI tools today live inside browsers.

VisionForge explores a different idea:

> *Can modern AI workflows feel like real desktop software again?*

This project bridges four engineering disciplines:

```
Systems Programming  +  Desktop Development  +  Automation Engineering  +  AI Tooling
```

---

## 🎯 Ideal For

- Students learning C++ and native application development
- Developers exploring hybrid C++ / Python architectures
- AI experimentation without cloud dependencies
- Offline-style workflows and privacy-focused use cases
- Portfolio demonstration of multi-layer engineering

---

## 🤝 Contributing

Ideas, feedback, and improvements are welcome. Open an issue or submit a pull request.

## ⭐ Support

If VisionForge is useful to you:

- **Star** the repository
- **Fork** it and build something even cooler
- **Share** it with someone learning C++ or AI

---


**Built by [Sachin Bhati](https://github.com/Sachin-bhati3824)**

*Computer Science Engineer — building systems, not just applications.*

---

*VisionForge · Native AI · C++ + Python · Windows Desktop*

</div>
