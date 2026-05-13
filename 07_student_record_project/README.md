# 07 Student Record Management System

## What This Program Does
A console-based student record management system written in C.
The program allows the user to add, display, and delete student 
records through an interactive menu. It can store up to 10 student 
records at a time.

## How to Use
When the program runs, a menu is displayed with the following options:

| Option | Action |
|--------|--------|
| 1 | Display all existing student records |
| 2 | Add a new student record |
| 3 | Delete a student record by roll number |
| 0 | Exit the application |

## What Each Record Contains
- Roll Number
- Student Name
- Branch
- Date of Birth (DD/MM/YYYY)
- Semester

## Concepts Covered
- Structs and typedef
- Arrays of structs
- Functions and function prototypes
- Pointers and passing structs by reference
- scanf and printf for user input/output
- switch statements and while loops
- memset for clearing memory
- String handling with scanf format specifiers

## Program Structure

| Function | What it does |
|----------|-------------|
| `main()` | Entry point, runs the main application loop |
| `display_menu()` | Prints the menu options to the user |
| `read_menu_code()` | Reads the user's menu selection |
| `decode_menu_code()` | Calls the right function based on user input |
| `display_all_records()` | Prints all stored student records |
| `check_roll_number()` | Checks if a roll number already exists |
| `add_new_record()` | Adds a new student record to the array |
| `delete_record()` | Deletes a record by matching roll number |

## Important Implementation Details
- The global array `students[10]` holds all records
- A record is considered empty if its `rollNumber` field is 0
- Deleting a record uses `memset` to zero out the entire struct,
  effectively marking it as empty for reuse
- Duplicate roll numbers are not allowed

## Notes
This was the capstone project for the Embedded C Fundamentals course,
combining structs, pointers, functions, and user input into one 
complete program.
