#!/bin/bash

echo "Building Hostel Outing & Leave Management System..."
g++ main.cpp -o hostel_management

if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo "Run ./hostel_management to start the program."
else
    echo "Build failed!"
    exit 1
fi

