#include <stdio.h>
#include <stdlib.h>

int main()
{
    char input_name[ 64 ] ;
    memset(&input_name[0], 0, sizeof(input_name));
    char output_name[ 64 ] ;
    memset(&output_name[0], 0, sizeof(output_name));
    char json[6] = ".json" ;
    char str[1024]; // maximum size of a line
    int firstplacement = 0 ;
    int InPlacement ; // are we within <Placement> ?
    FILE *original ;
    FILE *converted ;


    printf ("\nEnter the name of your XML file: ") ;
    scanf ("%s", input_name);
    printf("\n");
    if( strstr (input_name, ".xml") == NULL ) {// the user didn't add .xml at the end of the file name
        strcat (input_name, ".xml") ; // so we add it ourselves
    }
    strncpy (output_name, input_name, strlen(input_name)-4);
    strcat (output_name, json) ;

    original  = fopen(input_name , "r"); // now we read the file
    if(original == NULL) {
      perror("Error opening file");
      return 0;
    }
    printf(output_name);
    converted = fopen(output_name, "ab+");
    fprintf( converted, "%s", "[\n");
    while(!feof(original))
    {
        if( fgets(str, 1024, original) != NULL ) {
           if( strstr( str, "<Placement>") != NULL ) {
                if(firstplacement == 0) {
                    firstplacement = 1;
                    fprintf( converted, "%s", " {\n");
                }
                else{
                   fprintf( converted, "%s", ",\n {\n");
                }


               InPlacement = 1 ;
           }
           else if( strstr( str, "<HashName>") != NULL && InPlacement == 1 ) {
                char *token;
                token = strtok(str, ">");
                token = strtok(NULL, ">");
                char copy[256];
                memset(&copy[0], 0, sizeof(copy));
                char copy1[256] = "  \"model\": ";
                strncpy(copy, token, strlen(token)-10);
                strcat( copy1, copy ) ;
                strcat( copy1, ",\n") ;
                fprintf( converted, "%s", copy1);
				free(copy);
           }
           else if( strstr( str, "<X>") != NULL && InPlacement == 1 ) {
                char *token;
                token = strtok(str, ">");
                token = strtok(NULL, ">");
                char copy[256];
                memset(&copy[0], 0, sizeof(copy));
                char copy1[256] = "  \"x\": ";
                strncpy(copy, token, strlen(token)-3);
                strcat( copy1, copy ) ;
                strcat( copy1, ",\n") ;
                fprintf( converted, "%s", copy1);
				free(copy);
           }
           else if( strstr( str, "<Y>") != NULL && InPlacement == 1 ) {
                char *token;
                token = strtok(str, ">");
                token = strtok(NULL, ">");
                char copy[256];
                memset(&copy[0], 0, sizeof(copy));
                char copy1[256] = "  \"y\": ";
                strncpy(copy, token, strlen(token)-3);
                strcat( copy1, copy ) ;
                strcat( copy1, ",\n") ;
                fprintf( converted, "%s", copy1);
				free(copy);
           }
           else if( strstr( str, "<Z>") != NULL && InPlacement == 1 ) {
                char *token;
                token = strtok(str, ">");
                token = strtok(NULL, ">");
                char copy[256];
                memset(&copy[0], 0, sizeof(copy));
                char copy1[256] = "  \"z\": ";
                strncpy(copy, token, strlen(token)-3);
                strcat( copy1, copy ) ;
                strcat( copy1, ",\n") ;
                fprintf( converted, "%s", copy1);
				free(copy);
           }
           else if( strstr( str, "<Pitch>") != NULL && InPlacement == 1 ) {
                char *token;
                token = strtok(str, ">");
                token = strtok(NULL, ">");
                char copy[256];
                memset(&copy[0], 0, sizeof(copy));
                char copy1[256] = "  \"rx\": ";
                strncpy(copy, token, strlen(token)-7);
                strcat( copy1, copy ) ;
                strcat( copy1, ",\n") ;
                fprintf( converted, "%s", copy1);
				free(copy);
           }
           else if( strstr( str, "<Roll>") != NULL && InPlacement == 1 ) {
                char *token;
                token = strtok(str, ">");
                token = strtok(NULL, ">");
                char copy[256];
                memset(&copy[0], 0, sizeof(copy));
                char copy1[256] = "  \"ry\": ";
                strncpy(copy, token, strlen(token)-6);
                strcat( copy1, copy ) ;
                strcat( copy1, ",\n") ;
                fprintf( converted, "%s", copy1);
				free(copy);
           }
           else if( strstr( str, "<Yaw>") != NULL && 1 == InPlacement ) {
                char *token;
                token = strtok(str, ">");
                token = strtok(NULL, ">");
                char copy[256];
                memset(&copy[0], 0, sizeof(copy));
                char copy1[256] = "  \"rz\": ";
                strncpy(copy, token, strlen(token)-5);
                strcat( copy1, copy ) ;
                strcat( copy1, ",\n") ;
                fprintf( converted, "%s", copy1);
                fprintf( converted, "%s", "  \"col\": true,\n  \"freeze\": true\n");
				free(copy);
           }
           else if( strstr( str, "</Placement>") != NULL ) {
               fprintf( converted, "%s", " }");
               InPlacement = 0 ;
           }
        }
    }
    fprintf(converted, "%s", "\n]");
    fclose(original);
    fclose(converted);
	free(input_name);
	free(output_name);
    return 0;
}
