# flight-management-system



This project implements a Flight Records Management System using an array of structures in C++. Each record represents a flight with attributes like flight name, ID, capacity, arrival and departure times, class (VIP, VVIP, public), and more. Records are always kept sorted based on a unique key (flight ID and arrival time).

#### Features
- Insert or update flight records.
- Delete a record by flight ID.
- Get the total number of flights.
- Check if the list is empty or full.
- Update flight status (delay, on-time, cancelled) and delay time.
- Find the flight with the longest stay (arrival - departure time).
- Remove duplicate records, keeping the one with the least delay.
- Perform set operations on flight lists:
  - Union: Merge two lists, retaining entries from the first list in case of duplicates.
  - Intersection: Common records with the least delay.
  - Difference: Flights in the first list but not in the second.
  - Symmetric Difference: Flights unique to each list.

#### Usage
- Clone the repository.
- Compile and run the program with a C++ compiler.
- Use the menu-driven interface to perform operations.

Contributions are welcome!
