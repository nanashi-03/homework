/*1. From the EMP table show the minimum, maximum and average basic for each
department (show dept. Code).*/

SELECT DEPT_CODE,
       MIN(BASIC) AS MIN_BASIC, 
       MAX(BASIC) AS MAX_BASIC, 
       AVG(BASIC) AS AVG_BASIC
FROM EMPLOYEE
GROUP BY DEPT_CODE;

-- 2. Find the number of female employees in each department (show dept. Code).

SELECT DEPT_CODE, COUNT(*) AS FEMALE_COUNT
FROM EMPLOYEE
WHERE SEX = 'F'
GROUP BY DEPT_CODE;

-- 3. Find the city wise no. of employees for each department (show dept. Code).

SELECT DEPT_CODE, CITY, COUNT(*) AS EMP_COUNT
FROM EMPLOYEE
GROUP BY DEPT_CODE, CITY;

/*4. Show the designation wise no of employees who have joined in the year 2000 in each
department. The listing should appear in the ascending order of no. of employees.*/

SELECT DEPT_CODE, DESIG_CODE, COUNT(*) AS EMP_COUNT
FROM EMPLOYEE
WHERE TO_CHAR(JN_DT, 'YYYY') = '2010'
GROUP BY DEPT_CODE, DESIG_CODE
ORDER BY EMP_COUNT ASC;

/*5. Find the department code wise total basic of male employees only for the departments
for which such total is more than 50,000 and the listing should appear in the
descending order of total basic.*/

SELECT DEPT_CODE, SUM(BASIC) AS TOTAL_BASIC
FROM EMPLOYEE
WHERE SEX = 'M'
GROUP BY DEPT_CODE
HAVING SUM(BASIC) >= 50000
ORDER BY TOTAL_BASIC DESC;

-- 6. Show the employee name, Designation description and basic for all employees.

SELECT E.EMP_NAME, D.DESIG_NAME, E.BASIC
FROM EMPLOYEE E
JOIN DESIGNATION D ON E.DESIG_CODE = D.DESIG_CODE;

/*7. Show the employee name, Designation description, Department Name &amp; Basic for all
employees.*/

SELECT E.EMP_NAME, D.DESIG_NAME, DEPT.DEPT_NAME, E.BASIC
FROM EMPLOYEE E
JOIN DESIGNATION D ON E.DESIG_CODE = D.DESIG_CODE
JOIN DEPARTMENT DEPT ON E.DEPT_CODE = DEPT.DEPT_CODE;

-- 8. Find the department Codes in which no employee works.

SELECT DEPT_CODE 
FROM DEPARTMENT
WHERE DEPT_CODE NOT IN (SELECT DISTINCT DEPT_CODE FROM EMPLOYEE WHERE DEPT_CODE IS NOT NULL);

-- 9. Find the department names where at least one employee works.

SELECT DEPT_NAME 
FROM DEPARTMENT 
WHERE DEPT_CODE IN (SELECT DISTINCT DEPT_CODE FROM EMPLOYEE);

-- 10. Find the department names where at least 10 employees work.

SELECT DEPT.DEPT_NAME
FROM DEPARTMENT DEPT
JOIN EMPLOYEE E ON DEPT.DEPT_CODE = E.DEPT_CODE
GROUP BY DEPT.DEPT_NAME
HAVING COUNT(E.EMP_CODE) >= 10;

-- 11. Find the department code in which employee with highest Basic works.

SELECT DEPT_CODE 
FROM EMPLOYEE 
WHERE BASIC = (SELECT MAX(BASIC) FROM EMPLOYEE);

-- 12. Find the Designation description of the employee with highest basic.

SELECT DESIG_NAME 
FROM DESIGNATION 
WHERE DESIG_CODE = (SELECT DESIG_CODE FROM EMPLOYEE WHERE BASIC = (SELECT MAX(BASIC) FROM EMPLOYEE));

-- 13. Find the no. of managers in each department.

SELECT E.DEPT_CODE, COUNT(*) AS MANAGER_COUNT
FROM EMPLOYEE E
JOIN DESIGNATION D ON E.DESIG_CODE = D.DESIG_CODE
WHERE D.DESIG_NAME = 'Manager'
GROUP BY E.DEPT_CODE;

-- 14. Find the maximum basic from EMP table without using MAX().

SELECT BASIC FROM EMPLOYEE 
WHERE BASIC NOT IN (SELECT E1.BASIC FROM EMPLOYEE E1 JOIN EMPLOYEE E2 ON E1.BASIC < E2.BASIC)
LIMIT 1;

-- 15. Find the minimum basic from EMP table without using MIN().

SELECT BASIC FROM EMPLOYEE 
WHERE BASIC NOT IN (SELECT E1.BASIC FROM EMPLOYEE E1 JOIN EMPLOYEE E2 ON E1.BASIC > E2.BASIC)
LIMIT 1;

/*16. Find the name of the department with highest total basic. Do the same for highest
average basic and maximum no. of employee. (FIX) */

SELECT D.DEPT_NAME 
FROM DEPARTMENT D 
JOIN EMPLOYEE E ON D.DEPT_CODE = E.DEPT_CODE
GROUP BY D.DEPT_NAME 
ORDER BY SUM(E.BASIC) DESC 
LIMIT 1;

SELECT D.DEPT_NAME 
FROM DEPARTMENT D 
JOIN EMPLOYEE E ON D.DEPT_CODE = E.DEPT_CODE
GROUP BY D.DEPT_NAME 
ORDER BY AVG(E.BASIC) DESC 
LIMIT 1;

SELECT D.DEPT_NAME 
FROM DEPARTMENT D 
JOIN EMPLOYEE E ON D.DEPT_CODE = E.DEPT_CODE
GROUP BY D.DEPT_NAME 
ORDER BY COUNT(E.EMP_CODE) DESC 
LIMIT 1;

/*17. Insert same rows into EMP table with designation code not existing in
DESIGNATION table.*/

INSERT INTO EMPLOYEE (EMP_CODE, EMP_NAME, DEPT_CODE, DESIG_CODE, SEX, BASIC, JN_DT) 
VALUES ('E99', 'Ghost Employee', 'D01', 'G99', 'M', 25000, '01-01-23');

-- 18. Delete the rows from EMP table with invalid DESIG_CODE.

DELETE FROM EMPLOYEE 
WHERE DESIG_CODE NOT IN (SELECT DESIG_CODE FROM DESIGNATION);

/*19. Find the name of the female employees with basic greater than the average basic of
their respective department.*/

SELECT E1.EMP_NAME 
FROM EMPLOYEE E1
WHERE E1.SEX = 'F' 
AND E1.BASIC > (
    SELECT AVG(E2.BASIC) 
    FROM EMPLOYEE E2 
    WHERE E2.DEPT_CODE = E1.DEPT_CODE
);

-- 20. Find the number of female managers.

SELECT COUNT(*) AS FEMALE_MANAGERS
FROM EMPLOYEE E
JOIN DESIGNATION D ON E.DESIG_CODE = D.DESIG_CODE
WHERE E.SEX = 'F' AND D.DESIG_NAME = 'Manager';