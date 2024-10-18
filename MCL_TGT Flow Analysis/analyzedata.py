import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

def plot_data_from_csv(file_path):
    # Set Seaborn style for nicer plots
    sns.set(style="whitegrid")
    
    # Read CSV file using pandas
    data = pd.read_csv(file_path, header=None, names=['Time', 'Flow'])
    
    # Convert time from 0.001 sec intervals to seconds
    data['Time'] = data['Time'] * 0.001

    # Plot the data
    plt.figure(figsize=(12, 8))
    plt.plot(data['Time'], data['Flow'], label='Flow Rate', color='b', linewidth=2)
    
    # Labeling the axes
    plt.xlabel('Time (seconds)', fontsize=14)
    plt.ylabel('Flow Rate (L/min)', fontsize=14)
    plt.title('Flow Rate vs Time', fontsize=16, fontweight='bold')
    plt.legend(fontsize=12)
    
    # Customizing ticks for better readability
    plt.xticks(fontsize=12)
    plt.yticks(fontsize=12)
    
    # Add grid with transparency
    plt.grid(True, linestyle='--', alpha=0.6)
    
    # Show the plot
    plt.tight_layout()
    plt.show()

#Example usage
plot_data_from_csv('MCL_TGT Flow Analysis/MCL Data to Use/reduced_bloodflow_MCL_AUG_9.csv')
