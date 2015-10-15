qmqtt-client
============

MQTT Client GUI Written with Qt

![QMQTT](https://f.cloud.github.com/assets/11869/320033/9264bc5c-990e-11e2-91d0-ddcb400bbf5f.png)

## Usage under Linux

### Compiling

Get library [QMQTT](https://github.com/emqtt/qmqtt) (e.g. to ~/path_to_qmqtt) and compile. Then:
```bash
# add Qt tools (qmake etc) to the path
export PATH=~/Qt/Tools/QtCreator/bin:~/Qt/5.4/gcc_64/bin:$PATH

# add path to library-directory to LD_LIBRARY_PATH
export LIBRARY_PATH=~/path_to_qmqtt:$LIBRARY_PATH

# build qmqtt-client
cd qmqtt-client
qmake
make
```

### Running

```bash
cd qmqtt-client
export LD_LIBRARY_PATH=~/path_to_qmqtt:$LD_LIBRARY_PATH

# start an mqtt broker such as emqttd (or mosquitto)

# run the qmqtt-client
./qmqtt-client
```
