#pragma warning(push, 0)
#include <stdint.h>
#include <stdlib.h>


#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#pragma(pop)

#pragma warning(disable :5045)
#pragma warning(disable :4711)


typedef struct
{
  uint32_t x;
  uint32_t y;
} start_coord_t;

static int loops_counter = 0; // to check if it is the 1st loop of the execution
uint8_t *buffer; // the final returned buffer from simulate_life()



/*
uint8_t *simulate_life(uint32_t grid_dim, start_coord_t *initial_points, uint32_t initial_point_count)
{

  int big_grid_size = grid_dim * grid_dim * 2;
  int cordi = 0; // to convert the 2D coordinates to 1D array coordinates
  uint8_t *grid = calloc(big_grid_size , sizeof(uint8_t)); // to store the old grid and the updated one in one array
                                                          // because we are allowed to use one allocation

  if (loops_counter == 0) // taking the initial points only in the 1st loop of the application life time
  {
    for  (int i = 0; i < initial_point_count; i++)
    {
      // convert the 2D coordinates to 1D and store the initial points in the 2nd half of the 1D array:
      cordi = (initial_points[i].x + initial_points[i].y) + (initial_points[i].x * (grid_dim - 1)) + grid_dim;
      grid[cordi] = 1;
    }
  }
  // The logic:
  // copy the data from the 2nd half of the array to the 1st half
  // use the 1st have as input
  // update the 2nd half of the array according to the 1st one by Conway roles
  // returning a pointer to the 2nd half only which has the updated data 

  loops_counter++;
  return grid;
}
*/
// int count_neighbours(uint8_t map[2048][2048], uint32_t grid_dim, int x, int y)
// {
//   int counter = 0;
//   for (int dx = -1; dx <= 1; dx++)
//   {
//     for (int dy = -1; dy <= 1; dy++)
//     {
//       if (dx == 0 && dy == 0)
//         continue;
//       int nx = x + dx;
//       int ny = y + dy;
//       if ((nx >= 0 && nx < grid_dim) || (ny >= 0 && ny < grid_dim))
//       {
//         if(map[nx][ny] == 0)
//           counter++;
//       }
//     }
//   }
//   return counter;
// }

// uint8_t *get_next_generation(uint8_t map[2048][2048], uint32_t grid_dim, uint8_t *buffer)
// {
//   int counter = 0;
//   int cordi = 0; // to convert the 2D coordinates into 1D buffer index

//   for (int i = 0; i < grid_dim; i++)
//   {
//     for (int j = 0; j < grid_dim; j++)
//     {
//       cordi = (i + j) + (i * (grid_dim - 1)) + grid_dim;
//       counter = count_neighbours(map, grid_dim, i, j );
//       if (map[i][j] == 0) // alive cell
//       {
//         if (counter == 3)
//           buffer[cordi] = 1;
//         else
//           buffer[cordi] = 0;
//       }
//       else // dead
//       {
//         if (counter == 2 || counter == 3)
//           buffer[cordi] = 1;
//         else
//           buffer[cordi] = 0;
//       }

//     }
//   }
//   return buffer;
// }


int count_neighbours(uint8_t map[4096], uint32_t grid_dim, int x)
{
  int counter = 0;
  // for (int dx = -1; dx <= 1; dx++)
  // {
  //     if (dx == 0)
  //       continue;
  //     int nx = x + dx;
  //       if(map[nx] == 0)
  //         counter++;
  // }
  if (map[x - 17] == 1)
    counter++;
  if (map[x - 16] == 1)
    counter++;
  if (map[x - 15] == 1)
    counter++;
  if (map[x - 1] == 1)
    counter++;
  if (map[x + 17] == 1)
    counter++;
  if (map[x + 16] == 1)
    counter++;
  if (map[x + 15] == 1)
    counter++;
  if (map[x + 1] == 1)
    counter++;
   return counter;
}

uint8_t *get_next_generation(uint8_t map[4096], uint32_t grid_dim, uint8_t *buffer)
{
  int counter = 0;

  for (int i = 0; i < grid_dim * grid_dim; i++)
  {
      counter = count_neighbours(map, grid_dim, i);
      if (map[i] == 0) // alive cell
      {
        if (counter == 3)
          buffer[i] = 1;
        else
          buffer[i] = 0;
      }
      else // dead
      {
        if (counter == 2 || counter == 3)
          buffer[i] = 1;
        else
          buffer[i] = 0;
      }
  }
  return buffer;
}

uint8_t *simulate_life(uint32_t grid_dim, start_coord_t *initial_points, uint32_t initial_point_count)
{

  static uint8_t map[4096];
  int buffer_size = grid_dim * grid_dim;
  int x = 0;
  int y = 0;

  // ####### setting the old data which will be proccessed later: #######

  if (loops_counter == 0) // the 1st loop
  {
    // allocation for the 1st time only
    buffer  = calloc(buffer_size , sizeof(uint8_t));
    // reset the whole map:
    for (int i = 0 ; i < 256 ; i++)
    {
      map[i] = 0;
    }
    // taking the initial points into the map
    for (int k = 0 ; k < initial_point_count ; k++)
    {
      map[initial_points[k].y * grid_dim + initial_points[k].x] = 1;
    }
  }
  else
  {
    // iterating through the buffer and backing up the data into map
    for (int i = 0; i < buffer_size; i++)
    {
      map[i] = buffer[i];
      // if ( i % 2 == 0)
      //    map[i] = 1;
      // else
      //    map[i] = 0;
    }
  }

  buffer = get_next_generation(map, grid_dim, buffer);

  loops_counter++;
  return buffer;
  // return map;

}

  // char *error ="my error";
  // OutputDebugStringA(error);