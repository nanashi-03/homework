/*1.Create the following tables :
Tablename: EMPLOYEE
Structure :
EMP_CODE char(16)
EMP_NAME char(20)
DEPT_CODE char(16)
DESIG_CODE char(16)
SEX char(1)
ADDRESS char (25)
CITY char (20)
STATE char (20)
PIN char (6)
BASIC Number
JN_DT Date
Primary key is EMP_CODE
Tablename : DESIGNATION
Structure :
DESIG_CODE char(16)
DESIG_NAME char(20)
Primary key is DESIG_CODE
Tablename : DEPARTMENT
Structure :
DEPT_CODE char(16)
DEPT_NAME char(20)
Primary key is DEPT_CODE.*/

CREATE TABLE DEPARTMENT (
  DEPT_CODE CHAR(16) PRIMARY KEY,
  DEPT_NAME CHAR(20)
);

CREATE TABLE DESIGNATION (
  DESIG_CODE CHAR(16) PRIMARY KEY,
  DESIG_NAME CHAR(20)
);

CREATE TABLE EMPLOYEE (
  EMP_CODE CHAR(16) PRIMARY KEY,
  EMP_NAME CHAR(20),
  DEPT_CODE CHAR(16),
  DESIG_CODE CHAR(16),
  SEX CHAR(1),
  ADDRESS CHAR(25),
  CITY CHAR(20),
  STATE CHAR(20),
  PIN CHAR(6),
  BASIC DECIMAL,
  JN_DT DATE
);

-- 2. Display the structure of each table.

DESC DEPARTMENT;

DESC DESIGNATION;

DESC EMPLOYEE;

-- 3. Insert few rows in each table.

INSERT INTO DEPARTMENT (DEPT_CODE, DEPT_NAME) VALUES ('D01', 'Personnel');
INSERT INTO DEPARTMENT (DEPT_CODE, DEPT_NAME) VALUES ('D02', 'Production');
INSERT INTO DEPARTMENT (DEPT_CODE, DEPT_NAME) VALUES ('D03', 'Purchase');
INSERT INTO DEPARTMENT (DEPT_CODE, DEPT_NAME) VALUES ('D04', 'Finance');
INSERT INTO DEPARTMENT (DEPT_CODE, DEPT_NAME) VALUES ('D05', 'Research');

INSERT INTO DESIGNATION (DESIG_CODE, DESIG_NAME) VALUES ('G01', 'Manager');
INSERT INTO DESIGNATION (DESIG_CODE, DESIG_NAME) VALUES ('G02', 'Executive');
INSERT INTO DESIGNATION (DESIG_CODE, DESIG_NAME) VALUES ('G03', 'Officer');
INSERT INTO DESIGNATION (DESIG_CODE, DESIG_NAME) VALUES ('G04', 'Clerk');
INSERT INTO DESIGNATION (DESIG_CODE, DESIG_NAME) VALUES ('G05', 'Helper');

INSERT INTO EMPLOYEE (EMP_CODE, EMP_NAME, DEPT_CODE, DESIG_CODE, SEX, ADDRESS, CITY, STATE, PIN, BASIC, JN_DT) 
VALUES ('E01', 'Amit Sharma', 'D01', 'G01', 'M', '123 Park St', 'Kolkata', 'West Bengal', '700016', 50000, '2009-01-15');

INSERT INTO EMPLOYEE (EMP_CODE, EMP_NAME, DEPT_CODE, DESIG_CODE, SEX, ADDRESS, CITY, STATE, PIN, BASIC, JN_DT) 
VALUES ('E02', 'Sriya Das', 'D02', 'G02', 'F', '45 Lake Rd', 'Kolkata', 'West Bengal', '700029', 40000, '2012-05-12');

INSERT INTO EMPLOYEE (EMP_CODE, EMP_NAME, DEPT_CODE, DESIG_CODE, SEX, ADDRESS, CITY, STATE, PIN, BASIC, JN_DT) 
VALUES ('E03', 'Rahul Verma', 'D04', 'G03', 'M', '78 MG Rd', 'Mumbai', 'Maharashtra', '400001', 30000, '2015-01-20');

INSERT INTO EMPLOYEE (EMP_CODE, EMP_NAME, DEPT_CODE, DESIG_CODE, SEX, ADDRESS, CITY, STATE, PIN, BASIC, JN_DT) 
VALUES ('E04', 'Deepa Pillai', 'D03', 'G04', 'F', '12 Outer Ring Rd', 'Bangalore', 'Karnataka', '560001', 0, '2011-08-05');
    
-- 4. In EMP table insert few rows without DEPT_CODE and BASIC.

INSERT INTO EMPLOYEE (EMP_CODE, EMP_NAME, DEPT_CODE, DESIG_CODE, SEX, ADDRESS, CITY, STATE, PIN, BASIC, JN_DT) 
VALUES ('E05', 'Vikram Singh', 'D01', 'G05', 'M', '56 Mall Road', 'Delhi', 'Delhi', '110001', NULL, '2008-03-10');

INSERT INTO EMPLOYEE (EMP_CODE, EMP_NAME, DEPT_CODE, DESIG_CODE, SEX, ADDRESS, CITY, STATE, PIN, BASIC, JN_DT) 
VALUES ('E06', 'Karan Malhotra', 'D04', 'G03', 'M', '14 Link Rd', 'Mumbai', 'Maharashtra', '400053', NULL, '2016-11-22');

INSERT INTO EMPLOYEE (EMP_CODE, EMP_NAME, DEPT_CODE, DESIG_CODE, SEX, ADDRESS, CITY, STATE, PIN, BASIC, JN_DT) 
VALUES ('E07', 'Ananya Roy', NULL, 'G02', 'F', '99 Salt Lake', 'Kolkata', 'West Bengal', '700091', 35000, '2018-01-01');

INSERT INTO EMPLOYEE (EMP_CODE, EMP_NAME, DEPT_CODE, DESIG_CODE, SEX, ADDRESS, CITY, STATE, PIN, BASIC, JN_DT) 
VALUES ('E08', 'John Doe', NULL, 'G04', 'M', '22 Pine St', 'Mumbai', 'Maharashtra', '400002', 15000, '2014-09-14');

INSERT INTO EMPLOYEE (EMP_CODE, EMP_NAME, DEPT_CODE, DESIG_CODE, SEX, ADDRESS, CITY, STATE, PIN, BASIC, JN_DT) 
VALUES ('E09', 'Meera Nair', NULL, 'G02', 'F', '77 MG Road', 'Kochi', 'Kerala', '682016', NULL, '2020-07-19');

INSERT INTO EMPLOYEE (EMP_CODE, EMP_NAME, DEPT_CODE, DESIG_CODE, SEX, ADDRESS, CITY, STATE, PIN, BASIC, JN_DT) 
VALUES ('E10', 'Rajesh Kumar', NULL, 'G05', 'M', '88 Station Rd', 'Patna', 'Bihar', '800001', NULL, '2019-02-11');

-- 5. Find the rows with unassigned DEPT_CODE

SELECT * FROM EMPLOYEE WHERE DEPT_CODE IS NULL;

-- 6. Find the rows with BASIC equal to zero

SELECT * FROM EMPLOYEE WHERE BASIC = 0;

/*7. Find the rows with unassigned Basic [note down the difference between the results
obtained in Q.6 and Q.7]*/

SELECT * FROM EMPLOYEE WHERE BASIC IS NULL;

-- 8. Find the average basic of the employees.

SELECT AVG(BASIC) AS AVERAGE_BASIC FROM EMPLOYEE;

-- 9. Replace the BASIC with 0 for the rows with unassigned Basic.

UPDATE EMPLOYEE SET BASIC = 0 WHERE BASIC IS NULL;

-- 10. Again, find the average Basic. (Note the difference of result obtained in Q.8 &amp; Q.10.)

SELECT AVG(BASIC) AS AVERAGE_BASIC FROM EMPLOYEE;

-- 11. Delete the rows with unassigned DEPT_CODE.

DELETE FROM EMPLOYEE WHERE DEPT_CODE IS NULL;

/*12. Say, Net pay of an employee= Basic+HRA+DA where HRA is 50% of the Basic and
DA is 40% of Basic. Show the employee name and Net pay for all employees.*/

SELECT EMP_NAME, (BASIC + (0.5 * BASIC) + (0.4 * BASIC)) AS NET_PAY FROM EMPLOYEE;

/*13. Show the EMP_NAME and BASIC in the ascending order of DEPT_CODE. The
employee name must appear in uppercase.*/

SELECT UPPER(EMP_NAME) AS EMP_NAME, BASIC FROM EMPLOYEE ORDER BY DEPT_CODE ASC;

-- 14. Find the employees who have joined after 1 st January 2010.

SELECT * FROM EMPLOYEE WHERE JN_DT > '2010-01-01';
-- OR
-- SELECT * FROM EMPLOYEE WHERE JN_DT > '2020-01-01';

-- 15. Find, how many employees have joined in the month of January?

SELECT COUNT(*) AS January_Joinees FROM EMPLOYEE WHERE EXTRACT(MONTH FROM JN_DT) = 1;

-- 16. Find the maximum and minimum Basic.

SELECT MAX(BASIC) AS MAXIMUM_BASIC, MIN(BASIC) AS MINIMUM_BASIC FROM EMPLOYEE;

-- 17. Find how many Female employees are there?

SELECT COUNT(*) AS Female_Employee_Count FROM EMPLOYEE WHERE SEX = 'F';

-- 18. Replace CITY with existing value converted into uppercase for all rows.

UPDATE EMPLOYEE SET CITY = UPPER(CITY);

-- 19. Find in how many different cities various employees are residing?

SELECT COUNT(DISTINCT CITY) AS CITY_COUNT FROM EMPLOYEE;

/*20. Display the employee information in the ascending order of DEPT_CODE and with
in a Department, it should be in the descending order of BASIC.*/

SELECT * FROM EMPLOYEE ORDER BY DEPT_CODE ASC, BASIC DESC;