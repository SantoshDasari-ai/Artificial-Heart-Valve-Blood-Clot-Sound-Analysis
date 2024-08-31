import librosa
import numpy as np
import matplotlib.pyplot as plt
from scipy import signal
import soundfile as sf

# 1. Load an audio file
file_path = 'your_audio_file.wav'
y, sr = librosa.load(file_path, sr=None)

# 2. Analyze Pitch
pitches, magnitudes = librosa.core.piptrack(y=y, sr=sr)
pitch_values = np.max(pitches, axis=0)  # Get the highest pitch per time frame

# 3. Track Volume (RMS Amplitude)
rms = librosa.feature.rms(y=y)

# 4. Clean Up Unwanted Frequencies (High-pass filter at 1000 Hz)
sos = signal.butter(10, 1000, 'hp', fs=sr, output='sos')
filtered_y = signal.sosfilt(sos, y)

# 5. Save the Processed Audio
output_file = 'filtered_audio.wav'
sf.write(output_file, filtered_y, sr)

# 6. Plotting Results
# Plot Pitch Over Time
plt.figure(figsize=(10, 6))
plt.plot(pitch_values, label='Pitch')
plt.title('Pitch Over Time')
plt.xlabel('Frames')
plt.ylabel('Pitch (Hz)')
plt.show()

# Plot RMS Amplitude (Volume) Over Time
plt.figure(figsize=(10, 6))
plt.plot(rms[0], label='RMS Amplitude', color='orange')
plt.title('Volume (RMS) Over Time')
plt.xlabel('Frames')
plt.ylabel('RMS Amplitude')
plt.show()

print(f"Processed audio saved as {output_file}")
