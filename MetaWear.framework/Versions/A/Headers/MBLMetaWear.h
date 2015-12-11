/**
 * MBLMetaWear.h
 * MetaWear
 *
 * Created by Stephen Schiffli on 7/29/14.
 * Copyright 2014-2015 MbientLab Inc. All rights reserved.
 *
 * IMPORTANT: Your use of this Software is limited to those specific rights
 * granted under the terms of a software license agreement between the user who
 * downloaded the software, his/her employer (which must be your employer) and
 * MbientLab Inc, (the "License").  You may not use this Software unless you
 * agree to abide by the terms of the License which can be found at
 * www.mbientlab.com/terms.  The License limits your use, and you acknowledge,
 * that the Software may be modified, copied, and distributed when used in
 * conjunction with an MbientLab Inc, product.  Other than for the foregoing
 * purpose, you may not use, reproduce, copy, prepare derivative works of,
 * modify, distribute, perform, display or sell this Software and/or its
 * documentation for any purpose.
 *
 * YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
 * PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
 * NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
 * MBIENTLAB OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE,
 * STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE
 * THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED
 * TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST
 * PROFITS OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY,
 * SERVICES, OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY
 * DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *
 * Should you have any questions regarding your right to use this Software,
 * contact MbientLab via email: hello@mbientlab.com
 */

#import <CoreBluetooth/CoreBluetooth.h>
#import <MetaWear/MBLConstants.h>

@class MBLTemperature;
@class MBLAccelerometer;
@class MBLGyro;
@class MBLLED;
@class MBLMechanicalSwitch;
@class MBLGPIO;
@class MBLHapticBuzzer;
@class MBLiBeacon;
@class MBLNeopixel;
@class MBLEvent;
@class MBLANCS;
@class MBLI2C;
@class MBLTimer;
@class MBLGSR;
@class MBLBarometer;
@class MBLAmbientLight;
@class MBLSettings;


/**
 Current state of the MetaWear connection
 */
typedef NS_ENUM(NSInteger, MBLConnectionState) {
    MBLConnectionStateDisconnected = 0,
    MBLConnectionStateConnecting,
    MBLConnectionStateConnected,
    MBLConnectionStateDisconnecting,
    MBLConnectionStateDiscovery,
};

@class MBLMetaWear;


/**
 An MBLRestorable object is used to persist state across resets and disconnects.
 You create an object that conforms to this protocol and then assign it to an
 MBLMetaWear object using the setConfiguration:handler: method
 */
@protocol MBLRestorable <NSObject>
/**
 This function is called shortly after you assign this object to a MetaWear device.
 Override this function and use it as the main initialization point for setting up
 custom events needed for your application.
 
 Any API calls in this method will be persisted in non-volatile memory on the
 MetaWear, and be executed when the MetaWear powers on.  For example, if you want
 the device to automatically (after reset or power-loss) startLogging some 
 event, set the peripheral name, or modifiy a connection parameter, do that in this function.
 */
- (void)runOnDeviceBoot:(nonnull MBLMetaWear *)device;
@end



/**
 Each MBLMetaWear object corresponds a physical MetaWear board.  It contains all the logical
 methods you would expect for interacting with the device, such as, connecting, disconnecting,
 reading and writing state.
 
 Sensors and peripherals on the MetaWear are encapsulated within their own objects accessable 
 here via properties.  For example, all accelerometer functionality is contained in the 
 MBLAccelerometer class and is accessed using the accelerometer property
 */
@interface MBLMetaWear : NSObject <CBPeripheralDelegate>

///----------------------------------
/// @name Sensor and Peripheral Accessors
///----------------------------------

/**
 MBLMechanicalSwitch object contains all methods for interacting with the on-board button
 */
@property (nonatomic, readonly, nullable) MBLMechanicalSwitch *mechanicalSwitch;
/**
 MBLLED object contains all methods for interacting with the on-board LED
 */
@property (nonatomic, readonly, nullable) MBLLED *led;
/**
 MBLTemperature object contains all methods for interacting with the on-chip and external thermistor temperature sensors
 */
@property (nonatomic, readonly, nullable) MBLTemperature *temperature;
/**
 MBLAccelerometer object contains all methods for interacting with the on-board accelerometer sensor
 */
@property (nonatomic, readonly, nullable) MBLAccelerometer *accelerometer;
/**
 MBLGyro object contains all methods for interacting with the on-board gyroscope sensor
 */
@property (nonatomic, readonly, nullable) MBLGyro *gyro;
/**
 MBLGPIO object contains all methods for interacting with the on-board pins
 */
@property (nonatomic, readonly, nullable) MBLGPIO *gpio;
/**
 MBLHapticBuzzer object contains all methods for interacting with the external haptic or buzzer
 */
@property (nonatomic, readonly, nullable) MBLHapticBuzzer *hapticBuzzer;
/**
 MBLiBeacon object contains all methods for programming the device to advertise as an iBeacon
 */
@property (nonatomic, readonly, nullable) MBLiBeacon *iBeacon;
/**
 MBLNeopixel object contains all methods for interacting with an external NeoPixel chain
 */
@property (nonatomic, readonly, nullable) MBLNeopixel *neopixel;
/**
 MBLANCS object contains all methods for interacting with ANCS notifications
 */
@property (nonatomic, readonly, nullable) MBLANCS *ancs;
/**
 MBLTimer object contains all methods for programming timer based operations
 */
@property (nonatomic, readonly, nullable) MBLTimer *timer;
/**
 MBLTimer object contains all methods for performing raw I2C read/writes
 */
@property (nonatomic, readonly, nullable) MBLI2C *i2c;
/**
 MBLGSR object contains all methods for perfoming GSR reads
 */
@property (nonatomic, readonly, nullable) MBLGSR *gsr;
/**
 MBLBarometer object contains all methods for interacting with the barometer sensor
 */
@property (nonatomic, readonly, nullable) MBLBarometer *barometer;
/**
 MBLAmbientLight object contains all methods for interacting with the ambient light sensor
 */
@property (nonatomic, readonly, nullable) MBLAmbientLight *ambientLight;
/**
 MBLSettings object contains all methods for interacting with MetaWear device settings
 */
@property (nonatomic, readonly, nullable) MBLSettings *settings;
/**
 MBLDeviceInfo object contains version information about the device
 */
@property (nonatomic, readonly, nullable) MBLDeviceInfo *deviceInfo;


///----------------------------------
/// @name Persistent Configuration Settings
///----------------------------------

/**
 MBLRestorable object containing custom settings and events that are programmed
 to the MetaWear and preserved between disconnects and app termination.
 */
@property (nonatomic, readonly, nullable) id<MBLRestorable> configuration;

/**
 Assign a new configuration object to this MetaWear.  This only needs to be called once,
 likely after you confirm the device from a scanning screen or such.  Upon calling it will
 erase all non-volatile memory the device (which requires disconnect), then perform reset, 
 once its comes back online we will connect and invoke the setupEvents method.
 Then the runOnDeviceBoot method is invoked and all calls in that method are persisted 
 device side so after any future reset these settings will be applied automatically.
 @param configuration Pointer to object containing programming commands.  Writing nil
 will reset to factory settings.
 @param handler Callback once programming is complete
 */
- (void)setConfiguration:(nullable id<MBLRestorable>)configuration handler:(nullable MBLErrorHandler)handler;

///----------------------------------
/// @name State Accessors
///----------------------------------

/**
 Current connection state of this MetaWear
 */
@property (nonatomic, readonly) MBLConnectionState state;
/**
 If YES, then WARNING, this is not the owning application and you can cause 
 data loss for the other application that is using the device.
 */
@property (nonatomic, readonly) BOOL isGuestConnection;
/**
 iOS generated unique identifier for this MetaWear.  This is device specific and
 two different iOS devices with generate two different identifiers.
 */
@property (nonatomic, readonly, nonnull) NSUUID *identifier;
/**
 Stored value of signal strength at discovery time
 */
@property (nonatomic, nullable) NSNumber *discoveryTimeRSSI;
/**
 Advertised device name.  You can simply assign a new string
 if you wish to change the advertised name, max 8 characters!
 */
@property (nonatomic, nonnull) NSString *name;

///----------------------------------
/// @name Connect/Disconnect
///----------------------------------

/**
 Connect/reconnect to the MetaWear board. Once connection is complete, the provided block
 will be invoked.  If the NSError provided to the block is null then the connection
 succeeded, otherwise failure (see provided error for details)
 @param handler Callback once connection is complete
 */
- (void)connectWithHandler:(nullable MBLErrorHandler)handler;
/**
 Connect/reconnect to the MetaWear board, but with a timeout if the board can't be 
 located.  Once connection is complete, the provided block will be invoked.  If the 
 NSError provided to the block is null then the connection succeeded, otherwise 
 failure (see provided error for details)
 @param timeout Max time to search for MetaWear before giving up
 @param handler Callback once connection is complete
 */
- (void)connectWithTimeout:(NSTimeInterval)timeout handler:(nullable MBLErrorHandler)handler;

/**
 Disconnect from the MetaWear board.
 @param handler Callback once disconnection is complete
 */
- (void)disconnectWithHandler:(nullable MBLErrorHandler)handler;

///----------------------------------
/// @name Remember/Forget
///----------------------------------

/**
 Remember this MetaWear, it will be saved to disk and retrievable
 through [MBLMetaWearManager retrieveSavedMetaWears]
 */
- (void)rememberDevice;
/**
 Forget this MetaWear, it will no longer be retrievable
 through [MBLMetaWearManager retrieveSavedMetaWears]
 */
- (void)forgetDevice;

/**
 The state of all MetaWear modules are persisted to disk for ease of use
 across application launches.  Most of the time you don't need to explicitly
 call this function as it is called automatically after interactions with the 
 board.  Function that count as interacation include start/stopLogging,
 start/stopNotifications, program/eraseCommands.  If you make changes and don't
 call one of these functions, then it may be usefully to call this function so
 you don't lose the state of any settings.
 */
- (void)synchronize;

///----------------------------------
/// @name State Reading
///----------------------------------

/**
 Query the current RSSI
 @param handler Callback once RSSI reading is complete
 */
- (void)readRSSIWithHandler:(nonnull MBLNumberHandler)handler;
/**
 Query the percent remaining battery life, returns int between 0-100
 @param handler Callback once battery life reading is complete
 */
- (void)readBatteryLifeWithHandler:(nonnull MBLNumberHandler)handler;

///----------------------------------
/// @name Firmware Update and Reset
///----------------------------------

/**
 Perform a software reset of the device.  Note that all module properties of
 this object will be invalidated, so remove any external references to them.
 @warning This will cause the device to disconnect
 */
- (void)resetDevice;

/**
 See if this device is running the most up to date firmware
 @param handler Callback once current firmware version is checked against the latest
 */
- (void)checkForFirmwareUpdateWithHandler:(nonnull MBLBoolHandler)handler;

/**
 Updates the device to the latest firmware, or re-installs the latest firmware.
 
 Please make sure the device is charged at 50% or above to prevent errors.
 Executes the progressHandler periodically with the firmware image uploading
 progress (0.0 - 1.0), once it's called with 1.0, you can still expect another 5
 seconds while we wait for the device to install the firmware and reboot.  After
 the reboot, handler will be called and passed an NSError object if the update
 failed or nil if the update was successful.
 @param handler Callback once update is complete
 @param progressHandler Periodically called while firmware upload is in progress
 */
- (void)updateFirmwareWithHandler:(nonnull MBLErrorHandler)handler
                  progressHandler:(nullable MBLFloatHandler)progressHandler;


///----------------------------------
/// @name Utility Methods
///----------------------------------

/**
 Get a callback after all commands have been sent to the MetaWear
 board and expected responses recieved.
 @param handler Callback once all commands are complete
 */
- (void)waitForCommandCompletion:(nonnull MBLVoidHandler)handler;

///----------------------------------
/// @name Deprecated Methods
///----------------------------------

/**
 * @deprecated Use settings.advertisingInterval instead
 */
@property (nonatomic) uint16_t advertisingInterval DEPRECATED_MSG_ATTRIBUTE("Use settings.advertisingInterval instead");
/**
 * @deprecated Use settings.transmitPower instead
 */
@property (nonatomic) uint8_t transmitPower DEPRECATED_MSG_ATTRIBUTE("Use settings.transmitPower instead");
/**
 * @deprecated Use settings.scanResponse instead
 */
@property (nonatomic, nullable) NSData *scanResponse DEPRECATED_MSG_ATTRIBUTE("Use settings.scanResponse instead");
/**
 * @deprecated Use [settings initiatePairing] instead
 */
- (void)initiatePairing DEPRECATED_MSG_ATTRIBUTE("Use [settings initiatePairing] instead");
/**
 * @deprecated Use [settings deleteAllBonds] instead
 */
- (void)deleteAllBonds DEPRECATED_MSG_ATTRIBUTE("Use [settings deleteAllBonds] instead");

/**
 * @deprecated use setConfiguration:handler: instead
 */
- (nullable MBLEvent *)retrieveEventWithIdentifier:(nonnull NSString *)identifier DEPRECATED_MSG_ATTRIBUTE("Use setConfiguration:handler: instead");

/**
 * @deprecated use deviceInfo property instead
 */
- (void)readDeviceInfoWithHandler:(nonnull MBLDeviceInfoHandler)handler DEPRECATED_MSG_ATTRIBUTE("Use deviceInfo property instead");

/**
 * @deprecated Use connectWithHandler: instead
 */
- (void)connecWithHandler:(nullable MBLErrorHandler)handler DEPRECATED_MSG_ATTRIBUTE("Use connectWithHandler: instead");

@end
