# Overview

This repository contains two projects developed for the Data Structures and Algorithms I and II courses. They focus on low-level memory management, binary file manipulation, and custom data structure implementation in C.

# Part I: Data Structures - Stack Implementation

This module aims to apply core concepts of Stack data structures. A custom Stack was implemented from scratch to handle the following data manipulations:
- Insertion (Push)
- Removal (Pop)
- State Verification (Peek/IsEmpty)

# Part II: Binary File Management - ENEM Participants

This module implements a custom database engine to store, retrieve, and manage records in a binary file using a structured field and record architecture. It features a fully functional CRUD (Create, Read, Update, Delete) system with a dynamic space reclamation approach for logically deleted records.

## Core Technical Features:
- Developed entirely in **C**.
- Manipulates large datasets (ENEM - Brazilian National Exam participants) using low-level file I/O operations (`fread`, `fwrite`, `fseek`).
- Implements concepts of Disk Pages, Fixed/Variable-length fields, and Relative Record Numbers (RRN).
- Configured with Fixed Record Sizes (80 bytes) and Fixed Disk Pages (16,000 bytes).
- **Memory Padding:** When there is no more data to be written, the remainder of the disk page is filled with garbage padding (the `@` character) to maintain structural integrity.

## Header Record Architecture
The header record occupies an entire disk page (16,000 bytes) and contains metadata about the binary file state:

* **status:** Indicates data file consistency (e.g., corrupted due to power loss or crashes). `0` = inconsistent, `1` = consistent. (Size: 1-byte char).
* **topoPilha (Stack Top):** Stores the RRN of the last logically deleted record, acting as the head of the reclaimed space stack. `-1` if empty. (Size: 4-byte int).
* **Tags & Descriptions (Campo 1 to 5):** Metadata storing specific field identifiers (tags) and their full string descriptions (e.g., 'ENEM participant registration number', 'Math score').

**Graphical Representation of the Header Record:**
The active header record size is 285 bytes, structured as follows:
**[IMAGE]**

## Data Records Architecture
Each data record stores participant information based on real and synthetic ENEM datasets. 

**Fixed-length fields: 22 bytes total**
* `nroInscricao` (Registration ID) – integer (4 bytes)
* `nota` (Score) – double precision (8 bytes)
* `data` (Date) – string format DD/MM/YYYY (10 bytes)

**Variable-length fields:**
* `cidade` (City) – dynamically sized string
* `nomeEscola` (School Name) – dynamically sized string

**Deletion Management Fields:**
* **removido (IsDeleted):** Marks if the record is active (`-`) or logically deleted (`*`). (Size: 1-byte char).
* **encadeamento (Next Available RRN):** Stores the RRN of the next logically deleted record to manage the dynamic space reclamation stack. (Size: 4-byte int).

**Graphical Representation of the Data Record:**
The total size of each data record is exactly 80 bytes:
**[IMAGE]**

## CLI Features & Commands

The application provides a Command Line Interface (CLI) to manipulate the binary data file through specific numeric commands:

* **[1] CSV to Binary Parser:** Reads raw participant data from a `.csv` file and serializes it into a structured `.bin` file.
* **[2] Full Data Retrieval:** Deserializes and prints all active records from the binary file, handling garbage padding and calculating the total number of accessed Disk Pages.
* **[3] Conditional Search:** Retrieves records that match specific search criteria (e.g., Registration ID, Date, Score).
* **[4] Direct RRN Access:** Fetches a specific record instantly using its Relative Record Number, simulating O(1) disk read complexity.
* **[5] Logical Deletion:** Removes records based on search criteria and pushes their RRN to the deleted stack for future space reclamation.
* **[6] Dynamic Insertion:** Inserts new records. If there are logically deleted records available in the stack, the engine overwrites them to prevent file fragmentation; otherwise, it appends to the end of the file.
* **[7] Field Update:** Updates specific fields of an existing record via its RRN, filling any leftover byte space with garbage padding to maintain fixed record sizes.

## Data Structures (Structs)

**Header Struct:**
Stores the constant metadata used to initialize the first disk page.
```c
typedef struct {
    char status;         // 0 = Inconsistent, 1 = Consistent
    int topoPilha;       // Stack Top for deleted RRNs
    char tagCampo1;      // Registration tag
    char tagCampo2;      // Score tag
    char tagCampo3;      // Date tag
    char tagCampo4;      // City tag
    char tagCampo5;      // School name tag
    char desCampo1[max]; 
    char desCampo2[max]; 
    char desCampo3[max]; 
    char desCampo4[max]; 
    char desCampo5[max]; 
} Cabecalho;
```

**Record Struct:**
Used to temporarily hold deserialized data in RAM before writing it back to the disk.

typedef struct {
    char removido;       // '*' if deleted, '-' if active
    int encadeamento;    // Next deleted RRN in the stack
    int nroInscricao;
    double nota;
    char data[10];
    char cidade[max];
    char nomeEscola[max];
    int contCity;
    int contSchool;
} Registro;

## Conclusion
This project provided deep, hands-on experience with core C programming concepts, including pointer manipulation, memory allocation, binary serialization, and low-level disk I/O optimization using custom data structures.
