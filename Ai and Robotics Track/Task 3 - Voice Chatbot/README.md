# Voice Chatbot (Speech-to-Text → LLM → Text-to-Speech)

A real-time voice assistant that listens through the microphone, transcribes speech locally, sends the text to Cohere's Command model for a response, and speaks the reply back out loud — a complete audio-in, audio-out conversational loop.

## Pipeline

1. **Speech-to-text** — [RealtimeSTT](https://github.com/KoljaB/RealtimeSTT) captures microphone audio and transcribes it locally using a Whisper-based model (CPU mode, int8 quantization).
2. **Response generation** — [Cohere](https://docs.cohere.com/) `command-r-08-2024` generates a short, polite reply to the transcribed text.
3. **Text-to-speech** — [RealtimeTTS](https://github.com/KoljaB/RealtimeTTS) with the `EdgeEngine` streams the reply as natural-sounding speech through the speakers, using `mpv` for audio playback.

## Setup

```bash
conda create -n whisper_env python=3.10
conda activate whisper_env
pip install -r requirements.txt
```

Install `mpv` (required by RealtimeTTS's EdgeEngine for audio streaming) and make sure it's on your system PATH — download from [mpv.io](https://mpv.io/installation/) on Windows/Mac/Linux.

Set your Cohere API key as an environment variable:

```bash
setx COHERE_API_KEY "your-key-here"     # Windows
export COHERE_API_KEY="your-key-here"   # macOS/Linux
```

## Run

```bash
python voice_chatbot.py
```

Speak into the microphone. Say "goodbye," "bye," or "that's all" to end the conversation cleanly.

## Features

- Real-time microphone transcription (CPU-based, no GPU required)
- Short, conversational replies (bot is prompted to answer in under 10 words)
- Graceful handling of off-topic or rude input — the bot stays calm and redirects politely instead of breaking character
- Clean exit on spoken trigger phrases, instead of force-closing the terminal
- Error handling around the LLM call, so an API hiccup produces a spoken fallback line instead of crashing the whole program

## Issues faced during development

Building this pipeline surfaced a long chain of environment and dependency conflicts, mostly caused by mixing packages originally compiled for different Python versions inside the same conda environment.

- **OpenMP runtime conflict (`OMP: Error #15`)** — Multiple libraries (numpy, torch) each linked their own copy of the OpenMP runtime, causing a duplicate-initialization crash. Fixed by setting `os.environ["KMP_DUPLICATE_LIB_OK"] = "TRUE"` as the very first line of the script, before any other imports.
- **`pydantic_core` module not found** — A leftover compiled binary from an earlier Python 3.9 install conflicted with the Python 3.10 environment. Fixed by force-reinstalling `pydantic` and `pydantic-core`.
- **`pywin32` DLL load failure (`_win32sysloader`)** — `pyttsx3`'s Windows SAPI5 driver couldn't load because `pywin32` wasn't fully registered with Windows after a plain `pip install`. Fixed by running `pywin32_postinstall.py -install` manually.
- **`cublas64_12.dll` not found** — RealtimeSTT defaulted to GPU/CUDA transcription, but the required NVIDIA cuBLAS runtime wasn't installed. Fixed by forcing CPU-based transcription (`device="cpu"`, `compute_type="int8"`), which also proved plenty fast for real-time use.
- **`ffmpeg`/`ffprobe` missing (for the SAPI5-based `SystemEngine`)** — RealtimeTTS's default Windows TTS engine relies on `pydub`, which in turn needs `ffmpeg`/`ffprobe` to inspect audio files before playback. Installing ffmpeg via conda caused a separate DLL conflict with other GTK-related libraries already in the environment. Resolved by switching from `SystemEngine` to `EdgeEngine` entirely, removing the ffmpeg/pydub dependency from the audio-output path.
- **`mpv not found`** — `EdgeEngine` streams audio through `mpv` rather than pydub/ffmpeg. `mpv` wasn't installed and wasn't discoverable via `winget` due to a package-name ambiguity. Resolved by manually downloading the standalone Windows build and adding its folder to the system PATH.
- **Cohere model ID errors (`model not found`, 404)** — Used an incorrect/outdated model identifier. Fixed by confirming the exact valid model string from Cohere's documentation.
- **`AttributeError` on `response.message.content[0].text`** — Cohere's reasoning-capable models can return a "thinking" content block as the first item in the response instead of the text reply, breaking any code that assumes index `[0]` is always the text. Fixed by iterating through `response.message.content` and selecting the item where `type == "text"`.
- **`INVALID_TOOL_GENERATION` (422 error)** — The agentic `command-a-plus` model occasionally attempted an internal tool call even with no tools defined, producing a malformed request the API rejected. Resolved by switching to the non-agentic `command-r-08-2024` model, which doesn't exhibit this behavior, and wrapping the API call in a `try/except` so any future API error produces a spoken fallback instead of crashing.
- **Overlapping playback and recording (`play() called while already playing audio, skipping`)** — The microphone would start listening again before the previous spoken reply had finished, causing skipped audio and race conditions. Fixed by adding a blocking wait loop (`while tts_stream.is_playing(): time.sleep(0.1)`) after every `play()` call, so the program only starts listening again once speech playback has fully finished.

Most of these issues stemmed from the same root cause: mixing packages that were originally compiled or cached against a different Python version (3.9) inside a fresh Python 3.10 conda environment. Once each stale/incompatible binary was identified and reinstalled cleanly, the pipeline stabilized.

## Demo

See the attached demo video for a full walkthrough of the conversation flow, including normal Q&A, an off-topic question, a rude-input recovery test, and a clean spoken exit.
