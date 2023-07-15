#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 100

struct Entry {
    char date[20];
    char title[50];
    char content[500];
};

void addEntry() {
    struct Entry entry;
    
    printf("Enter the date (DD/MM/YYYY): ");
    scanf("%s", entry.date);
    
    printf("Enter the title: ");
    scanf(" %[^\n]s", entry.title);
    
    printf("Enter the content: ");
    scanf(" %[^\n]s", entry.content);
    
    FILE* file = fopen("diary.txt", "a");
    
    if (file == NULL) {
        printf("Error: Failed to open file.\n");
        return;
    }
    
    fprintf(file, "%s\n%s\n%s\n", entry.date, entry.title, entry.content);
    
    fclose(file);
    
    printf("Entry added successfully.\n");
}

void viewEntry() {
    char date[20];
    printf("Enter the date (DD/MM/YYYY): ");
    scanf("%s", date);
    
    FILE* file = fopen("diary.txt", "r");
    
    if (file == NULL) {
        printf("Error: Failed to open file.\n");
        return;
    }
    
    struct Entry entry;
    int found = 0;
    
    while (fscanf(file, "%s\n%[^\n]\n%[^\n]\n", entry.date, entry.title, entry.content) != EOF) {
        if (strcmp(entry.date, date) == 0) {
            printf("Date: %s\n", entry.date);
            printf("Title: %s\n", entry.title);
            printf("Content: %s\n", entry.content);
            found = 1;
            break;
        }
    }
    
    fclose(file);
    
    if (!found) {
        printf("Entry not found.\n");
    }
}

void deleteEntry() {
    char date[20];
    printf("Enter the date (DD/MM/YYYY) of the entry to delete: ");
    scanf("%s", date);
    
    FILE* file = fopen("diary.txt", "r");
    
    if (file == NULL) {
        printf("Error: Failed to open file.\n");
        return;
    }
    
    struct Entry entry;
    int found = 0;
    int lineCount = 0;
    long int offset = 0;
    
    while (fscanf(file, "%s\n%[^\n]\n%[^\n]\n", entry.date, entry.title, entry.content) != EOF) {
        lineCount++;
        
        if (strcmp(entry.date, date) == 0) {
            found = 1;
            break;
        }
        
        offset = ftell(file);
    }
    
    fclose(file);
    
    if (!found) {
        printf("Entry not found.\n");
        return;
    }
    
    file = fopen("diary.txt", "r+");
    
    if (file == NULL) {
        printf("Error: Failed to open file.\n");
        return;
    }
    
    fseek(file, offset, SEEK_SET);
    
    for (int i = lineCount; i < MAX_ENTRIES - 1; i++) {
        fscanf(file, "%s\n%[^\n]\n%[^\n]\n", entry.date, entry.title, entry.content);
        fseek(file, offset, SEEK_SET);
        fprintf(file, "%s\n%s\n%s\n", entry.date, entry.title, entry.content);
        offset = ftell(file);
    }
    
    ftruncate(fileno(file), offset);
    
    fclose(file);
    
    printf("Entry deleted successfully.\n");
}

int main() {
    int choice;
    
    do {
        printf("Diary Management System\n");
        printf("1. Add entry\n");
        printf("2. View entry\n");
        printf("3. Delete entry\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addEntry();
                break;
            case 2:
                viewEntry();
                break;
            case 3:
                deleteEntry();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Error: Invalid choice.\n");
                break;
        }
        
        printf("\n");
    } while (choice != 4);
    
    return 0;
}
