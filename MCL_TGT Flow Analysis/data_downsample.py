import pandas as pd

def downsample_csv(input_file, output_file, step):
    """
    Downsample a CSV file by keeping every 'step'th row, skipping the first row.

    Parameters:
    input_file (str): Path to the input CSV file.
    output_file (str): Path to save the downsampled CSV file.
    step (int): The step size for downsampling (e.g., 10 to keep every 10th row).
    """
    # Load the data, skipping the first row
    data = pd.read_csv(input_file, skiprows=[0])

    # Downsample by selecting every 'step'th row
    reduced_data = data.iloc[::step].reset_index(drop=True)

    # Save the reduced data to a new CSV file
    reduced_data.to_csv(output_file, index=False)
    print(f"Downsampled data saved to: {output_file}")

# Example usage
input_file = "MCL_TGT Flow Analysis/TGT Data to Use/V5_Hr0_bloodflow.csv"  # Replace with your input file path
output_file = "reduced_V5_Hr0_bloodflow.csv"  # Replace with desired output file path
step = 10  # Change step size to control downsampling

downsample_csv(input_file, output_file, step)
