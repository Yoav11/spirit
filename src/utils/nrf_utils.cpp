#include <nrf_utils.h>

RF24 radio(NRF_CE, NRF_CSN);
RF24Network network(radio);

void network_connect() {
    SPI.begin();
    radio.begin();
    network.begin(90, NODE_ID);
}

uint16_t network_read() {
    uint16_t incomingData;
    network.update();
    RF24NetworkHeader header;
    network.read(header, &incomingData, sizeof(incomingData));
    return incomingData;
}

bool network_write(int data) {
    network.update();
    RF24NetworkHeader header(00);
    bool ok = network.write(header, &data, sizeof(data));
    return(ok);
}

bool network_avaiable() {
    network.update();
    return(network.available());
}
