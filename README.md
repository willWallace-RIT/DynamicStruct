Dynamic struct

implementation of a dynamic struct for tranferring raw data between CPU to GPU. Accessing is
probably not safe but the main file does access it to show that it works.

A shared char pointer is created for the raw data and a size should be specified.

the main cpp shows the class in action.

credit to vixorien for the ground work for an implemention in DXD11. This is just an abstraction for future use cases like Vulkan.
