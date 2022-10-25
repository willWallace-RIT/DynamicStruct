Dynamic struct
implementation of a dynamic struct for tranferring raw data between CPU to GPU. Accessing is
probably not safe but the the main file does access it to show that it works.

A shared char pointer is created for the raw data and a size should be specified.

