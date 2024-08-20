#include <cmoc.h>
#include <coco.h>

#define NUM_FORECASTS 3

// Create structures
struct _fCastDay
{
    char DOW[10];
    byte iconCode;
    byte tempH;
    byte tempL;
    byte rchance;
};

// Declare global variables
int TEMPERATURE = 72; // Starting temperature

struct _fCastDay fCastWeek[NUM_FORECASTS];

// Icon data arrays
byte ICONS[5][70] = {
	{
	// SUN
	192,153,192,153,192,192,145,152,145,150,
	192,192,153,192,153,145,152,150,152,150,
	192,153,146,247,255,255,255,251,156,192,
	192,192,148,255,255,255,255,255,156,156,
	192,145,150,245,255,255,255,250,153,146,
	192,152,192,158,150,148,146,148,146,148,
	192,152,145,152,145,192,148,146,148,146
	},
	{
	//RAIN
	192,192,198,203,199,207,199,199,201,192,
	192,198,199,205,198,201,204,207,203,201,
	192,201,207,206,207,207,206,207,207,198,
	192,192,201,207,207,207,207,207,198,192,
	192,192,192,204,192,162,200,204,192,192,
	192,192,192,164,161,192,168,161,192,192,
	192,192,192,164,192,192,168,192,192,192
	},
	{
	//CLOUD
	192,192,198,203,199,207,199,199,201,192,
	192,198,199,205,198,201,204,207,203,201,
	192,201,207,206,207,207,206,207,207,198,
	192,192,201,207,207,207,207,207,198,192,
	192,192,192,204,196,192,200,204,192,192,
	192,192,192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,192,192
	},
	{
	//STORM
	192,192,198,203,199,207,199,199,201,192,
	192,198,199,205,198,201,204,207,203,201,
	192,201,207,206,207,207,206,207,207,198,
	192,192,201,207,207,207,209,207,198,192,
	192,192,162,204,192,209,216,204,161,192,
	192,192,162,168,211,216,161,164,161,192,
	192,161,192,214,192,162,161,164,161,192
	},
	{
	//SNOW
	192,199,207,207,207,207,207,207,207,203,
	192,192,193,192,193,192,193,192,193,192,
	192,194,192,193,192,194,192,193,192,193,
	192,192,193,192,193,192,193,192,193,192,
	192,193,192,194,192,193,192,193,192,193,
	192,192,193,192,193,192,193,192,194,192,
	192,192,192,192,192,192,192,192,192,192
	}
};

// Function prototypes
void initialize();
void get_forecast();
void get_temperature_now();
void update_display();
void putIcon(byte day,int icon);
int rnd(int max);
void printCharAt(byte x, byte y, byte asciiCode);

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//              Main Routine
int main() {
  
  initialize();
  while (1) {
	get_forecast();
	get_temperature_now();
	update_display();
	putIcon(1, fCastWeek[0].iconCode);
	putIcon(2, fCastWeek[1].iconCode);
	putIcon(3, fCastWeek[2].iconCode);
  sleep(20);
  }

  return 0;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//              Support Functions
void initialize() {
  initCoCoSupport();
  // Blank the screen map
	cls(0);
	locate(10,7);
	printf("INITIALIZING...");
	//sleep(2);    
}

void get_forecast() {
  // Random forcast for now. Need to link to FujiNet
	strncpy(fCastWeek[0].DOW, "monday", 9);
	strncpy(fCastWeek[1].DOW, "tuesday", 9);
	strncpy(fCastWeek[2].DOW, "wednesday", 9);

	fCastWeek[0].iconCode = convertIconCode((byte) rnd(5));
	fCastWeek[1].iconCode = convertIconCode((byte) rnd(5));
	fCastWeek[2].iconCode = convertIconCode((byte) rnd(5));

	fCastWeek[0].tempH = 72 + rnd(26);
	fCastWeek[1].tempH = 72 + rnd(26);
	fCastWeek[2].tempH = 72 + rnd(26);

	fCastWeek[0].tempL = 60 + rnd(24);
	fCastWeek[1].tempL = 60 + rnd(24);
	fCastWeek[2].tempL = 60 + rnd(24);

	fCastWeek[0].rchance = rnd(10) * 10;
	fCastWeek[1].rchance = rnd(10) * 10;
	fCastWeek[2].rchance = rnd(10) * 10;

}

byte convertIconCode(byte *iconCode){
	// Need to Map WeatherUnderground's weather iconCode to my Icons
	// for now just use random icons	
	int iconIndex = rnd(5);
	
	return (byte) iconIndex;
}

void get_temperature_now() {
	// Generate a random temperature for now. Need to link to FujiNet

	TEMPERATURE = 72 + rnd(26);

}

void update_display() 
{
  cls(0);	//Clear the screen Black
	
// Print the forecast days
	locate(2,0);
	printf("%s", fCastWeek[0].DOW);
	locate(13,0);
	printf("%s", fCastWeek[1].DOW);
	locate(23,0);
	printf("%s", fCastWeek[2].DOW);
	
// Print the High Temperatures
	locate(1,9);
	printf("high%c%df", 192, fCastWeek[0].tempH);
	locate(12,9);
	printf("high%c%df", 192, fCastWeek[1].tempH);
	locate(23,9);
	printf("high%c%df", 192, fCastWeek[2].tempH);
	
// Print the Low Temperatures
	locate(2,10);
	printf("low%c%df", 192, fCastWeek[0].tempL);
	locate(13,10);
	printf("low%c%df", 192, fCastWeek[1].tempL);
	locate(24,10);
	printf("low%c%df", 192, fCastWeek[2].tempL);
	
// Print the Rain Chances
	locate(1,11);
	printf("rain%c%d%", 192, fCastWeek[0].rchance);
	locate(12,11);
	printf("rain%c%d%", 192, fCastWeek[1].rchance);
	locate(23,11);
	printf("rain%c%d%", 192, fCastWeek[2].rchance);
	
// Print the Current Temperature
	locate(5,13);
	printf("current%ctemp%c%df", 192, 192, TEMPERATURE);
	locate(5,14);
	printf("feels%clike%c%df", 192, 192, TEMPERATURE + 5);
		
}

void putIcon(byte day, int icon)
{
	byte row = 1;
  byte col = 0;
  byte sCol;
	byte maxCol;
	
	if(day == 1) {
		sCol = 0;
	}
	if(day == 2) {
		sCol = 11;
	}
	if(day == 3) {
		sCol = 22;
	}
	col = sCol;
	maxCol = col + 10;

	for (byte icPos = 0; icPos <= 69; icPos++) {
		printCharAt( row, col, ICONS[icon][icPos]);
		//locate(1,1);
		//printf("row:%d\ncol:%d\nicPos:%d\nchar:%c",row, col, icPos, CLD[icPos]);
		col++;
		if (col >= maxCol) {
			//locate(1,6);
			//printf("-MaxCol-@%d",col);
			col = sCol;
			row++;
		}
		
	}
/*	
	locate(sCol,15);
	printf("icon %d", icon);
*/
}

void printCharAt(byte x, byte y, byte asciiCode)
{
	locate(y, x);
	putchar(asciiCode);
}

int rnd(int max) {
  return rand() % max;
}

