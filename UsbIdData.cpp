/**
    Peripherals/UsbIdData
    SfmlCtrlData.h
    Purpose: Definition file for the UsbIdData class, which can be used to identify all usb devices
    currently plugged into a computer.  It can also be used to find the vendor name for those
    devices using the hexidecimal vendor ID in the usb.ids file.
    @author Jeremiah Kellogg
    @version 1.0.0 2020-06-14
*/
#include "UsbIdData.h"

UsbIdData::UsbIdData() { }
UsbIdData::~UsbIdData() { }

//Searches for and returns the file path for the usb.ids file.
std::string UsbIdData::getUsbIdFilePath()
{
	strcpy(findUsbFile, "find / -xdev -type f -name 'usb.ids' 2>/dev/null > usbIdPath"); //send all errors to /dev/null
	system(findUsbFile);
	usbIdFile.open("usbIdPath");
	if(usbIdFile.is_open())
	{
		getline(usbIdFile, path);
	}
	else
	{
		path = "An error occured while trying to find the usb.ids file";
	}

	return path;
}

//Pulls the name of the vendor for a usb device in the usb.ids file.
std::string UsbIdData::getVendorName(std::string id)
{
	pathToUsbId = getUsbIdFilePath();
	usbIdFile.open(pathToUsbId, std::ios::in);
	if(usbIdFile.is_open())
	{

		while(getline(usbIdFile, fileLine))
		{
      char tabCheck = fileLine[0];

      if(fileLine.find(id) != std::string::npos && tabCheck != 9) //9 is the ASCII Hex value for a tab, which would indicate that the line is not a Vendor ID, but a product ID
			{
				vendorName = fileLine;
				vendorName.erase(0, 6);
				usbIdFile.close();
				break;
			}
      else
      {
        vendorName = "There is no vendor with ID of " + id;
      }
		}
	}
	else
	{
		vendorName = "There was a problem opening the usb.id file on this system following the " + pathToUsbId + " path";
	}

	return vendorName;
}

//Creates a file called usbList and writes a list of currently connect usb divices to that file
void UsbIdData::setUsbConnectedList()
{
  std::string fullUsbList = "";

  strcpy(createUsbList, "lsusb > usbList");
  system(createUsbList);
  ConnectedUsbFile.open("usbList", std::ios::in);

  if(ConnectedUsbFile.is_open())
  {
     std::string line;
     fullUsbList = "";

     while(getline(ConnectedUsbFile, line))
    {
      int lineSize = line.size();
      int position = lineSize - 8;
      std::string lastChars = line.substr(position, 8);
    }
    std::cout << "List of currently plugged in USB devices was succesfully created" << std::endl;
  }
  else
  {
    std::cout << "There was a problem creating the list of currently plugged in usb devices."  << std::endl;
  }

  ConnectedUsbFile.close();
}

//Displays the contents of the usbList file created by the setUsbConnectedList method
void UsbIdData::getUsbConnected()
{
  std::string outputLine;
  setUsbConnectedList();

  ConnectedUsbFile.open("usbList");

  if(ConnectedUsbFile.is_open())
  {
    while(getline(ConnectedUsbFile, outputLine))
    {
      int lineSize = outputLine.size();
      int position = lineSize - 8;
      std::string lastChars = outputLine.substr(position, 8);

      if(lastChars != "root hub")
      {
        std::cout << outputLine << std::endl;
      }
    }
  }
  else
  {
    std::cout << "There was a problem" << std::endl;
  }
  ConnectedUsbFile.close();
}
