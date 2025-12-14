# Quick Start Guide

## 🚀 Quick Compilation & Run

### Windows
```bash
# Option 1: Using build script
build.bat

# Option 2: Direct compilation
g++ main.cpp -o hostel_management.exe
hostel_management.exe
```

### Linux/Mac
```bash
# Option 1: Using build script
chmod +x build.sh
./build.sh

# Option 2: Using Makefile
make
make run

# Option 3: Direct compilation
g++ main.cpp -o hostel_management
./hostel_management
```

## 📋 First Steps

1. **Compile the program** using one of the methods above
2. **Run the executable** to start the system
3. **Add a leave entry** to test the system:
   - Select option 1 from the menu
   - Enter sample student details
4. **View records** using option 2
5. **Search records** using option 4
6. **Mark return** using option 3 when student returns

## 📝 Sample Test Data

Try adding these sample entries:

**Student 1:**
- Name: John Doe
- Roll: 2024001
- Room: A101
- Date: 15/12/2024
- Time Out: 10:00
- Expected Return: 16/12/2024 18:00
- Purpose: Home Visit

**Student 2:**
- Name: Jane Smith
- Roll: 2024002
- Room: B205
- Date: 20/12/2024
- Time Out: 14:30
- Expected Return: 22/12/2024 20:00
- Purpose: Medical Appointment

## ⚙️ System Requirements

- C++ compiler (g++, clang++, or MSVC)
- Windows/Linux/Mac OS
- Minimum 1MB disk space

## 🔧 Troubleshooting

**Compilation Error:**
- Ensure you have a C++ compiler installed
- Check that `main.cpp` exists in the current directory

**File Not Found:**
- The `leave_records.txt` file will be created automatically
- Ensure you have write permissions in the directory

**Program Crashes:**
- Check that all input fields are filled correctly
- Avoid special characters in file paths

## 📚 Need Help?

Refer to the main `README.md` for detailed documentation.

