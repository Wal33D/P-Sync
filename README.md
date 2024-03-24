# **Parallel Pi Calculator (ParallelPiCalculator)** 🎯

###### **`ParallelPiCalculator`** is a multithreaded application that estimates the value of π (Pi) 🥧 using the Monte Carlo simulation method. This project not only serves as a practical implementation of parallel computing concepts but also as an educational tool 📚 to explore the intersection of randomness 🎲 and precision 🔍 in computational mathematics.

## **Understanding the Monte Carlo Simulation for π Calculation**

The Monte Carlo simulation method is a fascinating approach that uses randomness to achieve precision. By scattering random points across a square with an inscribed circle, and calculating the ratio of points that fall inside the circle to the total number of points, we can estimate the value of π. This process is not just about computing π but also about understanding the power of parallel computing and process synchronization.

### **The Formula** 📐

The formula used for π calculation through Monte Carlo simulation is surprisingly straightforward:

π ≈ 4 × (number of points in circle / total number of points)

This ratio approximates π because it reflects the ratio of the circle's area to the square's area.

### **Parallel Computing and Process Synchronization** 💻

Implementing this simulation in a multithreaded environment demonstrates the importance of process synchronization in parallel computing. Each thread generates random points, determines whether they fall within the circle, and updates a shared global count, `circleCount`, of all points that do. Mutex locks 🔒 are used to prevent race conditions, ensuring accurate and consistent updates to `circleCount`.

## **How to Compile and Run** 🛠️

This section covers the necessary steps to compile and run the `ParallelPiCalculator` application.

### **Prerequisites**

- GCC compiler
- pthreads library for thread management

### **Compilation**

Use the provided Makefile for compilation by running:

```bash
make
```

This command compiles the source code into an executable named `pSync`.

### **Execution**

Run the application with:

```bash
./pSync
```

## **Educational Essence** 📘

This project is more than just a programming challenge; it's a lesson in mathematical simulations and the intricacies of parallel computing. It demonstrates how abstract mathematical concepts can have practical applications in computing, providing a deeper appreciation for both theory and practice in computer science.

## **Key Takeaways**

- **Monte Carlo Simulation**: A powerful technique using randomness to achieve precise outcomes, bridging probability and deterministic calculation.
- **π Calculation**: An excellent application of the Monte Carlo method, highlighting simple principles to solve complex mathematical problems.
- **Parallel Computing**: Explores the challenges and solutions of executing multiple threads in tandem, emphasizing the importance of synchronization for data consistency.

By sharing this exploration, the aim is to illuminate the rich interplay between mathematics and computing, showcasing the practical applications of abstract concepts.
