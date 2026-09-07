#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <float.h>
#include <math.h>

#define WIDTH 50
#define HEIGHT 50
#define PPM_SCALAR 25 
#define SAMPLE_SIZE 2000
#define BIAS 10.0
#define TRAIN_PASSES 2000

typedef float Layer[HEIGHT][WIDTH];

static Layer inputs;
static Layer weights;

static inline int clampi(int x, int low, int high);
float FF(Layer inputs, Layer weights);
void AIW(Layer inputs, Layer weights);
void SIW(Layer inputs, Layer weights);
void LFR(Layer layer, int x, int y, int w, int h, float value);
void LFC(Layer layer, int cx, int cy, int r, float value);
void PPM(Layer layer, const char *path);
void SBIN(Layer layer, const char *path);
// void LBIN(Layer layer, const char *path);
void RDM_RECT(Layer layer);
void RDM_CIRC(Layer layer);
int RDM_RANGE(int low, int high);
int TPS(Layer inputs, Layer weights);
int CPS(Layer inputs, Layer weights);

int main(void)
{
	char path[256];
	int i = 0;
	int adj = 0;
	int failed = 0;
	
	srand(20);
	failed = CPS(inputs, weights);
	printf(
			"The fail rate of untrained model is %f\n", 
			failed / (SAMPLE_SIZE * 2.0)
		  );

	for(i = 0; i < TRAIN_PASSES; ++i){
		srand(69);
		adj = TPS(inputs, weights);
		snprintf(path, sizeof(path), "Weight-%02d.ppm", i);
		printf("%s: adjusted %d times\n", path, adj);
		PPM(weights, path);
		if(adj <= 0) break;
	}

	srand(420);
	failed = CPS(inputs, weights);
	printf(
			"The fail rate of trained model is %f\n", 
			failed / (SAMPLE_SIZE * 2.0)
		  );

	return 0;
}

// Feed Forward Function
float FF(Layer inputs, Layer weights)
{
	float output = 0.0f;
	for(int y = 0; y < HEIGHT; ++y){
		for(int x = 0; x < WIDTH; ++x){
			output += inputs[y][x] * weights[y][x];
		}
	}
	return output;
}

// Add Inputs to Weights 
void AIW(Layer inputs, Layer weights)
{
	for(int y = 0; y < HEIGHT; ++y){
		for(int x = 0; x < WIDTH; ++x){
			weights[y][x] += inputs[y][x];
		}
	}
}

// Subtract Inputs from Weights
void SIW(Layer inputs, Layer weights)
{
	for(int y = 0; y < HEIGHT; ++y){
		for(int x = 0; x < WIDTH; ++x){
			weights[y][x] -= inputs[y][x];
		}
	}
}

// Train Pass
int TPS(Layer inputs, Layer weights)
{
	int adjusted = 0;

	for (int i = 0; i < SAMPLE_SIZE; ++i){
		RDM_RECT(inputs);
		if(FF(inputs, weights) > BIAS){
			SIW(inputs, weights);
			adjusted += 1;
		}

		RDM_CIRC(inputs);
		if(FF(inputs, weights) < BIAS){
			AIW(inputs, weights);
			adjusted += 1;
		}
	}

	return adjusted;
}

// Check Pass
int CPS(Layer inputs, Layer weights)
{
	int adjusted = 0;

	for (int i = 0; i < SAMPLE_SIZE; ++i){
		RDM_RECT(inputs);
		if(FF(inputs, weights) > BIAS){
			adjusted += 1;
		}

		RDM_CIRC(inputs);
		if(FF(inputs, weights) < BIAS){
			adjusted += 1;
		}
	}

	return adjusted;
}



// Min and Max Limited
static inline int clampi(int x, int low, int high)
{
	if(x < low) x = low;
	if(x > high) x = high;
	return x;
}

// Layer Fill Rectangle
void LFR(Layer layer, int x, int y, int w, int h, float value)
{
	assert(w > 0);
	assert(h > 0);
	int x0 = clampi(x, 0, WIDTH-1);
	int y0 = clampi(y, 0, HEIGHT-1);
	int x1 = clampi(x0+w-1, 0, WIDTH-1);
	int y1 = clampi(y0+h-1, 0, WIDTH-1);
	for(int y = y0; y <= y1; ++y){
		for(int x = x0; x <= x1; ++x){
			layer[y][x] = value;
		}
	}
}

// Layer Fill Circle
void LFC(Layer layer, int cx, int cy, int r, float value)
{
	assert(r > 0);
	int x0 = clampi(cx-r, 0, WIDTH-1);
	int y0 = clampi(cy-r, 0, HEIGHT-1);
	int x1 = clampi(cx+r, 0, WIDTH-1);
	int y1 = clampi(cy+r, 0, WIDTH-1);
	for(int y = y0; y <= y1; ++y){
		for(int x = x0; x <= x1; ++x){
			int dx = x - cx;
			int dy = y - cy;
			if(dx*dx + dy*dy <= r*r){ 
				layer[y][x] = value;
			}
		}
	}
}

// Layer Saved as PPM
void PPM(Layer layer, const char *path)
{
	float min = FLT_MIN;
	float max = FLT_MAX;
	for(int y = 0; y < HEIGHT-1; ++y){
		for(int x = 0; x < WIDTH-1; ++x){
			if(layer[y][x] < min) min = layer[y][x];
			if(layer[y][x] > max) max = layer[y][x];
		}
	}

	FILE *f = fopen(path, "wb");
	if(f == NULL){
		fprintf(
				stderr, 
				"ERROR: could not open file %s: %m\n",
				path
				);
		exit(1);
	}
	fprintf(
			f, 
			"P6\n%d %d 255\n", 
			WIDTH*PPM_SCALAR, 
			HEIGHT*PPM_SCALAR
			);
	for(int y = 0; y < HEIGHT * PPM_SCALAR; ++y){
		for(int x = 0; x < WIDTH * PPM_SCALAR; ++x){
			float s = (
					layer[y / PPM_SCALAR][x / PPM_SCALAR]
					) / (
						max - min
					);
			char pixel[3] = {
				(char) floorf(255 * (1.0f - s)), 
				(char) floorf(255 * s), 
				0
			};
			fwrite(pixel, sizeof(pixel), 1, f);
		}
	}
	fclose(f);
}

// Layer Save As BIN
void SBIN(Layer layer, const char *path)
{
	FILE *f = fopen(path, "wb");
	if(f == NULL){
		fprintf(
				stderr, 
				"ERROR: could not open file %s: %m", 
				path
				);
		exit(1);
	}
	fwrite(layer, sizeof(Layer), 1, f);
	fclose(f);
}

// Layer Load From BIN
// void LBIN(Layer layer, const char *path)
// {
//	assert(0 && "Todo : LBIN is not implemented yet!");
// }

// Random Range
int RDM_RANGE(int low, int high)
{
	assert(low < high);
	return rand() % (high - low) + low;
}

// Layer Random Rectangle
void RDM_RECT(Layer layer)
{
	LFR(layer, 0, 0, WIDTH, HEIGHT, 0.0f);
	int x = RDM_RANGE(0, WIDTH);
	int y = RDM_RANGE(0, HEIGHT);

	int w = WIDTH - x;
	if(w < 2) w = 2;
	w = RDM_RANGE(1, w);

	int h = HEIGHT - y;
	if(h < 2) h = 2;
	h = RDM_RANGE(1, h);

	LFR(layer, x, y, w, h, 1.0f);
}

// Layer Random Circle
void RDM_CIRC(Layer layer)
{
	LFR(layer, 0, 0, WIDTH, HEIGHT, 0.0f);
	int cx = RDM_RANGE(0, WIDTH);
	int cy = RDM_RANGE(0, HEIGHT);
	int r = INT_MAX;
	if(r > cx) r = cx;
	if(r > cy) r = cy;
	if(r > WIDTH - cx) r = WIDTH - cx;
	if(r > HEIGHT - cy) r = HEIGHT - cy;
	if(r < 2) r = 2;
	r = RDM_RANGE(1, r);
	LFC(layer, cx, cy, r, 1.0f);
}

