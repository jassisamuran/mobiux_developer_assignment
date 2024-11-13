# Mobiux_developer_assignment
A C++ program for analyzing ice cream parlour sales data, including monthly sales totals, popular items, revenue generation, and order statistics.

## Table of Contents
1. [Installation](#installation)
2. [Features](#features)
3. [Code Overview](#code-overview)
4. [Dependencies](#dependencies)
5. [Example Output](#example-output)

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/your-project.git
2. Navigate to the project directory:
   ````bash
   cd your-project
3. Compile the code (if applicable):
   ````bash
   g++ one.cpp -o sales_analysis
4. Run the program
   ````bash
   ./sales_analysis

## Features
1. **Total Sales Calculation**: Outputs the total revenue generated across all data.
2. **Monthly Sales Totals**: Shows total sales per month.
3. **Most Popular Items**: Finds the most frequently sold item for each month.
4. **Top Revenue-Generating Items**: Identifies the item with the highest revenue each month.
5. **Order Statistics**: Provides minimum, maximum, and average order quantities for the most popular items each month.

## Code Overview
- **`parseData`**: Reads data from a CSV file and parses it into `SaleRecord` objects.
- **`calculatesSales`**:
  - Calculates total and monthly sales.
  - Tracks the most popular items by quantity and revenue.
  - Computes order statistics (min, max, and average) for popular items.

## Dependencies
This program uses the following C++ libraries:

- `<iostream>`: For standard input and output.
- `<fstream>`: For file reading.
- `<sstream>`: To parse CSV data.
- `<vector>`: To store sales data records.
- `<map>`: To track monthly sales, popular items, and revenue.
- `<iomanip>`: For setting the precision of floating-point output.
- `<limits>`: To set min/max limits for order statistics.

## Example Output

   ````bash
   Total Sales of Store: 5000.00
   Month-wise Sales Total:
   2024-10: 1500.50
   2024-11: 3500.20
   Most Popular Items for Each Month:
   2024-10: Item: SKU123 Quantity Sold: 50
   2024-11: Item: SKU456 Quantity Sold: 70
   Items Generating Most Revenue Each Month:
   2024-10: Item: SKU123 Revenue: 125.50
   2024-11: Item: SKU456 Revenue: 210.70
   Order Statistics for Most Popular Item Each Month:
   2024-10 SKU123, Min Orders: 5, Max Orders: 20, Average Orders: 12.33


