#include <math.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>

#define No_of_vehicles 100


// Struct to store data for a single vehicle
typedef struct
{
	uint32_t pos_ID;
	char veh_reg[15];
	float latitude;
	float longitude;
	uint64_t UTC;

}vehicle_data;


// Struct to keep a record of the closest vehicles
typedef struct
{
	uint32_t pos_ID[No_of_vehicles];
	float distance[No_of_vehicles];

	float max_distance;
	uint8_t max_dist_index;

}vehicle_tracker;


void findMaxDistance(vehicle_tracker* vehicles);



int main(void)
{
	// Timing variables
	clock_t t_start, t_end;
	float tot_time;

	t_start = clock();
	

	vehicle_data currentData;
	vehicle_tracker closest_vehicle;
	

	// Distances from mid-point
	float delta_lat, delta_lng, distance;


	// Mid-point co-ordinates
	float lat_mid = 33.545789;
	float lng_mid = -98.4465375;


	// Open data file
	FILE* fptr;
	fptr = fopen("positions.dat", "rb");

	for (uint32_t x = 0; x < 2e6; x++)
	{
		fread(&currentData, sizeof(vehicle_data), 1, fptr);

		// Calculate distance from mid-point
		delta_lat = lat_mid - currentData.latitude;
		delta_lng = lng_mid - currentData.longitude;
		distance = sqrt((delta_lat * delta_lat) + (delta_lng * delta_lng)); // Distance formula


		if (x < No_of_vehicles) // Populate arrays 
		{
			closest_vehicle.pos_ID[x] = currentData.pos_ID;
			closest_vehicle.distance[x] = distance;

			// Determine vehicle furtheset away first time after all indicies have been populated
			if (x == (No_of_vehicles - 1))
			{
				findMaxDistance(&closest_vehicle);
			}

		}
		else
		{

			if (distance < closest_vehicle.max_distance)
			{

				// Replace vehicle located furthest away with the most recently read vehicle from data file
				closest_vehicle.pos_ID[closest_vehicle.max_dist_index] = currentData.pos_ID;
				closest_vehicle.distance[closest_vehicle.max_dist_index] = distance;

				// Determine vehicle furtheset away when a new value is placed in 
				findMaxDistance(&closest_vehicle);

			} // End if


		} // End else



	} // End loop



	t_end = clock();
	tot_time = ( (float)(t_end - t_start) ) / CLOCKS_PER_SEC;

	printf("\n\nTotal execution time: %f seconds\n\n\n", tot_time);
	system("PAUSE");

	return 0;
} // End main()





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
		if (vehicles->distance[i] > vehicles->max_distance)
		{
			vehicles->max_distance = vehicles->distance[i];
			vehicles->max_dist_index = i;
		}

	} //End loop

}
