# STM32 USBX DUAL CDC Example 

This code was created during the development of the "How to create a Dual CDC application using the Azure® USBX with STM32" article. This material presents a step-by-step tutorial with the instructions on how to create the project from scratch. Following the article you will be able to reproduce the implementation to your specific hardware. The article is available in the following link:

https://community.st.com/t5/stm32-mcus/how-to-create-a-dual-cdc-application-using-the-azure-usbx-with/ta-p/747380

In this repository : 
* The application is designed to present a simple application using the USBX to create two instances of the CDC ACM in a single USB interface.
* The application runs over the NUCLEO-H563ZI and can be tailored/used as example to other STM32 Families. 
* The repositor contains an STM32CubeIDE projects for the STM32H563ZI microcontroller.
* The project was built over the Azure(R) ThreadX RTOS, but it's also possible to modify the application to be executed in Stand-alone mode (without RTOS).

### <b>Application</b>

  This RTOS based application initializes by configuring all the necessary stacks, memory pools and peripherals to initialize the Azure(R) ThreadX, the Azure(R) USBX stack and to instantiate two CDC ACM interfaces. Then, three Threads (tasks) are created, to initialize the USB peripheral, and to write data through the two CDC interfaces.

### <b>Keywords</b>

USBX, USB Device, Composite, CDC, Dual, Interface, CDC ACM, STM32, STM32H5, STM32CubeIDE, Virtual COM Port

### <b>Directory contents</b>

   Here are the list of the most relevant files for the application. The other files are Read Only or were not modified to build the application.

  - Core/Src/main.c                                            -> Commom peripheral initialization functions, Azure ThreadX Stack initialization and execution
  - USBX/App/app_usbx_device.c                                 -> Initialization of the USBX stack, register of CDC ACM, Thread creations and USB peripheral initialization 
  - USBX/App/ux_device_cdc_acm.c                               -> USBD CDC ACM application functions and Threads
  - USBX/App/ux_device_cdc_acm.h                               -> Threads and functions prototypes used by the CDC ACM application
  - USBX/App/ux_device_descriptors.c                           -> Added code to include and register the second instance of the CDC into the application and descriptors
  - USBX/App/ux_device_descriptors.h                           -> Defines created to be used in the application


### <b>Hardware and Software environment</b>

  - This example has been tested with NUCLEO-H563ZI on Windows 10 and can be
    tailored to any other supported device and development board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open and import the project into STM32CubeIDE
 - Rebuild all files and load your image into target memory
 - Run the example
 - Connect the USB User cable to your board
 - Open the Device Manager to ensure that two Virtual COM ports were opened
 - Open a terminal for each Virtual COM port


### <b>Expected results:</b>

Two Virtual COM Ports at Device Manager:
 ![RM_IMAGE_0] (Images/device_manager.jpg)

Messages being transmitted through the terminal:
 ![RM_IMAGE_1] (Images/terminal.jpg)
 