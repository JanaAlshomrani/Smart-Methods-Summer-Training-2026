import os
os.environ["KMP_DUPLICATE_LIB_OK"] = "TRUE"

import ssl
ssl._create_default_https_context = ssl._create_unverified_context

import time
import cohere
from RealtimeSTT import AudioToTextRecorder
from RealtimeTTS import TextToAudioStream, EdgeEngine

co = cohere.ClientV2(os.environ["COHERE_API_KEY"])

tts_engine = EdgeEngine()
tts_stream = TextToAudioStream(tts_engine)

EXIT_PHRASES = ["Goodbye!", "Bye.", "Okay, I'm good.", "that's all", "stop listening", "see you"]

should_exit = False


def get_reply_text(response):
    for item in response.message.content:
        if item.type == "text":
            return item.text
    return "Sorry, I couldn't come up with a response."


def speak(text):
    tts_stream.feed(text)
    tts_stream.play()
    while tts_stream.is_playing():
        time.sleep(0.1)


def process_text(text):
    global should_exit

    print(f"\nYou said: {text}")
    if not text.strip():
        return

    lowered = text.lower().strip()
    if any(phrase in lowered for phrase in EXIT_PHRASES):
        farewell = "Goodbye! Talk to you soon."
        print(f"Bot: {farewell}")
        speak(farewell)
        should_exit = True
        return

    try:
        response = co.chat(
            model="command-r-08-2024",
            messages=[
                {"role": "system", "content": "Keep every response to one short sentence, no more than 10 words. Stay calm and polite even if the user is rude or off-topic."},
                {"role": "user", "content": text}
            ],
        )
        reply = get_reply_text(response)
    except Exception as e:
        print(f"[Cohere error: {e}]")
        reply = "Sorry, I had a little trouble with that. Could you say it again?"

    print(f"Bot: {reply}")
    speak(reply)


def on_start():
    print(">>> Recording started (I hear something)")


def on_stop():
    print(">>> Recording stopped (processing...)")


if __name__ == '__main__':
    print("Initializing microphone... say something!")
    recorder = AudioToTextRecorder(
        language="en",
        device="cpu",
        compute_type="int8",
        on_recording_start=on_start,
        on_recording_stop=on_stop,
        spinner=True
    )
    while not should_exit:
        recorder.text(process_text)

    print("Conversation ended. Exiting program.")
    recorder.shutdown()