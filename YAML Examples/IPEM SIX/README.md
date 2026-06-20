# IPEM SIX | ESP32C5 | DUAL ATM90E32 IoT Mains Power Energy Monitor

## **IPEM SIX - ESPHome Example Code**

This is a working ESPHome YAML development code for IPEM SIX, for Home Assistant.

[![IPEM SIX Preview](https://github.com/DitroniX/IPEM-SIX-ESP32C5-ATM90E32-IoT-Mains-Power-Energy-Monitor/blob/main/Datasheets%20and%20Information/IPEM%20SIX%20-%20Overview.png?raw=true)](https://github.com/DitroniX/IPEM-SIX-ESP32C5-ATM90E32-IoT-Mains-Power-Energy-Monitor)

## Summary

IPEM SIX C5 provides a complete energy monitoring platform:

✅ 6 CT channels  
✅ Dual ATM90E32 metering  
✅ Import/export detection  
✅ Per-channel energy tracking  
✅ Home Assistant native integration  
✅ WiFi diagnostics  
✅ Health monitoring  
✅ Configurable load alerts  
✅ OTA updates  
✅ ESP32-C5 performance platform

Designed as a professional-grade residential and small commercial energy monitoring solution.

## Snippet of the ESPHome Dash

![IPEM SIX ESPHome Preview](https://github.com/DitroniX/Home-Assistant-Dev/blob/main/YAML%20Examples/IPEM%20SIX/ipem-six-c5-single-phase-six-channel.png)

## Timeline

Now the code has been released and tested, other variants will also be provided.

* Split Phase
* Two Phase, over the Two Banks
* Three Phase

## **Code Overview**

**IPEM SIX C5** is a professional 6-channel dual-bank energy monitoring device based on the **ESP32-C5** platform and dual **ATM90E32** energy measurement ICs.

Demonstrate the power of the IPEM SIX by reading the all the data from the six current clamps and  input voltages, and provide a large range of information.

Provide:

-   Live sensor updates
-   Configuration control
-   Device status
-   Diagnostics

The device code presents:

-   6 independent CT current channels
-   Dual-bank monitoring architecture
-   Real-time power monitoring
-   Import/export power calculation
-   Energy accumulation (kWh)
-   Voltage and frequency measurement
-   Power factor and reactive power monitoring
-   Internal temperature monitoring
-   Wi-Fi diagnostics
-   Health/Status monitoring
-   Configurable load activity thresholds
-   LED heartbeat indication

Designed for integration with **Home Assistant via ESPHome API**.

## Documentation - IPEM SIX Firmware Overview

### **Basic Examples**

During development, I took baby steps in understanding how YAML worked and how to integrate the various elements of the IPEM SIX board.   These examples have been included for your information, in the Basic Examples folder.

### **Status**

The code should work as it is but you will ideally need to update the ESPHome API details, which I have xxxx out.

### Enable Home Assistant API
	api:
	  encryption:
	    key: "xxxx="

	ota:
	  - platform: esphome
	    password: "xxxx"

	wifi:
	  ssid: !secret wifi_ssid
	  password: !secret wifi_password

	  # Enable fallback hotspot (captive portal) in case wifi connection fails
	  ap:
	    ssid: "Wren-C5-Test Fallback Hotspot"
	    password: "xxxx"

## **Full Code Example View**

The initial release of this code is for single phase and six channels.  The code will be updated for split and three phase.

This is an example of the ESPHome Dash view


## **Open Source**
 
  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

## **Further Information**

Additional information, and other technical details on this project, maybe found in the related repository pages.

**Repository Folders**

 - **Code** *(Code examples for Arduino  IDE, Raspberry Pi and PlatformIO)*
 -  **Datasheets and Information** *(Component Datasheets, Schematics, Board Layouts, Photos, Technical Documentation)*
 - **Certification** *(Related Repository Project or Part, Certification Information)*

**Repository Tabs**

 - **Wiki** *(Related Repository Wiki pages and Technical User Information)*
 - **Discussions** *(Related Repository User Discussion Forum)*
 - **Issues** *(Related Repository Technical Issues and Fixes)*

***

We value our Customers, Users of our designs and STEM Communities, all over the World . Should you have any other questions, or feedback to share to others, please feel free to:

* Visit the related [Project](https://github.com/DitroniX?tab=repositories) *plus the related* **Discussions** and **Wiki** Pages.  See tab in each separate repository.
* **Project Community Information** can be found at https://www.hackster.io/DitroniX
* [DitroniX.net Website - Contact Us](https://ditronix.net/contact/)
* **Twitter**: [https://twitter.com/DitroniX](https://twitter.com/DitroniX)
* [Supporting the STEM Projects - BuyMeACoffee](https://www.buymeacoffee.com/DitroniX)
*  **LinkedIN**: [https://www.linkedin.com/in/g8puo/](https://www.linkedin.com/in/g8puo/)

***Dave Williams, Maidstone, UK.***

Electronics Engineer | Software Developer | R&D Support | RF Engineering | Product Certification and Testing | STEM Ambassador

## STEM

**Supporting [STEM Learning](https://www.stem.org.uk/)**

Life is one long exciting learning curve, help others by setting the seed to knowledge.

![DitroniX Supporting STEM](https://hackster.imgix.net/uploads/attachments/1606838/stem_ambassador_-_100_volunteer_badge_edxfxlrfbc1_bjdqharfoe1_xbqi2KUcri.png?auto=compress%2Cformat&w=540&fit=max)

