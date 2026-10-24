```
```

# Engineering Course Projects

A collection of projects I built to apply the core mathematics and computing courses of my engineering degree at the **University of Ghana, Faculty of Engineering Sciences**.

Each project uses one realistic engineering problem to cover the whole syllabus of a course. The problems include a projectile in flight, a noisy communication link, a circuit board, a digital logic unit, a sensor signal chain and a binary search tree. Every notebook starts with a project description, a problem statement and a table that maps course topics to sections. Results are computed in code and cross-checked against a second method: a formula, a numerical solver, a library function or brute force.

## Projects

| Course                                     | Project                                                                                                                           | Built with                  | Open                                                                                                                                                                                                                                |
| ------------------------------------------ | --------------------------------------------------------------------------------------------------------------------------------- | --------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| SENG 101 – Calculus I                     | [Projectile Motion with Air Resistance](Calculus/Projectile_Motion_Calculus_Project.ipynb)                                         | Python, SymPy, NumPy, SciPy | [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/AdikaNathaniel/School_Projects/blob/main/Calculus/Projectile_Motion_Calculus_Project.ipynb)                    |
| SENG 201 – Linear Algebra                 | [Electrical Circuit Analysis with Linear Algebra](Linear_Algebra/Circuit_Analysis_Linear_Algebra_Project.ipynb)                    | Python, NumPy               | [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/AdikaNathaniel/School_Projects/blob/main/Linear_Algebra/Circuit_Analysis_Linear_Algebra_Project.ipynb)         |
| SENG 202 – Differential Equations         | [RLC Circuits and Signal Filtering](Differential_Equations/RLC_Circuits_Signal_Filtering_Project.ipynb)                            | Python, SymPy, NumPy, SciPy | [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/AdikaNathaniel/School_Projects/blob/main/Differential_Equations/RLC_Circuits_Signal_Filtering_Project.ipynb)   |
| SENG 302 – Statistics for Engineers       | [Statistical Analysis of a Noisy Digital Communication Link](Statistics_For_Engineers/Communication_Link_Statistics_Project.ipynb) | Python, NumPy, SciPy        | [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/AdikaNathaniel/School_Projects/blob/main/Statistics_For_Engineers/Communication_Link_Statistics_Project.ipynb) |
| CPEN 213 – Discrete Mathematics           | [Digital Logic Circuit Designer](Discrete_Mathematics/Digital_Logic_Discrete_Math_Project.ipynb)                                   | Python (standard library)   | [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/AdikaNathaniel/School_Projects/blob/main/Discrete_Mathematics/Digital_Logic_Discrete_Math_Project.ipynb)       |
| CPEN 204 – Data Structures and Algorithms | [Binary Search Tree Traversals](Data_Structures_Algorithms/)                                                                       | C++11                       | see [build steps](#c-project)                                                                                                                                                                                                        |

---

### SENG 101 – Calculus I: Projectile Motion with Air Resistance

Models a projectile slowed by air drag as a vector function, then answers engineering questions about its flight: how high it goes, where it lands and how far it travels.

- **Limits and continuity:** terminal velocity, recovering the drag-free parabola, behaviour at impact
- **Differentiation:** velocity and acceleration, peak time from a logarithmic formula, best launch angle
- **Rolle's theorem and the Mean Value Theorem:** proving that a highest point exists
- **Leibniz's rule:** higher derivatives, and how sensitive the range is to drag
- **Trapezium and Simpson's rules:** written from scratch for path length and area, with error analysis
- **Systems of equations and matrices:** estimating gravity from noisy data
- **Inequalities:** finding launch angles that clear a wall and land in a target zone

### SENG 201 – Linear Algebra: Electrical Circuit Analysis

Analyses a small circuit board (DC network, AC filter, LED indicator, amplifier) before it is built.

- **Systems of linear equations:** Kirchhoff's laws as matrices, solved by Gaussian elimination, Cramer's rule and the inverse
- **Determinants:** when a unique solution exists, and counting spanning trees of the circuit
- **Vector spaces, subspaces and orthogonality:** allowed currents as a null space, Tellegen's power balance, Gram–Schmidt projection to clean noisy measurements
- **Eigenvalues and eigenvectors:** whether a circuit oscillates or settles, and resonant modes of coupled circuits
- **Linear transformations:** cascaded two-port stages as matrix products
- **Complex numbers, trigonometry, exp/log, binomial theorem, inequalities:** AC phasors, capacitor charging, amplifier distortion and safe component values

### SENG 202 – Differential Equations: RLC Circuits and Signal Filtering

Designs the front end of a sensor system whose signal is corrupted by mains hum, noise and clock interference.

- **First- and second-order ODEs:** RC switching, damping and resonance in RLC circuits
- **Initial-value problems:** exact SymPy solutions, each checked against a numerical solver
- **Laplace transforms:** switches, pulses, impulses, transfer functions, poles and convolution
- **Systems of ODEs:** phase portraits and a two-stage filter
- **Series solutions:** a circuit with a time-varying capacitor (Airy equation)
- **Fourier series and transforms:** square-wave harmonics, a tuned filter and noise removal
- **Boundary-value problems and PDEs:** a leaky cable, wire delay (diffusion equation) and pulse reflections (wave equation)

### SENG 302 – Statistics for Engineers: Noisy Communication Link

Simulates a digital communication link and analyses it statistically from end to end.

- **Probability and random variables:** Poisson packet arrivals, exponential gaps, binomial bit errors, normal noise
- **Conditional probability and Bayes' theorem:** the optimal receiver decision rule
- **Joint distributions, covariance and correlation:** a two-antenna receiver
- **Central limit theorem and sampling distributions:** why channel noise is normal
- **Estimation and hypothesis testing:** confidence intervals, z- and t-tests, Type I/II errors, power, ROC curve
- **Regression:** error rate against signal-to-noise ratio
- **Applications:** quality control and process control charts, and a statistical speech detector

### CPEN 213 – Discrete Mathematics: Digital Logic Circuit Designer

Designs, minimises and proves correct the logic for a small arithmetic and safety unit: a majority voter, adders, a parity generator and a Gray-code encoder.

- **Sets, Venn diagrams, power sets and complements:** inputs and Boolean functions as sets
- **Propositional logic and truth tables:** circuit specifications and the laws of logic
- **Functions and relations:** injective and surjective circuits, equivalence relations, partial orders
- **Counting, permutations and combinations:** design-space size, minimal circuits, the pigeonhole principle
- **Recursion and recurrence relations:** Gray codes, recursive adders and multiplexers, cost and delay
- **Proof techniques:** induction (the adder is correct for every word size), contradiction, constructive proof
- **Generating functions:** parity codes, crosstalk-free bus codes, chip combinations

### CPEN 204 – Data Structures and Algorithms: Binary Search Tree Traversals

A C++ lab implementing a binary search tree and analysing it with different traversal strategies (handout: [CPEN204_Lab_Two.pdf](Data_Structures_Algorithms/CPEN204_Lab_Two.pdf)).

- BST insertion with nodes and pointers
- Recursive in-order, pre-order and post-order traversals, plus queue-based level-order traversal
- Iterative traversals using an explicit stack (no recursion)
- Tree metrics: height, node count, leaf count and an O(n) balance check
- Rebuilding a tree from its pre-order and in-order sequences
- Each output is compared automatically with hand-worked predictions

---

## Repository structure

```
.
├── Calculus/
│   ├── Content.txt
│   └── Projectile_Motion_Calculus_Project.ipynb
├── Linear_Algebra/
│   └── Circuit_Analysis_Linear_Algebra_Project.ipynb
├── Differential_Equations/
│   └── RLC_Circuits_Signal_Filtering_Project.ipynb
├── Statistics_For_Engineers/
│   └── Communication_Link_Statistics_Project.ipynb
├── Discrete_Mathematics/
│   └── Digital_Logic_Discrete_Math_Project.ipynb
└── Data_Structures_Algorithms/
    ├── CPEN204_Lab_Two.pdf
    ├── bst.h
    ├── bst.cpp
    └── main.cpp
```

## How to run

### Notebooks

Click an **Open in Colab** badge above, then choose **Runtime → Run all**. Every library the notebooks use (NumPy, SciPy, SymPy, Matplotlib) is already installed in Google Colab, so no setup is needed. The notebooks are stored without outputs, so the results and plots are produced when you run them. Random simulations use fixed seeds, so the results are repeatable.

### C++ project

Compile with any C++11 (or later) compiler:

```bash
cd Data_Structures_Algorithms
g++ -std=c++11 -Wall -Wextra -o tree_lab main.cpp bst.cpp
./tree_lab
```

## Skills demonstrated

- Turning course theory into working, self-checking code
- Mathematical modelling of engineering systems: mechanics, circuits, signals, communications and digital logic
- Symbolic and numerical computation with Python (SymPy, NumPy, SciPy) and data visualisation with Matplotlib
- Algorithm design and memory management in C++
- Clear technical writing: problem statements, derivations, proofs and conclusions

