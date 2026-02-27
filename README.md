# Wokwi
This repo is a clone of the folder Wokwi you find in the VM provided in the IoT lab course.

These folders contain examples from the first lecture on wokwi and esp32.

To compile and run the following projects, use the compile.sh script you find in Wokwi folder for VS Code support, or just open the Brave browser

For those of you brave enough, here are the installation instructions.

# Installation
- Install [VSCode](https://code.visualstudio.com/)

- Install the following extension for VS Code:
  - [Wokwi Extension](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode)
  - [Serial Monitor](https://marketplace.visualstudio.com/items?itemName=ms-vscode.vscode-serial-monitor)
  
Once installed the Wokwi extension please log in with your Wokwi account to authenticate.

- ## [Install PlatformIO](https://docs.platformio.org/en/latest/core/installation/index.html):

### Super-Quick (macOS / Linux)
To install or upgrade PlatformIO Core, paste that at a Terminal prompt:

Using curl

```
curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
python3 get-platformio.py
```
or using wget
```
wget -O get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
python3 get-platformio.py
```
### Local Download (macOS / Linux / Windows)
To install or upgrade PlatformIO Core, download (save as...) get-platformio.py script. Then run the following:

Change directory to the folder where is located downloaded "get-platformio.py"
```
cd /path-to-dir/where/get-platformio.py/is-located

# run it

python get-platformio.py
```
On Windows OS it may look like this:
```
# change directory to the folder where is located downloaded "get-platformio.py"

cd C:/path-to-dir/where/get-platformio.py/is-located

# run it
python.exe get-platformio.py
```

## Building

This is a [PlatformIO](https://platformio.org) project. To build it, [install PlatformIO](https://docs.platformio.org/en/latest/core/installation/index.html), and then run the following command in the desired project folder:

```
pio run
```



## Simulate the project

To simulate this project, install [Wokwi for VS Code](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode). Open the project directory in Visual Studio Code, press **F1** and select "Wokwi: Start Simulator".
