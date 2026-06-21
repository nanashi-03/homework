1.Create the following tables :
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
DESIG_DESC char(20)
Primary key is DESIG_CODE
Tablename : DEPARTMENT
Structure :
DEPT_CODE char(16)
DEPT_NAME char(20)
Primary key is DEPT_CODE.

-> CREATE TABLE DEPARTMENT (
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

2. Display the structure of each table.

-> DESC DEPARTMENT;

DESC DESIGNATION;

DESC EMPLOYEE;

3. Insert few rows in each table.

-> INSERT ALL
    INTO DEPARTMENT VALUES ('D001', 'Personnel')
    INTO DEPARTMENT VALUES ('D002', 'Production')
    INTO DEPARTMENT VALUES ('D003', 'Purchase')
    INTO DEPARTMENT VALUES ('D004', 'Finance')
    INTO DEPARTMENT VALUES ('D005', 'Research')
SELECT * FROM DUAL;

INSERT ALL
    INTO DESIGNATION VALUES ('DS001', 'Manager')
    INTO DESIGNATION VALUES ('DS002', 'Executive')
    INTO DESIGNATION VALUES ('DS003', 'Officer')
    INTO DESIGNATION VALUES ('DS004', 'Clerk')
    INTO DESIGNATION VALUES ('DS005', 'Helper')
SELECT * FROM DUAL;

INSERT ALL
    INTO EMPLOYEE VALUES (
        'E001',
        'Amit Sharma',
        'D001',
        'DS001',
        'M',
        '12 Park Street',
        'Kolkata',
        'West Bengal',
        '700001',
        75000,
        '2018-05-10'
    )

    INTO EMPLOYEE VALUES (
        'E002',
        'Sneha Roy',
        'D002',
        'DS002',
        'F',
        '45 Lake Road',
        'Kolkata',
        'West Bengal',
        '700029',
        55000,
        '2020-07-15'
    )

    INTO EMPLOYEE VALUES (
        'E003',
        'Rahul Das',
        'D003',
        'DS003',
        'M',
        '78 MG Road',
        'Delhi',
        'Delhi',
        '110001',
        42000,
        '2019-11-01'
    )

    INTO EMPLOYEE VALUES (
        'E004',
        'Priya Sen',
        'D004',
        'DS004',
        'F',
        '23 Salt Lake',
        'Kolkata',
        'West Bengal',
        '700091',
        28000,
        '2021-03-20'
    )

    INTO EMPLOYEE VALUES (
        'E005',
        'Karan Mehta',
        'D005',
        'DS005',
        'M',
        '90 Nehru Nagar',
        'Mumbai',
        'Maharashtra',
        '400001',
        20000,
        '2022-01-05'
    )

SELECT * FROM DUAL;

4. In EMP table insert few rows without DEPT_CODE and BASIC.

-> INSERT INTO EMPLOYEE (
    EMP_CODE,
    EMP_NAME,
    DEPT_CODE,
    DESIG_CODE,
    SEX,
    ADDRESS,
    CITY,
    STATE,
    PIN,
    JN_DT
)
VALUES (
    'E006',
    'Riya Ghosh',
    'D002',
    'DS004',
    'F',
    '14 Central Ave',
    'Kolkata',
    'West Bengal',
    '700012',
    '2023-02-10'
);


INSERT INTO EMPLOYEE (
    EMP_CODE,
    EMP_NAME,
    DESIG_CODE,
    SEX,
    ADDRESS,
    CITY,
    STATE,
    PIN,
    BASIC,
    JN_DT
)
VALUES (
    'E007',
    'Arjun Nair',
    'DS005',
    'M',
    '88 Residency Road',
    'Bangalore',
    'Karnataka',
    '560001',
    56000
    '2022-09-18'
);


INSERT INTO EMPLOYEE (
    EMP_CODE,
    EMP_NAME,
    DESIG_CODE,
    SEX,
    ADDRESS,
    CITY,
    STATE,
    PIN,
    JN_DT
)
VALUES (
    'E008',
    'Neha Kapoor',
    'DS002',
    'F',
    '56 Green Park',
    'Delhi',
    'Delhi',
    '110016',
    '2021-12-01'
);

5. Find the rows with unassigned DEPT_CODE

-> SELECT * FROM EMPLOYEE WHERE DEPT_CODE IS NULL;

6. Find the rows with BASIC equal to zero

-> SELECT * FROM EMPLOYEE WHERE BASIC = 0;

7. Find the rows with unassigned Basic [note down the difference between the results
obtained in Q.6 and Q.7]

-> SELECT * FROM EMPLOYEE WHERE BASIC IS NULL;

8. Find the average basic of the employees.

-> SELECT AVG(BASIC) AS AVERAGE_BASIC FROM EMPLOYEE;

9. Replace the BASIC with 0 for the rows with unassigned Basic.

-> UPDATE EMPLOYEE SET BASIC = 0 WHERE BASIC IS NULL;

10. Again, find the average Basic. (Note the difference of result obtained in Q.8 &amp; Q.10.)

-> SELECT AVG(BASIC) AS AVERAGE_BASIC FROM EMPLOYEE;

11. Delete the rows with unassigned DEPT_CODE.

-> DELETE FROM EMPLOYEE WHERE DEPT_CODE IS NULL;

12. Say, Net pay of an employee= Basic+HRA+DA where HRA is 50% of the Basic and
DA is 40% of Basic. Show the employee name and Net pay for all employees.

-> SELECT EMP_NAME, (BASIC + (0.5 * BASIC) + (0.4 * BASIC)) AS NET_PAY FROM EMPLOYEE;

13. Show the EMP_NAME and BASIC in the ascending order of DEPT_CODE. The
employee name must appear in uppercase.

-> SELECT UPPER(EMP_NAME) AS EMP_NAME, BASIC FROM EMPLOYEE ORDER BY DEPT_CODE ASC;

14. Find the employees who have joined after 1 st January 2010.

-> SELECT * FROM EMPLOYEE WHERE JN_DT > '2010-01-01';
// SELECT * FROM EMPLOYEE WHERE JN_DT > '2020-01-01';

15. Find, how many employees have joined in the month of January?

-> SELECT COUNT(\*) AS January_Joinees FROM EMPLOYEE WHERE EXTRACT(MONTH FROM JN_DT) = 1;

16. Find the maximum and minimum Basic.

-> SELECT MAX(BASIC) AS MAXIMUM_BASIC, MIN(BASIC) AS MINIMUM_BASIC FROM EMPLOYEE;

17. Find how many Female employees are there?

-> SELECT COUNT(\*) AS Female_Employee_Count FROM EMPLOYEE WHERE SEX = 'F';

18. Replace CITY with existing value converted into uppercase for all rows.

-> UPDATE EMPLOYEE SET CITY = UPPER(CITY);

19. Find in how many different cities various employees are residing?

-> SELECT COUNT(DISTINCT CITY) AS CITY_COUNT FROM EMPLOYEE;

20. Display the employee information in the ascending order of DEPT_CODE and with
in a Department, it should be in the descending order of BASIC.

-> SELECT * FROM EMPLOYEE ORDER BY DEPT_CODE ASC, BASIC DESC;