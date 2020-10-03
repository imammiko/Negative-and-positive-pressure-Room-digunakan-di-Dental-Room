void nrfConfig(){
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  //radio.setDataRate(RF24_2MBPS);
}
