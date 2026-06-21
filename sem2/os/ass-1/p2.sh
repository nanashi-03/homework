#!/bin/bash

echo "========================================"
echo "      Employee Salary Input System      "
echo "========================================"

read -p "Enter Employee Name: " emp_name
read -p "Enter Basic Salary: " basic
read -p "Enter House Rent Allowance (HRA): " hra
read -p "Enter Dearness Allowance (DA): " da

net_salary=$(echo "$basic + $hra + $da" | bc -l)

echo ""
echo "----------------------------------------"
echo "             SALARY SLIP                "
echo "----------------------------------------"
echo " Employee Name : $emp_name"
printf " Basic Salary  : %.2f\n" "$basic"
printf " HRA           : %.2f\n" "$hra"
printf " DA            : %.2f\n" "$da"
echo "----------------------------------------"
printf " NET SALARY    : %.2f\n" "$net_salary"
echo "----------------------------------------"
echo " Status        : Processed Successfully"
echo "----------------------------------------"
