import pandas as pd
import numpy as np

def downsample_csv(input_file, output_file, downsample_factor=10):
    # Read the CSV file
    df = pd.read_csv(input_file)

    # Ensure we have two columns (Time and Flow)
    assert len(df.columns) == 2, "Input CSV should have exactly two columns: Time and Flow"

    # Rename columns for clarity
    df.columns = ['Time', 'Flow']

    # Downsample both Time and Flow columns simultaneously
    downsampled_data = df.iloc[::downsample_factor, :]

    # Reset the index
    downsampled_data = downsampled_data.reset_index(drop=True)

    # Save the downsampled data to a new CSV file
    downsampled_data.to_csv(output_file, index=False)

    print(f"Downsampled data saved to {output_file}")
    print(f"Original data shape: {df.shape}")
    print(f"Downsampled data shape: {downsampled_data.shape}")

# Example usage
input_file = "MCL_TGT Flow Analysis/TGT Data to Use/V5_Hr0_bloodflow.csv"
output_file = "downsampled_V5_Hr0_bloodflow.csv"
downsample_csv(input_file, output_file)
