# senseBox

With the senseBox application, you can read environmental data (temperature, humidity, and pressure) from a Bosch BME280 sensor and transmit this data to the openSenseMap project. The app is meant to run on a Raspberry Pi where the BME280 is connected to the Pis I2C interface.

## Compile / Install

```shell
git clone https://github.com/fruchtkeks/senseBox.git --branch main
cd senseBox
git submodule init && git submodule update
cmake .
make
```

## Configuration

After compiling the project you need to copy the box.config.example to box.config and fill in the parameters within the configuration file.
You can find the box_id in the dashboard of the openSenseMap project. The sensor ids you can find when going to the detail section of your box in the Sensors submenu.
The client only works with enabled authentication which you can activate in the Security submenu of your box (Access Token).

## Links

[openSenseMap](https://opensensemap.org)
