FROM hivemq/hivemq4:latest

RUN apt-get update
RUN apt install git python3 python3-pip -y

RUN pip3 install paho-mqtt

RUN git clone https://github.com/eclipse/paho.mqtt.python.git && \
    cd paho.mqtt.python && \
    python3 setup.py install

WORKDIR /dev

CMD [ "python3", "./client.py" ]
