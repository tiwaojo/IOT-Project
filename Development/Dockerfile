FROM hivemq/hivemq4:latest

# Setup Python3
RUN apt-get update
RUN apt install git python3 python3-pip -y

# Setting up django
EXPOSE 8000
WORKDIR /app
COPY requirements.txt /app

RUN pip3 install djangorestframework markdown django-filter pyserial nanpy arduino-python3
RUN pip3 install -r requirements.txt --no-cache-dir
COPY . /app


RUN pip3 install paho-mqtt

RUN git clone https://github.com/eclipse/paho.mqtt.python.git && \
    cd paho.mqtt.python && \
    python3 setup.py install

WORKDIR /app

ENTRYPOINT ["python3"]
CMD ["manage.py", "runserver", "0.0.0.0:8000"]
# CMD [ "python3", "./client.py" ]
