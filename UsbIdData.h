/**
    Peripherals/UsbIdData
    SfmlCtrlData.h
    Purpose: Header file for the UsbIdData class, which can be used to identify all usb devices
    currently plugged into a computer.  It can also be used to find the vendor name for those
    devices using the hexidecimal vendor ID in the usb.ids file.
    @author Jeremiah Kellogg
    @version 1.0.0 2020-06-14
*/
#pragma once
#include <string> //Dynamically linked from Standard Library
#include <fstream> //Dynamically linked from Standard Library
#include <stdio.h>  //Dynamically linked from Standard Library.  Needed for using system() method
#include <string.h> //Dynamically linked from Standard Library. Needed for strcpy command
#include <iostream> //Dynamically linked from Standard Library

class UsbIdData
{
public:
  UsbIdData();
  ~UsbIdData();

  /**
    Searches for and returns the file path for the usb.ids file.
  */
  std::string getUsbIdFilePath();

  /**
    Pulls the name of the vendor for a usb device in the usb.ids file.
    @param id The hexidecimal vendor id to search for in the usb.ids file.
  */
  std::string getVendorName(std::string id);

  /**
    Creates a file called usbList and writes a list of currently connect usb divices to that file
  */
  void setUsbConnectedList();

  /**
    Displays the contents of the usbList file created by the setUsbConnectedList method
  */
  void getUsbConnected();

private:
	std::string path; //The path to the usb.ids file returned by the getUsbIdFilePath method
  char findUsbFile[61]; //An array to store the shell command for finding the usb.ids file (used in a system() method)
	std::string pathToUsbId; //Path to the usb.ids file used by the getVendorName method
	std::string vendorName; //Variable to store a vendor name
	std::fstream usbIdFile; //For opening the usb.ids file
  std::string fileLine; //used for getline fstream function in getVendorName method;
  char createUsbList[16]; //An array to store the shell command for lsusb > usbList (used in a system() method)
  std::fstream ConnectedUsbFile; //Object for reading usbList file
};
