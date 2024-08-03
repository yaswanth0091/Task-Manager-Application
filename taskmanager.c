#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Structure to represent a task
struct Task {
    char description[100];
    int priority;
    struct Task* next;
};
// Function to create a new task node
struct Task* createTaskNode(char description[], int priority) {
    struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
    strcpy(newTask->description, description);
    newTask->priority = priority;
    newTask->next = NULL;
    return newTask;
}
// Function to add a task to the list
void addTask(struct Task** taskList, char description[], int priority) {
    struct Task* newTask = createTaskNode(description, priority);
    newTask->next = *taskList;
    *taskList = newTask;
    printf("Task added successfully.\n");
}
// Function to remove a task from the list by index
void removeTask(struct Task** taskList, int index) {
    if (*taskList == NULL) {
        printf("Task list is empty.\n");
        return;
    }
    if (index == 1) {
        struct Task* temp = *taskList;
        *taskList = (*taskList)->next;
        free(temp);
        printf("Task removed successfully.\n");
        return;
    }
    struct Task* current = *taskList;
    struct Task* prev = NULL;
    int i = 1;
    while (current != NULL && i < index) {
        prev = current;
        current = current->next;
        i++;
    }
    if (current == NULL) {
        printf("Invalid task index. Task not removed.\n");
        return;
    }
    if (prev == NULL) {
        *taskList = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
    printf("Task removed successfully.\n");
}
// Function to display all tasks while preserving priority order
void displayTasksByPriority(struct Task* taskList) {
    if (taskList == NULL) {
        printf("Task list is empty.\n");
        return;
    }
    printf("Tasks by Priority (High to Low):\n");
    // Loop through each priority level
    for (int priority = 3; priority >= 1; priority--) {
        struct Task* current = taskList;
        int taskCount = 0;
        printf("Priority %d:\n", priority);
        while (current != NULL) {
            if (current->priority == priority) {
                taskCount++;
                printf("Task %d:\n", taskCount);
                printf("Description: %s\n", current->description);
                printf("Priority: %d\n", current->priority);
                printf("\n");
            }
            current = current->next;
        }
        if (taskCount == 0) {
            printf("No tasks with Priority %d\n", priority);
        }
    }
}
int main() {
    struct Task* taskList = NULL;
    int choice;
    char description[100];
    int priority;
    while (1) {
        printf("\nOptions:\n");
        printf("1. Add a task\n");
        printf("2. Remove a task\n");
        printf("3. Display tasks by priority\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter task name: ");
                scanf(" %[^\n]", description);
                printf("Enter task priority (1 - low, 2 - medium, 3 - high): ");
                scanf("%d", &priority);
                if (priority < 1 || priority > 3) {
                    printf("Invalid priority. Task not added.\n");
                } else {
                    addTask(&taskList, description, priority);
                }
                break;
            case 2:
                printf("Enter the index of the task to remove: ");
                scanf("%d", &choice);
                removeTask(&taskList, choice);
                break;
            case 3:
                displayTasksByPriority(taskList);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}