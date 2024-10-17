import pandas as pd
import matplotlib.pyplot as plt

def plot_data_from_csv(file_path):
    # Read CSV file using pandas
    data = pd.read_csv(file_path, header=None, names=['Time', 'Flow'])
    
    # Convert time from 0.001 sec intervals to seconds
    data['Time'] = data['Time'] * 0.001

    # Plot the data
    plt.figure(figsize=(10, 6))
    plt.plot(data['Time'], data['Flow'], label='Flow Rate', color='b')
    
    # Labeling the axes
    plt.xlabel('Time (seconds)')
    plt.ylabel('Flow Rate (L/min)')
    plt.title('Flow Rate vs Time')
    plt.legend()
    plt.grid(True)
    
    # Show the plot
    plt.show()

#Example usage
plot_data_from_csv('path/to/your/data.csv')
