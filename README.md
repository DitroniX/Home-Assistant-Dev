
## Home Assistant Development and Integration 

#### Welcome to the DitroniX Home Asssitant Integration

This repository is for integration of DitroniX boards into Home Assistant using the ESPHome Components.

The development and integration repository is work in progress as various projects evolve.  It will also expand on route.

[![DitroniX Wiki Pages](https://github.com/DitroniX/Home-Assistant-Dev/blob/main/Datasheets%20and%20Information/GitHub%20WiKi.png?raw=true)](https://github.com/DitroniX/Home-Assistant-Dev/wiki)


#### User contributions

User contributions to the HA integration is welcome and of course, acknowledgements would be included.

If you have a contribution, or example you wish to discuss, please feel free to contact me on support@ditronix.net 

[![DitroniX Discussions Pages](https://github.com/DitroniX/DitroniX/blob/main/Files/GitHub%20Discussions.png?raw=true)](https://github.com/DitroniX/Home-Assistant-Dev/discussions)


### How Does It Work?

Using Home Assistant, with integrated ESPHome, you are easily able to create a new 'Device', then flash the board so it will then appear in your Dashboard > Devices.

Home Assistant (ESPHome), devices use .yaml code, which is initially flashed to the board via USB cable.  

Once flashed (so the board is 'talking' to Home Assistant'), you can then subsequently easily reflash to the board using OTA, Over-The-Air, via Wi-Fi.  USB re-flashing remains an option if needed.

![Example of New Device](https://github.com/DitroniX/Home-Assistant-Dev/blob/main/Datasheets%20and%20Information/Example%20of%20Device%20in%20Dash%20and%20Online.png)

### Home Assistant (ESPHome) Devices

Home Assistant (ESPHome), uses '[Components](https://developers.home-assistant.io/docs/creating_component_code_review/)', which configures and tells Home Assistant about the device which you are trying to add.

Two 'flavours' of components are available (as far as I am aware):
 * Internal Components (embedded into HA)
 * External Components (This is a custom component, not currently embedded into HA)

### DitroniX Component Development

During DitroniX Home Assistant Code Development, the required device 'Component', is simply connected to the DitroniX git repository, as an external component.  


You could of course, always 'clone' this component and make your own.

The below is an example of the source pointing to the git repository.

	- source:  
	type: git  
	url: [https://github.com/DitroniX/Home-Assistant-Dev]
	(https://github.com/DitroniX/Home-Assistant-Dev)
### Example of yaml code pasted in ESPHome
![Example of yaml code pasted in ESPHome](https://github.com/DitroniX/Home-Assistant-Dev/blob/main/Datasheets%20and%20Information/Example%20of%20code%20pasted%20in%20the%20yaml%20editor.png)

### Example of added Device Info
![Example of added Device Info](https://github.com/DitroniX/Home-Assistant-Dev/blob/main/Datasheets%20and%20Information/Example%20of%20added%20Device%20Info.png)

## Home Assistant - ESPHome Components

 - [**ATM90E36**](https://github.com/DitroniX/Home-Assistant-Dev/tree/main/components/ATM90E36 "ATM90E36")
	 - This is the initial development component for use on boards which use the ATM90E36 device, such as the [EPEM ATM90E36](https://github.com/DitroniX/EPEM-Ethernet-Power-Energy-Monitor)  Ethernet Power Energy Monitor


## Example Guide

An example guide has been put together which should help get your boards up and running!

[Wiki Guide](https://github.com/DitroniX/Home-Assistant-Dev/wiki/Creating-Your-First-Device-in-Home-Assistant-%E2%80%90-ESPHome)

## Versions


 - 260613 - Added TCA6408 for Dev Testing
 - 260529 - Refresh Information
 - 251217 - Initial upload of the ATM90E36 Component for EPEM E36. Could also be adapted for IPEM E36


## **Further Information**

Additional information, and other technical details on this project, maybe found in the related repository pages.

**Repository Folders**

 - **Components** *(Code examples for Home Assistant - ESPHome)*
 -  **Datasheets and Information** *(Component Datasheets, Schematics, Board Layouts, Photos, Technical Documentation)*

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
