-- 1. In an organization, number of departments exists. Each department has a name &amp; unique code. Number
-- of employees work in each department. Each employee has unique employee code. Detailed information
-- like name, address, city, basic, date of join are also stored. In a leave register for each employee leave
-- records are kept showing leave type (CL/EL/ML etc.), from-date and to-date. When an employee retires
-- or resigns then all the leave information pertaining to him are also deleted. Basic salary must be within
-- Rs.5000 to Rs.9000. A department can not be deleted if any employee record refers to it. Valid grades are
-- A/B/C. Employee name must be in uppercase only. Default value for joining date is system date.
-- Design &amp; implement the tables with necessary constraints to support the scenario depicted above.

CREATE TABLE DEPARTMENT (
    DEPT_CODE CHAR(16) PRIMARY KEY,
    DEPT_NAME VARCHAR(20) NOT NULL
);

CREATE TABLE EMPLOYEE (
    EMP_CODE CHAR(16) PRIMARY KEY,
    EMP_NAME VARCHAR(20) NOT NULL CHECK (EMP_NAME COLLATE utf8mb4_bin = UPPER(EMP_NAME)),
    DEPT_CODE CHAR(16),
    GRADE CHAR(1) CHECK (GRADE IN ('A', 'B', 'C')),
    ADDRESS VARCHAR(25),
    CITY VARCHAR(20),
    BASIC DECIMAL(10,2) CHECK (BASIC BETWEEN 5000 AND 9000),
    JN_DT DATE DEFAULT (CURDATE()),
    FOREIGN KEY (DEPT_CODE) REFERENCES DEPARTMENT(DEPT_CODE) ON DELETE RESTRICT
);

CREATE TABLE LEAVE_REGISTER (
    LEAVE_ID INT AUTO_INCREMENT PRIMARY KEY,
    EMP_CODE CHAR(16),
    LEAVE_TYPE VARCHAR(5) CHECK (LEAVE_TYPE IN ('CL', 'EL', 'ML')),
    FROM_DATE DATE,
    TO_DATE DATE,
    FOREIGN KEY (EMP_CODE) REFERENCES EMPLOYEE(EMP_CODE) ON DELETE CASCADE
);

-- Populate the tables
INSERT INTO DEPARTMENT (DEPT_CODE, DEPT_NAME) VALUES
('D001', 'SALES'),
('D002', 'HR'),
('D003', 'FINANCE'),
('D004', 'IT'),
('D005', 'MARKETING');

INSERT INTO EMPLOYEE
(EMP_CODE, EMP_NAME, DEPT_CODE, GRADE, ADDRESS, CITY, BASIC, JN_DT)
VALUES
('E001', 'RAHUL',   'D001', 'A', '12 PARK STREET',    'KOLKATA',   8500.00, '2023-01-15'),
('E002', 'PRIYA',   'D002', 'B', '45 MG ROAD',        'DELHI',     7500.00, '2023-02-10'),
('E003', 'AMIT',    'D003', 'A', '22 LAKE VIEW',      'MUMBAI',    9000.00, '2022-11-05'),
('E004', 'SNEHA',   'D004', 'C', '8 GREEN PARK',      'BENGALURU', 6000.00, '2024-03-01'),
('E005', 'VIKAS',   'D005', 'B', '16 HILL ROAD',      'CHENNAI',   7000.00, '2023-06-20'),
('E006', 'NEHA',    'D001', 'C', '90 STATION ROAD',   'KOLKATA',   5500.00, '2024-01-12'),
('E007', 'ROHIT',   'D004', 'A', '31 RIVER SIDE',     'PUNE',      8800.00, '2022-09-18'),
('E008', 'POOJA',   'D002', 'B', '55 MARKET ROAD',    'HYDERABAD', 6700.00, '2023-08-14'),
('E009', 'KARAN',   'D003', 'C', '10 TEMPLE STREET',  'JAIPUR',    5200.00, '2024-05-05'),
('E010', 'ANJALI',  'D005', 'A', '77 COLLEGE ROAD',   'LUCKNOW',   8300.00, '2023-04-22');

INSERT INTO LEAVE_REGISTER
(EMP_CODE, LEAVE_TYPE, FROM_DATE, TO_DATE)
VALUES
('E001', 'CL', '2024-01-10', '2024-01-12'),
('E001', 'EL', '2024-02-05', '2024-02-10'),
('E002', 'ML', '2024-03-15', '2024-03-20'),
('E001', 'CL', '2024-04-01', '2024-04-02'),
('E004', 'EL', '2024-04-20', '2024-04-25'),
('E004', 'ML', '2024-05-05', '2024-05-08'),
('E002', 'CL', '2024-06-10', '2024-06-11'),
('E001', 'EL', '2024-07-01', '2024-07-07'),
('E006', 'ML', '2024-08-12', '2024-08-18'),
('E010', 'CL', '2024-09-05', '2024-09-06');

-- Sir's Question - FInd the Emp with maximum leaves and minimum leaves
SELECT E.EMP_CODE, E.EMP_NAME
FROM EMPLOYEE E
JOIN LEAVE_REGISTER L ON E.EMP_CODE = L.EMP_CODE
GROUP BY E.EMP_CODE, E.EMP_NAME
HAVING SUM(DATEDIFF(L.TO_DATE, L.FROM_DATE) + 1) =
(
    SELECT MAX(TOTAL_LEAVES)
    FROM
    (
        SELECT SUM(DATEDIFF(TO_DATE, FROM_DATE) + 1) AS TOTAL_LEAVES
        FROM LEAVE_REGISTER
        GROUP BY EMP_CODE
    ) TEMP
);

SELECT E.EMP_CODE, E.EMP_NAME
FROM EMPLOYEE E
JOIN LEAVE_REGISTER L ON E.EMP_CODE = L.EMP_CODE
GROUP BY E.EMP_CODE, E.EMP_NAME
HAVING SUM(DATEDIFF(L.TO_DATE, L.FROM_DATE) + 1) =
(
    SELECT MIN(TOTAL_LEAVES)
    FROM
    (
        SELECT SUM(DATEDIFF(TO_DATE, FROM_DATE) + 1) AS TOTAL_LEAVES
        FROM LEAVE_REGISTER
        GROUP BY EMP_CODE
    ) TEMP
);

-- 2. Try to violate the constraints that you have implemented in the table &amp; note, what happens. [Try with
-- suitable INSERT/UPDATE/DELETE instruction]

INSERT INTO DEPARTMENT VALUES ('D01', 'PERSONNEL');
INSERT INTO EMPLOYEE (EMP_CODE, EMP_NAME, DEPT_CODE, GRADE, BASIC) VALUES ('E01', 'AMIT SHARMA', 'D01', 'A', 6000);

-- Violation A: Lowercase name check constraint (Fails)
INSERT INTO EMPLOYEE (EMP_CODE, EMP_NAME, DEPT_CODE, GRADE, BASIC) VALUES ('E02', 'sriya das', 'D01', 'B', 7000);
-- Error: CONSTRAINT `EMPLOYEE.EMP_NAME` failed for `assignment-3`.`EMPLOYEE`

-- Violation B: Invalid Grade (Fails)
INSERT INTO EMPLOYEE (EMP_CODE, EMP_NAME, DEPT_CODE, GRADE, BASIC) VALUES ('E03', 'RAHUL VERMA', 'D01', 'Z', 7000);
-- Error: CONSTRAINT `EMPLOYEE.GRADE` failed for `assignment-3`.`EMPLOYEE`

-- Violation C: Salary out of range (Fails)
INSERT INTO EMPLOYEE (EMP_CODE, EMP_NAME, DEPT_CODE, GRADE, BASIC) VALUES ('E04', 'DEEPA PILLAI', 'D01', 'B', 4500);
-- Error: CONSTRAINT `EMPLOYEE.BASIC` failed for `assignment-3`.`EMPLOYEE`

-- Violation D: Deleting a referenced Department (Fails)
DELETE FROM DEPARTMENT WHERE DEPT_CODE = 'D01';
-- Error: Cannot delete or update a parent row: a foreign key constraint fails

-- 3. a) create a view showing employee code, name, dcode &amp; Basic For a particular department.
-- b)Try to ensure a row into the view with valid department &amp; also with invalid ones.
-- c)Find the newly inserted row in the table From which view was created .
-- d) Try to increment basic by Rs.100/-
-- e) Check it in the original table.
-- f) Delete the view.

CREATE VIEW VW_EMP_DEPT AS 
SELECT EMP_CODE, EMP_NAME, DEPT_CODE, BASIC 
FROM EMPLOYEE 
WHERE DEPT_CODE = 'D01';

-- Valid insert (Belongs to department D01)
INSERT INTO VW_EMP_DEPT (EMP_CODE, EMP_NAME, DEPT_CODE, BASIC) 
VALUES ('E02', 'VIKRAM SINGH', 'D01', 7500);

-- Invalid insert
INSERT INTO VW_EMP_DEPT (EMP_CODE, EMP_NAME, DEPT_CODE, BASIC) 
VALUES ('E03', 'ROHAN DAS', 'D02', 8000);
-- Error : Cannot add or update a child row: a foreign key constraint fails 

SELECT * FROM EMPLOYEE WHERE EMP_CODE = 'E02';

UPDATE VW_EMP_DEPT SET BASIC = BASIC + 100 WHERE EMP_CODE = 'E02';

SELECT BASIC FROM EMPLOYEE WHERE EMP_CODE = 'E02';

DROP VIEW VW_EMP_DEPT;

-- 4. a) create a view Showing empcode, name, deptname, basic, leave type, From date &amp; to date.
-- b)Try to insert a row in the view. Check what happens?
-- c) Try to increment basic by Rs.100.
-- d) Delete the view.

CREATE VIEW VW_EMP_LEAVE_DETAILS AS
SELECT E.EMP_CODE, E.EMP_NAME, D.DEPT_NAME, E.BASIC, L.LEAVE_TYPE, L.FROM_DATE, L.TO_DATE
FROM EMPLOYEE E
JOIN DEPARTMENT D ON E.DEPT_CODE = D.DEPT_CODE
LEFT JOIN LEAVE_REGISTER L ON E.EMP_CODE = L.EMP_CODE;

INSERT INTO VW_EMP_LEAVE_DETAILS VALUES ('E05', 'KIRAN BEDI', 'PERSONNEL', 7000, 'CL', '2026-05-01', '2026-05-03');
-- Error : The target table VW_EMP_LEAVE_DETAILS of the INSERT is not insertable-into

UPDATE VW_EMP_LEAVE_DETAILS SET BASIC = BASIC + 100 WHERE EMP_CODE = 'E01';

SELECT * FROM EMPLOYEE;

DROP VIEW VW_EMP_LEAVE_DETAILS;

-- 5. a) Create a table having empcode , Name, deptname, &amp; basic From the existing tables along with the
-- records of the employee who are in a particular department (say, d1) and with a basic Rs. 7000/-
-- b) From the existing table, add the employees with the basic salary greater than or equal to 7000/-
-- c) Alter the table to add a net pay column.
-- d) Replace net pay with 1.5* Basic.
-- e) Try to remove the net net pay column.
-- [ It may require no. of steps]

CREATE TABLE NEW_EMP_LIST AS
SELECT E.EMP_CODE, E.EMP_NAME, D.DEPT_NAME, E.BASIC 
FROM EMPLOYEE E
JOIN DEPARTMENT D ON E.DEPT_CODE = D.DEPT_CODE
WHERE E.DEPT_CODE = 'D01' AND E.BASIC = 7000;

INSERT INTO NEW_EMP_LIST (EMP_CODE, EMP_NAME, DEPT_NAME, BASIC)
SELECT E.EMP_CODE, E.EMP_NAME, D.DEPT_NAME, E.BASIC
FROM EMPLOYEE E
JOIN DEPARTMENT D ON E.DEPT_CODE = D.DEPT_CODE
WHERE E.BASIC >= 7000;

ALTER TABLE NEW_EMP_LIST ADD NET_PAY DECIMAL(10,2);

UPDATE NEW_EMP_LIST SET NET_PAY = 1.5 * BASIC;

ALTER TABLE NEW_EMP_LIST DROP COLUMN NET_PAY;

-- 6. Drop all the tables that you have created .

DROP TABLE IF EXISTS LEAVE_REGISTER;
DROP TABLE IF EXISTS NEW_EMP_LIST;
DROP TABLE IF EXISTS EMPLOYEE;
DROP TABLE IF EXISTS DEPARTMENT;
DROP TABLE IF EXISTS DESIGNATION;