---
### **Practice Problems (Mid 1)**

1.  A teacher is organizing a quiz competition and wants to arrange the students' scores in ascending order so that she can easily see the lowest to highest scores. Instead of using loops, she decides to use a recursive approach to implement Bubble Sort. Write a recursive function that takes an array of integers (students' scores) and sorts them using **Bubble Sort** logic.

2.  Calculate total paths in a maze from 0,0 to 3,3 using recursion.

3.  Find the middle node of a singly linked list recursively.

4.  Imagine you are building an online bookstore application where customers can browse and purchase books. The application allows users to view book details, including the title and author, before making a purchase. Write a program to display book title with author name. (Use **copy constructor** and **destructor**).

5.  Build a system to analyze the grades of students in a school. The grades are recorded in a list, and your goal is to implement a program that performs various operations related to student grades.
    * **Sort Grades:** Implement the `sort_grades` method of the `GradeAnalyzer` class to sort the grades in ascending order.
    * **Grade Lookup:** Implement the `lookup_grade` method using **binary search** (Use the `sort_grades` method defined in part A) to look up the grade of a specific student given their ID.
    * **Grade Distribution:** Implement the `grade_distribution` method to analyze the distribution of grades and count the number of students in each grade range.

6.  Given an array of integers, write a recursive function to count the total number of zeros appearing in all the integers of the array.
    * **Example:**
        * **Input:** `[102, 500, 2040, 70007]`
        * **Count zeros in each number:**
            * 102 -> 1 zero
            * 500 -> 2 zeros
            * 2040 -> 2 zeros
            * 70007 -> 3 zeros
        * **Total zeros** = 1 + 2 + 2 + 3 = 8