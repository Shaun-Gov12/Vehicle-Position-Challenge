# Design Procedure

## Assumptions
My understanding of the question was that for each of the 10 locations/positions provided the 10 closest vehicles to those positions
had to be found. In total this is 100 vehicles.

The "benchmark approach" would have been to loop through all the data in the binary data file and compare each vehicle position 
with the 10 given positions.

## Solution
The approach taken in my solution was to find a central position, roughly in the middle of all 10 positions and find the closest 100 
vehicles to this central position. This method reduces the number of computations by comparing each vehicle's position to a single (central) position. Instead of comparing each vehicle's position to all 10 given positions.

The middle point was found by calculating the center betwen the minimum and maximum lattitudes of all 10 positions. The same was done for the longitude. This provided the position for the middle point in my solution. 

The C source code was written to follow the algorithm below:
* Read binary data file and extract the Position ID, Latitude and Longitude for a single vehicle
* Calculate how far away (the distance) the vehicle is from the mid-point
* Save the distances and position ID for the first 100 vehicles in 2 seperate arrays
* (After the first 100 vehicles are read from the data file) If the current distance is smaller than the largest distance from the 100 previous distances save the distance and position ID in arrays
* All 4 steps above were placed in a loop so that the process would be repeated for vehicles listed in the binary data file
	

## Possible Improvements
The solution described above could possibly produce results that are not as accurate at as the "benchmark approach". Speed has been gained at the cost of accuracy. The accuracy of the results could be improved by having 3 or 4 central points instead of just 1 central point. 
Consider a circle that contains inside it all 10 given positions. The circle could then be divided into 4 sections. Each section would then have it's own central point. The algorithm described in the solution (above) could be adapted to work for each individual section and find the closest 25 vehicles per section.

This method would reduce the inaccuracy of the results because the effect of each central point is limited to a quarter of the entire area. However this method does provide a different set of challenges:
* Finding the center point of each section is mathematically more intense. Accurate geometry is needed.
* The C code would need to have additional error checking algorithms for special conditions such as when the algorithm for section 2 selects a vehicle that has already been identified by the algorithm for section 1
