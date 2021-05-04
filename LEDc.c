//Code to control the LED3 usr by arguments
//27/04/2021
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LED3 "/sys/class/leds/beaglebone:green:usr3"

//Prototypes functions:
void WriteLED(char filename[], char value[]);
void RemoveTrigger();

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("Error: Wrong arguments number!!!\n");
		return 2;
	}
	printf("Starting script...\n");
	//Argument comparisson
	if(strcmp(argv[1], "on")==0){
		printf("LED on\n");
		RemoveTrigger();
		WriteLED("/brightness", "1");
	}
	
	if(strcmp(argv[1], "off")==0){
		printf("LED off\n");
		RemoveTrigger();
		WriteLED("/brightness", "0");
	}

	if(strcmp(argv[1], "flash")==0) {
		printf("LED flashing\n");
		RemoveTrigger();
		WriteLED("/trigger", "timer");
		WriteLED("/delay_on", "50");
		WriteLED("/delay_off", "50");
	}
	return 0;

}

//Complete functions
void WriteLED(char filename[], char value[]){
	FILE* fp;//
	char fullfn[100];
	sprintf(fullfn, LED3 "%s", filename);
	fp = fopen(fullfn, "w+");
	fprintf(fp, "%s", value);
	fclose(fp);
}

void RemoveTrigger(){
	WriteLED("/trigger", "none");
}
