import librosa
import numpy as np
from scipy.signal import butter, lfilter
import soundfile as sf

def butter_bandpass(lowcut, highcut, fs, order=5):
    nyq = 0.5 * fs
    low = lowcut / nyq
    high = highcut / nyq
    b, a = butter(order, [low, high], btype='band')
    return b, a

def butter_bandpass_filter(data, lowcut, highcut, fs, order=5):
    b, a = butter_bandpass(lowcut, highcut, fs, order=order)
    y = lfilter(b, a, data)
    return y

def detect_clicks(audio_path, lowcut, highcut):
    # Load audio file
    y, sr = librosa.load(audio_path)

    # Apply bandpass filter to isolate clicks
    filtered_y = butter_bandpass_filter(y, lowcut, highcut, sr)

    # Thresholding to detect clicks
    threshold = 0.5 * np.max(np.abs(filtered_y))
    clicks = np.where(np.abs(filtered_y) > threshold, filtered_y, 0)

    # Save isolated clicks to a new file
    sf.write('clicks_isolated.wav', clicks, sr)

# Example usage
audio_path = 'audio_files/unprocessed_audio/MarioHeart1.wav'
lowcut = 500  # Lower frequency bound for click detection
highcut = 1000  # Upper frequency bound for click detection
detect_clicks(audio_path, lowcut, highcut)
