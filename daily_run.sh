#!/bin/bash
# daily_run.sh - Full daily build & test for Students Management System
# Mitel-ready, cron-friendly, with logging

# --- Configuration ---
PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"
LOG_DIR="$PROJECT_DIR/logs"
DATA_FILE="$PROJECT_DIR/students.json"
LOG_FILE="$LOG_DIR/daily_run_$(date +%F).log"

# --- Ensure directories exist ---
mkdir -p "$BUILD_DIR" "$LOG_DIR"

# --- Environment for cron ---
export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin

echo "=== Daily Run Started: $(date) ===" | tee -a "$LOG_FILE"

# --- Build with CMake ---
echo "--- CMake Build ---" | tee -a "$LOG_FILE"
cd "$PROJECT_DIR" || { echo "Failed to cd to project dir" | tee -a "$LOG_FILE"; exit 1; }
cmake -S . -B "$BUILD_DIR" >> "$LOG_FILE" 2>&1
cmake --build "$BUILD_DIR" >> "$LOG_FILE" 2>&1
if [ $? -ne 0 ]; then
    echo "Build failed!" | tee -a "$LOG_FILE"
    exit 1
fi
echo "Build succeeded." | tee -a "$LOG_FILE"

# --- Run main executable ---
echo "--- Running Student Management ---" | tee -a "$LOG_FILE"
"$BUILD_DIR/student_management" "$DATA_FILE" 2>&1 | tee -a "$LOG_FILE"

# --- Run unit tests ---
echo "--- Running Unit Tests ---" | tee -a "$LOG_FILE"
ctest --test-dir "$BUILD_DIR" --output-on-failure >> "$LOG_FILE" 2>&1

# --- Summary statistics ---
if [ -f "$DATA_FILE" ]; then
    echo "--- Summary Statistics ---" | tee -a "$LOG_FILE"
    python3 - <<EOF 2>&1 | tee -a "$LOG_FILE"
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

echo "=== Daily Run Finished: $(date) ===" | tee -a "$LOG_FILE"
