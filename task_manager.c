/**
 * Simple Task Manager in C
 * 
 * Features:
 * - Add new tasks with title, priority, and due date
 * - List all tasks
 * - Mark tasks as completed
 * - Delete tasks
 * - Save tasks to file
 * - Load tasks from file
 */

 #include <stdio.h>
 #include <string.h>
 #include <ctype.h>
 #include <stdlib.h>

 #define TITLE_LENGTH 50
 #define DATE_LENGTH 12
 #define MAX_TASKS 100

 typedef struct 
 {
    int id;
    char title[TITLE_LENGTH];
    int priority;
    char due_date[DATE_LENGTH];
    int status;
 } Task;

 static void trimmer(char *s){
    int i = 0;
    int j = 0;
    
    while (isspace(s[i])) i++;
    
    while (s[j++] = s[i++]);
    
    int length = strlen(s);
    for (int k = length - 1; k > 0; k--)
    {
        if (!isspace(s[k]))
        {
            s[k+1] = '\0';
            break;
        }
        
    }
    
 }

 char* status_conversion(int status){
    if (status == 0)
    {
        return "Pending";
    }else
    {
        return "Completed";
    }
    
 }

 int status_conversion_to_int(char *str){
    return strcmp(str, "Pending") == 0 ? 0 : 1;    
 }

 int prioprity_conversion_to_int(char *str){
    if (strcmp(str, "High") == 0)
    {
        return 1;
    }else if (strcmp(str, "Medium") == 0)
    {
        return 2;
    }else
    {
        return 3;
    }
    
 }

  char* prioprity_conversion(int prio){
    if (prio == 1)
    {
        return "High";
    }else if (prio == 2)
    {
        return "Medium";
    }else
    {
        return "Low";
    }
    
 }
 
 void add_new_task(Task tasks[], int *task_count){
    if (*task_count >= MAX_TASKS)
    {
        printf("Task manager is full!");
        return;
    }
    

    Task task;
    task.id = *task_count + 1;
    task.status = 0;

    getchar();
    printf("Enter task title:\n");
    fgets(task.title, TITLE_LENGTH, stdin);
    task.title[strcspn(task.title, "\n")] = '\0';

    printf("Enter priority (1-High, 2-Medium, 3-Low):\n");
    scanf("%d", &task.priority);
    getchar();

    printf("Enter due date (YYYY-MM-DD):\n");
    fgets(task.due_date, DATE_LENGTH, stdin);
    task.due_date[strcspn(task.due_date, "\n")] = '\0';

    tasks[*task_count] = task;
    (*task_count)++;
    
 }

 void list_all_tasks(Task tasks[], int *task_count){


    printf("===== TASK LIST =====\n");
    printf("ID | Title                 | Priority | Due Date   | Status\n");
    printf("---+----------------------+----------+------------+--------\n");

    for (int i = 0; i < *task_count; i++)
    {
        printf("%-2d | %-20s | %-8s | %-10s | %s\n", tasks[i].id, tasks[i].title, prioprity_conversion(tasks[i].priority), tasks[i].due_date, status_conversion(tasks[i].status));
    }
    
 }

 void mark_as_completed(Task tasks[], int *task_count){
    int id;
    list_all_tasks(tasks, task_count);
    printf("Enter the ID of the task to mark as completed:");
    scanf("%d", &id);
    getchar();
    if (id > *task_count)
    {
        printf("Invalid ID!");
        return;
    }
    for (int i = 0; i < *task_count; i++)
    {
        if (tasks[i].id == id)  
        {
            tasks[i].status = 1;
        }
        
    }
    
    
 }

 void delete_task(Task tasks[], int *task_count){
    int id;
    list_all_tasks(tasks, task_count);
    printf("Enter the ID of the task to delete:");
    scanf("%d", &id);
    getchar();
    if (id > *task_count)
    {
        printf("Invalid ID!");
        return;
    }
    for (int i = 0; i < *task_count; i++)
    {
        if (tasks[i].id == id)  
        {
            for (int j = i; j < *task_count - 1; j++)
            {
                tasks[j] = tasks[j + 1];
            }
            (*task_count)--;
            return;
        }
        
    }
 }

 void save_task_to_file(Task tasks[], int *task_count){

    FILE *file = fopen("output.txt", "w");
    if (file == NULL)
    {
        perror("Error opening file\n");
        return;
    }
    for (int i = 0; i < *task_count; i++)
    {
        fprintf(file, "%-2d | %-20s | %-8s | %-10s | %s\n", tasks[i].id, tasks[i].title, prioprity_conversion(tasks[i].priority), tasks[i].due_date, status_conversion(tasks[i].status));
    }
    fclose(file);
    
 }

 void load_tasks_from_file(Task tasks[], int *task_count){
    FILE *f = fopen("output.txt", "r");

    if (f == NULL)
    {
        return;
    }

    char line[1024];

    while (fgets(line, sizeof(line), f))
    {
        line[strcspn(line, "\r\n")] = '\0';

        //Split the line

        char *save = NULL;
        char *tok = strtok_r(line, "|", &save);

        char fields[5][TITLE_LENGTH] = {{0}};
        int n = 0;

        while (tok && n < 5)
        {
            strncpy(fields[n], tok, TITLE_LENGTH - 1);
            fields[n][TITLE_LENGTH - 1] = '\0';
            trimmer(fields[n]);
            n++;
            tok = strtok_r(NULL, "|", &save);
        }
        if (n != 5)
        {
            continue;
        }

        tasks[*task_count].id = atoi(fields[0]);

        strncpy(tasks[*task_count].title, fields[1], TITLE_LENGTH-1);
        tasks[*task_count].title[TITLE_LENGTH-1] = '\0';

        tasks[*task_count].priority = prioprity_conversion_to_int(fields[2]);

        strncpy(tasks[*task_count].due_date, fields[3], DATE_LENGTH-1);
        tasks[*task_count].due_date[DATE_LENGTH-1] = '\0';

        tasks[*task_count].status = status_conversion_to_int(fields[4]);

        (*task_count)++;
        
    }
    fclose(f);
    
 }


 int main(){
     printf("Welcome to Simple Task Manager!\n");
     Task tasks[MAX_TASKS];
     int task_count = 0; //Follows the size of the tasks array

     load_tasks_from_file(tasks, &task_count);
     
    while (1)
    {
        printf("===== TASK MANAGER MENU =====\n");
        printf("1. Add new task\n");
        printf("2. List all tasks\n");
        printf("3. Mark task as completed\n");
        printf("4. Delete task\n");
        printf("5. Save tasks to file\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-6):");

        int choise;
        scanf("%d", &choise);
        
        switch (choise)
        {
        case 1:
            add_new_task(tasks, &task_count);
            break;
        case 2:
            list_all_tasks(tasks, &task_count);
            break;
        case 3:
            mark_as_completed(tasks, &task_count);
            break;
        case 4:
            delete_task(tasks, &task_count);
            break;
        case 5:
            save_task_to_file(tasks, &task_count);
            break;
        case 6:
            save_task_to_file(tasks, &task_count);
            return 0;
            break;
        default:
            printf("Please give a number between 1 and 6!");
            break;
        }
        
    }
    

    return 0;
 }