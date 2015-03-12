# MetaWear IOS API by MBIENTLAB

![alt tag](https://github.com/mbientlab/Metawear-iOSAPI/blob/master/Images/Metawear.png)

### Overview

[MetaWear](https://mbientlab.com) is a complete development and production platform for wearable and connected device applications.

MetaWear features a number of sensors and peripherals all easily controllable over Bluetooth 4.0 Low Energy using this iOS API, no firmware or hardware experience needed!

It comes pre-loaded with a wirelessly upgradeable firmware, so you can always take advantage of the latest features.

### Requirements
- [MetaWear board](http://mbientlab.com/store/)
- [Apple developer account](https://developer.apple.com/programs/ios/), note there are fees associated.
- Device running iOS 7.1 or later with Bluetooth 4.0

> REQUIREMENT NOTES  
The iOS simulator doesn’t support Bluetooth 4.0, so test apps must be run on a real iOS device which requires a developer account.  Bluetooth 4.0 avaliable on iPhone 4S+, iPad 3rd generation+, or iPod Touch 5th generation.

### License
See the [License](https://github.com/mbientlab/Metawear-iOSAPI/blob/master/LICENSE)

### Support
Reach out to the [community](http://community.mbientlab.com) if you encounter any problems, or just want to chat :)

## Getting Started

### Installation

If you are familiar with [CocoaPods](http://cocoapods.org/), you can use the pod named `'Metawear-iOSAPI'`.

Otherwise, download this project.  The API is available as a Framework for iOS called the MetaWear.framework. You will see a few header files along with a framework file included in your download.  To install, simply drag the MetaWear.framework folder into your Xcode project.  For step by instructions see the [video guide](https://youtu.be/B9DQQATNoGk).


![alt tag](https://github.com/mbientlab/Metawear-iOSAPI/blob/master/Images/FrameworkSetup.png)

### Simple API Test

Here is a walkthrough to showcase a very basic connect and toggle LED operation.

First, import the framework header files like this:
```obj-c
#import <MetaWear/MetaWear.h>
```

Then add the following code wherever appropriate to make the LED flash green:
```obj-c
// Begin scanning for MetaWear boards
[[MBLMetaWearManager sharedManager] startScanForMetaWearsWithHandler:^(NSArray *array) {
    // Hooray! We found a MetaWear board, so stop scanning for more
    [[MBLMetaWearManager sharedManager] stopScanForMetaWears];
    // Connect to the board we found
    MBLMetaWear *device = [array firstObject];
    [device connectWithHandler:^(NSError *error) {
        if (!error) {
            // Hooray! We connected to a MetaWear board, so flash its LED!
            [device.led flashLEDColor:[UIColor greenColor] withIntensity:0.5];
        }
    }];
}];
```
Now run the app on a physical device. 

*BLUETOOTH IS NOT SUPPORTED IN THE SIMULATOR* and you will receive a build ERROR when you attempt to compile a MetaWear project in the simulator.

### Sample iOS App

A sample iOS App using the MetaWear iOS API can be found at https://github.com/mbientlab/Metawear-SampleiOSApp.

The sample iOS App demonstrates the base functionality of the various MetaWear modules and serves as a good starting point for developers.

### API Documentation

See the [iOS Guide](http://docs.mbientlab.com/?page_id=15)
