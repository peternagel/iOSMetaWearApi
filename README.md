## MetaWear IOS API by MBIENTLAB

MetaWear is a complete development and production platform for wearable and connected device applications.  It features a powerful ARM processor and sensors, providing energy efficient Smartphone communication and central processing.  The MetaWear board comes pre-loaded with firmware so all sensors and on-board peripherals are controllable via this iOS API.

For more infomation and to order your MetaWear today see our website at https://mbientlab.com

You can join us on the [MbientLab Community Forums](http://community.mbientlab.com) to be part of the discussion.

### Getting Started

To get started you must have an Apple developer account. This is because the iOS simulator doesn’t support Bluetooth 4.0, so test apps must be run on a real iOS device* which requires a developer account.  
*Bluetooth 4.0 avaliable on iPhone 4S+, iPad 3rd generation+, or iPod Touch 5th generation.

Check out http://developer.apple.com to get started. 

Note that there are fees associated with an Apple developer account.

### Installation

If you are familiar with [CocoaPods](http://cocoapods.org/), you can use the pod named `'Metawear-iOSAPI'`.

Otherwise, download or fork this project.  The API is available as a Framework for iOS called the MetaWear.framework. You will see a few header files along with a framework file included in your download.  To install, simply drag the MetaWear.framework folder into your Xcode project.

[[Insert Picture]]

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

### Data Processing Module

The data processing module is separated into several "filters" which can be used standalone or chained together to create more complex filters.

The current filters available are:
- Summation of Events
- Periodic Sample of Events
- Peak Detector (coming soon)
- Low Pass Filter (coming soon)
- Threshold Detector (coming soon)

The generic nature of these filters allow you to give any data stream as input and receive the processed data as output, either directly or through a log entry.

The following quick example shows how to setup this data processing chain to report the summed RMS value of accelerometer data every minute. This is currently used in the MetaTracker App (https://github.com/mbientlab/MetaTracker) to estimate overall activity in a given time interval.

The following diagram describes the overall data gathering, processing, and storing that we want to achieve.

![alt tag](https://github.com/mbientlab/Metawear-iOSAPI/blob/master/DataProcessing.jpeg)

```obj-c
 MBLEvent *event = [self.device retrieveEventWithIdentifier:@"com.mbientlab.ActivityTrackerEvent"];
 if (!event) {
   // Program to sum accelerometer RMS and log sample every 1 second
   event = [[self.device.accelerometer.rmsDataReadyEvent summationOfEvent] periodicSampleOfEvent:60000 identifier:@"com.mbientlab.ActivityTrackerEvent"];
 }
 if (!event.isLogging) {
    self.device.accelerometer.fullScaleRange = MBLAccelerometerRange8G;
   self.device.accelerometer.filterCutoffFreq = 0;
   self.device.accelerometer.highPassFilter = YES;
   [event startLogging];
 }
```
