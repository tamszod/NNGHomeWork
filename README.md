# Detecting Duplicate House Numbers

The application identifies and lists house numbers that appear more than once in a street network datase. The house numbers are given to the program in segments. Each segment can be odd, even, or mixed within the specified range.

## Usage

The application accepts files as a command-line argument, placed in the same directory as the program under the name network.csv, or if none of the above is given, the file path can be typed on the standard input.

## Usage Example

	NNGHomeWork.exe network.csv

## Input file format
The input file must have 27 columns for the program to read it successfully. Column 17 should contain the street name (maximum 50 characters). 
Column 18 should contain the street type (maximum 20 characters). Column 21 should contain the left scheme and column 25 the right scheme. Each scheme can be
"E" for even numbers, "O" for odd numbers, "M" for mixed numbers. The two columns to the right of each scheme column should specify the range for that scheme.

	513739,391041,391039,"6",3,"","",46,"F","NNNNNNN",50,0,30,0,0,0,"Baross","utca","","","O",89,89,"",0,0,"Budaörs","Budaörs","","",244,244,"2040","2040"

## Output

Alsóhatár utca: E 14 26 <br/>
Baross utca: M 61 72 <br/>
Bazsarózsa utca: O 17 29 <br/>
Beregszászi utca: O 29 33 <br/>
Boglárka utca: O 3 33 <br/>
Bokréta utca: M 1 8 <br/>
Bokréta utca: M 10 10 <br/>

## Error Codes

	FilePathError (1): File path was not given.
	FileOpenError (2): File could not be open.
	UnimplementedError (3): Feature is not implemented
