#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char original_entries[7][16] = {
    "<HashName>",
    "<X>",
    "<Y>",
    "<Z>",
    "<Pitch>",
    "<Roll>",
    "<Yaw>"
};

char *converted_entries[7] = {
    "  \"model\": ",
    "  \"x\": ",
    "  \"y\": ",
    "  \"z\": ",
    "  \"rx\": ",
    "  \"ry\": ",
    "  \"rz\": "
};

int entries_size[7] = {
    10,
    3,
    3,
    3,
    7,
    6,
    5
} ;

void tokenize_string(char *original_string, char **token_string) {
    *token_string = strtok(original_string, ">");
    *token_string = strtok(NULL, ">");
}

void write_converted_string(FILE *destination, char *arg1, int arg2, char *token) {
    char final_string[256];
    char tmp[256];
    memset(&tmp[0], 0, sizeof(tmp));
    strcpy(final_string, arg1);
    strncpy(tmp, token, strlen(token)-arg2);
    strcat(final_string, tmp) ;
    strcat(final_string, ",\n") ;
    fprintf(destination, "%s", final_string);
}


int main()
{
    char input_name[64];
    char output_name[64];
    char json[6] = ".json";
    char str[1024]; // maximum size of a line

    int firstplacement = 0;
    int InPlacement; // are we within <Placement> ?

    FILE *original;
    FILE *converted;

    memset(&input_name[0], 0, sizeof(input_name));
    memset(&output_name[0], 0, sizeof(output_name));

    printf("\nEnter the name of your XML file: ");
    scanf("%s", input_name);
    printf("\n");

    if (strstr(input_name, ".xml") == NULL) {// the user didn't add .xml at the end of the file name
        strcat(input_name, ".xml"); // so we add it ourselves
    }
    strncpy(output_name, input_name, strlen(input_name)-4);
    strcat(output_name, json);

    original = fopen(input_name , "r"); // now we read the file
    if (original == NULL) {
      perror("Error opening file");
      return 0;
    }
    printf(output_name);
    converted = fopen(output_name, "ab+");
    fprintf(converted, "%s", "[\n");

    while(!feof(original))
    {
        if (fgets(str, 1024, original) != NULL) {
           if (strstr(str, "<Placement>") != NULL) {
                if (firstplacement == 0) {
                    firstplacement = 1;
                    fprintf(converted, "%s", " {\n");
                }
                else {
                   fprintf(converted, "%s", ",\n {\n");
                }
                InPlacement = 1 ;
           }
           else if (strstr( str, "</Placement>") != NULL) {
               fprintf(converted, "%s", " }");
               InPlacement = 0 ;
           }
           else {
            for (int i = 0; i < 7; i++) {
                if (strstr(str, original_entries[i]) != NULL && InPlacement == 1)
                {
                    char *token;
                    tokenize_string(str, &token);
                    write_converted_string(converted, converted_entries[i], entries_size[i], token);
                    if (strstr(original_entries[i], "<Yaw>")) {
                        fprintf(converted, "%s", "  \"col\": true,\n  \"freeze\": true\n");
                    }
                    break;
                }
            }
           }
        }
    }
    fprintf(converted, "%s", "\n]");
    fclose(original);
    fclose(converted);
    return 0;
}


