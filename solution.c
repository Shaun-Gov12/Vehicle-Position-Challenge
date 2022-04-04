#include <math.h>
#include <stdint.h>

#define No_of_vehicles 100

typedef struct
{
	uint32_t pos_ID[No_of_vehicles];
	float distance[No_of_vehicles];

	float max_distance;
	uint8_t max_dist_index;

}vehicle_tracker;


void extraxtDataFile(uint8_t x, uint32_t* ID, float* lat, float* lng);
void findMaxDistance(vehicle_tracker* vehicles);


int main(void)
{
	vehicle_tracker closest_vehicle;

	// ID and location for vehicle
	uint32_t ID;
	float lat, lng;

	// Distances from mid-point
	float delta_lat, delta_lng, distance; 
	
	

	// Mid-point co-ordinates
	float lat_mid = 33.545789;
	float lng_mid = -98.4465375;

	// Loop through data file
	for (uint32_t x = 0; x < 2e6; ++x)
	{
		extraxtDataFile(x, &ID, &lat, &lng);

		// Calculate distance from mid-point
		delta_lat = lat_mid - lat;
		delta_lng = lng_mid - lng;
		distance = sqrt( (delta_lat * delta_lat) + (delta_lng * delta_lng) ); // Distance formula


		if (x < No_of_vehicles) // Populate arrays 
		{
			closest_vehicle.pos_ID[x] = ID;
			closest_vehicle.distance[x] = distance;

			// Determine vehicle furtheset away first time after all indicies have been populated
			if (x == (No_of_vehicles - 1) )
			{
				findMaxDistance(&closest_vehicle);
			}
			 
		}
		else
		{
			
			if (distance < closest_vehicle.max_distance)
			{
				
				// Replace vehicle located furthest away with the most recently read vehicle from data file
				closest_vehicle.pos_ID[closest_vehicle.max_dist_index] = ID;
				closest_vehicle.distance[closest_vehicle.max_dist_index] = distance;

				// Determine vehicle furtheset away after a new value is placed in 
				findMaxDistance(&closest_vehicle);

			} // End if


		} // End else

		

	} // End loop


	return 0;
} // End main()





/* This functions reads the contents of the data file and extracts:
		--> Position ID
		--> Latitude
		--> Longitude
*/
void extraxtDataFile(uint8_t x, uint32_t* ID, float* lat, float* lng)
{
	// Read data file data for vehicle 'x'

	// Extract ID and store the value in variable ID

	// Extract latitude and store the value in variable lat

	// Extract longitude and store the value in variable lng
}






/* This function determines the maximum distance of all the distances in vehicle->distance[]
   Maximum distance is saved/stored in vehicle->max_distance
   Index of maximum distance is saved/stored in vehicle->max_dist_index
*/
void findMaxDistance(vehicle_tracker* vehicles)
{
	vehicles->max_distance = vehicles->distance[0];
	vehicles->max_dist_index = 0;
	
	for (uint8_t i = 1; i < No_of_vehicles; i++)
	{
		if ( vehicles->distance[i] > vehicles->max_distance )
		{
			vehicles->max_distance = vehicles->distance[i];
			vehicles->max_dist_index = i;
		}
	} //End loop

}
