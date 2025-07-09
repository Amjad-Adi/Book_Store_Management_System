# Book_Store_Management_System(10/10)

![image](https://github.com/user-attachments/assets/ed1b2e5e-4e95-4351-a397-da832a609cf0)

This is a C-based Book Store Management System that allows users to manage a catalog of books stored in a file.

 The program supports adding, removing, searching, printing, and saving books with their name, bin number (ID), and price.

Books are stored in three parallel arrays:
- `char names[MAXSIZE][NAMESIZE]` for names  
- `int bins[MAXSIZE]` for bin numbers  
- `double prices[MAXSIZE]` for prices  

The book records are maintained in sorted order based on bin numbers using binary search for efficient lookup.
🖥️ User Menu
Upon execution, the program displays the following menu:

mathematica
Copy
Edit
Please Select an Operation <1-5>:
1- Add a Book
2- Remove a Book
3- Search for a Book
4- Print Book List
5- Exit system
Choose an operation by entering the corresponding number.

💡 Features
✅ Load book data from a text file

✅ Add new book (bin number must be unique)

✅ Remove book by bin number

✅ Search for a book by bin number (using binary search)

✅ Display all books

✅ Save changes back to books.txt

🧠 Implementation Highlights
Global variables are used for convenience with user input (enteredId, cost)

Binary Search (binarySearch) is used for efficient lookups

Sorted insertion ensures books remain ordered by bin number

File I/O: uploadDataFile reads from books.txt, and updateDataFile writes to it

Maximum capacity: 100 books
