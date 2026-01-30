# Mini-AI-Infrastructure-Simulator-C-
This project is a C++ mini–AI infrastructure simulation designed to demonstrate core object-oriented and systems-level design patterns commonly used in AI infrastructure, compute backends, and large-scale frameworks.
It focuses on clean architecture, resource abstraction, and safe ownership, rather than ML algorithms themselves.

Goals:
Practice real-world C++ OOP patterns
Model AI infrastructure components (GPU, TPU, storage, clusters)
Demonstrate safe resource management
Prepare for AI infrastructure / systems engineering roles

Key Concepts Demonstrated:
Core C++ / OOP
   Abstract base classes and interfaces
   Polymorphism with virtual functions
   Virtual destructors
   Encapsulation and access control
   Namespaces for modular architecture
Resource Management
   RAII using std::unique_ptr
   Ownership transfer with move semantics
   Copy and move constructors/assignments (Rule of 5)
   Static members for global resource tracking
Architecture Patterns
   Composition over inheritance
   Manager classes (GPUManager)
   Compute abstraction via ComputeResource
   Cluster-style execution model
   
ARCHITECTURE OVERVIEW 
   +-------------+
   | GPUManager  |
   +-------------+
   | vector<GPU> |
   +-------------+
          |
          | manages
          v
        +-----+
        | GPU |
        +-----+

   +--------------+
   | ModelTrainer |
   +--------------+
   | uses Compute |
   +--------------+

   +--------------------+
   | ComputeResource    |<-----+
   +--------------------+      |
   | compute()          |      |
   +--------------------+      |
          ^                     |
          |                     |
      +-------+            +--------+
      | GPU   |            | TPU    |
      +-------+            +--------+

   +------------------------------+
   | Cluster                      |
   +------------------------------+
   | vector<ComputeResource>      |
   +------------------------------+

Error Handling
   Exceptions for invalid states
   Status-style validation helpers
   Project Structure
Resources namespace
   Storage interfaces (Disk, Memory)
   ComputeResource abstraction
   Cluster execution system
AIInfra namespace
   GPU and GPUManager
   Model, Trainer, Inspector
   Tensor with full copy/move semantics
