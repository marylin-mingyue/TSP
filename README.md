# TSP
Traditional Graph Theory Method and Intelligent Optimization Method （Approximate Method）include Local Search (Heuristic Algorithm，Simulated Annealing, Tabu Search),from an icpc beginner and a researcher perspective, include well-constructed code and in-detail annotation, also been visualized.


## Quick Start

- [Introduction to TSP](#introduction-to-TSP)
  - [Promblem Restatement](#Problem-Restatement)
  - [Overview of Algorithms](#Overview-of-the-Algorithms)
  - [Performance Analysis](#Performance-Analysis)


## introduction-to-TSP

In the world of "The theorem of computation complexity", there has four types of problem.

1. Polynomial Problem (P): Problems that can be solved in polynomial time.
2. Nondeterministic Polynominal Problem (NP) : Problems that can be proved true or false in polynominal time, but could not determine to solve in  polynomial time.
   note : NP problem is not the complement of the P problem, as "N" is Nondeterministic instead of "Not"

3. NP-Complete (NPC) :
  （1） This is a NP problem
   (2) All NP problem can be reduced to it in Polynominal time

4. NP-Hard (NPH):
   Not necessary to be NP Problem.

Discribe them in a graph:

<img width="154" height="234" alt="Untitled Diagram drawio (1)" src="https://github.com/user-attachments/assets/d039787c-bfaa-428a-9d19-cbff93358773" />


## Problem-Restatement

 Traveling Salesperson Problem

Given a list of cities and the distances between each pair of cities, the TSP seeks to find a Hamiltonian cycle (a cycle that visits each vertex exactly once) with the minimum total distance. 

## Overview-of-the-Algorithms


| Type | Algorithm | Code |
|---|---|---|
| heuristics Algorithm | Construction Algorithm: Insertation,<br>Improvement : First-improve, best-improve,<br>Operator : 2-Exchange, 2-Opt | [code](https://github.com/marylin-mingyue/TSP/blob/main/TSP.cpp) |
| Dynamic Programming | State Compression Dynamic Progrmming | [code](https://github.com/marylin-mingyue/TSP/blob/main/TSP_dp.cpp)




## Performance-Analysis

<img width="871" height="658" alt="截屏2025-08-01 下午3 22 02" src="https://github.com/user-attachments/assets/66fb97f6-d725-4eed-9270-d70c2628a3a8" />

[code](https://github.com/marylin-mingyue/TSP/blob/main/vis.py)

