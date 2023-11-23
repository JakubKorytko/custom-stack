# Custom Stack

[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)](LICENSE)
![Visual Studio](https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white)
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

[![Open Source Love svg1](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](https://github.com/ellerbrock/open-source-badges/)
[![Run Super-Linter](https://github.com/JakubKorytko/custom-stack/actions/workflows/super-linter.yml/badge.svg)](https://github.com/JakubKorytko/custom-stack/actions/workflows/super-linter.yml)

## Table of Contents

- [Custom Stack](#custom-stack)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Usage](#usage)
    - [Menu](#menu)
    - [Actions](#actions)
  - [Changing the data type used in the stack](#changing-the-data-type-used-in-the-stack)
    - [Before you start](#before-you-start)
    - [Steps](#steps)
  - [Why is this an application and not a library?](#why-is-this-an-application-and-not-a-library)
  - [Contributing](#contributing)
  - [Contact](#contact)
  - [License](#license)

## Introduction

This project is a custom stack implementation in C using the Visual Studio 2022.
It allows you to create a stack of any data type you want.
It is also possible to add multiple data types and switch between them.
What is unique about this stack is that **it is implemented without using array for the stack elements**.
Instead, it uses a pointer to the previous element in the stack and a pointer to the top element.
This allows you to create a stack of any size you want without having to allocate a large array for the stack elements.

Although this project is based on the [instructions](./docs/Instructions.pdf) located in the [docs](./docs/) directory,
it has been extended with additional features to make it more user-friendly and to make it easier to add new data types.

There are some Visual Studio specific configurations in the project,
if you plan to use this project in another IDE or extend it,
see the [before you start](#before-you-start) section (the first two points).

**This project was created targeting Windows. It has not been tested on other operating systems.**

## Prerequisites

Before using the Custom Stack, make sure that you have the following prerequisites installed on your system:

- [Visual Studio 2022 (version 17.6.3 or later)](https://visualstudio.microsoft.com/vs/)
  - "Desktop development with C++" workload installed.

## Installation

1. Clone this repository to your local machine using Git,
or download the ZIP file and extract it to a directory of your choice:

    ```bash
    git clone https://github.com/JakubKorytko/custom-stack.git
    ```

1. Change to the project directory:

    ```bash
    cd custom-stack
    ```

1. Open the `custom-stack.sln` solution file in Visual Studio.

1. Build or run the project in Visual Studio:

    - **Run the project** in the Visual Studio
      - `F5` /  `Ctrl + F5` by default
      - or `Debug` -> `Start Debugging` / `Start Without Debugging` on the toolbar

    - or **Build project** executable
      - `Ctrl + B` / `Ctrl + Shift + B` by default
      - or `Build` -> `Build Solution` / `Build custom_stack` on the toolbar

    The executable will be available in the `build` directory in both cases.

## Usage

After running the project, you will be presented with the menu.

### Menu

The application has an interactive menu that allows you to use the stack.
It takes input (number) from the user and performs the corresponding action.
The menu is displayed after each action.

### Actions

The following actions are available (9 in total):

- **Push** (0) - adds an element to the stack
- **Pop** (1) - removes an element from the stack and prints it
- **Print stack** (2) - prints all elements in the stack
- **Print top element** (3) - prints the top element of the stack
- **Find** (4) -  searches for an element in the stack based on the search data provided by the user
- **Save to disk** (5) - saves the stack to a file
- **Read from disk** (6) - reads the stack from a file
- **Clear** (7) - clears the stack
- **Finish** (8) - exit the application

*There are plans to add an option to change the data type
used in the stack directly from the menu but this is not implemented yet.*

## Changing the data type used in the stack

### Before you start

- Additional Include Directories (`Project -> Properties -> Configuration Properties -> C/C++ -> General -> Additional Include Directories`) are used in the project. Precisely:
  - `$(SolutionDir)src` ([src](./src/) directory)
  - `$(SolutionDir)data` ([data](./data/) directory)
  - `$(SolutionDir)config` ([config](./config/) directory)
  - `$(SolutionDir)` ([root](./) directory)
- This project uses precompiled headers,
so for each `.c` file you need to include the `pch_source/stdafx.h` header.
Check the [src/pch_source/stdafx.h](./src/pch_source/stdafx.h) file to see which headers are included in the precompiled headers. You can also add your own headers there.
- In the steps below, replace `CUSTOM_DATA_TYPE` or `custom_data_type` in the names of the files, functions or variables with the name of the new data type.
- You can add as many data types as you like, but only one at a time can be used by the stack.
- If any step is unclear, check the `MY_STUDENT` data type implementation for reference.

### Steps

1. Add new data type to the `MY_DATA_TYPE` enum in the [config/general_config.h](./config/general_config.h) file (`Config -> General -> general_config.h` in the Visual Studio Solution Explorer):

    ```c
    enum MY_DATA_TYPE {
        // ...
        DATA_TYPE__CUSTOM_DATA_TYPE,
        // ...

        DATA_TYPE__TOTAL
    };
    ```

    Remember to add the new data type before the `DATA_TYPE__TOTAL` element.

1. Add the directory containing the logic for the new data type to the project in the [data](./data/) folder
(you can of course add it in the Visual Studio Solution Explorer, but it will be created in the [vcx](./vcx/) directory,
so to keep the project clean,
you should create the files manually in the [data](./data/) folder and then add them to the project in the `Data` filter).
It can contain anything but it must export the following functions
(names are not important, just match the return type and the arguments):

    ```c

    // function that handles printing the element data
    void CUSTOM_DATA_TYPE_Print(void *ptr);

    // function to free the memory allocated for the data
    void CUSTOM_DATA_TYPE_Free(void *ptr);

    // function that saves the element data to a file
    int CUSTOM_DATA_TYPE_Save(void **pdat, FILE *pf);

    // function to read element data from a file
    int CUSTOM_DATA_TYPE_Read(void **pdat, FILE *pf);

    // function that returns a pointer to the element
    // that should be pushed to the stack
    void *CUSTOM_DATA_TYPE_Push();

    // function that compares two elements
    // should return 1 if the elements are equal
    // and 0 otherwise
    int CUSTOM_DATA_TYPE_Compare(void *pCurData, void *pSearchData);

    // function that takes input from the user
    // and returns a pointer to the data to search for
    void *CUSTOM_DATA_TYPE_SearchData();

    // function that releases the memory allocated for the search data
    void CUSTOM_DATA_TYPE_SearchData_Free(void *searchDat);

    // function that returns the data type of the element
    // MY_DATA_TYPE is an enum defined in general_config.h
    // it is available in the whole project
    // thanks to the pre-compiled headers
    enum MY_DATA_TYPE CUSTOM_DATA_TYPE_GetType();
    ```

1. Create a new pair of files in the [config](./config/) folder (you can of course add them in the Visual Studio Solution Explorer, but they will be created in the [vcx](./vcx/) directory, so to keep the project clean, you should manually create the files in the [config](./config/) folder and then add them to the project in the `Config` filter):

    - `custom_data_type_config.c`
    - `custom_data_type_config.h`

1. If you need to use output messages, you can use the following function:

    ```c
    output(enum CUSTOM_MESSAGES message)
    ```

    To use it, add the enum (to the CUSTOM_MESSAGES enum in the [config/general_config.h](./config/general_config.h)) and string (to the custom_messages array in the [config/general_config.c](./config/general_config.c)) pairs for the new data type. Then you can use the function like this:

    ```c
    output(MESSAGE__CUSTOM_DATA_TYPE__SOME_MESSAGE);
    ```

    To keep the code clean, you can define the macros for the enum and the array in the `config/custom_data_type_config.h` file and then include them in the [config/general_config.h](./config/general_config.h) and [config/general_config.c](./config/general_config.c) files (see [config/student_config.h](./config/student_config.h) for a reference)

1. Include following headers in `custom_data_type_config.c`:

    ```c

    #include "pch_source/stdafx.h"
    #include "data_type_config.h"
    #include "data_type/data_type.h"
    ```

1. Add the following structure to `custom_data_type_config.c`:

    ```c
    struct MY_DATA_POINTERS CUSTOM_DATA_TYPE__POINTERS = {
        .type = DATA_TYPE__CUSTOM_DATA_TYPE,
        .fun_print = CUSTOM_DATA_TYPE_Print,
        .fun_free = CUSTOM_DATA_TYPE_Free,
        .fun_save = CUSTOM_DATA_TYPE_Save,
        .fun_read = CUSTOM_DATA_TYPE_Read,
        .fun_push = CUSTOM_DATA_TYPE_Push,
        .fun_comp = CUSTOM_DATA_TYPE_Compare,
        .fun_search_data = CUSTOM_DATA_TYPE_SearchData,
        .fun_free_search_data = CUSTOM_DATA_TYPE_SearchData_Free,
        .fun_get_type = CUSTOM_DATA_TYPE_GetType
    }

1. Finally, add the reference to the `CUSTOM_DATA_TYPE__POINTERS` structure to the `MY_DATA_POINTERS_ARRAY` array in the `custom_data_type_config.c`:

    ```c
    const struct MY_DATA_POINTERS *MY_DATA_POINTERS_ARRAY[DATA_TYPE__TOTAL] = {
        // ...
        &CUSTOM_DATA_TYPE__POINTERS,
        // ...
    }
    ```

    And set the `const enum MY_DATA_TYPE interface_type` variable to the new data type:

    ```c
    const enum MY_DATA_TYPE interface_type = DATA_TYPE__CUSTOM_DATA_TYPE;
    ```

## Why is this an application and not a library?

I'm aware that this project could be implemented as a library because it makes more sense, and I plan to do so in the future. However, I decided to implement it as an app for now because I'm not familiar with the library implementation in C and I wanted to focus on the stack implementation itself.

Feel free to make a pull request if you want to implement it as a library. I will be happy to merge it.

## Contributing

If you find issues or have suggestions for improvements,
feel free to open an issue or submit a pull request.
Contributions are welcome!

## Contact

If you have any questions, feel free to contact me at <jakub@korytko.me>.

## License

This project is released under the MIT License. See the [LICENSE](LICENSE) file for details.
