#include <stdio.h>
#include <string.h>
#include <time.h>
#include "receipter.h"

#define MAX_WIDTH (50)
/*마지막 널문자가 들어갈 자리 포함*/
#define MAX_MESSAGE (76)
#define MAX_FOOD_NAME (26) 

static size_t s_item_count = 0u;
static char s_food_name[10][MAX_FOOD_NAME] = { 0, };
static double s_food_price[10] = { 0, };
static double s_subtotal = 0.0;

static double s_tip_price = 0u;

static char s_write_message[MAX_MESSAGE] = { 0, };

int add_item(const char* name, double price)
{
    if (s_item_count >= 10) {
        return FALSE;
    }
    
    strncpy(s_food_name[s_item_count], name, MAX_FOOD_NAME);
    s_food_name[s_item_count][MAX_FOOD_NAME - 1] = '\0';
    s_food_price[s_item_count] = price;
    
    s_subtotal += price;
    s_item_count++;
    return TRUE;
}

void set_tip(double tip)
{
    s_tip_price = tip;
}

void set_message(const char* message)
{
    strncpy(s_write_message, message, MAX_MESSAGE);
    s_write_message[MAX_MESSAGE - 1] = '\0';
}

int print_receipt(const char* filename, time_t timestamp)
{
    FILE* file;
    struct tm* t = localtime(&timestamp);
    size_t i = 0u;
    static size_t s_receipter_number = 0u;
    
    if (s_item_count == 0) {
        return FALSE;
    }
    
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("error while writing file");
        return 1;
    }
    
    fprintf(file, "Charles' Seafood\n");
    fprintf(file, "--------------------------------------------------\n");
    fprintf(file, "%d-%d-%d %d:%d:%d                           %05d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_hour, t->tm_hour, t->tm_min, t->tm_sec, receipter_number);
    fprintf(file, "--------------------------------------------------\n");
    
    /*Food List*/
    for (i = 0; i < s_item_count; i++) {
        fprintf(file, "%33s", s_food_name[i]);
        fprintf(file, "%17.2f\n", s_food_price[i]);
    }
    fprintf(file, "\n");
	
    /*s_subtotal*/
    fprintf(file, "%33s", "Subtotal");
    fprintf(file, "%17.2f\n", s_subtotal);
    
    /*Tip*/
    if (s_tip_price != 0) {
        fprintf(file, "%33s", "Tip");
        fprintf(file, "%17.2f\n", s_tip_price);
    }
    
    /*Tex*/
    fprintf(file, "%33s", "Tax");
    fprintf(file, "%17.2f\n", s_subtotal * 0.05);
    
    /*Total*/
    fprintf(file, "%33s", "Total");
    fprintf(file, "%17.2f\n\n", s_subtotal + s_tip_price + (s_subtotal * 0.05));
    
    /*Messasge*/
    fprintf(file, "%s\n", s_write_message);
    
    fprintf(file, "==================================================\n");
    fprintf(file, "%50s", "Tax#-51234");
    
    if (fclose(file) == EOF) {
        perror("error while closing file");
    }
    
    s_receipter_number++;
    memset(s_write_message, 0, MAX_MESSAGE);
    s_subtotal = 0.0;
    s_item_count = 0u;
    s_tip_price = 0.0;
    return TRUE;
}
