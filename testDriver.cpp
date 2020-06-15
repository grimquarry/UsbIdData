/**
    Peripherals/UsbIdData
    testDriver.cpp
    Purpose: A driver program for testing UsbIdData objects
    @author Jeremiah Kellogg
    @version 1.0.0 2020-06-14
*/
#include <iostream>
#include <string>
#include "UsbIdData.h"

int main()
{
  UsbIdData usbIdData;

  std::string vendorHexId = "0079"; //make this "0071 to test if product IDs are being searched for, too (they shouldn't be)"
  std::string usbIdPath = usbIdData.getUsbIdFilePath();
  std::string vendorName = usbIdData.getVendorName(vendorHexId);

  std::cout << "File path for usb.id is: " << usbIdPath << std::endl;
  std::cout << "Vendor name with hex ID of " << vendorHexId << " is: " << vendorName << std::endl;

  usbIdData.getUsbConnected();
  //usbIdData.setUsbConnectedList();  //Commented out because it's used in the getUsbConnected method
  return 0;
}
