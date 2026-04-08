#!/bin/bash

# Title: Shell Scripting Interactive Tour
# Description: A master script to explore and run the Shell tutorials.

# Function to explain and run a script
run_tutorial() {
    local script=$1
    local description=$2
    
    echo -e "\n--------------------------------------------------"
    echo -e "Tutorial: \033[1;34m$script\033[0m"
    echo -e "Description: $description"
    echo -e "--------------------------------------------------"
    read -p "Press [Enter] to run this tutorial..."
    
    chmod +x "$script"
    ./"$script"
    
    echo -e "\nTutorial Finished. Returning to menu."
}

# Clear screen for a clean start
clear
echo -e "\033[1;32mWelcome to the Shell Scripting Masterclass!\033[0m"
echo "Select a tutorial to explore or quit."

options=(
    "Arrays (array.sh)"
    "Command Line Arguments (commnd_line_shell.sh)"
    "Conditionals (conditions.sh)"
    "File Checking (file_checking.sh)"
    "File Operations (file_operations.sh)"
    "Functions (func.sh)"
    "IP Checker (ipchecker.sh)"
    "Loops (loops.sh)"
    "Miscellaneous (others.sh)"
    "Print Formatting (print.sh)"
    "Python Python Integration (py_call.sh)"
    "Reading User Input (read_from_shell.sh)"
    "File Renaming (renaming_files.sh)"
    "Signal Traps (trap.sh)"
    "Variable Counts (variable_count.sh)"
    "Quit"
)

select opt in "${options[@]}"
do
    case $opt in
        "Arrays (array.sh)")
            run_tutorial "array.sh" "Mastering indexed and associative arrays in Bash."
            ;;
        "Command Line Arguments (commnd_line_shell.sh)")
            run_tutorial "commnd_line_shell.sh" "Learn how to pass and handle arguments ($1, $2, etc.) in your scripts."
            ;;
        "Conditionals (conditions.sh)")
            run_tutorial "conditions.sh" "Using if, elif, and else to build logic."
            ;;
        "File Checking (file_checking.sh)")
            run_tutorial "file_checking.sh" "Check if files exist, are readable, or are directories."
            ;;
        "File Operations (file_operations.sh)")
            run_tutorial "file_operations.sh" "How to read from and write to text files dynamically."
            ;;
        "Functions (func.sh)")
            run_tutorial "func.sh" "Encapsulating code into reusable functions."
            ;;
        "IP Checker (ipchecker.sh)")
            run_tutorial "ipchecker.sh" "A practical example of using ping to check network connectivity."
            ;;
        "Loops (loops.sh)")
            run_tutorial "loops.sh" "Exploring For, While, and Until loops."
            ;;
        "Miscellaneous (others.sh)")
            run_tutorial "others.sh" "Various useful shell commands and tips."
            ;;
        "Print Formatting (print.sh)")
            run_tutorial "print.sh" "The differences between echo and printf for output."
            ;;
        "Python Python Integration (py_call.sh)")
            run_tutorial "py_call.sh" "Learn how to trigger Python scripts from within your Shell environment."
            ;;
        "Reading User Input (read_from_shell.sh)")
            run_tutorial "read_from_shell.sh" "Capturing interactive user input using the read command."
            ;;
        "File Renaming (renaming_files.sh)")
            run_tutorial "renaming_files.sh" "Batch renaming files using loops and text manipulation."
            ;;
        "Signal Traps (trap.sh)")
            run_tutorial "trap.sh" "Learn signal handling (CTRL+C) using the trap command."
            ;;
        "Variable Counts (variable_count.sh)")
            run_tutorial "variable_count.sh" "Basic variable arithmetic and counting logic."
            ;;
        "Quit")
            echo "Happy Coding! Goodbye."
            break
            ;;
        *) echo "Invalid option $REPLY";;
    esac
done
