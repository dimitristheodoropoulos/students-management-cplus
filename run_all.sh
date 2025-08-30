#!/bin/bash
# run_all.sh - Mitel-ready CMake build, daily logs, JSON persistence

# --- Colors ---
RED='\033[0;31m'; GREEN='\033[0;32m'; YELLOW='\033[1;33m'; CYAN='\033[0;36m'; NC='\033[0m'

# --- Paths ---
BUILD_DIR="build"
DATE_DIR=$(date +%F)             # YYYY-MM-DD
LOG_DIR="$BUILD_DIR/logs/$DATE_DIR"
DATA_FILE="students.json"
MAIN_EXE="$BUILD_DIR/student_management"
TEST_EXE="$BUILD_DIR/test_student_manager"

mkdir -p $BUILD_DIR $LOG_DIR

# --- Determine if rebuild is needed ---
rebuild=0
SRC_FILES=$(find src include tests -type f \( -name "*.cpp" -o -name "*.hpp" \))
if [ ! -f "$MAIN_EXE" ] || [ ! -f "$TEST_EXE" ]; then
    rebuild=1
else
    for f in $SRC_FILES; do
        if [ "$f" -nt "$MAIN_EXE" ] || [ "$f" -nt "$TEST_EXE" ]; then
            rebuild=1
            break
        fi
    done
fi

# --- Build with CMake ---
if [ $rebuild -eq 1 ]; then
    echo -e "${CYAN}Sources changed or executables missing. Running CMake build...${NC}"
    cmake -S . -B $BUILD_DIR &> $LOG_DIR/cmake_config.log
    if [ $? -ne 0 ]; then echo -e "${RED}CMake configuration failed! Check $LOG_DIR/cmake_config.log${NC}"; exit 1; fi

    cmake --build $BUILD_DIR --parallel &> $LOG_DIR/build.log
    if [ $? -ne 0 ]; then echo -e "${RED}Build failed! Check $LOG_DIR/build.log${NC}"; exit 1; fi
    echo -e "${GREEN}Build succeeded! Logs: $LOG_DIR/build.log${NC}"
else
    echo -e "${YELLOW}Executables up-to-date, skipping rebuild.${NC}"
fi

# --- Run main program ---
echo -e "\n${CYAN}=== Running Student Management (JSON: $DATA_FILE) ===${NC}"
$MAIN_EXE $DATA_FILE &> $LOG_DIR/run_main.log
cat $LOG_DIR/run_main.log

# --- Run unit tests ---
echo -e "\n${CYAN}=== Running Unit Tests ===${NC}"
ctest --test-dir $BUILD_DIR --output-on-failure &> $LOG_DIR/run_tests.log
cat $LOG_DIR/run_tests.log

# --- Summary statistics ---
if [ -f "$DATA_FILE" ]; then
    echo -e "\n${CYAN}=== Summary Statistics ===${NC}"
    python3 - <<EOF
import json
with open("$DATA_FILE") as f:
    students = json.load(f)
grades = [s["grade"] for s in students]
if grades:
    print(f"Number of students: {len(grades)}")
    print(f"Average grade: {sum(grades)/len(grades):.2f}")
    print(f"Min grade: {min(grades)}")
    print(f"Max grade: {max(grades)}")
    buckets = [0]*10
    for g in grades: buckets[min(g//10,9)]+=1
    print("Grade distribution (0-100 by 10):")
    for i in range(10): print(f"{i*10}-{99 if i<9 else 100}: {buckets[i]}")
else:
    print("No students in file.")
EOF
fi

echo -e "\n${GREEN}All done! Daily logs saved in $LOG_DIR/${NC}"
