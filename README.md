# Snitch
Snitch is a mesh tally clustering program built on top of libMesh. Currently I am using and developing this as a test bed framework for my research

## Running Snitch
To execute Snitch, use the following command format (assuming the executable for the test case is called snitch):

```
./snitch nx ny lower_left_x upper_left_x lower_left_y upper_left_y
```

### Command-Line Arguments
- **nx** : Number of elements in the x-direction
- **ny** : Number of elements in the y-direction
- **lower_left_x** : Leftmost coordinate in the x-axis
- **upper_left_x** : Rightmost coordinate in the x-axis
- **lower_left_y** : Bottom-most coordinate in the y-axis
- **upper_left_y** : Top-most coordinate in the y-axis

## Example Usage
To create a mesh with 10x10 elements in a region spanning from (0,0) to (1,1), execute:
```
./snitch 10 10 0.0 1.0 0.0 1.0
```
