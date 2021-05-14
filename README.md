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

## Links

[openSenseMap](https://opensensemap.org)
