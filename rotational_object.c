#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define WIDTH  25
#define HEIGHT 25
#define K2 5
#define K1 WIDTH*K2*3/(25)

#define BUF_SIZE 100
#define SPACE_SIZE 20
#define VOLUME_SIZE SPACE_SIZE / 2

// Construct space data type.
typedef struct space_s
{
	float theta;  // The angle rotate about x-axis.
	float phi;    // The angle rotate about z-axis.
	float ip;     // i'(i prime) is standing for projection of i after ratation.
	float jp;     // j'(j prime) is standing for projection of j after ratation.
	float kp;     // k'(k prime) is standing for projection of k after ratation.
	float inv_kp; // The inverse of k' .
	// Each vector for the object.
	char  object[SPACE_SIZE][SPACE_SIZE][SPACE_SIZE];
} space_t;

// Construct screen data type.
typedef struct screen_s
{
	int   xp;     // x'(x prime) is standing for screen's x-axis after projection on the screen.
	int   yp;     // y'(y prime) is standing for screen's y-axis after projection on the screen.
    float lumin;  // derivated from dot product.
	float depth[BUF_SIZE][BUF_SIZE];
    char  output[BUF_SIZE][BUF_SIZE];
} screen_t;

static float    sin_theta, cos_theta, sin_phi, cos_phi;
static space_t  space;
static screen_t screen;

inline static void initial_object(void);
inline static void reset_buffer(void);
inline static void for_each_vector(void);
inline static bool probe_screen(int, int, int);
inline static void render_frame(int, int, int, float, float, float, float);
inline static void output_screen(void);
inline static void bias_angle(float, float);

void main()
{
	initial_object();
    while(1)
    {
    	reset_buffer();
        for_each_vector();
		bias_angle(0.05, 0.05);
        output_screen();
    }
}

inline static void initial_object(void)
{
	int i, j, k;
	
	memset(space.object, ' ', SPACE_SIZE * SPACE_SIZE * SPACE_SIZE);
    for(i = 0; i < VOLUME_SIZE; ++i)
    {
    	for(j = 0; j < VOLUME_SIZE; ++j)
    	{
    		for(k = 0; k < VOLUME_SIZE; ++k)
    		{
    			space.object[3+i][3+j][3+k] = '=';
			}
		}
	}
    printf("\x1b[2J");
}

inline static void reset_buffer(void)
{
	memset(screen.output, ' ', BUF_SIZE * BUF_SIZE);
    memset(screen.depth,  0.0, BUF_SIZE * BUF_SIZE * sizeof(float));
    
    // Compute the trigonometric functions for each rotated angle.
    sin_theta = sin(space.theta); 
    cos_theta = cos(space.theta); 
    sin_phi   = sin(space.phi);
    cos_phi   = cos(space.phi);
}

void for_each_vector(void)
{
	int i, j, k;
	for(i = 0; i < VOLUME_SIZE; ++i)
    {
    	for(j = 0; j < VOLUME_SIZE; ++j)
    	{
    		for(k = 0; k < VOLUME_SIZE; ++k)
    		{
    			render_frame(i, j, k, sin_theta, cos_theta, sin_phi, cos_phi);
			}
		}
	}
}

void render_frame(int i, int j, int k,
                  float sin_theta, float cos_theta, float sin_phi, float cos_phi)
{
	// Rotate about x-axis and z-axis.
	space.ip = -j*sin_phi*cos_theta + k*sin_phi*sin_theta + i*cos_phi;
	space.jp =  j*cos_phi*cos_theta - k*cos_phi*sin_theta + i*sin_phi;
	space.kp =  j*sin_theta + k*cos_theta + K2;
	space.inv_kp = 1.0 / space.kp;
	
	// Compute the luminance for each vector of the object.
	screen.lumin = 15 + 
	               ( j*cos_phi*cos_theta - 
	                 k*cos_phi*sin_theta + 
	                 i*sin_phi - 
	                (j*sin_theta + k*cos_theta + K2));
	
	// Project on screen.
	screen.xp = (int)(K1*space.ip*space.inv_kp);
	screen.yp = (int)(K1*space.jp*space.inv_kp);
	
	// Write to the output buffer.
	if (probe_screen(i, j, k) && 
	    space.inv_kp > screen.depth[screen.xp][screen.yp])
	{
		screen.depth [screen.xp][screen.yp] = space.inv_kp;
		screen.output[screen.xp][screen.yp] = "..,-~:;=!**##$$@@"[(int) screen.lumin]; 
	}
}

bool probe_screen(int i, int j, int k)
{
	return screen.xp > 0        && 
	       screen.xp < BUF_SIZE && 
	       screen.yp > 0        && 
	       screen.yp < BUF_SIZE && 
		   space.object[i][j][k] == '=';
}

void output_screen(void)
{
	int i, j;
	
	printf("\x1b[H");
    for (j = 0; j < HEIGHT; ++j)
    {
        for (i = 0; i < WIDTH; ++i)
        {
            putchar(screen.output[i][j]);
        }
        putchar('\n');
    }
}

void bias_angle(float theta_bias, float phi_bias)
{
	space.theta += theta_bias;
    space.phi   += phi_bias;
}
